/*
 *  14/06/2022 - synced with jpcsp 14/06/2022 - a5e0793
 */
#include "..\PCSPCommon.h"
#include "PSF.h"

/*TODO*/  //    private LinkedList<PSFKeyValuePair> pairList;
/*TODO*/  //
/*TODO*/  //
PSF::PSF(u32 psfOffset) {
    this->psfOffset = psfOffset;
    size = 0;

    sizeDirty = true;
    tablesDirty = true;
    /*TODO*/  //
    /*TODO*/  //        ident = PSF_IDENT;
    /*TODO*/  //        version = 0x0101;
    /*TODO*/  //
    /*TODO*/  //        pairList = new LinkedList<PSFKeyValuePair>();
    /*TODO*/  //
}
PSF::PSF() : PSF(0) {}

void PSF::read(std::ifstream &f) 
{ 
    psfOffset = f.tellg();
    PsfHeader hdr;
    f.read((char *)&hdr, sizeof(hdr));
    if (hdr.ident != PSF_IDENT) {
/*TODO*/  //            System.out.println("Not a valid PSF file (ident=" + String.format("%08X", ident) + ")");
                return;
    }
    // index table
    for (int i = 0; i < hdr.indexEntryCount; i++) {
        PSFKeyValuePair *pair = new PSFKeyValuePair();
        pair->read(f);
        pairList.push_back(pair);
    }
    // key/pairs
    for (auto pair : pairList) {
        f.seekg(psfOffset + hdr.keyTableOffset + pair->PsfSection.keyOffset);
        char c;
        f.read(&c, 1);
        while (c != 0) {
            pair->key.append(&c, 0, 1);
            f.read(&c, 1);
        }
        f.seekg(psfOffset + hdr.valueTableOffset + pair->PsfSection.valueOffset);         
        switch (pair->PsfSection.dataType) {
                   case PSF_DATA_TYPE_BINARY:
                        pair->data.resize(pair->PsfSection.dataSize;
                        f.read((char*)&pair->data[0], pair->PsfSection.dataSize);
                       break;
                   case PSF_DATA_TYPE_STRING:
                       pair->data.resize(pair->PsfSection.dataSize + 1);
                       f.read((char *)&pair->data[0], pair->PsfSection.dataSize);
                       pair->data[pair->PsfSection.dataSize] = 0;
                       break;
                  case PSF_DATA_TYPE_INT32:
                       f.read((char *)&pair->number, 4);
                       pair->data.resize(4);
                       std::sprintf((char*)&pair->data[0], "%d", pair->number);
                    break;
                    default:
                      assert(0);
                    
    /*TODO*/  //                    System.out.println(String.format("offset=%08X key='%s' unhandled data type %d
              //                    [len=%d]",
    /*TODO*/  //                        keyTableOffset + pair.keyOffset, pair.key, pair.dataType, pair.dataSize));
                        break;
                }
    }
    /*TODO*/  //
    /*TODO*/  //        sizeDirty = true;
    /*TODO*/  //        tablesDirty = false;
    /*TODO*/  //        calculateSize();
}
/*TODO*/  //    public void write(RandomAccessFile output) throws IOException {
/*TODO*/  //    	byte[] buffer = new byte[size()];
/*TODO*/  //    	ByteBuffer byteBuffer = ByteBuffer.wrap(buffer);
/*TODO*/  //    	write(byteBuffer);
/*TODO*/  //
/*TODO*/  //    	// Write the file and truncate it to the correct length
/*TODO*/  //    	output.write(buffer);
/*TODO*/  //    	output.setLength(buffer.length);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    // assumes we want to write at the start of the buffer, and that the current buffer position is 0
/*TODO*/  //    // doesn't handle psfOffset
/*TODO*/  //    public void write(ByteBuffer f) {
/*TODO*/  //        if (indexEntryCount != pairList.size())
/*TODO*/  //            throw new RuntimeException("incremental size and actual size do not match! " + indexEntryCount +
          //            "/" + pairList.size());
/*TODO*/  //
/*TODO*/  //        if (tablesDirty) {
/*TODO*/  //            calculateTables();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        // header
/*TODO*/  //        writeWord(f, ident);
/*TODO*/  //        writeWord(f, version);
/*TODO*/  //        writeWord(f, keyTableOffset);
/*TODO*/  //        writeWord(f, valueTableOffset);
/*TODO*/  //        writeWord(f, indexEntryCount);
/*TODO*/  //
/*TODO*/  //        // index table
/*TODO*/  //        for (PSFKeyValuePair pair : pairList) {
/*TODO*/  //            pair.write(f);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        // key/value pairs
/*TODO*/  //
/*TODO*/  //        for (PSFKeyValuePair pair : pairList) {
/*TODO*/  //            f.position(keyTableOffset + pair.keyOffset);
/*TODO*/  //            //System.err.println("PSF write key   fp=" + f.position() + " datalen=" + (pair.key.length() +
          //            1) + " top=" + (f.position() + pair.key.length() + 1));
/*TODO*/  //            writeStringZ(f, pair.key);
/*TODO*/  //
/*TODO*/  //            f.position(valueTableOffset + pair.valueOffset);
/*TODO*/  //            //System.err.println("PSF write value fp=" + f.position() + " datalen=" + (pair.dataSizePadded)
          //            + " top=" + (f.position() + pair.dataSizePadded));
/*TODO*/  //            switch(pair.dataType) {
/*TODO*/  //                case PSF_DATA_TYPE_BINARY:
/*TODO*/  //                    f.put((byte[])pair.data);
/*TODO*/  //                    break;
/*TODO*/  //
/*TODO*/  //                case PSF_DATA_TYPE_STRING:
/*TODO*/  //                    String s = (String)pair.data;
/*TODO*/  //                    f.put(s.getBytes(Constants.charset));
/*TODO*/  //                    writeByte(f, (byte)0);
/*TODO*/  //                    break;
/*TODO*/  //
/*TODO*/  //                case PSF_DATA_TYPE_INT32:
/*TODO*/  //                    writeWord(f, (Integer)pair.data);
/*TODO*/  //                    break;
/*TODO*/  //
/*TODO*/  //                default:
/*TODO*/  //                    System.out.println("not writing unhandled data type " + pair.dataType);
/*TODO*/  //                    break;
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public Object get(String key) {
/*TODO*/  //        for (PSFKeyValuePair pair : pairList) {
/*TODO*/  //            if (pair.key.equals(key))
/*TODO*/  //                return pair.data;
/*TODO*/  //        }
/*TODO*/  //        return null;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public String getString(String key) {
/*TODO*/  //        Object obj = get(key);
/*TODO*/  //        if (obj != null)
/*TODO*/  //            return (String)obj;
/*TODO*/  //        return null;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    /** kxploit patcher tool adds "\nKXPloit Boot by PSP-DEV Team" */
/*TODO*/  //    public String getPrintableString(String key) {
/*TODO*/  //        String rawString = getString(key);
/*TODO*/  //        if (rawString == null) {
/*TODO*/  //        	return null;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        StringBuilder sb = new StringBuilder();
/*TODO*/  //        for (int i = 0; i < rawString.length(); i++) {
/*TODO*/  //            char c = rawString.charAt(i);
/*TODO*/  //            if (c == '\0' || c == '\n')
/*TODO*/  //                break;
/*TODO*/  //            sb.append(rawString.charAt(i));
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return sb.toString();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getNumeric(String key) {
/*TODO*/  //        Object obj = get(key);
/*TODO*/  //        if (obj != null)
/*TODO*/  //            return (Integer)obj;
/*TODO*/  //        return 0;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void put(String key, byte[] data) {
/*TODO*/  //        PSFKeyValuePair pair = new PSFKeyValuePair(key, PSF_DATA_TYPE_BINARY, data.length, data);
/*TODO*/  //        pairList.add(pair);
/*TODO*/  //
/*TODO*/  //        sizeDirty = true;
/*TODO*/  //        tablesDirty = true;
/*TODO*/  //        indexEntryCount++;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void put(String key, String data, int rawlen) {
/*TODO*/  //        byte[] b = (data.getBytes(Constants.charset));
/*TODO*/  //
/*TODO*/  //        //if (b.length != data.length())
/*TODO*/  //        //    System.out.println("put string '" + data + "' size mismatch. UTF-8=" + b.length + " regular="
          //        + (data.length() + 1));
/*TODO*/  //
/*TODO*/  //        //PSFKeyValuePair pair = new PSFKeyValuePair(key, PSF_DATA_TYPE_STRING, data.length() + 1, rawlen,
          //        data);
/*TODO*/  //        PSFKeyValuePair pair = new PSFKeyValuePair(key, PSF_DATA_TYPE_STRING, b.length + 1, rawlen, data);
/*TODO*/  //        pairList.add(pair);
/*TODO*/  //
/*TODO*/  //        sizeDirty = true;
/*TODO*/  //        tablesDirty = true;
/*TODO*/  //        indexEntryCount++;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void put(String key, String data) {
/*TODO*/  //        byte[] b = (data.getBytes(Constants.charset));
/*TODO*/  //        //int rawlen = data.length() + 1;
/*TODO*/  //        int rawlen = b.length + 1;
/*TODO*/  //
/*TODO*/  //        put(key, data, (rawlen + 3) & ~3);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void put(String key, int data) {
/*TODO*/  //        PSFKeyValuePair pair = new PSFKeyValuePair(key, PSF_DATA_TYPE_INT32, 4, data);
/*TODO*/  //        pairList.add(pair);
/*TODO*/  //
/*TODO*/  //        sizeDirty = true;
/*TODO*/  //        tablesDirty = true;
/*TODO*/  //        indexEntryCount++;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void calculateTables() {
/*TODO*/  //        tablesDirty = false;
/*TODO*/  //
/*TODO*/  //        // position the key table after the index table and before the value table
/*TODO*/  //        // 20 byte PSF header
/*TODO*/  //        // 16 byte per index entry
/*TODO*/  //        keyTableOffset = 5 * 4 + indexEntryCount * 0x10;
/*TODO*/  //
/*TODO*/  //
/*TODO*/  //        // position the value table after the key table
/*TODO*/  //        valueTableOffset = keyTableOffset;
/*TODO*/  //
/*TODO*/  //        for (PSFKeyValuePair pair : pairList) {
/*TODO*/  //            // keys are not aligned
/*TODO*/  //            valueTableOffset += pair.key.length() + 1;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        // 32-bit align for data start
/*TODO*/  //        valueTableOffset = (valueTableOffset + 3) & ~3;
/*TODO*/  //
/*TODO*/  //
/*TODO*/  //        // index table
/*TODO*/  //        int keyRunningOffset = 0;
/*TODO*/  //        int valueRunningOffset = 0;
/*TODO*/  //
/*TODO*/  //        for (PSFKeyValuePair pair : pairList) {
/*TODO*/  //            pair.keyOffset = keyRunningOffset;
/*TODO*/  //            keyRunningOffset += pair.key.length() + 1;
/*TODO*/  //
/*TODO*/  //            pair.valueOffset = valueRunningOffset;
/*TODO*/  //            valueRunningOffset += pair.dataSizePadded;
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void calculateSize() {
/*TODO*/  //        sizeDirty = false;
/*TODO*/  //        size = 0;
/*TODO*/  //
/*TODO*/  //        if (tablesDirty) {
/*TODO*/  //            calculateTables();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        for (PSFKeyValuePair pair : pairList) {
/*TODO*/  //            int keyHighBound = keyTableOffset + pair.keyOffset + pair.key.length() + 1;
/*TODO*/  //            int valueHighBound = valueTableOffset + pair.valueOffset + pair.dataSizePadded;
/*TODO*/  //            if (keyHighBound > size)
/*TODO*/  //                size = keyHighBound;
/*TODO*/  //            if (valueHighBound > size)
/*TODO*/  //                size = valueHighBound;
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int size() {
/*TODO*/  //        if (sizeDirty) {
/*TODO*/  //            calculateSize();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return size;
/*TODO*/  //    }
std::string PSF::toString() {
    std::string str = "";
    for (auto pair : pairList) {
        str.append(pair->toString());
    }
    return str;
    /*TODO*/  //    @Override
    /*TODO*/  //    public String toString() {
    /*TODO*/  //        StringBuilder sb = new StringBuilder();
    /*TODO*/  //
    /*TODO*/  //        for (PSFKeyValuePair pair : pairList) {
    /*TODO*/  //        	if (sb.length() > 0) {
    /*TODO*/  //                sb.append(System.lineSeparator());
    /*TODO*/  //        	}
    /*TODO*/  //            sb.append(pair.toString());
    /*TODO*/  //        }
    /*TODO*/  //
    /*TODO*/  //        if (isLikelyHomebrew()) {
    /*TODO*/  //        	if (sb.length() > 0) {
    /*TODO*/  //                sb.append(System.lineSeparator());
    /*TODO*/  //        	}
    /*TODO*/  //            sb.append("This is likely a homebrew");
    /*TODO*/  //        }
    /*TODO*/  //
    /*TODO*/  //        return sb.toString();
}
/*TODO*/  //
/*TODO*/  //    /** used by isLikelyHomebrew() */
/*TODO*/  //    private boolean safeEquals(Object a, Object b) {
/*TODO*/  //        return (a == null && b == null) || (a != null && a.equals(b));
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public boolean isLikelyHomebrew() {
/*TODO*/  //        boolean homebrew = false;
/*TODO*/  //
/*TODO*/  //        String disc_version = getString("DISC_VERSION");
/*TODO*/  //        String disc_id = getString("DISC_ID");
/*TODO*/  //        String category = getString("CATEGORY");
/*TODO*/  //        Integer bootable = (Integer)get("BOOTABLE"); // don't use getNumeric, we also want to know if the
          //        entry exists or not
/*TODO*/  //        Integer region = (Integer)get("REGION");
/*TODO*/  //        String psp_system_ver = getString("PSP_SYSTEM_VER");
/*TODO*/  //        Integer parental_level = (Integer)get("PARENTAL_LEVEL");
/*TODO*/  //
/*TODO*/  //        Integer ref_one = 1;
/*TODO*/  //        Integer ref_region = 32768;
/*TODO*/  //
/*TODO*/  //        if (safeEquals(disc_version, "1.00") &&
/*TODO*/  //            safeEquals(disc_id, "UCJS10041") && // loco roco demo, should not false positive since that demo
          //            has sys ver 3.40
/*TODO*/  //            safeEquals(category, "MG") &&
/*TODO*/  //            safeEquals(bootable, ref_one) &&
/*TODO*/  //            safeEquals(region, ref_region) &&
/*TODO*/  //            safeEquals(psp_system_ver, "1.00") &&
/*TODO*/  //            safeEquals(parental_level, ref_one)) {
/*TODO*/  //
/*TODO*/  //            if (indexEntryCount == 8) {
/*TODO*/  //                homebrew = true;
/*TODO*/  //            } else if (indexEntryCount == 9 &&
/*TODO*/  //                safeEquals(get("MEMSIZE"), ref_one)) {
/*TODO*/  //                // lua player hm 8
/*TODO*/  //                homebrew = true;
/*TODO*/  //            }
/*TODO*/  //        } else if (indexEntryCount == 4 &&
/*TODO*/  //            safeEquals(category, "MG") &&
/*TODO*/  //            safeEquals(bootable, ref_one) &&
/*TODO*/  //            safeEquals(region, ref_region)) {
/*TODO*/  //            homebrew = true;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return homebrew;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static class PSFKeyValuePair {
/*TODO*/  //        // data table info
/*TODO*/  //        public Object data;
/*TODO*/  //
/*TODO*/  //        public PSFKeyValuePair() {
/*TODO*/  //            this(null, 0, 0, null);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        public PSFKeyValuePair(String key, int dataType, int dataSize, Object data) {
/*TODO*/  //            this(key, dataType, dataSize, (dataSize + 3) & ~3, data);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        public PSFKeyValuePair(String key, int dataType, int dataSize, int dataSizePadded, Object data) {
/*TODO*/  //            this.key = key;
/*TODO*/  //            this.dataType = dataType;
/*TODO*/  //            this.dataSize = dataSize;
/*TODO*/  //            this.dataSizePadded = dataSizePadded;
/*TODO*/  //            this.data = data;
/*TODO*/  //
/*TODO*/  //            // yapspd: 4
/*TODO*/  //            // probably alignment of the value data
/*TODO*/  //            unknown1 = 4;
/*TODO*/  //        }
/*TODO*/  //
/** only reads the index entry, since this class has doesn't know about the psf/key/value offsets */
void PSFKeyValuePair::read(std::ifstream& f) 
{ 
    f.read((char *)&PsfSection, sizeof(PsfSection)); 
}
    /*TODO*/  //        /** only reads the index entry, since this class has doesn't know about the psf/key/value offsets */
/*TODO*/  //        public void read(ByteBuffer f) throws IOException {
/*TODO*/  //            // index table entry
/*TODO*/  //            keyOffset = readUHalf(f);
/*TODO*/  //            unknown1 = readUByte(f);
/*TODO*/  //            dataType = readUByte(f);
/*TODO*/  //            dataSize = readUWord(f);
/*TODO*/  //            dataSizePadded = readUWord(f);
/*TODO*/  //            valueOffset = readUWord(f);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        /** only writes the index entry, since this class has doesn't know about the psf/key/value offsets
          //        */
/*TODO*/  //        public void write(ByteBuffer f) {
/*TODO*/  //            // index table entry
/*TODO*/  //            writeHalf(f, keyOffset);
/*TODO*/  //            writeByte(f, unknown1);
/*TODO*/  //            writeByte(f, dataType);
/*TODO*/  //            writeWord(f, dataSize);
/*TODO*/  //            writeWord(f, dataSizePadded);
/*TODO*/  //            writeWord(f, valueOffset);
/*TODO*/  //        }
/*TODO*/  //
std::string PSFKeyValuePair::toString() {
    std::string str = "";
    char tmp[128];
    std::string st(data.begin(), data.end());
    sprintf(tmp, "%-10s = %s\n", key.c_str(),st.c_str());
    str.append(tmp);
    return str;
}
