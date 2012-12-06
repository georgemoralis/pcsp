#include "stdafx.h"
#include "gl_ShaderPreprocessor.h"

#include <QByteArray>
#include <QStack>

gl_ShaderPreprocessor::gl_ShaderPreprocessor()
{

}

gl_ShaderPreprocessor::~gl_ShaderPreprocessor()
{

}

bool gl_ShaderPreprocessor::Preprocess(const QString &source)
{
    QStack< bool > appendable;

    appendable.push(true);

    foreach (QString block, source.split("#", QString::SkipEmptyParts))
    {
        if      (block.startsWith("if") && block.size() > 2 && block[2].isSpace())
        {
            if (!appendable.top() || !ConditionalExpression(block, 2))
            {
                appendable.push(false);
            }
            else
            {
                appendable.push(true);
                m_preprocessed_source.append(block);
            }
        }
        else if (block.startsWith("elif") && block.size() > 4 && block[4].isSpace())
        {
            if (appendable.size() > 1)
            {
                if (appendable.top() || !ConditionalExpression(block, 4))
                {
                    appendable.pop();
                    appendable.push(false);
                }
                else
                {
                    appendable.pop();
                    appendable.push(true);
                    m_preprocessed_source.append(block);
                }
            }
            else
            {
                qCritical("gl_ShaderPreprocessor::Preprocess: unexpected #elif");

                return false;
            }
        }
        else if (block.startsWith("else") && (block.size() == 4 || block[4].isSpace()))
        {
            if (appendable.size() > 1)
            {
                bool state = appendable.top();
                appendable.pop();
                if (state || !appendable.top())
                {
                    appendable.push(false);
                }
                else
                {
                    appendable.push(true);
                    block.remove(0, 4);
                    m_preprocessed_source.append(block);
                }
            }
            else
            {
                qCritical("gl_ShaderPreprocessor::Preprocess: unexpected #else");

                return false;
            }
        }
        else if (block.startsWith("endif") && (block.size() == 5 || block[5].isSpace()))
        {
            appendable.pop();

            if (appendable.size())
            {
                if (appendable.top())
                {
                    block.remove(0, 5);
                    m_preprocessed_source.append(block);
                }
            }
            else
            {
                qCritical("gl_ShaderPreprocessor::Preprocess: mismatched #endif");

                return false;
            }
        }
        else if (appendable.top())
        {
            m_preprocessed_source.append(block);
        }
    }

    return m_preprocessed_source.size() != 0;
}

static bool Expression(QStringList const &words, int &pos, int &result);

/// PrimaryExpression -> NUMBER | '(' Expression ')'
static bool PrimaryExpression(QStringList const &words, int &pos, int &result)
{
    int back = pos;

    if (pos < words.size())
    {
        if (words.at(pos) == "(")
        {
            ++pos;

            if (Expression(words, pos, result))
            {
                if (pos < words.size() && words.at(pos) == ")")
                {
                    ++pos;

                    return true;
                }
            }
        }
        else
        {
            bool ok = false;
            result = words.at(pos).toInt(&ok, 0);
            if (ok)
            {
                ++pos;

                return true;
            }
        }
    }

    pos = back;

    return false;
}

/// UnaryExpression -> PrimaryExpression | [('+' | '-' | '!' | '~')] UnaryExpression
static bool UnaryExpression(QStringList const &words, int &pos, int &result)
{
    int value;
    int back = pos;

    if (pos < words.size())
    {
        if      (words.at(pos) == "+")
        {
            ++pos;
            if (UnaryExpression(words, pos, result))
            {
                return true;
            }
        }
        else if (words.at(pos) == "-")
        {
            ++pos;
            if (UnaryExpression(words, pos, value))
            {
                result = -value;
                return true;
            }
        }
        else if (words.at(pos) == "!")
        {
            ++pos;
            if (UnaryExpression(words, pos, value))
            {
                result = int(!value);
                return true;
            }
        }
        else if (words.at(pos) == "~")
        {
            ++pos;
            if (UnaryExpression(words, pos, value))
            {
                result = ~value;
                return true;
            }
        }
        else if (PrimaryExpression(words, pos, result))
        {
            return true;
        }
    }

    pos = back;

    return false;
}

/// MultiplicativeExpression -> [MultiplicativeExpression ('*' | '/' | '%')] UnaryExpression
static bool MultiplicativeExpression(QStringList const &words, int &pos, int &result)
{
    bool ok = false;
    int value;
    int back = pos;

    if (pos < words.size())
    {
        if (UnaryExpression(words, pos, result))
        {
loop:
            ok = true;
            if (pos < words.size())
            {
                if      (words.at(pos) == "*")
                {
                    ++pos;
                    if (UnaryExpression(words, pos, value))
                    {
                        result = result * value;
                        goto loop;
                    }
                    ok = false;
                }
                else if (words.at(pos) == "/")
                {
                    ++pos;
                    if (UnaryExpression(words, pos, value))
                    {
                        result = result / value;
                        goto loop;
                    }
                    ok = false;
                }
                else if (words.at(pos) == "%")
                {
                    ++pos;
                    if (UnaryExpression(words, pos, value))
                    {
                        result = result % value;
                        goto loop;
                    }
                    ok = false;
                }
            }
        }
    }

    if (!ok)
    {
        pos = back;
    }

    return ok;
}

/// AdditiveExpression -> [AdditiveExpression ('+' | '-')] MultiplicativeExpression
static bool AdditiveExpression(QStringList const &words, int &pos, int &result)
{
    bool ok = false;
    int value;
    int back = pos;

    if (pos < words.size())
    {
        if (MultiplicativeExpression(words, pos, result))
        {
loop:
            ok = true;
            if (pos < words.size())
            {
                if      (words.at(pos) == "+")
                {
                    ++pos;
                    if (MultiplicativeExpression(words, pos, value))
                    {
                        result = result + value;
                        goto loop;
                    }
                    ok = false;
                }
                else if (words.at(pos) == "-")
                {
                    ++pos;
                    if (MultiplicativeExpression(words, pos, value))
                    {
                        result = result - value;
                        goto loop;
                    }
                    ok = false;
                }
            }
        }
    }

    if (!ok)
    {
        pos = back;
    }

    return ok;
}

/// ShiftExpression -> [ShiftExpression ('<<' | '>>')] AdditiveExpression
static bool ShiftExpression(QStringList const &words, int &pos, int &result)
{
    bool ok = false;
    int value;
    int back = pos;

    if (pos < words.size())
    {
        if (AdditiveExpression(words, pos, result))
        {
loop:
            ok = true;
            if (pos < words.size())
            {
                if      (words.at(pos) == "<<")
                {
                    ++pos;
                    if (AdditiveExpression(words, pos, value))
                    {
                        result = result << value;
                        goto loop;
                    }
                    ok = false;
                }
                else if (words.at(pos) == ">>")
                {
                    ++pos;
                    if (AdditiveExpression(words, pos, value))
                    {
                        result = result >> value;
                        goto loop;
                    }
                    ok = false;
                }
            }
        }
    }

    if (!ok)
    {
        pos = back;
    }

    return ok;
}

/// RelationalExpression -> [RelationalExpression ('<' | '<=' | '>' | '>=')] ShiftExpression
static bool RelationalExpression(QStringList const &words, int &pos, int &result)
{
    bool ok = false;
    int value;
    int back = pos;

    if (pos < words.size())
    {
        if (ShiftExpression(words, pos, result))
        {
loop:
            ok = true;
            if (pos < words.size())
            {
                if      (words.at(pos) == "<")
                {
                    ++pos;
                    if (ShiftExpression(words, pos, value))
                    {
                        result = int(result < value);
                        goto loop;
                    }
                    ok = false;
                }
                else if (words.at(pos) == "<=")
                {
                    ++pos;
                    if (ShiftExpression(words, pos, value))
                    {
                        result = int(result <= value);
                        goto loop;
                    }
                    ok = false;
                }
                else if (words.at(pos) == ">")
                {
                    ++pos;
                    if (ShiftExpression(words, pos, value))
                    {
                        result = int(result > value);
                        goto loop;
                    }
                    ok = false;
                }
                else if (words.at(pos) == ">=")
                {
                    ++pos;
                    if (ShiftExpression(words, pos, value))
                    {
                        result = int(result >= value);
                        goto loop;
                    }
                    ok = false;
                }
            }
        }
    }

    if (!ok)
    {
        pos = back;
    }

    return ok;
}

/// EqualityExpression -> [EqualityExpression ('<<' | '>>')] RelationalExpression
static bool EqualityExpression(QStringList const &words, int &pos, int &result)
{
    bool ok = false;
    int value;
    int back = pos;

    if (pos < words.size())
    {
        if (RelationalExpression(words, pos, result))
        {
loop:
            ok = true;
            if (pos < words.size())
            {
                if      (words.at(pos) == "==")
                {
                    ++pos;
                    if (RelationalExpression(words, pos, value))
                    {
                        result = int(result == value);
                        goto loop;
                    }
                    ok = false;
                }
                else if (words.at(pos) == "!=")
                {
                    ++pos;
                    if (RelationalExpression(words, pos, value))
                    {
                        result = int(result != value);
                        goto loop;
                    }
                    ok = false;
                }
            }
        }
    }

    if (!ok)
    {
        pos = back;
    }

    return ok;
}

/// AndExpression -> [AndExpression '&'] EqualityExpression
static bool AndExpression(QStringList const &words, int &pos, int &result)
{
    bool ok = false;
    int value;
    int back = pos;

    if (pos < words.size())
    {
        if (EqualityExpression(words, pos, result))
        {
loop:
            ok = true;
            if (pos < words.size())
            {
                if (words.at(pos) == "&")
                {
                    ++pos;
                    if (EqualityExpression(words, pos, value))
                    {
                        result = result & value;
                        goto loop;
                    }
                    ok = false;
                }
            }
        }
    }

    if (!ok)
    {
        pos = back;
    }

    return ok;
}

/// ExclusiveOrExpression -> [ExclusiveOrExpression '^'] AndExpression
static bool ExclusiveOrExpression(QStringList const &words, int &pos, int &result)
{
    bool ok = false;
    int value;
    int back = pos;

    if (pos < words.size())
    {
        if (AndExpression(words, pos, result))
        {
loop:
            ok = true;
            if (pos < words.size())
            {
                if (words.at(pos) == "^")
                {
                    ++pos;
                    if (AndExpression(words, pos, value))
                    {
                        result = result ^ value;
                        goto loop;
                    }
                    ok = false;
                }
            }
        }
    }

    if (!ok)
    {
        pos = back;
    }

    return ok;
}

/// InclusiveOrExpression -> [InclusiveOrExpression '|'] ExclusiveOrExpression
static bool InclusiveOrExpression(QStringList const &words, int &pos, int &result)
{
    bool ok = false;
    int value;
    int back = pos;

    if (pos < words.size())
    {
        if (ExclusiveOrExpression(words, pos, result))
        {
loop:
            ok = true;
            if (pos < words.size())
            {
                if (words.at(pos) == "|")
                {
                    ++pos;
                    if (ExclusiveOrExpression(words, pos, value))
                    {
                        result = result ^ value;
                        goto loop;
                    }
                    ok = false;
                }
            }
        }
    }

    if (!ok)
    {
        pos = back;
    }

    return ok;
}

/// LogicalAndExpression -> [LogicalAndExpression '&&'] InclusiveOrExpression
static bool LogicalAndExpression(QStringList const &words, int &pos, int &result)
{
    bool ok = false;
    int value;
    int back = pos;

    if (pos < words.size())
    {
        if (InclusiveOrExpression(words, pos, result))
        {
loop:
            ok = true;
            if (pos < words.size())
            {
                if (words.at(pos) == "&&")
                {
                    ++pos;
                    if (InclusiveOrExpression(words, pos, value))
                    {
                        result = int(bool(result) && bool(value));
                        goto loop;
                    }
                    ok = false;
                }
            }
        }
    }

    if (!ok)
    {
        pos = back;
    }

    return ok;
}

/// LogicalOrExpression -> [LogicalOrExpression '&&'] LogicalAndExpression
static bool LogicalOrExpression(QStringList const &words, int &pos, int &result)
{
    bool ok = false;
    int value;
    int back = pos;

    if (pos < words.size())
    {
        if (LogicalAndExpression(words, pos, result))
        {
loop:
            ok = true;
            if (pos < words.size())
            {
                if (words.at(pos) == "||")
                {
                    ++pos;
                    if (LogicalAndExpression(words, pos, value))
                    {
                        result = int(bool(result) || bool(value));
                        goto loop;
                    }
                    ok = false;
                }
            }
        }
    }

    if (!ok)
    {
        pos = back;
    }

    return ok;
}

/// ConditionalExpression -> LogicalOrExpression ['?' Expression ':' ConditionalExpression]
static bool ConditionalExpression(QStringList const &words, int &pos, int &result)
{
    bool ok = false;
    int back = pos;

    if (pos < words.size())
    {
        if (LogicalOrExpression(words, pos, result))
        {
            ok = true;
            if (pos < words.size())
            {
                if (words.at(pos) == "?")
                {
                    int value1, value2;
                    ++pos;
                    if (Expression(words, pos, value1))
                    {
                        if (pos < words.size())
                        {
                            if (words.at(pos) == ":")
                            {
                                ++pos;
                                if (ConditionalExpression(words, pos, value2))
                                {
                                    result = bool(result) ?  value1 : value2;
                                    return true;
                                }
                            }
                        }
                    }
                    ok = false;
                }
            }
        }
        if (!ok)
        {
            pos = back;
        }
    }

    return ok;
}

static bool Expression(QStringList const &words, int &pos, int &result)
{
    return ConditionalExpression(words, pos, result);
}

bool gl_ShaderPreprocessor::ConditionalExpression(QString &block, int skip)
{
    int pos = 0;

    if (skip) block.remove(0, skip);

    while (pos < block.size())
    {
        char c = block[pos].toAscii();

        if (c == '\n' || c == '\r')
        {
            c = block[++pos].toAscii();

            if (c == '\n' || c == '\r')
            {
                ++pos;
            }

            QString expression = QStringRef(&block, 0, pos).toString();

            block.remove(0, pos);

            QStringList words = expression.split(QRegExp("\\s+"), QString::SkipEmptyParts);
            
            pos = 0;

            int value = 0;

            if (Expression(words, pos, value) && pos == words.size())
            {
                return !!value;
            }
            else
            {
                qCritical("gl_ShaderPreprocessor::Preprocess: invalid conditional expression in #if/elif: %s", expression.toAscii().data());
            }
                    
            return false;
        }

        ++pos;
    }

    block.remove(0, pos);

    return false;
}