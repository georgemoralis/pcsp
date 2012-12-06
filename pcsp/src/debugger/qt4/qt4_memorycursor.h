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
#ifndef QT4_MEMORYCURSOR_H
#define QT4_MEMORYCURSOR_H

class Qt4_MemoryCursor
{
  public:
    Qt4_MemoryCursor(
        int byteOffset = 0,
        int charOffset = 0,
        int low        = 0,
        int high       = 1,
        int charsPerByte = 2);
    Qt4_MemoryCursor(const Qt4_MemoryCursor &c);

    int incrByChar(int n);
    int incrByByte(int n);
    int decrByChar(int n);
    int decrByByte(int n);

    int byteOffset() const;
    int charOffset() const;
    int charOffsetAbsolute() const;

    bool setRange(int low, int high);
    int setCharsPerByte(int charsPerByte);
    void setOffset(int byteOffset, int charOffset);

  protected:
    void assignClamped(int &dst, int src, int low, int high);

    enum
    {
      OutOfRange = -1,
    };

  protected:
    int m_byteOffset;
    int m_charOffset;
    int m_low;
    int m_high;
    int m_charsPerByte;
};

#endif // QMEMORYCURSOR_H
