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
#ifndef QT4_MEMORYWIDGET_H
#define QT4_MEMORYWIDGET_H

#include <QtGui/QWidget>
#include "common_types.h"
#include "types.h"
#include "qt4_memorycursor.h"


class qt4_MemoryWidget : public QWidget
{
  Q_OBJECT

  public:
    qt4_MemoryWidget(QWidget *parent = 0);
    ~qt4_MemoryWidget();
    u32 offset() const;

    void seeCursor();
    void cursorLeft();
    void cursorRight();
    void cursorUp();
    void cursorDown();
    int  wordWidth() const;
    int  wordSpacing() const;
    void setCursorFromXY(int x, int y);
  public:
    enum SelectionPos
    {
      SelectionStart,
      SelectionEnd,
    };

    void setSelection(SelectionPos pos, int offset);
    int selectionStart() const;
    int selectionEnd() const;
    int offsetToPercent(int offset);

    int localByteOffsetAtXY(int x, int y);
protected:
    int localByteOffset() const;
    int localColumnOffset() const;
    int localCharOffset() const;
    int localLineOffset() const;

  signals:
    void rangeChanged(int low, int high);
    void addressChanged(int address);
    void lineChanged(int line);
    void offsetChanged(int offset);
    void selectionChanged(const QString &selection);

  public slots:
    void changeAddressRange(int choice);
    void changeAddressRange(int start, int end);
    void changeAddress(int address);
    void changeLine(int line);

    void setOffset(int offset);
    void setBytesPerColumn(int i);
    void set1BytePerColumn() { setBytesPerColumn(1); };
    void set2BytesPerColumn() { setBytesPerColumn(2); };
    void set4BytesPerColumn() { setBytesPerColumn(4); };
    void set8BytesPerColumn() { setBytesPerColumn(8); };
    void toggleEndianness() { m_endianness = 1 - m_endianness; };
    void nextLine();
    void prevLine();
    void nextPage();
    void prevPage();
    void setFont(const QFont &font);
    void undo();
    void redo();
    void search(const QString &text, bool forwards);
    void setBase(int base);
    void setBaseHex();
    void setBaseOctal();
    void setBaseBinary();
    void setBaseASCII();

  protected:
    void setTopLeft(int offset);
    bool moveTopLeft(int offset);

  protected:
    bool columnModified(int index) const;
    template< class T >
    void setColumn(int index, const T &str);
    QRect charBBox(int index) const;
    QRect byteBBox(int index) const;

    int pointToColumn(const QPoint &point);
    QChar &pointToChar(const QPoint &point);

  protected:
    void calculateFontMetrics();
    int charsPerByte() const;
    int charsPerColumn() const;
    int charsPerLine() const;
    int bytesPerPage() const;
    int bytesPerColumn() const;
    int bytesPerLine() const;
    int columnsPerLine() const;
    int columnsPerPage() const;
    int linesPerPage() const;
    int columnSpacing() const;
    int columnWidth() const;
    int lineSpacing() const;
    int fontHeight() const;
    int fontMaxWidth() const;
    int topMargin() const;
    int leftMargin() const;

    int globalOffset(int local) const;
    int localOffset(int global) const;

  protected:
    void showMatch(int pos, int len);

  protected:
    QString getDisplayText();
    void drawCursor(QPainter &p);
    void drawSelection(QPainter &p);
    void drawTextRegion(QPainter &p, const QString &text, int row_start, int row_end, int col_start, int col_end);

  protected:
    void resizeEvent(QResizeEvent *e);
    void updateColumn(int index);
    void paintEvent(QPaintEvent *e);
    void paintLabels(QPainter *p);
    void focusInEvent(QFocusEvent*e);
    void focusOutEvent(QFocusEvent*e);
    void keyPressEvent(QKeyEvent *e);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void contextMenuEvent(QContextMenuEvent *e);

  protected:
    u32 m_start;
    u32 m_end;

    int m_columnSpacing;
    int m_columnWidth;
    int m_lineSpacing;
    int m_fontHeight;
    int m_bytesPerColumn;
    int m_charsPerByte;
    int m_topLeft;

    u8 *m_data;
    int m_base;
    int m_lastValidColumn;
    
    int m_endianness;

    QVector< QRect > m_lineBBox;
    QVector< QRect > m_columnBBox;
    QRect m_labelBBox;

    int m_fontMaxWidth;

    int m_topMargin;
    int m_leftMargin;
    int m_offsetLabelBytes;

    int m_cols;
    int m_rows;
    int m_width;
    Qt4_MemoryCursor m_cursor;
    int m_selection[2];
};

#endif
