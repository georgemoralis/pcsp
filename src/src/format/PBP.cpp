/*
 *  14/06/2022 - synced with jpcsp 14/06/2022 - a5e0793
 */
#include "..\PCSPCommon.h"
#include "PSF.h"
#include "PBP.h"

/*TODO*/  //    private Elf32 elf32;
/*TODO*/  //    private PSF psf;

bool PBP::isValid() const 
{ 
    return (size_pbp != 0 && data.p_magic == PBP_MAGIC); 
}
/*TODO*/  //
/*TODO*/  //    public void setElf32(Elf32 elf) {
/*TODO*/  //        elf32 = elf;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public Elf32 getElf32() {
/*TODO*/  //        return elf32;
/*TODO*/  //    }
/*TODO*/  //
PSF *PBP::getPsf() const { return psf; }

PBP::PBP(std::ifstream &f) : psf(NULL){
    u32 pos = (u32)f.tellg();
    f.seekg(0, std::ios::end);
    size_pbp = (u32)f.tellg();
    f.seekg(pos, std::ios::beg);

    if (size_pbp == 0) return;

    f.read((char*)&data, sizeof(data));

    p_offsets[0] = data.p_offset_param_sfo;
    p_offsets[1] = data.p_offset_icon0_png;
    p_offsets[2] = data.p_offset_icon1_pmf; 
    p_offsets[3] = data.p_offset_pic0_png;
    p_offsets[4] = data.p_offset_pic1_png; 
    p_offsets[5] = data.p_offset_snd0_at3; 
    p_offsets[6] = data.p_offset_psp_data; 
    p_offsets[7] = data.p_offset_psar_data;
    p_offsets[8] = size_pbp;
}

PBP::PBP() : psf(NULL)  {

}

PBP::~PBP() {
    if (psf != NULL) {
        delete psf;
        psf = NULL;
    }
}

PSF *PBP::readPSF(std::ifstream &file) {
    if (getOffsetParam() > 0) {
        file.seekg(getOffsetParam());
        psf = new PSF(getOffsetParam());
        psf->read(file);
        return psf;
    }
    return NULL;
}

std::string PBP::toString() {
    std::string str = "--------PBP HEADER--------\n";
    char tmp[128];

    sprintf(tmp, "p_magic            0x%08X\n", data.p_magic);
    str.append(tmp);
    sprintf(tmp, "p_version          0x%08X\n", data.p_version);
    str.append(tmp);
    sprintf(tmp, "p_offset_param_sfo 0x%08X\n", getOffsetParam());
    str.append(tmp);
    sprintf(tmp, "p_offset_icon0_png 0x%08X\n", getOffsetIcon0());
    str.append(tmp);
    sprintf(tmp, "p_offset_icon1_pmf 0x%08X\n", getOffsetIcon1());
    str.append(tmp);
    sprintf(tmp, "p_offset_pic0_png  0x%08X\n", getOffsetPic0());
    str.append(tmp);
    sprintf(tmp, "p_offset_pic1_png  0x%08X\n", getOffsetPic1());
    str.append(tmp);
    sprintf(tmp, "p_offset_snd0_at3  0x%08X\n", getOffsetSnd0());
    str.append(tmp);
    sprintf(tmp, "p_offset_psp_data  0x%08X\n", getOffsetPspData());
    str.append(tmp);
    sprintf(tmp, "p_offset_psar_data 0x%08X\n", getOffsetPsarData());
    str.append(tmp);

    return str;
}

std::string PBP::getName(int index) {
    return FILE_NAMES[index];
}
u32 PBP::getOffset(int index) {
    return p_offsets[index];
}

u32 PBP::getSize(int index) 
{ 
    return p_offsets[index + 1] - p_offsets[index]; 
}

std::unique_ptr<u8> PBP::getBytes(std::ifstream &f,int index) { 
    u32 pos = f.tellg();
    std::unique_ptr<u8> data(new u8[getSize(index)]); 
    f.seekg(getOffset(index));
    f.read((char*)data.get(), getSize(index));
    f.seekg(pos);
    return data;
}

u32 PBP::getMagic() { return data.p_magic; }

u32 PBP::getVersion() { return data.p_version; }

u32 PBP::getOffsetParam() {
    return getOffset(PARAM_SFO);
}

u32 PBP::getOffsetIcon0() {
    return getOffset(ICON0_PNG);
 }

u32 PBP::getOffsetIcon1() {
    return getOffset(ICON1_PMF);
}

u32 PBP::getOffsetPic0() {
    return getOffset(PIC0_PNG);
}

u32 PBP::getOffsetPic1() {
    return getOffset(PIC1_PNG);
}

u32 PBP::getOffsetSnd0() {
    return getOffset(SND0_AT3);
}

u32 PBP::getOffsetPspData() {
    return getOffset(PSP_DATA);
}

u32 PBP::getOffsetPsarData() {
    return getOffset(PSAR_DATA);
}

u32 PBP::getSizeIcon0() {
    return getSize(ICON0_PNG);
}

u32 PBP::getSizePsarData() {
    return getSize(PSAR_DATA);
}

void PBP::unpackPBP(std::ifstream& f) {
    f.seekg(0);
    PBP pbp(f);

    if (!pbp.isValid()) return;
    if (std::filesystem::is_directory(PBP_UNPACK_PATH_PREFIX)) {
        std::filesystem::remove_all(PBP_UNPACK_PATH_PREFIX);  // delete all files and directory
    }
    std::filesystem::create_directory(PBP_UNPACK_PATH_PREFIX);
    for (int index = 0; index < TOTAL_FILES; index++) {
        std::unique_ptr<u8> bytes = pbp.getBytes(f, index);
        if (bytes && getSize(index)>0) {
            std::ofstream ofs;
            std::string path = PBP_UNPACK_PATH_PREFIX + pbp.getName(index);
            ofs.open(path.c_str(), std::ios::out | std::ios::binary);
            if (ofs.is_open()) {
                ofs.write((char*)bytes.get(), pbp.getSize(index));
                ofs.close();
            }
        }
    }
}
/*TODO*/  //
/*TODO*/  //    /**
/*TODO*/  //     * Unpack a PBP file, avoiding to consume too much memory
/*TODO*/  //     * (i.e. not reading each section completely in memory).
/*TODO*/  //     *
/*TODO*/  //     * @param vFile        the PBP file
/*TODO*/  //     * @throws IOException
/*TODO*/  //     */
/*TODO*/  //    public static void unpackPBP(IVirtualFile vFile) throws IOException {
/*TODO*/  //    	vFile.ioLseek(0L);
/*TODO*/  //    	PBP pbp = new PBP();
/*TODO*/  //    	pbp.size_pbp = (int) vFile.length();
/*TODO*/  //    	pbp.p_magic = read32(vFile);
/*TODO*/  //    	if (!pbp.isValid()) {
/*TODO*/  //    		return;
/*TODO*/  //    	}
/*TODO*/  //    	pbp.p_version = read32(vFile);
/*TODO*/  //        pbp.p_offsets = new int[] { read32(vFile), read32(vFile), read32(vFile), read32(vFile),
          //        read32(vFile), read32(vFile), read32(vFile), read32(vFile), pbp.size_pbp };
/*TODO*/  //
/*TODO*/  //        File dir = new File(PBP_UNPACK_PATH_PREFIX);
/*TODO*/  //        deleteDir(dir); //delete all files and directory
/*TODO*/  //        dir.mkdir();
/*TODO*/  //
/*TODO*/  //        final byte[] buffer = new byte[10 * 1024];
/*TODO*/  //        for (int index = 0; index < TOTAL_FILES; index++) {
/*TODO*/  //        	int size = pbp.getSize(index);
/*TODO*/  //        	if (size > 0) {
/*TODO*/  //        		long offset = pbp.getOffset(index) & 0xFFFFFFFFL;
/*TODO*/  //        		if (vFile.ioLseek(offset) == offset) {
/*TODO*/  //            		OutputStream os = new FileOutputStream(new File(PBP_UNPACK_PATH_PREFIX +
          //            pbp.getName(index)));
/*TODO*/  //	        		while (size > 0) {
/*TODO*/  //	        			int length = Math.min(size, buffer.length);
/*TODO*/  //	        			int readLength = vFile.ioRead(buffer, 0, length);
/*TODO*/  //	        			if (readLength > 0) {
/*TODO*/  //	        				os.write(buffer, 0, readLength);
/*TODO*/  //	        				size -= readLength;
/*TODO*/  //	        			}
/*TODO*/  //	        			if (readLength != length) {
/*TODO*/  //	        				break;
/*TODO*/  //	        			}
/*TODO*/  //	        		}
/*TODO*/  //	        		os.close();
/*TODO*/  //        		}
/*TODO*/  //        	}
/*TODO*/  //        }
/*TODO*/  //    }
