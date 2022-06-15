/*
 *  14/06/2022 - synced with jpcsp 14/06/2022 - a5e0793
 */
#pragma once

class PSFKeyValuePair {
    friend class PSF;

  public:
    void read(std::ifstream &f); 
    std::string toString();
  private:
    struct {
        u16 keyOffset;
        u8 unknown1;
        u8 dataType;
        u32 dataSize;
        u32 dataSizePadded;
        u32 valueOffset;
    } PsfSection;// index table info  
    std::string key;  // key table info
    std::vector<u8> data;
};

class PSF 
{
  public:
    static constexpr int PSF_IDENT = 0x46535000;
    static constexpr int PSF_DATA_TYPE_BINARY = 0;
    static constexpr int PSF_DATA_TYPE_STRING = 2;
    static constexpr int PSF_DATA_TYPE_INT32 = 4;

    PSF(u32 psfOffset);
    PSF();
    void read(std::ifstream &f); 
    std::string toString();
  private:
    struct PsfHeader {
            u32 ident;
            u32 version;// yapspd: 0x1100. actual: 0x0101.
            u32 keyTableOffset;
            u32 valueTableOffset;
            u32 indexEntryCount;
    };
    u32 psfOffset;
    u32 size;
    bool sizeDirty;
    bool tablesDirty;
    std::vector<PSFKeyValuePair*> pairList;
};
