#ifndef ge_Constants_h__
#define ge_Constants_h__

#define PI 3.1415926536f

enum ge_CommandType
{
	CMD_NOP         = 0x00,
	CMD_VADDR       = 0x01,
	CMD_IADDR       = 0x02,
	CMD_PRIM        = 0x04,
	CMD_BEZIER      = 0x05,
	CMD_SPLINE      = 0x06,
	CMD_BBOX        = 0x07,
	CMD_JUMP        = 0x08,
	CMD_BJUMP       = 0x09,
	CMD_CALL        = 0x0A,
	CMD_RET         = 0x0B,
	CMD_END         = 0x0C,
	CMD_SIGNAL      = 0x0E,
	CMD_FINISH      = 0x0F,
	CMD_BASE        = 0x10,
	CMD_VTYPE       = 0x12,
	CMD_OFFSET      = 0x13,
	CMD_ORIGIN      = 0x14,
	CMD_REGION1     = 0x15,
	CMD_REGION2     = 0x16,
	CMD_LTE         = 0x17,
	CMD_LE0         = 0x18,
	CMD_LE1         = 0x19,
	CMD_LE2         = 0x1A,
	CMD_LE3         = 0x1B,
	CMD_CLE         = 0x1C,
	CMD_BCE         = 0x1D,
	CMD_TME         = 0x1E,
	CMD_FGE         = 0x1F,
	CMD_DTE         = 0x20,
	CMD_ABE         = 0x21,
	CMD_ATE         = 0x22,
	CMD_ZTE         = 0x23,
	CMD_STE         = 0x24,
	CMD_AAE         = 0x25,
	CMD_PCE         = 0x26,
	CMD_CTE         = 0x27,
	CMD_LOE         = 0x28,
	CMD_BONEN       = 0x2A,
	CMD_BONED       = 0x2B,
	CMD_WEIGHT0     = 0x2C,
	CMD_WEIGHT1     = 0x2D,
	CMD_WEIGHT2     = 0x2E,
	CMD_WEIGHT3     = 0x2F,
	CMD_WEIGHT4     = 0x30,
	CMD_WEIGHT5     = 0x31,
	CMD_WEIGHT6     = 0x32,
	CMD_WEIGHT7     = 0x33,
	CMD_DIVIDE      = 0x36,
	CMD_PPM         = 0x37,
	CMD_PFACE       = 0x38,
	CMD_WORLDN      = 0x3A,
	CMD_WORLDD      = 0x3B,
	CMD_VIEWN       = 0x3C,
	CMD_VIEWD       = 0x3D,
	CMD_PROJN       = 0x3E,
	CMD_PROJD       = 0x3F,
	CMD_TGENN       = 0x40,
	CMD_TGEND       = 0x41,
	CMD_SX          = 0x42,
	CMD_SY          = 0x43,
	CMD_SZ          = 0x44,
	CMD_TX          = 0x45,
	CMD_TY          = 0x46,
	CMD_TZ          = 0x47,
	CMD_SU          = 0x48,
	CMD_SV          = 0x49,
	CMD_TU          = 0x4A,
	CMD_TV          = 0x4B,
	CMD_OFFSETX     = 0x4C,
	CMD_OFFSETY     = 0x4D,
	CMD_SHADE       = 0x50,
	CMD_NREV        = 0x51,
	CMD_MATERIAL    = 0x53,
	CMD_MEC         = 0x54,
	CMD_MAC         = 0x55,
	CMD_MDC         = 0x56,
	CMD_MSC         = 0x57,
	CMD_MAA         = 0x58,
	CMD_MK          = 0x5B,
	CMD_AC          = 0x5C,
	CMD_AA          = 0x5D,
	CMD_LMODE       = 0x5E,
	CMD_LTYPE0      = 0x5F,
	CMD_LTYPE1      = 0x60,
	CMD_LTYPE2      = 0x61,
	CMD_LTYPE3      = 0x62,
	CMD_LX0         = 0x63,
	CMD_LY0         = 0x64,
	CMD_LZ0         = 0x65,
	CMD_LX1         = 0x66,
	CMD_LY1         = 0x67,
	CMD_LZ1         = 0x68,
	CMD_LX2         = 0x69,
	CMD_LY2         = 0x6A,
	CMD_LZ2         = 0x6B,
	CMD_LX3         = 0x6C,
	CMD_LY3         = 0x6D,
	CMD_LZ3         = 0x6E,
	CMD_LDX0        = 0x6F,
	CMD_LDY0        = 0x70,
	CMD_LDZ0        = 0x71,
	CMD_LDX1        = 0x72,
	CMD_LDY1        = 0x73,
	CMD_LDZ1        = 0x74,
	CMD_LDX2        = 0x75,
	CMD_LDY2        = 0x76,
	CMD_LDZ2        = 0x77,
	CMD_LDX3        = 0x78,
	CMD_LDY3        = 0x79,
	CMD_LDZ3        = 0x7A,
	CMD_LKA0        = 0x7B,
	CMD_LKB0        = 0x7C,
	CMD_LKC0        = 0x7D,
	CMD_LKA1        = 0x7E,
	CMD_LKB1        = 0x7F,
	CMD_LKC1        = 0x80,
	CMD_LKA2        = 0x81,
	CMD_LKB2        = 0x82,
	CMD_LKC2        = 0x83,
	CMD_LKA3        = 0x84,
	CMD_LKB3        = 0x85,
	CMD_LKC3        = 0x86,
	CMD_LKS0        = 0x87,
	CMD_LKS1        = 0x88,
	CMD_LKS2        = 0x89,
	CMD_LKS3        = 0x8A,
	CMD_LKO0        = 0x8B,
	CMD_LKO1        = 0x8C,
	CMD_LKO2        = 0x8D,
	CMD_LKO3        = 0x8E,
	CMD_LAC0        = 0x8F,
	CMD_LDC0        = 0x90,
	CMD_LSC0        = 0x91,
	CMD_LAC1        = 0x92,
	CMD_LDC1        = 0x93,
	CMD_LSC1        = 0x94,
	CMD_LAC2        = 0x95,
	CMD_LDC2        = 0x96,
	CMD_LSC2        = 0x97,
	CMD_LAC3        = 0x98,
	CMD_LDC3        = 0x99,
	CMD_LSC3        = 0x9A,
	CMD_CULL        = 0x9B,
	CMD_FBP         = 0x9C,
	CMD_FBW         = 0x9D,
	CMD_ZBP         = 0x9E,
	CMD_ZBW         = 0x9F,
	CMD_TBP0        = 0xA0,
	CMD_TBP1        = 0xA1,
	CMD_TBP2        = 0xA2,
	CMD_TBP3        = 0xA3,
	CMD_TBP4        = 0xA4,
	CMD_TBP5        = 0xA5,
	CMD_TBP6        = 0xA6,
	CMD_TBP7        = 0xA7,
	CMD_TBW0        = 0xA8,
	CMD_TBW1        = 0xA9,
	CMD_TBW2        = 0xAA,
	CMD_TBW3        = 0xAB,
	CMD_TBW4        = 0xAC,
	CMD_TBW5        = 0xAD,	
	CMD_TBW6        = 0xAE,
	CMD_TBW7        = 0xAF,
	CMD_CBP         = 0xB0,
	CMD_CBW         = 0xB1,
	CMD_XBP1        = 0xB2,
	CMD_XBPW1       = 0xB3,
	CMD_XBP2        = 0xB4,
	CMD_XBPW2       = 0xB5,
	CMD_TSIZE0      = 0xB8,
	CMD_TSIZE1      = 0xB9,
	CMD_TSIZE2      = 0xBA,
	CMD_TSIZE3      = 0xBB,
	CMD_TSIZE4      = 0xBC,
	CMD_TSIZE5      = 0xBD,
	CMD_TSIZE6      = 0xBE,
	CMD_TSIZE7      = 0xBF,
	CMD_TMAP        = 0xC0,
	CMD_TSHADE      = 0xC1,
	CMD_TMODE       = 0xC2,
	CMD_TPF         = 0xC3,
	CMD_CLOAD       = 0xC4,
	CMD_CLUT        = 0xC5,
	CMD_TFILTER     = 0xC6,
	CMD_TWRAP       = 0xC7,
	CMD_TLEVEL      = 0xC8,
	CMD_TFUNC       = 0xC9,
	CMD_TEC         = 0xCA,
	CMD_TFLUSH      = 0xCB,
	CMD_TSYNC       = 0xCC,
	CMD_FOG1        = 0xCD,
	CMD_FOG2        = 0xCE,
	CMD_FC          = 0xCF,
	CMD_TSLOPE      = 0xD0,
	CMD_FPF         = 0xD2,
	CMD_CMODE       = 0xD3,
	CMD_SCISSOR1    = 0xD4,
	CMD_SCISSOR2    = 0xD5,
	CMD_MINZ        = 0xD6,
	CMD_MAXZ        = 0xD7,
	CMD_CTEST       = 0xD8,
	CMD_CREF        = 0xD9,
	CMD_CMSK        = 0xDA,
	CMD_ATEST       = 0xDB,
	CMD_STEST       = 0xDC,
	CMD_SOP         = 0xDD,
	CMD_ZTEST       = 0xDE,
	CMD_BLEND       = 0xDF,
	CMD_FIXA        = 0xE0,
	CMD_FIXB        = 0xE1,				
	CMD_DITH1       = 0xE2,
	CMD_DITH2       = 0xE3,
	CMD_DITH3       = 0xE4,
	CMD_DITH4       = 0xE5,
	CMD_LOP         = 0xE6,
	CMD_ZMSK        = 0xE7,
	CMD_PMSK1       = 0xE8,
	CMD_PMSK2       = 0xE9,
	CMD_XSTART      = 0xEA,
	CMD_XPOS1       = 0xEB,
	CMD_XPOS2       = 0xEC,
	CMD_XSIZE       = 0xEE,
	CMD_X2          = 0xF0,
	CMD_Y2          = 0xF1,
	CMD_Z2          = 0xF2,
	CMD_S2          = 0xF3,
	CMD_T2          = 0xF4,
	CMD_Q2          = 0xF5,
	CMD_RGB2        = 0xF6,
	CMD_AP2         = 0xF7,
	CMD_F2          = 0xF8,
	CMD_I2          = 0xF9,
};

enum ge_VType
{
    GE_VTYPE_TRANSFORM      = (0<<23),
    GE_VTYPE_THROUGH        = (1<<23),
    GE_VTYPE_THROUGH_MASK   = (1<<23),

    GE_VTYPE_TC_NONE        = (0<<0),
    GE_VTYPE_TC_8BIT        = (1<<0),
    GE_VTYPE_TC_16BIT       = (2<<0),
    GE_VTYPE_TC_FLOAT       = (3<<0),
    GE_VTYPE_TC_MASK        = (3<<0),
    GE_VTYPE_TC_SHIFT       = 0,

    GE_VTYPE_COL_NONE       = (0<<2),
    GE_VTYPE_COL_565        = (4<<2),
    GE_VTYPE_COL_5551       = (5<<2),
    GE_VTYPE_COL_4444       = (6<<2),
    GE_VTYPE_COL_8888       = (7<<2),
    GE_VTYPE_COL_MASK       = (7<<2),
    GE_VTYPE_COL_SHIFT      = 2,

    GE_VTYPE_NRM_NONE       = (0<<5),
    GE_VTYPE_NRM_8BIT       = (1<<5),
    GE_VTYPE_NRM_16BIT      = (2<<5),
    GE_VTYPE_NRM_FLOAT      = (3<<5),
    GE_VTYPE_NRM_MASK       = (3<<5),
    GE_VTYPE_NRM_SHIFT      = 5,

    GE_VTYPE_POSITION_NONE  = (0<<7),
    GE_VTYPE_POS_8BIT       = (1<<7),
    GE_VTYPE_POS_16BIT      = (2<<7),
    GE_VTYPE_POS_FLOAT      = (3<<7),
    GE_VTYPE_POS_MASK       = (3<<7),
    GE_VTYPE_POS_SHIFT      = 7,

    GE_VTYPE_WEIGHT_NONE    = (0<<9),
    GE_VTYPE_WEIGHT_8BIT    = (1<<9),
    GE_VTYPE_WEIGHT_16BIT   = (2<<9),
    GE_VTYPE_WEIGHT_FLOAT   = (3<<9),
    GE_VTYPE_WEIGHT_MASK    = (3<<9),
    GE_VTYPE_WEIGHT_SHIFT   = 9,

    GE_VTYPE_SKIN_MASK      = (7<<14),
    GE_VTYPE_SKIN_SHIFT     = 14,

    GE_VTYPE_MORPH_MASK     = (7<<19),
    GE_VTYPE_MORPH_SHIFT    = 19,

    GE_VTYPE_IDX_NONE       = (0<<11),
    GE_VTYPE_IDX_8BIT       = (1<<11),
    GE_VTYPE_IDX_16BIT      = (2<<11),
    GE_VTYPE_IDX_MASK       = (3<<11),
    GE_VTYPE_IDX_SHIFT      = 11,

    GE_VTYPE_ALL_MASK       = GE_VTYPE_THROUGH_MASK|GE_VTYPE_TC_MASK|GE_VTYPE_COL_MASK|GE_VTYPE_NRM_MASK|GE_VTYPE_POS_MASK|GE_VTYPE_WEIGHT_MASK|GE_VTYPE_SKIN_MASK
};

enum ge_TextureFormat
{
	GE_TFMT_5650        = 0,
	GE_TFMT_5551        = 1,
	GE_TFMT_4444        = 2,
	GE_TFMT_8888        = 3,
	GE_TFMT_CLUT4       = 4,
	GE_TFMT_CLUT8       = 5,
	GE_TFMT_CLUT16      = 6,
	GE_TFMT_CLUT32      = 7,
	GE_TFMT_DXT1        = 8,
	GE_TFMT_DXT3        = 9,
	GE_TFMT_DXT5        = 10,
	GE_TFMT_RESERVED0   = 11,
	GE_TFMT_RESERVED1   = 12,
	GE_TFMT_RESERVED2   = 13,
	GE_TFMT_RESERVED3   = 14,
	GE_TFMT_RESERVED4   = 15,
};

//stencil test
#define STST_FUNCTION_NEVER_PASS_STENCIL_TEST        0x00
#define STST_FUNCTION_ALWAYS_PASS_STENCIL_TEST       0x01
#define STST_FUNCTION_PASS_TEST_IF_MATCHES           0x02
#define STST_FUNCTION_PASS_TEST_IF_DIFFERS           0x03
#define STST_FUNCTION_PASS_TEST_IF_LESS              0x04
#define STST_FUNCTION_PASS_TEST_IF_LESS_OR_EQUAL     0x05
#define STST_FUNCTION_PASS_TEST_IF_GREATER           0x06
#define STST_FUNCTION_PASS_TEST_IF_GREATER_OR_EQUAL  0x07
//stencil op
#define SOP_KEEP_STENCIL_VALUE        0x00
#define SOP_ZERO_STENCIL_VALUE        0x01
#define SOP_REPLACE_STENCIL_VALUE     0x02
#define SOP_INVERT_STENCIL_VALUE      0x03
#define SOP_INCREMENT_STENCIL_VALUE   0x04
#define SOP_DECREMENT_STENCIL_VALUE   0x05

enum ge_PrimitiveType
{
	GE_PRIM_POINTS          = 0,
	GE_PRIM_LINES           = 1,
	GE_PRIM_LINE_STRIP      = 2,
	GE_PRIM_TRIANGLES       = 3,
	GE_PRIM_TRIANGLE_STRIP  = 4,
	GE_PRIM_TRIANGLE_FAN    = 5,
	GE_PRIM_RECTANGLES      = 6,
};

enum ge_LightType
{
    GE_LIGHT_TYPE_DIRECTIONAL = 0x00,
    GE_LIGHT_TYPE_POINT       = 0x01,
    GE_LIGHT_TYPE_SPOT        = 0x02,
};

enum ge_LightKind
{
    GE_LIGHT_KIND_DIFFUSE_ONLY                 = 0x00,
    GE_LIGHT_KIND_DIFFUSE_AND_SPECULAR         = 0x01,
    GE_LIGHT_KIND_POWERED_DIFFUSE_AND_SPECULAR = 0x02,
};

#define MAX_PATCH_DIVS 64

#define ATST_NEVER_PASS_PIXEL 0
#define ATST_ALWAYS_PASS_PIXEL 1
#define ATST_PASS_PIXEL_IF_MATCHES 2
#define ATST_PASS_PIXEL_IF_DIFFERS 3
#define ATST_PASS_PIXEL_IF_LESS 4
#define ATST_PASS_PIXEL_IF_LESS_OR_EQUAL 5
#define ATST_PASS_PIXEL_IF_GREATER 6
#define ATST_PASS_PIXEL_IF_GREATER_OR_EQUAL 7

#define  TPSM_PIXEL_STORAGE_MODE_16BIT_BGR5650 0
#define  TPSM_PIXEL_STORAGE_MODE_16BIT_ABGR5551 1
#define  TPSM_PIXEL_STORAGE_MODE_16BIT_ABGR4444 2
#define  TPSM_PIXEL_STORAGE_MODE_32BIT_ABGR8888 3
#define  TPSM_PIXEL_STORAGE_MODE_4BIT_INDEXED 4
#define  TPSM_PIXEL_STORAGE_MODE_8BIT_INDEXED 5
#define  TPSM_PIXEL_STORAGE_MODE_16BIT_INDEXED 6
#define  TPSM_PIXEL_STORAGE_MODE_32BIT_INDEXED 7
#define  TPSM_PIXEL_STORAGE_MODE_DXT1 8
#define  TPSM_PIXEL_STORAGE_MODE_DXT3 9
#define  TPSM_PIXEL_STORAGE_MODE_DXT5 10

#define CMODE_FORMAT_16BIT_BGR5650 0
#define CMODE_FORMAT_16BIT_ABGR5551 1
#define CMODE_FORMAT_16BIT_ABGR4444 2
#define CMODE_FORMAT_32BIT_ABGR8888 3


#define TFLT_NEAREST 0
#define TFLT_LINEAR 1
#define TFLT_UNKNOW1 2
#define TFLT_UNKNOW2 3
#define TFLT_NEAREST_MIPMAP_NEAREST 4
#define TFLT_LINEAR_MIPMAP_NEAREST 5
#define TFLT_NEAREST_MIPMAP_LINEAR 6
#define TFLT_LINEAR_MIPMAP_LINEAR 7

#define TWRAP_WRAP_MODE_REPEAT 0
#define TWRAP_WRAP_MODE_CLAMP 1

#define TFUNC_FRAGMENT_DOUBLE_ENABLE_COLOR_UNTOUCHED 0
#define TFUNC_FRAGMENT_DOUBLE_ENABLE_COLOR_DOUBLED 1
#define TFUNC_FRAGMENT_DOUBLE_TEXTURE_COLOR_ALPHA_IS_IGNORED 0
#define TFUNC_FRAGMENT_DOUBLE_TEXTURE_COLOR_ALPHA_IS_READ 1
#define TFUNC_FRAGMENT_DOUBLE_TEXTURE_EFECT_MODULATE 0
#define TFUNC_FRAGMENT_DOUBLE_TEXTURE_EFECT_DECAL 1
#define TFUNC_FRAGMENT_DOUBLE_TEXTURE_EFECT_BLEND 2
#define TFUNC_FRAGMENT_DOUBLE_TEXTURE_EFECT_REPLACE 3
#define TFUNC_FRAGMENT_DOUBLE_TEXTURE_EFECT_ADD 4
#define TFUNC_FRAGMENT_DOUBLE_TEXTURE_EFECT_UNKNOW1 5
#define TFUNC_FRAGMENT_DOUBLE_TEXTURE_EFECT_UNKNOW2 6
#define TFUNC_FRAGMENT_DOUBLE_TEXTURE_EFECT_UNKNOW3 7
#endif // ge_Constants_h__