#include "stdafx.h"

#include "IsoFile.h"

#include "../../log.h"

using namespace std;

IsoFile::IsoFile()
{
	internalReader = 0;
	currentSectorNumber = 0;
	currentOffset = 0;
	sectorOffset = 0;
	maxOffset = 0;
}

IsoFile::IsoFile(const IsoFile& file)
{
	fileEntry = file.fileEntry;
	internalReader = file.internalReader;
	currentSectorNumber=file.currentSectorNumber;
	currentOffset = file.currentOffset;
	sectorOffset = file.sectorOffset;
	maxOffset = file.maxOffset;

	if(maxOffset>0)
		internalReader->ReadBlock(currentSectorNumber,currentSector,1);
}

IsoFile::IsoFile(fs_BlockDevice* reader, FileInfo _fileEntry)
{
	Assign(reader,_fileEntry);
}

void IsoFile::Assign(fs_BlockDevice* reader, FileInfo _fileEntry)
{
	fileEntry = _fileEntry;

	internalReader = reader;
	currentSectorNumber=fileEntry.lba;
	currentOffset = 0;
	sectorOffset = 0;
	maxOffset = fileEntry.size;

	if(maxOffset>0)
		internalReader->ReadBlock(currentSectorNumber,currentSector,1);
}

void IsoFile::seek(__int64 offset)
{
	__int64 endOffset = offset;

	if(offset<0)
	{
		errorf(isoFileSystem, "Seek offset out of bounds.");
		return;
	}

	int oldSectorNumber = currentSectorNumber;
	__int64 newOffset = endOffset;
	int newSectorNumber = fileEntry.lba + (int)(newOffset / sectorLength);
	if(oldSectorNumber != newSectorNumber)
	{
		internalReader->ReadBlock(newSectorNumber, currentSector, 1);
	}
	currentOffset = newOffset;
	currentSectorNumber = newSectorNumber;
	sectorOffset = (int)(currentOffset % sectorLength);
}

void IsoFile::seek(__int64 offset, int ref_position)
{
	if(ref_position == SEEK_SET)
		seek(offset);

	if(ref_position == SEEK_CUR)
		seek(currentOffset+offset);

	if(ref_position == SEEK_END)
		seek(fileEntry.size+offset);
}

void IsoFile::reset()
{
	seek(0);
}

__int64 IsoFile::skip(__int64 n)
{
	__int64 oldOffset = currentOffset;

	if(n<0)
		return n;

	seek(currentOffset+n);

	return currentOffset-oldOffset;
}

__int64 IsoFile::getFilePointer()
{
	return currentOffset;
}

bool IsoFile::eof()
{
	return (currentOffset == maxOffset);
}

void IsoFile::makeDataAvailable()
{
	if (sectorOffset >= sectorLength) {
		currentSectorNumber++;
		internalReader->ReadBlock(currentSectorNumber, currentSector, 1);
		sectorOffset -= sectorLength;
	}
}

int IsoFile::read()
{
	if(currentOffset >= maxOffset)
	{
		return -1;
	}

	makeDataAvailable();

	currentOffset++;

	return currentSector[sectorOffset++];
}

int IsoFile::internalRead(u8* b, int off, int len)
{
	if (len > 0)
	{
		if (len > (maxOffset - currentOffset))
		{
			len = (int) (maxOffset - currentOffset);
		}

		memcpy(b + off, currentSector + sectorOffset, len);

		sectorOffset += len;
		currentOffset += len;
	}

	return len;
}

int IsoFile::read(u8* b, int len)
{
	if (b == NULL)
	{
		errorf(isoFileSystem,"Null pointer in param 'b'.");
	}

	if (len < 0)
	{
		errorf(isoFileSystem,"len<0.");
	}

	int off=0;

	int totalLength = 0;

	if ((len > 0) && (currentOffset < maxOffset)) 
	{
		int firstSector = internalRead(b, off, min(maxOffset-currentOffset,min(len, sectorLength - sectorOffset)));
		off += firstSector;
		len -= firstSector;
		totalLength += firstSector;

		// Read whole sectors
		while ((len >= sectorLength) && (currentOffset < maxOffset))
		{
			makeDataAvailable();
			int n = internalRead(b, off, sectorLength);
			off += n;
			len -= n;
			totalLength += n;
		}

		// Read remaining, if any
		if ((len > 0) && (currentOffset < maxOffset)) 
		{
			makeDataAvailable();
			int lastSector = internalRead(b, off, len);
			totalLength += lastSector;
		}
	}

	return totalLength;
}

string IsoFile::readLine()
{
	string s;
	char c;

	s.clear();
	do {
		if(eof())
			break;

		c = read();

		if((c=='\n')||(c=='\r')||(c<=0))
			break;

		s.append(1,c);
	} while(true);

	return s;
}

wstring IsoFile::readLineW()
{
	wstring s;
	wchar_t c;

	s.clear();
	do {
		if(eof())
			break;

		c = read<wchar_t>();

		if((c==L'\n')||(c==L'\r')||(c==0))
			break;

		s.append(1,c);
	} while(true);

	return s;
}

__int64 IsoFile::getLength()
{
	return maxOffset;
}

const FileInfo& IsoFile::getEntry()
{
	return fileEntry;
}

IsoFile::~IsoFile(void) 
{

}
