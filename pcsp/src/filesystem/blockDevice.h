#pragma once

#include "common/types.h"

//compressed ISO(9660) header format
typedef struct ciso_header
{
    unsigned char      magic[4];    // +00 : 'C','I','S','O'                 
    u32                header_size;	// +04 : header size (==0x18)
    unsigned long long total_bytes;	// +08 : number of original data size
    u32                block_size;	// +10 : number of compressed block size
    unsigned char      ver;			// +14 : version 01                      
    unsigned char      align;       // +15 : align of index value            
    unsigned char      rsv_06[2];   // +16 : reserved                        
} CISO_H;

class fs_BlockDevice
{
public:
    virtual ~fs_BlockDevice() {}
    
    virtual bool    ReadBlock(int blockNumber, u8 *outPtr,int size) = 0;
            int     GetBlockSize() const { return 2048; }
    virtual int     GetBlockCount() = 0;
};


class fs_CSOFileBlockDevice : public fs_BlockDevice
{
    std::string filename;
    FILE *f;
    u32 *index;
    int indexShift;
    u32 blockSize;
    int numBlocks;

public:
    fs_CSOFileBlockDevice(std::string _filename);
    ~fs_CSOFileBlockDevice();

    bool            ReadBlock(int blockNumber, u8 *outPtr,int size);
    int             GetBlockCount();
};



class fs_ISOFileBlockDevice : public fs_BlockDevice
{
    std::string filename;
    FILE *f;
    size_t filesize;

public:
    fs_ISOFileBlockDevice(std::string _filename);
    ~fs_ISOFileBlockDevice();

    bool            ReadBlock(int blockNumber, u8 *outPtr,int size);
    int             GetBlockCount();
};

