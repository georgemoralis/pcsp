#include "stdafx.h"
#include <string>
#include <list>
#include "psf.h"
#include "log.h"

char PsfMagic[] = "\0PSF";

psf_loader::psf_loader()
{
	size = 0;

	sizeDirty = true;
	tablesDirty = true;
	indexCount = 0;

}
psf_loader::~psf_loader()
{

}
void psf_loader::read(u8 *fileptr)
{
	u8   *psflabels;
	u8   *psfdata;
	u32 i;

	//step1: check the first 4 bytes is it's a psf
	if (::memcmp(PsfMagic, fileptr, 4))
	{
		errorf(loader, "This file isn't a PSF file! [PSF Magic == 0x%08x]\n", *(u32 *)PsfMagic);
		return;
	}
	psfheader   = (struct Psf_header *)fileptr;
	psfsections = (struct Psf_section *)(fileptr + sizeof(struct Psf_header));
	psflabels   = fileptr + psfheader->keyTableOffset;
	psfdata     = fileptr + psfheader->valueTableOffset;

	for (i = 0, sect = psfsections; i < psfheader->indexEntryCount; i++, sect++)
	{
		PSFKeyValuePair *pair=new PSFKeyValuePair();
		pair->read(sect);
		pairList.append(pair);
	}
    // key/pairs
	 QMutableLinkedListIterator<PSFKeyValuePair*> pairIterator(pairList);
     while (pairIterator.hasNext())
	 {
	   //read the keys
	   u8 *test = &psflabels[pairIterator.next()->section->keyOffset];
	   QString merge((const char*)test);
       pairIterator.value()->key=merge.trimmed();//trimm whitespaces
	   //infof(loader, "Loading %s...", merge.toStdString().c_str());
       //read the data part
	   switch(pairIterator.value()->section->dataType)
	   {
         case PSF_DATA_TYPE_BINARY:
			 pairIterator.value()->data = QString(*(unsigned char *)&psfdata[pairIterator.value()->section->valueOffset]);
			 break;
		 case PSF_DATA_TYPE_STRING:
			 pairIterator.value()->data = QString((const char *)&psfdata[pairIterator.value()->section->valueOffset]);
			 break;
		 case PSF_DATA_TYPE_INT32:
             pairIterator.value()->data = QString("%1").arg(*(int *)&psfdata[pairIterator.value()->section->valueOffset]);
			 break;
		default:
			 errorf(loader, "Unhandled datatype %x in key %s",pairIterator.value()->section->dataType,merge.toStdString().c_str());
			 break;
	   }
		
     }
	sizeDirty = true;
	tablesDirty = false;
	calculateSize();
}
void psf_loader::write(const char *filepath) 
{
	// Open file.
	QFile file(filepath);
	file.open(QIODevice::WriteOnly);

	// Assign data stream.
	QDataStream fs(&file);
	fs.setByteOrder(QDataStream::LittleEndian);

	QMutableLinkedListIterator<PSFKeyValuePair*> pairIterator(pairList);
	psfheader = (struct Psf_header *)malloc(sizeof(struct Psf_header));

	// Set default header values.
	psfheader->magic = (u32)PSF_IDENT;
	psfheader->version = (u32)0x0101;

	// Calculate tables.
	if(tablesDirty) {
		calculateTables();
	}

	// Output header fields.
	fs << psfheader->magic; 
	fs << psfheader->version;
	fs << psfheader->keyTableOffset;
	fs << psfheader->valueTableOffset;
	fs << psfheader->indexEntryCount;

	// Output section fields for each pair.
	while (pairIterator.hasNext())
	{
		PSFKeyValuePair* value = pairIterator.next();

		fs << value->section->keyOffset; 
		fs << value->section->padding;
		fs << value->section->dataType;
		fs << value->section->dataSize;
		fs << value->section->dataSizePadded;
		fs << value->section->valueOffset;
		 
	}
	pairIterator.toFront();

	// Position the stream and output the key/data pairs.
	while (pairIterator.hasNext())
	{
		PSFKeyValuePair* value = pairIterator.next();

		fs.device()->seek(psfheader->keyTableOffset + value->section->keyOffset);
		fs.writeRawData(value->key.toLatin1().data(), value->key.length()); 
		fs.device()->seek(psfheader->valueTableOffset + value->section->valueOffset);
		fs.writeRawData(value->data.toLatin1().data(), value->data.length());
		
		// Padding.
		for(u32 i = 0; i < (value->section->dataSizePadded - value->data.length()); i++) {
			fs.device()->putChar(0x00);
		}
	}

	file.close();
	free(psfheader);
}
void psf_loader::calculateSize()
{
	sizeDirty = false;
	size = 0;

	if (tablesDirty)
	{
		calculateTables();
	}
	QMutableLinkedListIterator<PSFKeyValuePair*> pairIterator(pairList);
	while (pairIterator.hasNext())
	{
		u32 keyHighBound = psfheader->keyTableOffset + pairIterator.next()->section->keyOffset + pairIterator.value()->key.size() + 1;
		u32 valueHighBound = psfheader->valueTableOffset + pairIterator.value()->section->valueOffset + pairIterator.value()->section->dataSizePadded;
		if (keyHighBound > size)
			size = keyHighBound;
		if (valueHighBound > size)
			size = valueHighBound;
	}
}
void psf_loader::calculateTables() {  
	tablesDirty = false;

	psfheader->indexEntryCount = (u32)indexCount;
	psfheader->keyTableOffset = (u32)(5 * 4 + psfheader->indexEntryCount * 0x10);
	psfheader->valueTableOffset = psfheader->keyTableOffset; 
	
	QMutableLinkedListIterator<PSFKeyValuePair*> pairIterator(pairList);

	while (pairIterator.hasNext())
	{
		PSFKeyValuePair* value = pairIterator.next();
		psfheader->valueTableOffset += (u32)(value->key.length() + 1); 		
	}
	psfheader->valueTableOffset = (u32)((psfheader->valueTableOffset + 3) & ~3); 
	
	pairIterator.toFront();

	int keyRunningOffset = 0; 
	int valueRunningOffset = 0; 

	while (pairIterator.hasNext())
	{
		PSFKeyValuePair* value = pairIterator.next();

		value->section->keyOffset = keyRunningOffset; 
		keyRunningOffset += value->key.length() + 1;
		
		value->section->valueOffset = valueRunningOffset; 
		valueRunningOffset += value->section->dataSizePadded;
	}
} 
void psf_loader::printpsf()
{
	QMutableLinkedListIterator<PSFKeyValuePair*> pairIterator(pairList);
	while (pairIterator.hasNext())
	{
       if(pairIterator.next()->section->dataType==PSF_DATA_TYPE_STRING)
	   {
          infof(loader, "%s = %s", pairIterator.value()->key.toStdString().c_str(), pairIterator.value()->data.toStdString().c_str());
	   }
	   if(pairIterator.value()->section->dataType==PSF_DATA_TYPE_INT32)
	   {
          infof(loader, "%s = %d", pairIterator.value()->key.toStdString().c_str(), pairIterator.value()->data.toInt());
	   }
	   
	}
}
QString psf_loader::getString(QString Key)
{
	QMutableLinkedListIterator<PSFKeyValuePair*> pairIterator(pairList);
	while (pairIterator.hasNext())
	{
		if(pairIterator.next()->key == Key)
		{
			return pairIterator.value()->data;
		}
	}
	return "";

}
//used for strings that are in UTF8 like "TITLE"
QString psf_loader::getPrintableString(QString Key)
{
	QMutableLinkedListIterator<PSFKeyValuePair*> pairIterator(pairList);
	while (pairIterator.hasNext())
	{
		if(pairIterator.next()->key == Key)
		{
			return QString::fromUtf8(pairIterator.value()->data.toLatin1().data());
		}
	}
	return "";
}
u32 psf_loader::getInteger(QString Key)
{
	QMutableLinkedListIterator<PSFKeyValuePair*> pairIterator(pairList);
	while (pairIterator.hasNext())
	{
		if(pairIterator.next()->key == Key)
		{
			return pairIterator.value()->data.toUInt();
		}
	}
	return 0;
}
void psf_loader::putString(QString Key, QString Data, int rawlen)
{
	PSFKeyValuePair* newKey = new PSFKeyValuePair(Key, PSF_DATA_TYPE_STRING, Data.toLatin1().length() + 1, (rawlen + 3) & ~3, Data.toLatin1().data()); 
	pairList.append(newKey);

	sizeDirty = true;
	tablesDirty = true;
	indexCount++;
}
void psf_loader::putInteger(QString Key, int Data)
{
	PSFKeyValuePair* newKey = new PSFKeyValuePair(Key, PSF_DATA_TYPE_INT32, 4, 4, QString(Data)); 
	pairList.append(newKey);

	sizeDirty = true;
	tablesDirty = true;
	indexCount++;
}
