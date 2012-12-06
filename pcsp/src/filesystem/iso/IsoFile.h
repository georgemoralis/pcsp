#pragma once

#include "../genericfilesystem.h"

#include "filesystem/blockDevice.h"

class IsoFile
{
public:
	static const int sectorLength = 2048;

private:
	FileInfo fileEntry;

	__int64 currentOffset;
	__int64 maxOffset;

	int currentSectorNumber;
	u8  currentSector[sectorLength];
	int sectorOffset;

	fs_BlockDevice* internalReader;

	void makeDataAvailable();
	int  internalRead(u8* b, int off, int len);

public:
	IsoFile();
	IsoFile(const IsoFile& file);
	IsoFile(fs_BlockDevice* reader, FileInfo fileEntry);

	void Assign(fs_BlockDevice* reader, FileInfo fileEntry);

	void seek(__int64 offset);
	void seek(__int64 offset, int ref_position);
	void reset();

	__int64 skip(__int64 n);
	__int64 getFilePointer();

	bool eof();
	int  read();
	int  read(u8* b, int len);

	// Tool to read a specific value type, including structs.
	template<class T>
	T read()
	{
		if(sizeof(T)==1)
			return (T)read();
		else
		{
			T t;
			read((u8*)&t,sizeof(t));
			return t;
		}
	}

	std::string readLine();   // Assume null-termination
	std::wstring readLineW(); // (this one too)

	__int64 getLength();

	const FileInfo& getEntry();
	
	~IsoFile(void);
};
