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
#include <limits.h>
#include <stdexcept>
#include <QtGlobal>
#include "qt4_memorycursor.h"

Qt4_MemoryCursor::Qt4_MemoryCursor(
    int byteOffset,
    int charOffset,
    int low,
    int high,
    int charsPerByte)
: m_byteOffset(byteOffset)
, m_charOffset(charOffset)
, m_low(low)
, m_high(high)
, m_charsPerByte(charsPerByte)
{}

bool Qt4_MemoryCursor::setRange(int low, int high)
{
  if (low > high)
  {
    return false;
  }
  m_low = low;
  m_high = high;
  return true;
}

int Qt4_MemoryCursor::decrByByte(int n)
{
  if (n > m_byteOffset)
  {
    return OutOfRange;
  }
  else
  {
    m_byteOffset -= n;
  }
  return m_byteOffset;
}
int Qt4_MemoryCursor::decrByChar(int n)
{
  int byteDelta = n / m_charsPerByte;
  int charDelta = n % m_charsPerByte;

  if (charDelta > m_charOffset)
  {
    if (byteDelta == LONG_MAX )
    {
      throw std::out_of_range("Cursor decrement underflowed.\n");
    }
    byteDelta++;
  }

  if (byteDelta && OutOfRange == decrByByte(byteDelta))
  {
    return m_charOffset;
  }

  if (charDelta > m_charOffset)
  {
    m_charOffset = (m_charsPerByte) - (charDelta - m_charOffset);
  }
  else
  {
    m_charOffset -= charDelta;
  }
  return m_charOffset;
}

int Qt4_MemoryCursor::incrByChar(int n)
{
  int byteDelta = n / m_charsPerByte;
  int charDelta = n % m_charsPerByte;

  if (charDelta + m_charOffset >= m_charsPerByte)
  {
    if (byteDelta == LONG_MAX)
    {
      throw std::out_of_range("Cursor increment exceeded maximum offset.\n");
    }
    byteDelta++;
  }
  if (byteDelta && OutOfRange == incrByByte(byteDelta))
  {
    return m_charOffset;
  }
  m_charOffset = (charDelta + m_charOffset) % m_charsPerByte;
  return m_charOffset;
}

int Qt4_MemoryCursor::incrByByte(int byteDelta)
{
  if (byteDelta > LONG_MAX - m_byteOffset)
  {
    throw std::out_of_range("Cursor increment exceeded maximum offset.\n");
  }
  if (m_byteOffset + byteDelta >= m_high)
    return OutOfRange;
  return (m_byteOffset += byteDelta);
}

int Qt4_MemoryCursor::byteOffset() const
{
  return m_byteOffset;
}
int Qt4_MemoryCursor::charOffset() const
{
  return m_charOffset;
}

int Qt4_MemoryCursor::setCharsPerByte( int charsPerByte )
{
  m_charsPerByte = charsPerByte;
  m_charOffset = qMin(m_charOffset, charsPerByte - 1);
  return m_charsPerByte;
}

void Qt4_MemoryCursor::setOffset(int byteOffset, int charOffset)
{
  assignClamped(m_byteOffset, byteOffset, 0, m_high);
  assignClamped(m_charOffset, charOffset, 0, m_charsPerByte);
}

int Qt4_MemoryCursor::charOffsetAbsolute() const
{
  return m_byteOffset * m_charsPerByte + m_charOffset;
}

void Qt4_MemoryCursor::assignClamped(int &dst, int src, int low, int high)
{
  if (src < low)
  {
    dst = low;
  }
  else if (src >= high)
  {
    dst = high - 1;
  }
  else
  {
    dst = src;
  }
}
