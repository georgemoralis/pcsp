/*
 *  14/06/2022 - synced with jpcsp 14/06/2022 - a5e0793
 */
#pragma once

class PSF;
class Elf32;

class PBP 
{
  private:
    std::string getName(int index);
    u32 getOffset(int index);
    u32 getSize(int index);
    std::unique_ptr<u8> getBytes(std::ifstream &f, int index);

    const std::string PBP_UNPACK_PATH_PREFIX = "unpacked-pbp/";

    const std::vector<std::string> FILE_NAMES = std::vector<std::string>{
        "param.sfo", "icon0.png", "icon1.pmf", "pic0.png", "pic1.png", "snd0.at3", "psp.data", "psar.data"};

    static constexpr int TOTAL_FILES = 8;
    static constexpr int PARAM_SFO = 0;
    static constexpr int ICON0_PNG = 1;
    static constexpr int ICON1_PMF = 2;
    static constexpr int PIC0_PNG = 3;
    static constexpr int PIC1_PNG = 4;
    static constexpr int SND0_AT3 = 5;
    static constexpr int PSP_DATA = 6;
    static constexpr int PSAR_DATA = 7;

    struct {
        u32 p_magic;
        u32 p_version;
        u32 p_offset_param_sfo;
        u32 p_offset_icon0_png;
        u32 p_offset_icon1_pmf;
        u32 p_offset_pic0_png;
        u32 p_offset_pic1_png;
        u32 p_offset_snd0_at3;
        u32 p_offset_psp_data;
        u32 p_offset_psar_data;
    } data;

    PSF *psf;
    u32 size_pbp;
    u32 p_offsets[9];
    Elf32 *elf32;

  public:
    static constexpr int PBP_MAGIC = 0x50425000;
    PBP();
    PBP(std::ifstream &f);
    ~PBP();
    bool isValid() const;
    PSF *readPSF(std::ifstream &file);
    PSF *getPsf() const;
    u32 getMagic(); 
    u32 getVersion();
    u32 getOffsetParam();
    u32 getOffsetIcon0();
    u32 getOffsetIcon1();
    u32 getOffsetPic0();
    u32 getOffsetPic1();
    u32 getOffsetSnd0();
    u32 getOffsetPspData();
    u32 getOffsetPsarData();
    u32 getSizeIcon0();
    u32 getSizePsarData();
    void unpackPBP(std::ifstream& f);
    std::string toString();
    void setElf32(const Elf32 &elf);
    Elf32 *getElf32() const;
    
    static const int PBP_HEADER_SIZE = 8 + TOTAL_FILES * 4;
    static const int PBP_PSP_DATA_OFFSET = 8 + PSP_DATA * 4;
    static const int PBP_PSAR_DATA_OFFSET = 8 + PSAR_DATA * 4;
 
};
