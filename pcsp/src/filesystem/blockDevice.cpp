#include "stdafx.h"
#include "log.h"

extern "C"
{
#include "zlib.h"
};

#include "blockDevice.h"

fs_ISOFileBlockDevice::fs_ISOFileBlockDevice(std::string _filename)
: filename(_filename)
{
	f = fopen(_filename.c_str(), "rb");
	fseek(f,0,SEEK_END);
	filesize = ftell(f);
	fseek(f,0,SEEK_SET);
}

fs_ISOFileBlockDevice::~fs_ISOFileBlockDevice()
{
	fclose(f);
}

bool fs_ISOFileBlockDevice::ReadBlock(int blockNumber, u8 *outPtr,int size) 
{
	fseek(f, blockNumber * GetBlockSize(), SEEK_SET);
	fread(outPtr, 2048, size, f);
	return true;
}

int fs_ISOFileBlockDevice::GetBlockCount()
{
    return (filesize + GetBlockSize() - 1)/GetBlockSize();
}

fs_CSOFileBlockDevice::fs_CSOFileBlockDevice(std::string _filename)
: filename(_filename)
{
	f = fopen(filename.c_str(), "rb");
	CISO_H hdr;
	fread(&hdr, 1, sizeof(CISO_H), f);
	if (memcmp(hdr.magic, "CISO", 4) != 0)
	{
		warnf(isoFileSystem,"CSO header doesn't appear valid");
	}
	else
	{
		infof(isoFileSystem,"CSO header valid continue normal");
	}
	if (hdr.ver > 1)
	{
		warnf(isoFileSystem,"CSO version >1");
	}

	int hdrSize = hdr.header_size;
	blockSize = hdr.block_size;
	if (blockSize != 0x800)
	{
		errorf(isoFileSystem,"Unsupported blockSize! (!=0x800)");
	}
	indexShift = hdr.align;
	u64 totalSize = hdr.total_bytes;
	numBlocks = (int)(totalSize / blockSize);
	infof(isoFileSystem,"CSO hdrSize=%i numBlocks=%i align=%i", hdrSize, numBlocks, indexShift);

	int indexSize = numBlocks + 1;

	index = new u32[indexSize];
	fread(index, 4, indexSize, f);
}

fs_CSOFileBlockDevice::~fs_CSOFileBlockDevice()
{
	fclose(f);
	delete [] index;
}

static u8 inbuffer[4096]; //too big
static z_stream z;
static u8 inbuffer2[4096]; //too big

bool fs_CSOFileBlockDevice::ReadBlock(int blockNumber, u8 *outPtr,int size) 
{
	while(size>0)
	{
		u32 idx = index[blockNumber];
		u32 idx2 = index[blockNumber+1];

		int plain = idx & 0x80000000;

		idx = (idx & 0x7FFFFFFF) << indexShift;
		idx2 = (idx2 & 0x7FFFFFFF) << indexShift;

		u32 compressedReadPos = idx;
		u32 compressedReadSize = idx2 - idx;

		if (plain)
		{
			fseek(f, compressedReadPos, SEEK_SET);
			fread(outPtr, compressedReadSize, 1, f);

			if (compressedReadSize<2048)
            {
                memset(outPtr+compressedReadSize, 0, 2048-compressedReadSize);
            }
		}
		else
		{
			fseek(f, compressedReadPos, SEEK_SET);
			fread(inbuffer, compressedReadSize, 1, f);

			memset(outPtr, 0, 2048);
			z.zalloc = Z_NULL;
			z.zfree = Z_NULL;
			z.opaque = Z_NULL;
			if (inflateInit2(&z, -15) != Z_OK)
			{
				errorf(isoFileSystem, "deflateInit : %s\n", (z.msg) ? z.msg : "???");
				return 1;
			}
			z.avail_in = compressedReadSize;
			z.next_out = outPtr;
			z.avail_out = blockSize;
			z.next_in = inbuffer;

			int status = inflate(&z, Z_FULL_FLUSH);
			if (status != Z_STREAM_END)
			{
				errorf(isoFileSystem, "block %d:inflate : %s[%d]\n", blockNumber, (z.msg) ? z.msg : "error", status);
				return 1;
			}
			u32 cmp_size = blockSize - z.avail_out;
			if (cmp_size != blockSize)
			{
				errorf(isoFileSystem, "block %d : block size error %d != %d\n", blockNumber, cmp_size, blockSize);
				return 1;
			}

			if (inflateEnd(&z) != Z_OK)
			{
				errorf(isoFileSystem, "cannot end inflation");
			}
		}

		outPtr+=2048;
		blockNumber++;
		size--;
	}
	return 1;
}

int fs_CSOFileBlockDevice::GetBlockCount()
{
    return numBlocks;
}