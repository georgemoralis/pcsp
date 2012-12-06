#ifndef GL_SHADERPREPROCESSOR_H
#define GL_SHADERPREPROCESSOR_H

#include <QStringList>

class gl_ShaderPreprocessor
{
public:
    gl_ShaderPreprocessor();
    ~gl_ShaderPreprocessor();

    bool Preprocess(const QString &source);

    const QString &Result() { return m_preprocessed_source; }

protected:
    bool ConditionalExpression(QString &block, int skip = 0);

private:
    QString m_preprocessed_source;
};

#endif // GL_GLSLPREPROCESSOR_H
