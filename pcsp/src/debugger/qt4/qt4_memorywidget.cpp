/*
This file is part of pcsp.

pcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

pcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with pcsp.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stdafx.h"
#include "types.h"
#include "qt4_memorycursor.h"
#include "qt4_translate.h"
#include "qt4_memorywidget.h"  
#include "memory.h"
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QProgressDialog>
#include <QPainter>
#include <QPixmap>
#include <QFocusEvent>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QAction>
#include <QMenu>
#include <QStyle>
#include <QStyleOption>
#include <cmath>

qt4_MemoryWidget::qt4_MemoryWidget(QWidget *parent)
: QWidget(parent)
, m_columnSpacing(6)
, m_bytesPerColumn(1)
, m_charsPerByte(2)
, m_topLeft(0)
, m_base(16)
, m_lastValidColumn(-1)
, m_topMargin(6)
, m_cols(16)
, m_rows(32)
, m_endianness(1)
{
    m_selection[SelectionStart] = -1;
    m_selection[SelectionEnd] = -1;

    setFocusPolicy(Qt::StrongFocus);
    QFont font("Courier");
    font.setFixedPitch(1);
    setFont(font);
    changeAddressRange(0);
}

qt4_MemoryWidget::~qt4_MemoryWidget()
{

}
void qt4_MemoryWidget::setBytesPerColumn(int bytes)
{
    m_bytesPerColumn = bytes;
    calculateFontMetrics();
    QResizeEvent re = QResizeEvent(QSize(size()), QSize(size()));
    resizeEvent(&re);
}
int qt4_MemoryWidget::fontHeight() const
{
    return m_fontHeight;
}
int qt4_MemoryWidget::lineSpacing() const
{
    return m_lineSpacing;
}
int qt4_MemoryWidget::fontMaxWidth() const
{
    return m_fontMaxWidth;
}
void qt4_MemoryWidget::calculateFontMetrics()
{
    m_lineSpacing = fontMetrics().lineSpacing();
    m_fontMaxWidth = fontMetrics().maxWidth();
    m_columnWidth = m_fontMaxWidth * charsPerColumn();
    m_fontHeight = fontMetrics().height();
    if (m_start != m_end)
    {
        m_offsetLabelBytes = 8;
    }
    else
    {
        m_offsetLabelBytes = 0;
    }
    m_leftMargin = m_topMargin + m_fontMaxWidth * (m_offsetLabelBytes + 2);
    QResizeEvent re = QResizeEvent(QSize(size()), QSize(size()));
    resizeEvent(&re);
}

void qt4_MemoryWidget::setFont(const QFont& font )
{
    QWidget::setFont(font);
    calculateFontMetrics();
}

bool qt4_MemoryWidget::moveTopLeft(int offset)
{
    static bool inTopLeft = false;
    if (inTopLeft)
    {
        return false;
    }
    inTopLeft = true;
    try
    {
        if (offset < 0)
        {
            m_topLeft = 0;
        }
        else if (offset > int(m_end - m_start))
        {
            m_topLeft = m_end - m_start;
        }
        else
        {
            m_topLeft = offset;
        }

        m_topLeft = (m_topLeft * bytesPerLine()) / bytesPerLine();

        repaint();

        inTopLeft = false;

        return true;
    }
    catch (const std::exception &e)
    {
        inTopLeft = false;
        throw e;
    }
    inTopLeft = false;
    return false;
}

void qt4_MemoryWidget::changeLine(int line)
{
    if (moveTopLeft(line * bytesPerLine()))
    {
        emit addressChanged(m_topLeft + m_start);
    }
}

void qt4_MemoryWidget::changeAddress(int address)
{
    setOffset(address - m_start);
    seeCursor();
}

void qt4_MemoryWidget::setTopLeft(int offset)
{
    if (moveTopLeft(offset))
    {
        //emit addressChanged(m_topLeft + m_start);
        emit lineChanged(m_topLeft / bytesPerLine());
    }
}

int qt4_MemoryWidget::topMargin() const
{
    return m_topMargin;
}
int qt4_MemoryWidget::leftMargin() const
{
    return m_leftMargin;
}

int qt4_MemoryWidget::bytesPerPage() const
{
    return m_rows * m_cols * bytesPerColumn();
}
int qt4_MemoryWidget::bytesPerColumn() const
{
    return m_bytesPerColumn;
}
int qt4_MemoryWidget::bytesPerLine() const
{
    return bytesPerColumn() * columnsPerLine();
}
int qt4_MemoryWidget::columnsPerLine() const
{
    return m_cols;
}
int qt4_MemoryWidget::linesPerPage() const
{
    return m_rows;
}
int qt4_MemoryWidget::columnsPerPage() const
{
    return m_rows * m_cols;
}
int qt4_MemoryWidget::charsPerByte() const
{
    return m_charsPerByte;
}
int qt4_MemoryWidget::charsPerColumn() const
{
    return m_charsPerByte * bytesPerColumn();
}
int qt4_MemoryWidget::charsPerLine() const
{
    return m_charsPerByte * (bytesPerLine());
}

int qt4_MemoryWidget::globalOffset(int local) const
{
    return local + m_topLeft;
}

int qt4_MemoryWidget::localOffset(int global) const
{
    return global - m_topLeft;
}

int qt4_MemoryWidget::offsetToPercent(int offset)
{
    return (m_end - m_start) ? (int)ceil(100.0 * offset / int(m_end - m_start)) : 0;
}

QRect qt4_MemoryWidget::charBBox(int charIndex) const
{
    int columnIndex = (charIndex / charsPerByte()) / bytesPerColumn();
    int localCharIndex = charIndex % charsPerColumn();
    return QRect(
        m_columnBBox[columnIndex].left() + localCharIndex * fontMaxWidth() + columnSpacing() / 2,
        m_columnBBox[columnIndex].top(),
        fontMaxWidth(),
        fontHeight());

}

QRect qt4_MemoryWidget::byteBBox(int byteIndex) const
{
    int columnIndex = byteIndex / bytesPerColumn();
    int localByteIndex = byteIndex % bytesPerColumn();
    return QRect(
        m_columnBBox[columnIndex].left() + localByteIndex * 2 * fontMaxWidth() + columnSpacing() / 2,
        m_columnBBox[columnIndex].top(),
        fontMaxWidth() * 2,
        lineSpacing());

}

void qt4_MemoryWidget::setOffset(int offset)
{
    int oldColumnOffset = localColumnOffset();
    m_cursor.setOffset(offset, 0);
    updateColumn(oldColumnOffset);
    emit offsetChanged(m_cursor.byteOffset());
}

void qt4_MemoryWidget::nextLine()
{
    setTopLeft(m_topLeft + bytesPerLine());
}
void qt4_MemoryWidget::prevLine()
{
    setTopLeft(m_topLeft - bytesPerLine());
}
void qt4_MemoryWidget::nextPage()
{
    setTopLeft(m_topLeft + bytesPerPage());
}
void qt4_MemoryWidget::prevPage()
{
    setTopLeft(m_topLeft - bytesPerPage());
}

int qt4_MemoryWidget::localByteOffsetAtXY(int x, int y)
{
    int ColumnIndex;
    int columnLength = columnSpacing() + columnWidth();
    int line = qMin(y / lineSpacing(), (int)linesPerPage());

    x = qMax(0, x - leftMargin());
    x = qMin(columnsPerLine() * columnLength - 1, x);
    y = qMax(0, y - topMargin());
    line = qMin(y / lineSpacing(), linesPerPage() - 1);
    ColumnIndex = line * columnsPerLine() + x / columnLength;

    int byteOffsetInColumn = ((x % columnLength) * bytesPerColumn()) / columnLength;
    return qMin(bytesPerPage() - 1, ColumnIndex * bytesPerColumn() + byteOffsetInColumn);

}

void qt4_MemoryWidget::setCursorFromXY(int x, int y)
{
    int oldColumnIndex = localColumnOffset();

    m_cursor.setOffset(m_topLeft + localByteOffsetAtXY(x,y), 0);

    if (oldColumnIndex != localColumnOffset())
    {
        updateColumn(oldColumnIndex);
    }
    updateColumn(localColumnOffset());
    emit offsetChanged(m_cursor.byteOffset());
    emit addressChanged(m_start + m_cursor.byteOffset());
}

void qt4_MemoryWidget::mousePressEvent(QMouseEvent *e)
{
    setCursorFromXY(e->x(), e->y());

    int offset = localByteOffset();
    QRect bbox = byteBBox(offset);
    if (e->x() > bbox.right())
    {
        offset++;
    }

    setSelection(SelectionStart, globalOffset(offset));
}

void qt4_MemoryWidget::mouseMoveEvent(QMouseEvent *e)
{
    setCursorFromXY(e->x(), e->y());

    int offset = localByteOffset();
    QRect bbox = byteBBox(offset);
    if (e->x() > bbox.right())
    {
        offset++;
    }

    setSelection(SelectionEnd, globalOffset(offset));
}

void qt4_MemoryWidget::mouseReleaseEvent(QMouseEvent *e)
{
    setCursorFromXY(e->x(), e->y());

    int offset = localByteOffset();
    QRect bbox = byteBBox(offset);
    if (e->x() > bbox.right())
    {
        offset++;
    }

    setSelection(SelectionEnd, globalOffset(offset));
}

void qt4_MemoryWidget::contextMenuEvent(QContextMenuEvent *e)
{
    // view menu
    QMenu viewMenu("&View", this);

    QMenu *baseMenu = new QMenu("&Editing base", this);
    baseMenu->addAction("&Hex", this, SLOT(setBaseHex()));
    baseMenu->addAction("&ASCII", this, SLOT(setBaseASCII()));
    baseMenu->addAction("&Binary", this, SLOT(setBaseBinary()));
    if (bytesPerColumn() == 1)
    {
        baseMenu->addAction("&Octal", this, SLOT(setBaseOctal()));
    }
    viewMenu.addMenu(baseMenu);

    QMenu *bpcMenu = new QMenu("&Bytes per column",this);
    bpcMenu->addAction("&1", this, SLOT(set1BytePerColumn()));
    if (m_base != 8)
    {
        bpcMenu->addAction("&2", this, SLOT(set2BytesPerColumn()));
        bpcMenu->addAction("&4", this, SLOT(set4BytesPerColumn()));
        bpcMenu->addAction("&8", this, SLOT(set8BytesPerColumn()));
    }
    viewMenu.addMenu(bpcMenu);

    QMenu *endMenu = new QMenu("&Endianness",this);
    if (m_base != 8)
    {
        if (m_endianness == 0)
        {
            endMenu->addAction("Little Endian", this, SLOT(toggleEndianness()));
        }
        else
        {
            endMenu->addAction("Big Endian", this, SLOT(toggleEndianness()));
        }
    }

    viewMenu.addMenu(endMenu);

    viewMenu.exec(e->globalPos());
}

int qt4_MemoryWidget::selectionStart() const
{
    if (m_selection[SelectionStart] == -1 || m_selection[SelectionEnd] == -1)
        return -1;
    return qMin(m_selection[SelectionStart], m_selection[SelectionEnd]);
}

int qt4_MemoryWidget::selectionEnd() const
{
    if (m_selection[SelectionStart] == -1 || m_selection[SelectionEnd] == -1)
        return -1;
    return qMax(m_selection[SelectionStart], m_selection[SelectionEnd]);
}

void qt4_MemoryWidget::setSelection(SelectionPos pos, int offset)
{
    if (m_end - m_start)
    {
        return;
    }

    if (pos == SelectionStart)
    {
        m_selection[SelectionEnd] = -1;
    }

    m_selection[pos] = offset;

    if (m_selection[SelectionStart] < 0)
    {
        emit selectionChanged("");
    }
    else
    {
        if (selectionEnd() > -1 && selectionEnd() <= int(m_end - m_start))
        {
            QString data;
            for (int i = selectionStart(); i < selectionEnd(); ++i)
            {
                data += Qt4_Translate::ByteToHex(Memory::membu(m_start + i));
            }
            emit selectionChanged(data);
        }
        else
        {
            emit selectionChanged("");
        }
    }

    repaint();
}

void qt4_MemoryWidget::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();

    int mask = m_endianness * (bytesPerColumn() - 1);

    switch (m_base)
    {
    case -1:
        if (key >= Qt::Key_Space && key <= Qt::Key_AsciiTilde)
        {
            seeCursor();
            std::vector< u8 > oldData;
            std::vector< u8 > newData;
            std::vector< u8 > chars;

            oldData.push_back(m_data[localByteOffset() ^ mask]);
            Qt4_Translate::ByteToChar(chars, oldData);
            chars[0] = key;
            Qt4_Translate::CharToByte(newData, chars);
            m_data[(m_cursor.byteOffset() - m_topLeft) ^ mask] = newData[0];
            cursorRight();
            setSelection(SelectionStart, -1);
            return;
        }
        break;
    case 16:
        if (key >= 'A' && key <= 'F')
        {
            key = tolower(key);
        }
        if ((key >= 'a' && key <= 'f') || (key >= '0' && key <= '9'))
        {
            seeCursor();
            std::vector< u8 > oldData;
            std::vector< u8 > newData;
            std::vector< u8 > hex;

            oldData.push_back(m_data[localByteOffset() ^ mask]);
            Qt4_Translate::ByteToHex(hex, oldData);
            hex[m_cursor.charOffset()] = key;
            Qt4_Translate::HexToByte(newData, hex);

            m_data[(m_cursor.byteOffset() - m_topLeft) ^ mask] = newData[0];
            cursorRight();
            setSelection(SelectionStart, -1);
            return;
        }
        break;
    case 8:
        if (key >= '0' && key < '8')
        {
            seeCursor();
            std::vector< u8 > oldData;
            std::vector< u8 > newData;
            std::vector< u8 > octal;

            oldData.push_back(m_data[localByteOffset()]);
            Qt4_Translate::ByteToOctal(octal, oldData);
            octal[m_cursor.charOffset()] = key;
            Qt4_Translate::OctalToByte(newData, octal);
            m_data[m_cursor.byteOffset( ) - m_topLeft] = newData[0];
            cursorRight();
            setSelection(SelectionStart, u32(-1));
            return;
        }
        break;
    case 2:
        if (key >= '0' && key < '2')
        {
            seeCursor();
            std::vector< u8 > oldData;
            std::vector< u8 > newData;
            std::vector< u8 > binary;

            oldData.push_back(m_data[localByteOffset() ^ mask]);
            Qt4_Translate::ByteToBinary(binary,oldData);
            binary[m_cursor.charOffset()] = key;
            Qt4_Translate::BinaryToByte(newData,binary);

            m_data[(m_cursor.byteOffset() - m_topLeft) ^ mask] = newData[0];
            cursorRight();
            setSelection(SelectionStart, -1);
            return;
        }
        break;
    }

    switch (e->key())
    {
    case Qt::Key_Left:
        cursorLeft();
        break;
    case Qt::Key_Right:
        cursorRight();
        break;
    case Qt::Key_Up:
        cursorUp();
        break;
    case Qt::Key_Down:
        cursorDown();
        break;
    case Qt::Key_PageUp:
        prevPage();
        break;
    case Qt::Key_PageDown:
        nextPage();
        break;
    case Qt::Key_End:
        setTopLeft((m_end - m_start) - bytesPerPage()/2);
        break;
    case Qt::Key_Home:
        setTopLeft(0);
        break;
    default:
        e->ignore();
        break;
    }
}

void qt4_MemoryWidget::wheelEvent(QWheelEvent *e)
{
    int numDegrees = e->delta() / 8;
    int numSteps = numDegrees / 15;

    setTopLeft(m_topLeft - numSteps * bytesPerLine());

    e->accept();
}

void qt4_MemoryWidget::resizeEvent(QResizeEvent *e)
{
    int height = lineSpacing();
    int totalColumnWidth = columnWidth() + columnSpacing();
    int linewidth = e->size().width();

    m_rows = qMax(1, (e->size().height() - m_topMargin) / height);
    m_cols = qMax(1, (e->size().width() - m_leftMargin) / totalColumnWidth);

    //m_lineBBox.reserve(m_rows);
    // m_columnBBox.reserve(m_rows * m_cols);//hmm vstudio doesn't like that?
    m_lineBBox.resize(m_rows);
    m_columnBBox.resize(m_rows * m_cols);
    int top, left;
    for (int r = 0; r < m_rows; r++)
    {
        top = r * height + m_topMargin;
        for (int c = 0; c < m_cols; c++)
        {
            left = totalColumnWidth * c + m_leftMargin;
            int index = r* m_cols+c;
            int size = m_columnBBox.size();
            m_columnBBox[r * m_cols + c] = QRect(left, top, totalColumnWidth, height);
        }
        m_lineBBox[r] = QRect(m_leftMargin, top, linewidth, height);
    }
    m_labelBBox.setRect(0, 0, m_leftMargin, e->size().height());

    setTopLeft(m_topLeft);
    emit rangeChanged(0, (m_end - m_start) / bytesPerLine());
}

void qt4_MemoryWidget::focusInEvent(QFocusEvent *e)
{
    QWidget::focusInEvent(e);
}

void qt4_MemoryWidget::focusOutEvent(QFocusEvent *e)
{
    QWidget::focusOutEvent(e);
}

void qt4_MemoryWidget::updateColumn(int columnIndex)
{
    if (columnIndex > -1 && columnIndex < m_rows * m_cols)
        repaint(m_columnBBox[columnIndex]);
}

void qt4_MemoryWidget::paintLabels(QPainter *p)
{
    int y = m_columnBBox[0].bottom();
    int offset = m_topLeft + m_start;

    for (int row = 0; row < m_rows; ++row)
    {
        p->drawText(5, y, QString("%1").arg((unsigned int)offset, 8, 16, QChar('0')).toUpper());
        offset += bytesPerLine();
        y += lineSpacing();
    }
    int x = leftMargin() - fontMaxWidth();
    p->drawLine(x, topMargin(), x, height() - topMargin());
}

void qt4_MemoryWidget::paintEvent(QPaintEvent *e)
{
    QStyleOption option;
    option.initFrom(this);
    option.state = hasFocus() ? QStyle::State_HasFocus : QStyle::State_Enabled;

    QPainter p(this);

    p.setFont(font());
    p.setBrush(qApp->palette().base());

    style()->drawPrimitive(QStyle::PE_FrameLineEdit, &option, &p, this);

    if (m_labelBBox.intersects(e->rect()))
    {
        paintLabels(&p);
    }

    QString text = getDisplayText();
    drawCursor(p);
    drawSelection(p);

    int totalColumnWidth = columnWidth() + columnSpacing();
    int row_start = qMax(0, (e->rect().top() - topMargin()) / lineSpacing() );
    int col_start = qMax(0, (e->rect().left() - leftMargin()) / totalColumnWidth);
    int row_stop  = qMin(m_rows - 1, e->rect().bottom() / lineSpacing());
    int col_stop  = qMin(m_cols - 1, e->rect().right() / totalColumnWidth);

    drawTextRegion(p, text, row_start, row_stop, col_start, col_stop);
}

QString qt4_MemoryWidget::getDisplayText()
{
    QString text;
    u32 end = m_start + m_topLeft + bytesPerPage();
    int size = (end < m_end) ? bytesPerPage() : (m_end - m_start - m_topLeft);
    int mask = m_endianness * (bytesPerColumn() - 1);

    switch (m_base)
    {
    case 16:
        Qt4_Translate::ByteToHex(text, m_data + m_topLeft, size, mask);
        break;
    case 8:
        Qt4_Translate::ByteToOctal(text, m_data + m_topLeft, size, 0);
        break;
    case 2:
        Qt4_Translate::ByteToBinary(text, m_data + m_topLeft, size, mask);
        break;
    case -1:
        Qt4_Translate::ByteToChar(text, m_data + m_topLeft, size, mask);
        break;
    }
    return text;
}

int qt4_MemoryWidget::localByteOffset()  const
{
    return (m_cursor.byteOffset() - m_topLeft);
}

int qt4_MemoryWidget::localColumnOffset() const
{
    return localByteOffset() / bytesPerColumn();
}

int qt4_MemoryWidget::localCharOffset() const
{
    return localByteOffset() * charsPerByte() + m_cursor.charOffset();
}

int qt4_MemoryWidget::localLineOffset() const
{
    return localColumnOffset( ) / columnsPerLine();
}

int qt4_MemoryWidget::columnWidth() const
{
    return m_fontMaxWidth * charsPerColumn();
}

int qt4_MemoryWidget::columnSpacing() const
{
    return m_columnSpacing;
}

void qt4_MemoryWidget::seeCursor()
{
    if (m_cursor.byteOffset() >= m_topLeft && m_cursor.byteOffset() <= m_topLeft + bytesPerPage() - 1)
    {
        updateColumn(localColumnOffset());
    }
    else
    {
        setTopLeft(qMax(m_cursor.byteOffset() - (bytesPerPage() + bytesPerLine()) / 2, 0));
    }
}

void qt4_MemoryWidget::cursorLeft()
{
    int oldColumnIndex = localColumnOffset();
    m_cursor.decrByChar(1);
    seeCursor();
    if (localColumnOffset() != oldColumnIndex)
        updateColumn(oldColumnIndex);
    emit offsetChanged(m_cursor.byteOffset());
}

void qt4_MemoryWidget::cursorRight()
{
    int oldColumnIndex = localColumnOffset();
    m_cursor.incrByChar(1);
    seeCursor();
    if (localColumnOffset() != oldColumnIndex)
        updateColumn(oldColumnIndex);
    emit offsetChanged(m_cursor.byteOffset());
}

void qt4_MemoryWidget::cursorUp()
{
    int oldColumnIndex = localColumnOffset();
    m_cursor.decrByByte(bytesPerLine());
    seeCursor();
    if (localColumnOffset() != oldColumnIndex)
        updateColumn(oldColumnIndex );
    emit offsetChanged(m_cursor.byteOffset());
}

void qt4_MemoryWidget::cursorDown()
{
    int oldColumnIndex = localColumnOffset();
    m_cursor.incrByByte(bytesPerLine());
    seeCursor();
    if (localColumnOffset() != oldColumnIndex)
        updateColumn(oldColumnIndex);
    emit offsetChanged(m_cursor.byteOffset());
}

void qt4_MemoryWidget::redo()
{
    setTopLeft(m_topLeft);
    int start = selectionStart();
    int end   = selectionEnd();
    setSelection(SelectionStart, start);
    setSelection(SelectionEnd, end);
}

void qt4_MemoryWidget::undo()
{
    setTopLeft(m_topLeft);
    int start = selectionStart();
    int end   = selectionEnd();
    setSelection(SelectionStart, start);
    setSelection(SelectionEnd, end);
}

void qt4_MemoryWidget::search(const QString &text, bool forwards)
{
#if 0
    QApplication::setOverrideCursor(QMemoryCursor(Qt::WaitCursor));

    if (!text.length() || (m_end - m_start))
        return;

    vector<uchar> data;

    QTranslate::HexToByte(data, hexText);

    u32 pos;
    if( forwards )
    {
        pos = _reader.findIndex(_cursor.byteOffset(),data,_reader.size()-1);
    }
    else
    {
        pos = _reader.rFindIndex(_cursor.byteOffset(),data,0);
    }

    if( pos < _reader.size() )
    {
        showMatch(pos,data.size());
        setOffset(forwards?selectionEnd():selectionStart() - 1);
        seeCursor();
    }
    else
    {
        QMessageBox::information(this,PROGRAM_STRING,
            "Could not find search data 0x" + hexText);
    }
    QApplication::restoreOverrideCursor();
#endif
}

void qt4_MemoryWidget::setBase(int base)
{
    switch(base)
    {
    case -1:
        m_charsPerByte = 1;
        break;
    case 2:
        m_charsPerByte = 8;
        break;
    case 8:
        m_charsPerByte = 3;
        break;
    case 16:
        m_charsPerByte = 2;
        break;
    default:
        return;
    }

    m_base = base;
    m_cursor.setCharsPerByte(m_charsPerByte);
    QResizeEvent re = QResizeEvent(QSize(size()), QSize(size()));
    resizeEvent(&re);
    seeCursor();
}

void qt4_MemoryWidget::setBaseASCII()
{
    setBase(-1);
}
void qt4_MemoryWidget::setBaseHex()
{
    setBase(16);
}

void qt4_MemoryWidget::setBaseOctal()
{
    setBase(8);
}

void qt4_MemoryWidget::setBaseBinary()
{
    setBase(2);
}

u32 qt4_MemoryWidget::offset() const
{
    return m_cursor.byteOffset();
}

void qt4_MemoryWidget::showMatch(int pos, int len)
{
    setSelection(SelectionStart, pos);
    setSelection(SelectionEnd, pos + len);
}

void qt4_MemoryWidget::drawTextRegion(QPainter &paint,
                                      const QString &text,
                                      int row_start,
                                      int row_stop,
                                      int col_start,
                                      int col_stop)
{
    paint.setPen(qApp->palette().windowText().color());
    for (int r = row_start; r <= row_stop; r++)
    {
        for (int c = col_start; c <= col_stop; c++)
        {
            int index = r * m_cols + c;
            paint.drawText( m_columnBBox[index].left() + columnSpacing()/2, m_columnBBox[index].bottom(), text.mid(index * charsPerColumn(), charsPerColumn()));
        }
    }
}

void qt4_MemoryWidget::drawSelection(QPainter &paint)
{
    int start = qMax(0, selectionStart() - m_topLeft);
    if (start < bytesPerPage())
    {
        int stop = qMin(selectionEnd() - m_topLeft, bytesPerPage());
        paint.setPen(Qt::NoPen);
        paint.setBrush(qApp->palette().highlight());
        stop--;
        while (start <= stop)
        {
            int linestop = qMin(stop, start + bytesPerLine() - 1 -(start % bytesPerLine()));
            QRect bbox = byteBBox(start);
            bbox.setRight(byteBBox(linestop).right());
            paint.drawRect(bbox);
            start = linestop + 1;
        }
    }
}

void qt4_MemoryWidget::drawCursor(QPainter &paint)
{
    if (localColumnOffset() > -1 && localColumnOffset() < columnsPerPage())
    {
        if (hasFocus())
        {
            paint.setPen(Qt::NoPen);
            paint.setBrush(qApp->palette().mid());
        }
        else
        {
            paint.setPen(Qt::NoPen);
            paint.setBrush(qApp->palette().midlight());
        }
        QRect box = charBBox(localCharOffset());
        paint.drawRect(box);
    }
}

void qt4_MemoryWidget::changeAddressRange(int start, int end)
{
    m_start = start;
    m_end   = end;
    m_data = Memory::addrbu(m_start);
    m_cursor.setRange(0, (m_end - m_start));
    m_cursor.setCharsPerByte(m_charsPerByte);
    setSelection(SelectionStart, -1);
    setSelection(SelectionEnd, -1);
    emit rangeChanged(0, int(m_end - m_start) / bytesPerLine());
    calculateFontMetrics();
    setTopLeft(0);
}

void qt4_MemoryWidget::changeAddressRange(int choice)
{
    int start, end;
    switch (choice)
    {
    case 0:
        start = 0x08800000;
        end   = 0x0C000000;
        break;
    case 1:
        start = 0x08000000;
        end   = 0x08800000;
        break;
    case 2:
        start = 0x04000000;
        end   = 0x04400000;
        break;
    case 3:
        start = 0x00010000;
        end   = 0x00014000;
        break;
    }
    changeAddressRange(start, end);
}

