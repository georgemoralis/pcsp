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
#ifndef QTRANSLATE_H_
#define QTRANSLATE_H_

#include "types.h"

#include <vector>
#include <QString>

namespace Qt4_Translate
{
  const char *ByteToHex(u8 b);
  void ByteToHex(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask = 0);
  void ByteToChar(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask = 0);
  void ByteToOctal(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask = 0);
  void ByteToBinary(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask = 0);


  void ByteToHex(QString &dst, const u8 *src, int len, int mask = 0);
  void ByteToChar(QString &dst, const u8 *src, int len, int mask = 0);
  void ByteToOctal(QString &dst, const u8 *src, int len, int mask = 0);
  void ByteToBinary(QString &dst, const u8 *src, int len, int mask = 0);

  void BinaryToByte(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask = 0);

  void OctalToByte(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask = 0);

  void CharToByte(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask = 0);
  void CharToByte(std::vector< u8 > &dst, const QString &src, int mask = 0);

  void HexToByte(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask = 0);
  void HexToByte(std::vector< u8 > &dst, const QString &src, int mask = 0);
};

#endif /* QTRANSLATE_H_ */
