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
#include "qt4_translate.h"

namespace Qt4_Translate
{
    const char *byteToBinaryMap[256] =
    {
        "00000000", "00000001", "00000010", "00000011",
        "00000100", "00000101", "00000110", "00000111",
        "00001000", "00001001", "00001010", "00001011",
        "00001100", "00001101", "00001110", "00001111",
        "00010000", "00010001", "00010010", "00010011",
        "00010100", "00010101", "00010110", "00010111",
        "00011000", "00011001", "00011010", "00011011",
        "00011100", "00011101", "00011110", "00011111",
        "00100000", "00100001", "00100010", "00100011",
        "00100100", "00100101", "00100110", "00100111",
        "00101000", "00101001", "00101010", "00101011",
        "00101100", "00101101", "00101110", "00101111",
        "00110000", "00110001", "00110010", "00110011",
        "00110100", "00110101", "00110110", "00110111",
        "00111000", "00111001", "00111010", "00111011",
        "00111100", "00111101", "00111110", "00111111",
        "01000000", "01000001", "01000010", "01000011",
        "01000100", "01000101", "01000110", "01000111",
        "01001000", "01001001", "01001010", "01001011",
        "01001100", "01001101", "01001110", "01001111",
        "01010000", "01010001", "01010010", "01010011",
        "01010100", "01010101", "01010110", "01010111",
        "01011000", "01011001", "01011010", "01011011",
        "01011100", "01011101", "01011110", "01011111",
        "01100000", "01100001", "01100010", "01100011",
        "01100100", "01100101", "01100110", "01100111",
        "01101000", "01101001", "01101010", "01101011",
        "01101100", "01101101", "01101110", "01101111",
        "01110000", "01110001", "01110010", "01110011",
        "01110100", "01110101", "01110110", "01110111",
        "01111000", "01111001", "01111010", "01111011",
        "01111100", "01111101", "01111110", "01111111",
        "10000000", "10000001", "10000010", "10000011",
        "10000100", "10000101", "10000110", "10000111",
        "10001000", "10001001", "10001010", "10001011",
        "10001100", "10001101", "10001110", "10001111",
        "10010000", "10010001", "10010010", "10010011",
        "10010100", "10010101", "10010110", "10010111",
        "10011000", "10011001", "10011010", "10011011",
        "10011100", "10011101", "10011110", "10011111",
        "10100000", "10100001", "10100010", "10100011",
        "10100100", "10100101", "10100110", "10100111",
        "10101000", "10101001", "10101010", "10101011",
        "10101100", "10101101", "10101110", "10101111",
        "10110000", "10110001", "10110010", "10110011",
        "10110100", "10110101", "10110110", "10110111",
        "10111000", "10111001", "10111010", "10111011",
        "10111100", "10111101", "10111110", "10111111",
        "11000000", "11000001", "11000010", "11000011",
        "11000100", "11000101", "11000110", "11000111",
        "11001000", "11001001", "11001010", "11001011",
        "11001100", "11001101", "11001110", "11001111",
        "11010000", "11010001", "11010010", "11010011",
        "11010100", "11010101", "11010110", "11010111",
        "11011000", "11011001", "11011010", "11011011",
        "11011100", "11011101", "11011110", "11011111",
        "11100000", "11100001", "11100010", "11100011",
        "11100100", "11100101", "11100110", "11100111",
        "11101000", "11101001", "11101010", "11101011",
        "11101100", "11101101", "11101110", "11101111",
        "11110000", "11110001", "11110010", "11110011",
        "11110100", "11110101", "11110110", "11110111",
        "11111000", "11111001", "11111010", "11111011",
        "11111100", "11111101", "11111110", "11111111",
    };

    const char byteToCharMap[256] =
    {
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        ' ','!','"','#','.','%','&','\'',
        '(',')','*','+',',','-','.','/',
        '0','1','2','3','4','5','6','7',
        '8','9',':',';','<','=','>','?',
        '@','A','B','C','D','E','F','G',
        'H','I','J','K','L','M','N','O',
        'P','Q','R','S','T','U','V','W',
        'X','Y','Z','[','\\',']','^','_',
        '`','a','b','c','d','e','f','g',
        'h','i','j','k','l','m','n','o',
        'p','q','r','s','t','u','v','w',
        'x','y','z','{','|','}','~','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.',
        '.','.','.','.','.','.','.','.'
    };

    const char *byteToHexMap[256] =
    {
        "00", "01", "02", "03", "04", "05", "06", "07",
        "08", "09", "0A", "0B", "0C", "0D", "0E", "0F",
        "10", "11", "12", "13", "14", "15", "16", "17",
        "18", "19", "1A", "1B", "1C", "1D", "1E", "1F",
        "20", "21", "22", "23", "24", "25", "26", "27",
        "28", "29", "2A", "2B", "2C", "2D", "2E", "2F",
        "30", "31", "32", "33", "34", "35", "36", "37",
        "38", "39", "3A", "3B", "3C", "3D", "3E", "3F",
        "40", "41", "42", "43", "44", "45", "46", "47",
        "48", "49", "4A", "4B", "4C", "4D", "4E", "4F",
        "50", "51", "52", "53", "54", "55", "56", "57",
        "58", "59", "5A", "5B", "5C", "5D", "5E", "5F",
        "60", "61", "62", "63", "64", "65", "66", "67",
        "68", "69", "6A", "6B", "6C", "6D", "6E", "6F",
        "70", "71", "72", "73", "74", "75", "76", "77",
        "78", "79", "7A", "7B", "7C", "7D", "7E", "7F",
        "80", "81", "82", "83", "84", "85", "86", "87",
        "88", "89", "8A", "8B", "8C", "8D", "8E", "8F",
        "90", "91", "92", "93", "94", "95", "96", "97",
        "98", "99", "9A", "9B", "9C", "9D", "9E", "9F",
        "A0", "A1", "A2", "A3", "A4", "A5", "A6", "A7",
        "A8", "A9", "AA", "AB", "AC", "AD", "AE", "AF",
        "B0", "B1", "B2", "B3", "B4", "B5", "B6", "B7",
        "B8", "B9", "BA", "BB", "BC", "BD", "BE", "BF",
        "C0", "C1", "C2", "C3", "C4", "C5", "C6", "C7",
        "C8", "C9", "CA", "CB", "CC", "CD", "CE", "CF",
        "D0", "D1", "D2", "D3", "D4", "D5", "D6", "D7",
        "D8", "D9", "DA", "DB", "DC", "DD", "DE", "DF",
        "E0", "E1", "E2", "E3", "E4", "E5", "E6", "E7",
        "E8", "E9", "EA", "EB", "EC", "ED", "EE", "EF",
        "F0", "F1", "F2", "F3", "F4", "F5", "F6", "F7",
        "F8", "F9", "FA", "FB", "FC", "FD", "FE", "FF"
    };

    const char *byteToOctalMap[256] =
    {
        "000", "001", "002", "003", "004", "005", "006", "007",
        "010", "011", "012", "013", "014", "015", "016", "017",
        "020", "021", "022", "023", "024", "025", "026", "027",
        "030", "031", "032", "033", "034", "035", "036", "037",
        "040", "041", "042", "043", "044", "045", "046", "047",
        "050", "051", "052", "053", "054", "055", "056", "057",
        "060", "061", "062", "063", "064", "065", "066", "067",
        "070", "071", "072", "073", "074", "075", "076", "077",
        "100", "101", "102", "103", "104", "105", "106", "107",
        "110", "111", "112", "113", "114", "115", "116", "117",
        "120", "121", "122", "123", "124", "125", "126", "127",
        "130", "131", "132", "133", "134", "135", "136", "137",
        "140", "141", "142", "143", "144", "145", "146", "147",
        "150", "151", "152", "153", "154", "155", "156", "157",
        "160", "161", "162", "163", "164", "165", "166", "167",
        "170", "171", "172", "173", "174", "175", "176", "177",
        "200", "201", "202", "203", "204", "205", "206", "207",
        "210", "211", "212", "213", "214", "215", "216", "217",
        "220", "221", "222", "223", "224", "225", "226", "227",
        "230", "231", "232", "233", "234", "235", "236", "237",
        "240", "241", "242", "243", "244", "245", "246", "247",
        "250", "251", "252", "253", "254", "255", "256", "257",
        "260", "261", "262", "263", "264", "265", "266", "267",
        "270", "271", "272", "273", "274", "275", "276", "277",
        "300", "301", "302", "303", "304", "305", "306", "307",
        "310", "311", "312", "313", "314", "315", "316", "317",
        "320", "321", "322", "323", "324", "325", "326", "327",
        "330", "331", "332", "333", "334", "335", "336", "337",
        "340", "341", "342", "343", "344", "345", "346", "347",
        "350", "351", "352", "353", "354", "355", "356", "357",
        "360", "361", "362", "363", "364", "365", "366", "367",
        "370", "371", "372", "373", "374", "375", "376", "377"
    };

    const u8 hexToByteMap[256] =
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 2, 3, 4, 5, 6, 7,
        8, 9, 0, 0, 0, 0, 0, 0,
        0,10,11,12,13,14,15, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0,10,11,12,13,14,15, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };
}

void Qt4_Translate::CharToByte(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask)
{
    if (mask)
    {
        for (u32 i = 0; i < src.size(); ++i)
            dst[i] = src[i ^ mask];
    }
    else
    {
        dst = std::vector< u8 >(src.begin(), src.end());
    }
}
void Qt4_Translate::CharToByte(std::vector< u8 > &dst, const QString &src, int mask)
{
    dst.resize(src.length());
    for (int i = 0; i < src.length(); ++i)
        dst[i] = src[i ^ mask].toAscii();
}


void Qt4_Translate::ByteToChar(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask)
{
    dst.erase(dst.begin(), dst.end());
    dst.reserve(src.size());
    for (unsigned int i = 0; i < src.size(); i++)
    {
        dst.push_back(Qt4_Translate::byteToCharMap[src[i ^ mask]]);
    }
}

void Qt4_Translate::HexToByte(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask)
{
    dst.erase(dst.begin(), dst.end());
    int start;

    if (src.size() % 2)
    {
        dst.reserve(src.size() / 2 + 1);
        dst.push_back(Qt4_Translate::hexToByteMap[src[0 ^ mask]]);
        start = 1;
    }
    else
    {
        start = 0;
        dst.reserve(src.size() / 2);
    }
    for (unsigned int i = start; i < src.size(); i += 2)
    {
        dst.push_back(Qt4_Translate::hexToByteMap[src[i ^ mask]] * 16 + Qt4_Translate::hexToByteMap[src[(i ^ mask)+1]]);
    }
}

void Qt4_Translate::HexToByte(std::vector< u8 > &dst, const QString &src, int mask)
{
    dst.erase(dst.begin(), dst.end());
    dst.reserve(src.length() / 2);
    int i = 0;
    if (src.length() % 2)
    {
        i = 1;
    }
    for (; i < src.length(); i += 2)
    {
        u8 hi = src[i ^ mask].toAscii();
        u8 lo = src[(i ^ mask)+1].toAscii();
        dst.push_back(Qt4_Translate::hexToByteMap[hi] * 16 + Qt4_Translate::hexToByteMap[lo]);
    }
}

void Qt4_Translate::OctalToByte(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask)
{
    dst.erase(dst.begin(), dst.end());
    dst.reserve(src.size() / 3);
    for (unsigned int i = 0; i + 2 < src.size(); i += 3)
    {
        dst.push_back(Qt4_Translate::hexToByteMap[src[i]] * 64 + Qt4_Translate::hexToByteMap[src[i+1]] * 8 + Qt4_Translate::hexToByteMap[src[i+2]]);
    }
}

void Qt4_Translate::BinaryToByte(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask)
{
    dst.erase(dst.begin(), dst.end());
    dst.reserve(src.size() / 8);
    for (unsigned int i = 0; i < src.size(); i += 8)
    {
        dst.push_back(Qt4_Translate::hexToByteMap[src[(i ^ mask)+0]] * 128 +
            Qt4_Translate::hexToByteMap[src[(i ^ mask)+1]] * 64 +
            Qt4_Translate::hexToByteMap[src[(i ^ mask)+2]] * 32 +
            Qt4_Translate::hexToByteMap[src[(i ^ mask)+3]] * 16 +
            Qt4_Translate::hexToByteMap[src[(i ^ mask)+4]] * 8 +
            Qt4_Translate::hexToByteMap[src[(i ^ mask)+5]] * 4 +
            Qt4_Translate::hexToByteMap[src[(i ^ mask)+6]] * 2 +
            Qt4_Translate::hexToByteMap[src[(i ^ mask)+7]] * 1);
    }
}

const char *Qt4_Translate::ByteToHex(u8 b)
{
    return Qt4_Translate::byteToHexMap[b];
}

void Qt4_Translate::ByteToHex(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask)
{
    const char *str;
    dst.erase(dst.begin(), dst.end());
    dst.reserve(src.size() * 2);
    for (unsigned int i = 0; i < src.size(); i++)
    {
        str = Qt4_Translate::byteToHexMap[src[(i ^ mask)]];
        dst.push_back(*(str+0));
        dst.push_back(*(str+1));
    }
}

void Qt4_Translate::ByteToOctal(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask)
{
    dst.erase(dst.begin(), dst.end());
    dst.reserve(src.size() * 3);

    const char *str;
    for (int i = 0; i < (int)src.size(); ++i)
    {
        str = Qt4_Translate::byteToOctalMap[src[(i ^ mask)]];
        dst.insert(dst.end(), str, str + 3);
    }
}

void Qt4_Translate::ByteToBinary(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask)
{
    dst.erase(dst.begin(), dst.end());
    dst.reserve(src.size() * 8);

    const char *str;
    for (int i = 0; i < (int)src.size(); ++i)
    {
        str = Qt4_Translate::byteToBinaryMap[src[(i ^ mask)]];
        dst.insert(dst.end(), str, str + 8);
    }
}

void Qt4_Translate::ByteToChar(QString &dst, const u8 *src, int len, int mask)
{
    dst = "";
    for (int i = 0; i < len; i++)
    {
        dst += Qt4_Translate::byteToCharMap[*((const u8 *)((intptr_t)src++ ^ mask))];
    }
}

void Qt4_Translate::ByteToHex(QString &dst, const u8 *src, int len, int mask)
{
    dst = "";
    for (int i = 0; i < len; i++)
    {
        dst += Qt4_Translate::byteToHexMap[*((const u8 *)((intptr_t)src++ ^ mask))];
    }
}

void Qt4_Translate::ByteToOctal(QString &dst, const u8 *src, int len, int mask)
{
    dst = "";
    for (int i = 0; i < len; ++i)
    {
        dst += Qt4_Translate::byteToOctalMap[*((const u8 *)((intptr_t)src++ ^ mask))];
    }
}

void Qt4_Translate::ByteToBinary(QString &dst, const u8 *src, int len, int mask)
{
    dst = "";
    for (int i = 0; i < len; ++i)
    {
        dst += Qt4_Translate::byteToBinaryMap[*((const u8 *)((intptr_t)src++ ^ mask))];
    }
}

#if 0
void QTranslate::ByteToChar(QString &dst, const std::vector< u8 > &src)
{
    dst = "";
    for (unsigned int i = 0; i < src.size(); i++)
    {
        dst += QTranslate::byteToCharMap[src[i]];
    }
}

void QTranslate::ByteToHex(QString &dst, const std::vector< u8 > &src)
{
    dst = "";
    for (int i = 0; i < src.size(); i++)
    {
        dst += QTranslate::byteToHexMap[src[i]];
    }
}

void QTranslate::ByteToOctal(std::vector< u8 > &dst, const std::vector< u8 > &src)
{
    dst.erase(dst.begin(), dst.end());
    dst.reserve(src.size() * 3);

    std::vector< u8 >::const_iterator i;
    const char *str;
    for (i = src.begin(); i != src.end(); ++i)
    {
        str = QTranslate::byteToOctalMap[*i];
        dst.insert(dst.end(), str, str + 3);
    }
}

void QTranslate::ByteToOctal(QString &dst, const std::vector< u8 > &src)
{
    dst = "";
    std::vector< u8 >::const_iterator i;
    for (i = src.begin(); i != src.end(); ++i)
    {
        dst += QTranslate::byteToOctalMap[*i];
    }
}

void QTranslate::ByteToBinary(QString &dst, const std::vector< u8 > &src)
{
    dst = "";
    std::vector< u8 >::const_iterator i;
    for (i = src.begin(); i != src.end(); ++i)
    {
        dst += QTranslate::byteToBinaryMap[*i];
    }
}
#endif
