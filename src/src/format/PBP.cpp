/*
 *  12/06/2022 - synced with jpcsp 31/05/2022 - 90841114
 */
#include "PBP.h"

/*TODO*/  //    public static final int PBP_MAGIC = 0x50425000;
/*TODO*/  //    private static final String PBP_UNPACK_PATH_PREFIX = "unpacked-pbp/";
/*TODO*/  //
/*TODO*/  //    static private final String[] FILE_NAMES = new String[]{
/*TODO*/  //            "param.sfo",
/*TODO*/  //            "icon0.png",
/*TODO*/  //            "icon1.pmf",
/*TODO*/  //            "pic0.png",
/*TODO*/  //            "pic1.png",
/*TODO*/  //            "snd0.at3",
/*TODO*/  //            "psp.data",
/*TODO*/  //            "psar.data",
/*TODO*/  //    };
/*TODO*/  //
/*TODO*/  //    static private final int TOTAL_FILES = 8;
/*TODO*/  //
/*TODO*/  //    static private final int PARAM_SFO = 0;
/*TODO*/  //    static private final int ICON0_PNG = 1;
/*TODO*/  //    static private final int ICON1_PMF = 2;
/*TODO*/  //    static private final int PIC0_PNG = 3;
/*TODO*/  //    static private final int PIC1_PNG = 4;
/*TODO*/  //    static private final int SND0_AT3 = 5;
/*TODO*/  //    static private final int PSP_DATA = 6;
/*TODO*/  //    static private final int PSAR_DATA = 7;
/*TODO*/  //
/*TODO*/  //    static public final int PBP_HEADER_SIZE = 8 + TOTAL_FILES * 4;
/*TODO*/  //    static public final int PBP_PSP_DATA_OFFSET = 8 + PSP_DATA * 4;
/*TODO*/  //    static public final int PBP_PSAR_DATA_OFFSET = 8 + PSAR_DATA * 4;
/*TODO*/  //
/*TODO*/  //    private String info;
/*TODO*/  //    private int size_pbp;
/*TODO*/  //
/*TODO*/  //    private int p_magic;
/*TODO*/  //    private int p_version;
/*TODO*/  //    private int[] p_offsets;
/*TODO*/  //    private Elf32 elf32;
/*TODO*/  //    private PSF psf;
/*TODO*/  //
/*TODO*/  //    public boolean isValid() {
/*TODO*/  //        return size_pbp != 0 && p_magic == PBP_MAGIC;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void setElf32(Elf32 elf) {
/*TODO*/  //        elf32 = elf;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public Elf32 getElf32() {
/*TODO*/  //        return elf32;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public PSF getPSF() {
/*TODO*/  //        return psf;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public void setInfo(String msg) {
/*TODO*/  //        info = msg;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public String getInfo() {
/*TODO*/  //        return info;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public PBP(ByteBuffer f) throws IOException {
/*TODO*/  //        size_pbp = f.limit();
/*TODO*/  //        if (size_pbp == 0) {
/*TODO*/  //            return;
/*TODO*/  //        }
/*TODO*/  //        p_magic = readUWord(f);
/*TODO*/  //        if (isValid()) {
/*TODO*/  //            p_version = readUWord(f);
/*TODO*/  //
/*TODO*/  //            p_offsets = new int[]
          //            {readUWord(f),readUWord(f),readUWord(f),readUWord(f),readUWord(f),readUWord(f),readUWord(f),readUWord(f),size_pbp};
/*TODO*/  //
/*TODO*/  //            info = toString();
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private PBP() {
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public PSF readPSF(ByteBuffer f) throws IOException {
/*TODO*/  //        if (getOffsetParam() > 0) {
/*TODO*/  //            f.position(getOffsetParam());
/*TODO*/  //            psf = new PSF(getOffsetParam());
/*TODO*/  //            psf.read(f);
/*TODO*/  //            return psf;
/*TODO*/  //        }
/*TODO*/  //        return null;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    @Override
/*TODO*/  //    public String toString() {
/*TODO*/  //        StringBuilder str = new StringBuilder();
/*TODO*/  //        str.append("-----PBP HEADER---------" + "\n");
/*TODO*/  //        str.append("p_magic " + "\t\t" + formatString("long", Long.toHexString(p_magic &
          //        0xFFFFFFFFL).toUpperCase()) + "\n");
/*TODO*/  //        str.append("p_version " + "\t\t" + formatString("long", Long.toHexString(p_version &
          //        0xFFFFFFFFL).toUpperCase()) + "\n");
/*TODO*/  //        str.append("p_offset_param_sfo " + "\t" + formatString("long", Long.toHexString(getOffsetParam() &
          //        0xFFFFFFFFL).toUpperCase()) + "\n");
/*TODO*/  //        str.append("p_offset_icon0_png " + "\t" + formatString("long", Long.toHexString(getOffsetIcon0() &
          //        0xFFFFFFFFL).toUpperCase()) + "\n");
/*TODO*/  //        str.append("p_offset_icon1_pmf " + "\t" + formatString("long", Long.toHexString(getOffsetIcon1() &
          //        0xFFFFFFFFL).toUpperCase()) + "\n");
/*TODO*/  //        str.append("p_offset_pic0_png " + "\t" + formatString("long", Long.toHexString(getOffsetPic0() &
          //        0xFFFFFFFFL).toUpperCase()) + "\n");
/*TODO*/  //        str.append("p_offset_pic1_png " + "\t" + formatString("long", Long.toHexString(getOffsetPic1() &
          //        0xFFFFFFFFL).toUpperCase()) + "\n");
/*TODO*/  //        str.append("p_offset_snd0_at3 " + "\t" + formatString("long", Long.toHexString(getOffsetSnd0() &
          //        0xFFFFFFFFL).toUpperCase()) + "\n");
/*TODO*/  //        str.append("p_offset_psp_data " + "\t" + formatString("long", Long.toHexString(getOffsetPspData() &
          //        0xFFFFFFFFL).toUpperCase()) + "\n");
/*TODO*/  //        str.append("p_offset_psar_data " + "\t" + formatString("long", Long.toHexString(getOffsetPsarData()
          //        & 0xFFFFFFFFL).toUpperCase()) + "\n");
/*TODO*/  //        return str.toString();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private String getName(int index) {
/*TODO*/  //        return FILE_NAMES[index];
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private int getOffset(int index) {
/*TODO*/  //        return this.p_offsets[index];
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private int getSize(int index) {
/*TODO*/  //        return this.p_offsets[index + 1] - this.p_offsets[index];
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private byte[] getBytes(ByteBuffer f, int index) {
/*TODO*/  //        return ByteUtil.readBytes(f, getOffset(index), getSize(index));
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getMagic() {
/*TODO*/  //        return p_magic;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getVersion() {
/*TODO*/  //        return p_version;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getOffsetParam() {
/*TODO*/  //        return getOffset(PARAM_SFO);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getOffsetIcon0() {
/*TODO*/  //        return getOffset(ICON0_PNG);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getOffsetIcon1() {
/*TODO*/  //        return getOffset(ICON1_PMF);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getOffsetPic0() {
/*TODO*/  //        return getOffset(PIC0_PNG);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getOffsetPic1() {
/*TODO*/  //        return getOffset(PIC1_PNG);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getOffsetSnd0() {
/*TODO*/  //        return getOffset(SND0_AT3);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getOffsetPspData() {
/*TODO*/  //        return getOffset(PSP_DATA);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getOffsetPsarData() {
/*TODO*/  //        return getOffset(PSAR_DATA);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getSizeIcon0() {
/*TODO*/  //        return getSize(ICON0_PNG);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public int getSizePsarData() {
/*TODO*/  //    	return getSize(PSAR_DATA);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static boolean deleteDir(File dir) {
/*TODO*/  //        if (dir.isDirectory()) {
/*TODO*/  //            String[] children = dir.list();
/*TODO*/  //            for (int i = 0; i < children.length; i++) {
/*TODO*/  //                boolean success = deleteDir(new File(dir, children[i]));
/*TODO*/  //                if (!success) {
/*TODO*/  //                    return false;
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //        // The directory is now empty so delete it
/*TODO*/  //        return dir.delete();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static void unpackPBP(ByteBuffer f) throws IOException {
/*TODO*/  //        f.position(0);//seek to 0
/*TODO*/  //        PBP pbp = new PBP(f);
/*TODO*/  //        if (!pbp.isValid()) {
/*TODO*/  //            return;
/*TODO*/  //        }
/*TODO*/  //        File dir = new File(PBP_UNPACK_PATH_PREFIX);
/*TODO*/  //        deleteDir(dir);//delete all files and directory
/*TODO*/  //        dir.mkdir();
/*TODO*/  //
/*TODO*/  //        for (int index = 0; index < TOTAL_FILES; index++) {
/*TODO*/  //        	byte[] bytes = pbp.getBytes(f, index);
/*TODO*/  //        	if (bytes != null && bytes.length > 0) {
/*TODO*/  //        		FileUtil.writeBytes(new File(PBP_UNPACK_PATH_PREFIX + pbp.getName(index)), bytes);
/*TODO*/  //        	}
/*TODO*/  //        }
/*TODO*/  //    }
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
