#ifndef gl_Core_h__
#define gl_Core_h__

#undef NO_ERROR
#undef DOMAIN

class gl_Core
{
    friend class gl_VertexBufferObject;
    friend class gl_IndexBufferObject;

public:
    void Initialize();
    void Terminate();

    gl_Core()  {}
    ~gl_Core() {}

    static bool framebuffer_object;
    static bool texture_lod_bias;
    static bool depth_bounds_test;

    static bool version_1_5;

protected:
    enum GLenum_AttribMask
    {
        CURRENT_BIT                    = 0x00000001,
        POINT_BIT                      = 0x00000002,
        LINE_BIT                       = 0x00000004,
        POLYGON_BIT                    = 0x00000008,
        POLYGON_STIPPLE_BIT            = 0x00000010,
        PIXEL_MODE_BIT                 = 0x00000020,
        LIGHTING_BIT                   = 0x00000040,
        FOG_BIT                        = 0x00000080,
        DEPTH_BUFFER_BIT               = 0x00000100,
        ACCUM_BUFFER_BIT               = 0x00000200,
        STENCIL_BUFFER_BIT             = 0x00000400,
        VIEWPORT_BIT                   = 0x00000800,
        TRANSFORM_BIT                  = 0x00001000,
        ENABLE_BIT                     = 0x00002000,
        COLOR_BUFFER_BIT               = 0x00004000,
        HINT_BIT                       = 0x00008000,
        EVAL_BIT                       = 0x00010000,
        LIST_BIT                       = 0x00020000,
        TEXTURE_BIT                    = 0x00040000,
        SCISSOR_BIT                    = 0x00080000,
        ALL_ATTRIB_BITS                = 0x000FFFFF
    };

    enum GLenum_Core_1_1
    {
        ACCUM                          = 0x0100,
        LOAD                           = 0x0101,
        RETURN                         = 0x0102,
        MULT                           = 0x0103,
        ADD                            = 0x0104,

        POINTS                         = 0x0000,
        LINES                          = 0x0001,
        LINE_LOOP                      = 0x0002,
        LINE_STRIP                     = 0x0003,
        TRIANGLES                      = 0x0004,
        TRIANGLE_STRIP                 = 0x0005,
        TRIANGLE_FAN                   = 0x0006,
        QUADS                          = 0x0007,
        QUAD_STRIP                     = 0x0008,
        POLYGON                        = 0x0009,

        NEVER                          = 0x0200,
        LESS                           = 0x0201,
        EQUAL                          = 0x0202,
        LEQUAL                         = 0x0203,
        GREATER                        = 0x0204,
        NOTEQUAL                       = 0x0205,
        GEQUAL                         = 0x0206,
        ALWAYS                         = 0x0207,

        ZERO                           = 0,
        ONE                            = 1,
        SRC_COLOR                      = 0x0300,
        ONE_MINUS_SRC_COLOR            = 0x0301,
        SRC_ALPHA                      = 0x0302,
        ONE_MINUS_SRC_ALPHA            = 0x0303,
        DST_ALPHA                      = 0x0304,
        ONE_MINUS_DST_ALPHA            = 0x0305,

        DST_COLOR                      = 0x0306,
        ONE_MINUS_DST_COLOR            = 0x0307,
        SRC_ALPHA_SATURATE             = 0x0308,

        NONE                           = 0,
        FRONT_LEFT                     = 0x0400,
        FRONT_RIGHT                    = 0x0401,
        BACK_LEFT                      = 0x0402,
        BACK_RIGHT                     = 0x0403,
        FRONT                          = 0x0404,
        BACK                           = 0x0405,
        LEFT                           = 0x0406,
        RIGHT                          = 0x0407,
        FRONT_AND_BACK                 = 0x0408,
        AUX0                           = 0x0409,
        AUX1                           = 0x040A,
        AUX2                           = 0x040B,
        AUX3                           = 0x040C,

        NO_ERROR                       = 0,
        INVALID_ENUM                   = 0x0500,
        INVALID_VALUE                  = 0x0501,
        INVALID_OPERATION              = 0x0502,
        STACK_OVERFLOW                 = 0x0503,
        STACK_UNDERFLOW                = 0x0504,
        OUT_OF_MEMORY                  = 0x0505,

        PASS_THROUGH_TOKEN             = 0x0700,
        POINT_TOKEN                    = 0x0701,
        LINE_TOKEN                     = 0x0702,
        POLYGON_TOKEN                  = 0x0703,
        BITMAP_TOKEN                   = 0x0704,
        DRAW_PIXEL_TOKEN               = 0x0705,
        COPY_PIXEL_TOKEN               = 0x0706,
        LINE_RESET_TOKEN               = 0x0707,


        EXP                            = 0x0800,
        EXP2                           = 0x0801,

        CW                             = 0x0900,
        CCW                            = 0x0901,

        COEFF                          = 0x0A00,
        ORDER                          = 0x0A01,
        DOMAIN                         = 0x0A02,

        CURRENT_COLOR                  = 0x0B00,
        CURRENT_INDEX                  = 0x0B01,
        CURRENT_NORMAL                 = 0x0B02,
        CURRENT_TEXTURE_COORDS         = 0x0B03,
        CURRENT_RASTER_COLOR           = 0x0B04,
        CURRENT_RASTER_INDEX           = 0x0B05,
        CURRENT_RASTER_TEXTURE_COORDS  = 0x0B06,
        CURRENT_RASTER_POSITION        = 0x0B07,
        CURRENT_RASTER_POSITION_VALID  = 0x0B08,
        CURRENT_RASTER_DISTANCE        = 0x0B09,
        POINT_SMOOTH                   = 0x0B10,
        POINT_SIZE                     = 0x0B11,
        POINT_SIZE_RANGE               = 0x0B12,
        POINT_SIZE_GRANULARITY         = 0x0B13,
        LINE_SMOOTH                    = 0x0B20,
        LINE_WIDTH                     = 0x0B21,
        LINE_WIDTH_RANGE               = 0x0B22,
        LINE_WIDTH_GRANULARITY         = 0x0B23,
        LINE_STIPPLE                   = 0x0B24,
        LINE_STIPPLE_PATTERN           = 0x0B25,
        LINE_STIPPLE_REPEAT            = 0x0B26,
        LIST_MODE                      = 0x0B30,
        MAX_LIST_NESTING               = 0x0B31,
        LIST_BASE                      = 0x0B32,
        LIST_INDEX                     = 0x0B33,
        POLYGON_MODE                   = 0x0B40,
        POLYGON_SMOOTH                 = 0x0B41,
        POLYGON_STIPPLE                = 0x0B42,
        EDGE_FLAG                      = 0x0B43,
        CULL_FACE                      = 0x0B44,
        CULL_FACE_MODE                 = 0x0B45,
        FRONT_FACE                     = 0x0B46,
        LIGHTING                       = 0x0B50,
        LIGHT_MODEL_LOCAL_VIEWER       = 0x0B51,
        LIGHT_MODEL_TWO_SIDE           = 0x0B52,
        LIGHT_MODEL_AMBIENT            = 0x0B53,
        SHADE_MODEL                    = 0x0B54,
        COLOR_MATERIAL_FACE            = 0x0B55,
        COLOR_MATERIAL_PARAMETER       = 0x0B56,
        COLOR_MATERIAL                 = 0x0B57,
        FOG                            = 0x0B60,
        FOG_INDEX                      = 0x0B61,
        FOG_DENSITY                    = 0x0B62,
        FOG_START                      = 0x0B63,
        FOG_END                        = 0x0B64,
        FOG_MODE                       = 0x0B65,
        FOG_COLOR                      = 0x0B66,
        DEPTH_RANGE                    = 0x0B70,
        DEPTH_TEST                     = 0x0B71,
        DEPTH_WRITEMASK                = 0x0B72,
        DEPTH_CLEAR_VALUE              = 0x0B73,
        DEPTH_FUNC                     = 0x0B74,
        ACCUM_CLEAR_VALUE              = 0x0B80,
        STENCIL_TEST                   = 0x0B90,
        STENCIL_CLEAR_VALUE            = 0x0B91,
        STENCIL_FUNC                   = 0x0B92,
        STENCIL_VALUE_MASK             = 0x0B93,
        STENCIL_FAIL                   = 0x0B94,
        STENCIL_PASS_DEPTH_FAIL        = 0x0B95,
        STENCIL_PASS_DEPTH_PASS        = 0x0B96,
        STENCIL_REF                    = 0x0B97,
        STENCIL_WRITEMASK              = 0x0B98,
        MATRIX_MODE                    = 0x0BA0,
        NORMALIZE                      = 0x0BA1,
        VIEWPORT                       = 0x0BA2,
        MODELVIEW_STACK_DEPTH          = 0x0BA3,
        PROJECTION_STACK_DEPTH         = 0x0BA4,
        TEXTURE_STACK_DEPTH            = 0x0BA5,
        MODELVIEW_MATRIX               = 0x0BA6,
        PROJECTION_MATRIX              = 0x0BA7,
        TEXTURE_MATRIX                 = 0x0BA8,
        ATTRIB_STACK_DEPTH             = 0x0BB0,
        CLIENT_ATTRIB_STACK_DEPTH      = 0x0BB1,
        ALPHA_TEST                     = 0x0BC0,
        ALPHA_TEST_FUNC                = 0x0BC1,
        ALPHA_TEST_REF                 = 0x0BC2,
        DITHER                         = 0x0BD0,
        BLEND_DST                      = 0x0BE0,
        BLEND_SRC                      = 0x0BE1,
        BLEND                          = 0x0BE2,
        LOGIC_OP_MODE                  = 0x0BF0,
        INDEX_LOGIC_OP                 = 0x0BF1,
        COLOR_LOGIC_OP                 = 0x0BF2,
        AUX_BUFFERS                    = 0x0C00,
        DRAW_BUFFER                    = 0x0C01,
        READ_BUFFER                    = 0x0C02,
        SCISSOR_BOX                    = 0x0C10,
        SCISSOR_TEST                   = 0x0C11,
        INDEX_CLEAR_VALUE              = 0x0C20,
        INDEX_WRITEMASK                = 0x0C21,
        COLOR_CLEAR_VALUE              = 0x0C22,
        COLOR_WRITEMASK                = 0x0C23,
        INDEX_MODE                     = 0x0C30,
        RGBA_MODE                      = 0x0C31,
        DOUBLEBUFFER                   = 0x0C32,
        STEREO                         = 0x0C33,
        RENDER_MODE                    = 0x0C40,
        PERSPECTIVE_CORRECTION_HINT    = 0x0C50,
        POINT_SMOOTH_HINT              = 0x0C51,
        LINE_SMOOTH_HINT               = 0x0C52,
        POLYGON_SMOOTH_HINT            = 0x0C53,
        FOG_HINT                       = 0x0C54,
        TEXTURE_GEN_S                  = 0x0C60,
        TEXTURE_GEN_T                  = 0x0C61,
        TEXTURE_GEN_R                  = 0x0C62,
        TEXTURE_GEN_Q                  = 0x0C63,
        PIXEL_MAP_I_TO_I               = 0x0C70,
        PIXEL_MAP_S_TO_S               = 0x0C71,
        PIXEL_MAP_I_TO_R               = 0x0C72,
        PIXEL_MAP_I_TO_G               = 0x0C73,
        PIXEL_MAP_I_TO_B               = 0x0C74,
        PIXEL_MAP_I_TO_A               = 0x0C75,
        PIXEL_MAP_R_TO_R               = 0x0C76,
        PIXEL_MAP_G_TO_G               = 0x0C77,
        PIXEL_MAP_B_TO_B               = 0x0C78,
        PIXEL_MAP_A_TO_A               = 0x0C79,
        PIXEL_MAP_I_TO_I_SIZE          = 0x0CB0,
        PIXEL_MAP_S_TO_S_SIZE          = 0x0CB1,
        PIXEL_MAP_I_TO_R_SIZE          = 0x0CB2,
        PIXEL_MAP_I_TO_G_SIZE          = 0x0CB3,
        PIXEL_MAP_I_TO_B_SIZE          = 0x0CB4,
        PIXEL_MAP_I_TO_A_SIZE          = 0x0CB5,
        PIXEL_MAP_R_TO_R_SIZE          = 0x0CB6,
        PIXEL_MAP_G_TO_G_SIZE          = 0x0CB7,
        PIXEL_MAP_B_TO_B_SIZE          = 0x0CB8,
        PIXEL_MAP_A_TO_A_SIZE          = 0x0CB9,
        UNPACK_SWAP_BYTES              = 0x0CF0,
        UNPACK_LSB_FIRST               = 0x0CF1,
        UNPACK_ROW_LENGTH              = 0x0CF2,
        UNPACK_SKIP_ROWS               = 0x0CF3,
        UNPACK_SKIP_PIXELS             = 0x0CF4,
        UNPACK_ALIGNMENT               = 0x0CF5,
        PACK_SWAP_BYTES                = 0x0D00,
        PACK_LSB_FIRST                 = 0x0D01,
        PACK_ROW_LENGTH                = 0x0D02,
        PACK_SKIP_ROWS                 = 0x0D03,
        PACK_SKIP_PIXELS               = 0x0D04,
        PACK_ALIGNMENT                 = 0x0D05,
        MAP_COLOR                      = 0x0D10,
        MAP_STENCIL                    = 0x0D11,
        INDEX_SHIFT                    = 0x0D12,
        INDEX_OFFSET                   = 0x0D13,
        RED_SCALE                      = 0x0D14,
        RED_BIAS                       = 0x0D15,
        ZOOM_X                         = 0x0D16,
        ZOOM_Y                         = 0x0D17,
        GREEN_SCALE                    = 0x0D18,
        GREEN_BIAS                     = 0x0D19,
        BLUE_SCALE                     = 0x0D1A,
        BLUE_BIAS                      = 0x0D1B,
        ALPHA_SCALE                    = 0x0D1C,
        ALPHA_BIAS                     = 0x0D1D,
        DEPTH_SCALE                    = 0x0D1E,
        DEPTH_BIAS                     = 0x0D1F,
        MAX_EVAL_ORDER                 = 0x0D30,
        MAX_LIGHTS                     = 0x0D31,
        MAX_CLIP_PLANES                = 0x0D32,
        MAX_TEXTURE_SIZE               = 0x0D33,
        MAX_PIXEL_MAP_TABLE            = 0x0D34,
        MAX_ATTRIB_STACK_DEPTH         = 0x0D35,
        MAX_MODELVIEW_STACK_DEPTH      = 0x0D36,
        MAX_NAME_STACK_DEPTH           = 0x0D37,
        MAX_PROJECTION_STACK_DEPTH     = 0x0D38,
        MAX_TEXTURE_STACK_DEPTH        = 0x0D39,
        MAX_VIEWPORT_DIMS              = 0x0D3A,
        MAX_CLIENT_ATTRIB_STACK_DEPTH  = 0x0D3B,
        SUBPIXEL_BITS                  = 0x0D50,
        INDEX_BITS                     = 0x0D51,
        RED_BITS                       = 0x0D52,
        GREEN_BITS                     = 0x0D53,
        BLUE_BITS                      = 0x0D54,
        ALPHA_BITS                     = 0x0D55,
        DEPTH_BITS                     = 0x0D56,
        STENCIL_BITS                   = 0x0D57,
        ACCUM_RED_BITS                 = 0x0D58,
        ACCUM_GREEN_BITS               = 0x0D59,
        ACCUM_BLUE_BITS                = 0x0D5A,
        ACCUM_ALPHA_BITS               = 0x0D5B,
        NAME_STACK_DEPTH               = 0x0D70,
        AUTO_NORMAL                    = 0x0D80,
        MAP1_COLOR_4                   = 0x0D90,
        MAP1_INDEX                     = 0x0D91,
        MAP1_NORMAL                    = 0x0D92,
        MAP1_TEXTURE_COORD_1           = 0x0D93,
        MAP1_TEXTURE_COORD_2           = 0x0D94,
        MAP1_TEXTURE_COORD_3           = 0x0D95,
        MAP1_TEXTURE_COORD_4           = 0x0D96,
        MAP1_VERTEX_3                  = 0x0D97,
        MAP1_VERTEX_4                  = 0x0D98,
        MAP2_COLOR_4                   = 0x0DB0,
        MAP2_INDEX                     = 0x0DB1,
        MAP2_NORMAL                    = 0x0DB2,
        MAP2_TEXTURE_COORD_1           = 0x0DB3,
        MAP2_TEXTURE_COORD_2           = 0x0DB4,
        MAP2_TEXTURE_COORD_3           = 0x0DB5,
        MAP2_TEXTURE_COORD_4           = 0x0DB6,
        MAP2_VERTEX_3                  = 0x0DB7,
        MAP2_VERTEX_4                  = 0x0DB8,
        MAP1_GRID_DOMAIN               = 0x0DD0,
        MAP1_GRID_SEGMENTS             = 0x0DD1,
        MAP2_GRID_DOMAIN               = 0x0DD2,
        MAP2_GRID_SEGMENTS             = 0x0DD3,
        TEXTURE_1D                     = 0x0DE0,
        TEXTURE_2D                     = 0x0DE1,
        FEEDBACK_BUFFER_POINTER        = 0x0DF0,
        FEEDBACK_BUFFER_SIZE           = 0x0DF1,
        FEEDBACK_BUFFER_TYPE           = 0x0DF2,
        SELECTION_BUFFER_POINTER       = 0x0DF3,
        SELECTION_BUFFER_SIZE          = 0x0DF4,

        TEXTURE_WIDTH                  = 0x1000,
        TEXTURE_HEIGHT                 = 0x1001,
        TEXTURE_INTERNAL_FORMAT        = 0x1003,
        TEXTURE_BORDER_COLOR           = 0x1004,
        TEXTURE_BORDER                 = 0x1005,

        DONT_CARE                      = 0x1100,
        FASTEST                        = 0x1101,
        NICEST                         = 0x1102,

        LIGHT0                         = 0x4000,
        LIGHT1                         = 0x4001,
        LIGHT2                         = 0x4002,
        LIGHT3                         = 0x4003,
        LIGHT4                         = 0x4004,
        LIGHT5                         = 0x4005,
        LIGHT6                         = 0x4006,
        LIGHT7                         = 0x4007,

        AMBIENT                        = 0x1200,
        DIFFUSE                        = 0x1201,
        SPECULAR                       = 0x1202,
        POSITION                       = 0x1203,
        SPOT_DIRECTION                 = 0x1204,
        SPOT_EXPONENT                  = 0x1205,
        SPOT_CUTOFF                    = 0x1206,
        CONSTANT_ATTENUATION           = 0x1207,
        LINEAR_ATTENUATION             = 0x1208,
        QUADRATIC_ATTENUATION          = 0x1209,

        COMPILE                        = 0x1300,
        COMPILE_AND_EXECUTE            = 0x1301,

        BYTE                           = 0x1400,
        UNSIGNED_BYTE                  = 0x1401,
        SHORT                          = 0x1402,
        UNSIGNED_SHORT                 = 0x1403,
        INT                            = 0x1404,
        UNSIGNED_INT                   = 0x1405,
        FLOAT                          = 0x1406,
        DOUBLE                         = 0x140A,

        CLEAR                          = 0x1500,
        AND                            = 0x1501,
        AND_REVERSE                    = 0x1502,
        COPY                           = 0x1503,
        AND_INVERTED                   = 0x1504,
        NOOP                           = 0x1505,
        XOR                            = 0x1506,
        OR                             = 0x1507,
        NOR                            = 0x1508,
        EQUIV                          = 0x1509,
        INVERT                         = 0x150A,
        OR_REVERSE                     = 0x150B,
        COPY_INVERTED                  = 0x150C,
        OR_INVERTED                    = 0x150D,
        NAND                           = 0x150E,
        SET                            = 0x150F,

        EMISSION                       = 0x1600,
        SHININESS                      = 0x1601,
        AMBIENT_AND_DIFFUSE            = 0x1602,
        COLOR_INDEXES                  = 0x1603,

        MODELVIEW                      = 0x1700,
        PROJECTION                     = 0x1701,
        TEXTURE                        = 0x1702,

        COLOR                          = 0x1800,
        DEPTH                          = 0x1801,
        STENCIL                        = 0x1802,

        COLOR_INDEX                    = 0x1900,
        STENCIL_INDEX                  = 0x1901,
        DEPTH_COMPONENT                = 0x1902,
        RED                            = 0x1903,
        GREEN                          = 0x1904,
        BLUE                           = 0x1905,
        ALPHA                          = 0x1906,
        RGB                            = 0x1907,
        RGBA                           = 0x1908,
        LUMINANCE                      = 0x1909,
        LUMINANCE_ALPHA                = 0x190A,

        BITMAP                         = 0x1A00,

        POINT                          = 0x1B00,
        LINE                           = 0x1B01,
        FILL                           = 0x1B02,

        RENDER                         = 0x1C00,
        FEEDBACK                       = 0x1C01,
        SELECT                         = 0x1C02,

        FLAT                           = 0x1D00,
        SMOOTH                         = 0x1D01,

        KEEP                           = 0x1E00,
        REPLACE                        = 0x1E01,
        INCR                           = 0x1E02,
        DECR                           = 0x1E03,

        VENDOR                         = 0x1F00,
        RENDERER                       = 0x1F01,
        VERSION                        = 0x1F02,
        EXTENSIONS                     = 0x1F03,

        S                              = 0x2000,
        T                              = 0x2001,
        R                              = 0x2002,
        Q                              = 0x2003,

        MODULATE                       = 0x2100,
        DECAL                          = 0x2101,

        TEXTURE_ENV_MODE               = 0x2200,
        TEXTURE_ENV_COLOR              = 0x2201,

        TEXTURE_ENV                    = 0x2300,

        EYE_LINEAR                     = 0x2400,
        OBJECT_LINEAR                  = 0x2401,
        SPHERE_MAP                     = 0x2402,

        TEXTURE_GEN_MODE               = 0x2500,
        OBJECT_PLANE                   = 0x2501,
        EYE_PLANE                      = 0x2502,

        NEAREST                        = 0x2600,
        LINEAR                         = 0x2601,

        NEAREST_MIPMAP_NEAREST         = 0x2700,
        LINEAR_MIPMAP_NEAREST          = 0x2701,
        NEAREST_MIPMAP_LINEAR          = 0x2702,
        LINEAR_MIPMAP_LINEAR           = 0x2703,

        TEXTURE_MAG_FILTER             = 0x2800,
        TEXTURE_MIN_FILTER             = 0x2801,
        TEXTURE_WRAP_S                 = 0x2802,
        TEXTURE_WRAP_T                 = 0x2803,

        CLAMP                          = 0x2900,
        REPEAT                         = 0x2901,

        CLIP_PLANE0                    = 0x3000,
        CLIP_PLANE1                    = 0x3001,
        CLIP_PLANE2                    = 0x3002,
        CLIP_PLANE3                    = 0x3003,
        CLIP_PLANE4                    = 0x3004,
        CLIP_PLANE5                    = 0x3005,

        LOGIC_OP                       = INDEX_LOGIC_OP,

    };

    __forceinline static void              Accum(GLenum op, GLfloat value) { glAccum(op, value); }
    __forceinline static void              AlphaFunc(GLenum func, GLclampf ref) { glAlphaFunc(func, ref); }
    __forceinline static GLboolean         AreTexturesResident(GLsizei n, const GLuint *textures, GLboolean *residences) { glAreTexturesResident(n, textures, residences); }
    __forceinline static void              ArrayElement(GLint i) { glArrayElement(i); }
    __forceinline static void              Begin(GLenum mode) { glBegin(mode); }
    __forceinline static void              BindTexture(GLenum target, GLuint texture) { glBindTexture(target, texture); }
    __forceinline static void              Bitmap(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap) { glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap); }
    __forceinline static void              BlendFunc(GLenum sfactor, GLenum dfactor) { glBlendFunc(sfactor, dfactor); }
    __forceinline static void              CallList(GLuint list) { glCallList(list); }
    __forceinline static void              CallLists(GLsizei n, GLenum type, const GLvoid *lists) { glCallLists(n, type, lists); }
    __forceinline static void              Clear(GLbitfield mask) { glClear(mask); }
    __forceinline static void              ClearAccum(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) { glClearAccum(red, green, blue, alpha); }
    __forceinline static void              ClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) { glClearColor(red, green, blue, alpha); }
    __forceinline static void              ClearDepth(GLclampd depth) { glClearDepth(depth); }
    __forceinline static void              ClearIndex(GLfloat c) { glClearIndex(c); }
    __forceinline static void              ClearStencil(GLint s) { glClearStencil(s); }
    __forceinline static void              ClipPlane(GLenum plane, const GLdouble *equation) { glClipPlane(plane, equation); }
    __forceinline static void              Color3b(GLbyte red, GLbyte green, GLbyte blue) { glColor3b(red, green, blue); }
    __forceinline static void              Color3bv(const GLbyte *v) { glColor3bv(v); }
    __forceinline static void              Color3d(GLdouble red, GLdouble green, GLdouble blue) { glColor3d(red, green, blue); }
    __forceinline static void              Color3dv(const GLdouble *v) { glColor3dv(v); }
    __forceinline static void              Color3f(GLfloat red, GLfloat green, GLfloat blue) { glColor3f(red, green, blue); }
    __forceinline static void              Color3fv(const GLfloat *v) { glColor3fv(v); }
    __forceinline static void              Color3i(GLint red, GLint green, GLint blue) { glColor3i(red, green, blue); }
    __forceinline static void              Color3iv(const GLint *v) { glColor3iv(v); }
    __forceinline static void              Color3s(GLshort red, GLshort green, GLshort blue) { glColor3s(red, green, blue); }
    __forceinline static void              Color3sv(const GLshort *v) { glColor3sv(v); }
    __forceinline static void              Color3ub(GLubyte red, GLubyte green, GLubyte blue) { glColor3ub(red, green, blue); }
    __forceinline static void              Color3ubv(const GLubyte *v) { glColor3ubv(v); }
    __forceinline static void              Color3ui(GLuint red, GLuint green, GLuint blue) { glColor3ui(red, green, blue); }
    __forceinline static void              Color3uiv(const GLuint *v) { glColor3uiv(v); }
    __forceinline static void              Color3us(GLushort red, GLushort green, GLushort blue) { glColor3us(red, green, blue); }
    __forceinline static void              Color3usv(const GLushort *v) { glColor3usv(v); }
    __forceinline static void              Color4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha) { glColor4b(red, green, blue, alpha); }
    __forceinline static void              Color4bv(const GLbyte *v) { glColor4bv(v); }
    __forceinline static void              Color4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha) { glColor4d(red, green, blue, alpha); }
    __forceinline static void              Color4dv(const GLdouble *v) { glColor4dv(v); }
    __forceinline static void              Color4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) { glColor4f(red, green, blue, alpha); }
    __forceinline static void              Color4fv(const GLfloat *v) { glColor4fv(v); }
    __forceinline static void              Color4i(GLint red, GLint green, GLint blue, GLint alpha) { glColor4i(red, green, blue, alpha); }
    __forceinline static void              Color4iv(const GLint *v) { glColor4iv(v); }
    __forceinline static void              Color4s(GLshort red, GLshort green, GLshort blue, GLshort alpha) { glColor4s(red, green, blue, alpha); }
    __forceinline static void              Color4sv(const GLshort *v) { glColor4sv(v); }
    __forceinline static void              Color4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) { glColor4ub(red, green, blue, alpha); }
    __forceinline static void              Color4ubv(const GLubyte *v) { glColor4ubv(v); }
    __forceinline static void              Color4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha) { glColor4ui(red, green, blue, alpha); }
    __forceinline static void              Color4uiv(const GLuint *v) { glColor4uiv(v); }
    __forceinline static void              Color4us(GLushort red, GLushort green, GLushort blue, GLushort alpha) { glColor4us(red, green, blue, alpha); }
    __forceinline static void              Color4usv(const GLushort *v) { glColor4usv(v); }
    __forceinline static void              ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) { glColorMask(red, green, blue, alpha); }
    __forceinline static void              ColorMaterial(GLenum face, GLenum mode) { glColorMaterial(face, mode); }
    __forceinline static void              ColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) { glColorPointer(size, type, stride, pointer); }
    __forceinline static void              CopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type) { glCopyPixels(x, y, width, height, type); }
    __forceinline static void              CopyTexImage1D(GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border) { glCopyTexImage1D(target, level, internalFormat, x, y, width, border); }
    __forceinline static void              CopyTexImage2D(GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) { glCopyTexImage2D(target, level, internalFormat, x, y, width, height, border); }
    __forceinline static void              CopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) { glCopyTexSubImage1D(target, level, xoffset, x, y, width); }
    __forceinline static void              CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) { glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height); }
    __forceinline static void              CullFace(GLenum mode) { glCullFace(mode); }
    __forceinline static void              DeleteLists(GLuint list, GLsizei range) { glDeleteLists(list, range); }
    __forceinline static void              DeleteTextures(GLsizei n, const GLuint *textures) { glDeleteTextures(n, textures); }
    __forceinline static void              DepthFunc(GLenum func) { glDepthFunc(func); }
    __forceinline static void              DepthMask(GLboolean flag) { glDepthMask(flag); }
    __forceinline static void              DepthRange(GLclampd zNear, GLclampd zFar) { glDepthRange(zNear, zFar); }
    __forceinline static void              Disable(GLenum cap) { glDisable(cap); }
    __forceinline static void              DisableClientState(GLenum array) { glDisableClientState(array); }
    __forceinline static void              DrawArrays(GLenum mode, GLint first, GLsizei count) { glDrawArrays(mode, first, count); }
    __forceinline static void              DrawBuffer(GLenum mode) { glDrawBuffer(mode); }
    __forceinline static void              DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices) { glDrawElements(mode, count, type, indices); }
    __forceinline static void              DrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) { glDrawPixels(width, height, format, type, pixels); }
    __forceinline static void              EdgeFlag(GLboolean flag) { glEdgeFlag(flag); }
    __forceinline static void              EdgeFlagPointer(GLsizei stride, const GLvoid *pointer) { glEdgeFlagPointer(stride, pointer); }
    __forceinline static void              EdgeFlagv(const GLboolean *flag) { glEdgeFlagv(flag); }
    __forceinline static void              Enable(GLenum cap) { glEnable(cap); }
    __forceinline static void              EnableClientState(GLenum array) { glEnableClientState(array); }
    __forceinline static void              End(void) { glEnd(); }
    __forceinline static void              EndList(void) { glEndList(); }
    __forceinline static void              EvalCoord1d(GLdouble u) { glEvalCoord1d(u); }
    __forceinline static void              EvalCoord1dv(const GLdouble *u) { glEvalCoord1dv(u); }
    __forceinline static void              EvalCoord1f(GLfloat u) { glEvalCoord1f(u); }
    __forceinline static void              EvalCoord1fv(const GLfloat *u) { glEvalCoord1fv(u); }
    __forceinline static void              EvalCoord2d(GLdouble u, GLdouble v) { glEvalCoord2d(u, v); }
    __forceinline static void              EvalCoord2dv(const GLdouble *u) { glEvalCoord2dv(u); }
    __forceinline static void              EvalCoord2f(GLfloat u, GLfloat v) { glEvalCoord2f(u, v); }
    __forceinline static void              EvalCoord2fv(const GLfloat *u) { glEvalCoord2fv(u); }
    __forceinline static void              EvalMesh1(GLenum mode, GLint i1, GLint i2) { glEvalMesh1(mode, i1, i2); }
    __forceinline static void              EvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2) { glEvalMesh2(mode, i1, i2, j1, j2); }
    __forceinline static void              EvalPoint1(GLint i) { glEvalPoint1(i); }
    __forceinline static void              EvalPoint2(GLint i, GLint j) { glEvalPoint2(i, j); }
    __forceinline static void              FeedbackBuffer(GLsizei size, GLenum type, GLfloat *buffer) { glFeedbackBuffer(size, type, buffer); }
    __forceinline static void              Finish(void) { glFinish(); }
    __forceinline static void              Flush(void) { glFlush(); }
    __forceinline static void              Fogf(GLenum pname, GLfloat param) { glFogf(pname, param); }
    __forceinline static void              Fogfv(GLenum pname, const GLfloat *params) { glFogfv(pname, params); }
    __forceinline static void              Fogi(GLenum pname, GLint param) { glFogi(pname, param); }
    __forceinline static void              Fogiv(GLenum pname, const GLint *params) { glFogiv(pname, params); }
    __forceinline static void              FrontFace(GLenum mode) { glFrontFace(mode); }
    __forceinline static void              Frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) { glFrustum(left, right, bottom, top, zNear, zFar); }
    __forceinline static GLuint            GenLists(GLsizei range) { glGenLists(range); }
    __forceinline static void              GenTextures(GLsizei n, GLuint *textures) { glGenTextures(n, textures); }
    __forceinline static void              GetBooleanv(GLenum pname, GLboolean *params) { glGetBooleanv(pname, params); }
    __forceinline static void              GetClipPlane(GLenum plane, GLdouble *equation) { glGetClipPlane(plane, equation); }
    __forceinline static void              GetDoublev(GLenum pname, GLdouble *params) { glGetDoublev(pname, params); }
    __forceinline static GLenum            GetError(void) { glGetError(); }
    __forceinline static void              GetFloatv(GLenum pname, GLfloat *params) { glGetFloatv(pname, params); }
    __forceinline static void              GetIntegerv(GLenum pname, GLint *params) { glGetIntegerv(pname, params); }
    __forceinline static void              GetLightfv(GLenum light, GLenum pname, GLfloat *params) { glGetLightfv(light, pname, params); }
    __forceinline static void              GetLightiv(GLenum light, GLenum pname, GLint *params) { glGetLightiv(light, pname, params); }
    __forceinline static void              GetMapdv(GLenum target, GLenum query, GLdouble *v) { glGetMapdv(target, query, v); }
    __forceinline static void              GetMapfv(GLenum target, GLenum query, GLfloat *v) { glGetMapfv(target, query, v); }
    __forceinline static void              GetMapiv(GLenum target, GLenum query, GLint *v) { glGetMapiv(target, query, v); }
    __forceinline static void              GetMaterialfv(GLenum face, GLenum pname, GLfloat *params) { glGetMaterialfv(face, pname, params); }
    __forceinline static void              GetMaterialiv(GLenum face, GLenum pname, GLint *params) { glGetMaterialiv(face, pname, params); }
    __forceinline static void              GetPixelMapfv(GLenum map, GLfloat *values) { glGetPixelMapfv(map, values); }
    __forceinline static void              GetPixelMapuiv(GLenum map, GLuint *values) { glGetPixelMapuiv(map, values); }
    __forceinline static void              GetPixelMapusv(GLenum map, GLushort *values) { glGetPixelMapusv(map, values); }
    __forceinline static void              GetPointerv(GLenum pname, GLvoid* *params) { glGetPointerv(pname, params); }
    __forceinline static void              GetPolygonStipple(GLubyte *mask) { glGetPolygonStipple(mask); }
    __forceinline static const GLubyte *   GetString(GLenum name) { glGetString(name); }
    __forceinline static void              GetTexEnvfv(GLenum target, GLenum pname, GLfloat *params) { glGetTexEnvfv(target, pname, params); }
    __forceinline static void              GetTexEnviv(GLenum target, GLenum pname, GLint *params) { glGetTexEnviv(target, pname, params); }
    __forceinline static void              GetTexGendv(GLenum coord, GLenum pname, GLdouble *params) { glGetTexGendv(coord, pname, params); }
    __forceinline static void              GetTexGenfv(GLenum coord, GLenum pname, GLfloat *params) { glGetTexGenfv(coord, pname, params); }
    __forceinline static void              GetTexGeniv(GLenum coord, GLenum pname, GLint *params) { glGetTexGeniv(coord, pname, params); }
    __forceinline static void              GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels) { glGetTexImage(target, level, format, type, pixels); }
    __forceinline static void              GetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat *params) { glGetTexLevelParameterfv(target, level, pname, params); }
    __forceinline static void              GetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint *params) { glGetTexLevelParameteriv(target, level, pname, params); }
    __forceinline static void              GetTexParameterfv(GLenum target, GLenum pname, GLfloat *params) { glGetTexParameterfv(target, pname, params); }
    __forceinline static void              GetTexParameteriv(GLenum target, GLenum pname, GLint *params) { glGetTexParameteriv(target, pname, params); }
    __forceinline static void              Hint(GLenum target, GLenum mode) { glHint(target, mode); }
    __forceinline static void              IndexMask(GLuint mask) { glIndexMask(mask); }
    __forceinline static void              IndexPointer(GLenum type, GLsizei stride, const GLvoid *pointer) { glIndexPointer(type, stride, pointer); }
    __forceinline static void              Indexd(GLdouble c) { glIndexd(c); }
    __forceinline static void              Indexdv(const GLdouble *c) { glIndexdv(c); }
    __forceinline static void              Indexf(GLfloat c) { glIndexf(c); }
    __forceinline static void              Indexfv(const GLfloat *c) { glIndexfv(c); }
    __forceinline static void              Indexi(GLint c) { glIndexi(c); }
    __forceinline static void              Indexiv(const GLint *c) { glIndexiv(c); }
    __forceinline static void              Indexs(GLshort c) { glIndexs(c); }
    __forceinline static void              Indexsv(const GLshort *c) { glIndexsv(c); }
    __forceinline static void              Indexub(GLubyte c) { glIndexub(c); }
    __forceinline static void              Indexubv(const GLubyte *c) { glIndexubv(c); }
    __forceinline static void              InitNames(void) { glInitNames(); }
    __forceinline static void              InterleavedArrays(GLenum format, GLsizei stride, const GLvoid *pointer) { glInterleavedArrays(format, stride, pointer); }
    __forceinline static GLboolean         IsEnabled(GLenum cap) { glIsEnabled(cap); }
    __forceinline static GLboolean         IsList(GLuint list) { glIsList(list); }
    __forceinline static GLboolean         IsTexture(GLuint texture) { glIsTexture(texture); }
    __forceinline static void              LightModelf(GLenum pname, GLfloat param) { glLightModelf(pname, param); }
    __forceinline static void              LightModelfv(GLenum pname, const GLfloat *params) { glLightModelfv(pname, params); }
    __forceinline static void              LightModeli(GLenum pname, GLint param) { glLightModeli(pname, param); }
    __forceinline static void              LightModeliv(GLenum pname, const GLint *params) { glLightModeliv(pname, params); }
    __forceinline static void              Lightf(GLenum light, GLenum pname, GLfloat param) { glLightf(light, pname, param); }
    __forceinline static void              Lightfv(GLenum light, GLenum pname, const GLfloat *params) { glLightfv(light, pname, params); }
    __forceinline static void              Lighti(GLenum light, GLenum pname, GLint param) { glLighti(light, pname, param); }
    __forceinline static void              Lightiv(GLenum light, GLenum pname, const GLint *params) { glLightiv(light, pname, params); }
    __forceinline static void              LineStipple(GLint factor, GLushort pattern) { glLineStipple(factor, pattern); }
    __forceinline static void              LineWidth(GLfloat width) { glLineWidth(width); }
    __forceinline static void              ListBase(GLuint base) { glListBase(base); }
    __forceinline static void              LoadIdentity(void) { glLoadIdentity(); }
    __forceinline static void              LoadMatrixd(const GLdouble *m) { glLoadMatrixd(m); }
    __forceinline static void              LoadMatrixf(const GLfloat *m) { glLoadMatrixf(m); }
    __forceinline static void              LoadName(GLuint name) { glLoadName(name); }
    __forceinline static void              LogicOp(GLenum opcode) { glLogicOp(opcode); }
    __forceinline static void              Map1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points) { glMap1d(target, u1, u2, stride, order, points); }
    __forceinline static void              Map1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points) { glMap1f(target, u1, u2, stride, order, points); }
    __forceinline static void              Map2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points) { glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points); }
    __forceinline static void              Map2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points) { glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points); }
    __forceinline static void              MapGrid1d(GLint un, GLdouble u1, GLdouble u2) { glMapGrid1d(un, u1, u2); }
    __forceinline static void              MapGrid1f(GLint un, GLfloat u1, GLfloat u2) { glMapGrid1f(un, u1, u2); }
    __forceinline static void              MapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2) { glMapGrid2d(un, u1, u2, vn, v1, v2); }
    __forceinline static void              MapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2) { glMapGrid2f(un, u1, u2, vn, v1, v2); }
    __forceinline static void              Materialf(GLenum face, GLenum pname, GLfloat param) { glMaterialf(face, pname, param); }
    __forceinline static void              Materialfv(GLenum face, GLenum pname, const GLfloat *params) { glMaterialfv(face, pname, params); }
    __forceinline static void              Materiali(GLenum face, GLenum pname, GLint param) { glMateriali(face, pname, param); }
    __forceinline static void              Materialiv(GLenum face, GLenum pname, const GLint *params) { glMaterialiv(face, pname, params); }
    __forceinline static void              MatrixMode(GLenum mode) { glMatrixMode(mode); }
    __forceinline static void              MultMatrixd(const GLdouble *m) { glMultMatrixd(m); }
    __forceinline static void              MultMatrixf(const GLfloat *m) { glMultMatrixf(m); }
    __forceinline static void              NewList(GLuint list, GLenum mode) { glNewList(list, mode); }
    __forceinline static void              Normal3b(GLbyte nx, GLbyte ny, GLbyte nz) { glNormal3b(nx, ny, nz); }
    __forceinline static void              Normal3bv(const GLbyte *v) { glNormal3bv(v); }
    __forceinline static void              Normal3d(GLdouble nx, GLdouble ny, GLdouble nz) { glNormal3d(nx, ny, nz); }
    __forceinline static void              Normal3dv(const GLdouble *v) { glNormal3dv(v); }
    __forceinline static void              Normal3f(GLfloat nx, GLfloat ny, GLfloat nz) { glNormal3f(nx, ny, nz); }
    __forceinline static void              Normal3fv(const GLfloat *v) { glNormal3fv(v); }
    __forceinline static void              Normal3i(GLint nx, GLint ny, GLint nz) { glNormal3i(nx, ny, nz); }
    __forceinline static void              Normal3iv(const GLint *v) { glNormal3iv(v); }
    __forceinline static void              Normal3s(GLshort nx, GLshort ny, GLshort nz) { glNormal3s(nx, ny, nz); }
    __forceinline static void              Normal3sv(const GLshort *v) { glNormal3sv(v); }
    __forceinline static void              NormalPointer(GLenum type, GLsizei stride, const GLvoid *pointer) { glNormalPointer(type, stride, pointer); }
    __forceinline static void              Ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) { glOrtho(left, right, bottom, top, zNear, zFar); }
    __forceinline static void              PassThrough(GLfloat token) { glPassThrough(token); }
    __forceinline static void              PixelMapfv(GLenum map, GLsizei mapsize, const GLfloat *values) { glPixelMapfv(map, mapsize, values); }
    __forceinline static void              PixelMapuiv(GLenum map, GLsizei mapsize, const GLuint *values) { glPixelMapuiv(map, mapsize, values); }
    __forceinline static void              PixelMapusv(GLenum map, GLsizei mapsize, const GLushort *values) { glPixelMapusv(map, mapsize, values); }
    __forceinline static void              PixelStoref(GLenum pname, GLfloat param) { glPixelStoref(pname, param); }
    __forceinline static void              PixelStorei(GLenum pname, GLint param) { glPixelStorei(pname, param); }
    __forceinline static void              PixelTransferf(GLenum pname, GLfloat param) { glPixelTransferf(pname, param); }
    __forceinline static void              PixelTransferi(GLenum pname, GLint param) { glPixelTransferi(pname, param); }
    __forceinline static void              PixelZoom(GLfloat xfactor, GLfloat yfactor) { glPixelZoom(xfactor, yfactor); }
    __forceinline static void              PointSize(GLfloat size) { glPointSize(size); }
    __forceinline static void              PolygonMode(GLenum face, GLenum mode) { glPolygonMode(face, mode); }
    __forceinline static void              PolygonOffset(GLfloat factor, GLfloat units) { glPolygonOffset(factor, units); }
    __forceinline static void              PolygonStipple(const GLubyte *mask) { glPolygonStipple(mask); }
    __forceinline static void              PopAttrib(void) { glPopAttrib(); }
    __forceinline static void              PopClientAttrib(void) { glPopClientAttrib(); }
    __forceinline static void              PopMatrix(void) { glPopMatrix(); }
    __forceinline static void              PopName(void) { glPopName(); }
    __forceinline static void              PrioritizeTextures(GLsizei n, const GLuint *textures, const GLclampf *priorities) { glPrioritizeTextures(n, textures, priorities); }
    __forceinline static void              PushAttrib(GLbitfield mask) { glPushAttrib(mask); }
    __forceinline static void              PushClientAttrib(GLbitfield mask) { glPushClientAttrib(mask); }
    __forceinline static void              PushMatrix(void) { glPushMatrix(); }
    __forceinline static void              PushName(GLuint name) { glPushName(name); }
    __forceinline static void              RasterPos2d(GLdouble x, GLdouble y) { glRasterPos2d(x, y); }
    __forceinline static void              RasterPos2dv(const GLdouble *v) { glRasterPos2dv(v); }
    __forceinline static void              RasterPos2f(GLfloat x, GLfloat y) { glRasterPos2f(x, y); }
    __forceinline static void              RasterPos2fv(const GLfloat *v) { glRasterPos2fv(v); }
    __forceinline static void              RasterPos2i(GLint x, GLint y) { glRasterPos2i(x, y); }
    __forceinline static void              RasterPos2iv(const GLint *v) { glRasterPos2iv(v); }
    __forceinline static void              RasterPos2s(GLshort x, GLshort y) { glRasterPos2s(x, y); }
    __forceinline static void              RasterPos2sv(const GLshort *v) { glRasterPos2sv(v); }
    __forceinline static void              RasterPos3d(GLdouble x, GLdouble y, GLdouble z) { glRasterPos3d(x, y, z); }
    __forceinline static void              RasterPos3dv(const GLdouble *v) { glRasterPos3dv(v); }
    __forceinline static void              RasterPos3f(GLfloat x, GLfloat y, GLfloat z) { glRasterPos3f(x, y, z); }
    __forceinline static void              RasterPos3fv(const GLfloat *v) { glRasterPos3fv(v); }
    __forceinline static void              RasterPos3i(GLint x, GLint y, GLint z) { glRasterPos3i(x, y, z); }
    __forceinline static void              RasterPos3iv(const GLint *v) { glRasterPos3iv(v); }
    __forceinline static void              RasterPos3s(GLshort x, GLshort y, GLshort z) { glRasterPos3s(x, y, z); }
    __forceinline static void              RasterPos3sv(const GLshort *v) { glRasterPos3sv(v); }
    __forceinline static void              RasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) { glRasterPos4d(x, y, z, w); }
    __forceinline static void              RasterPos4dv(const GLdouble *v) { glRasterPos4dv(v); }
    __forceinline static void              RasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) { glRasterPos4f(x, y, z, w); }
    __forceinline static void              RasterPos4fv(const GLfloat *v) { glRasterPos4fv(v); }
    __forceinline static void              RasterPos4i(GLint x, GLint y, GLint z, GLint w) { glRasterPos4i(x, y, z, w); }
    __forceinline static void              RasterPos4iv(const GLint *v) { glRasterPos4iv(v); }
    __forceinline static void              RasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w) { glRasterPos4s(x, y, z, w); }
    __forceinline static void              RasterPos4sv(const GLshort *v) { glRasterPos4sv(v); }
    __forceinline static void              ReadBuffer(GLenum mode) { glReadBuffer(mode); }
    __forceinline static void              ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels) { glReadPixels(x, y, width, height, format, type, pixels); }
    __forceinline static void              Rectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) { glRectd(x1, y1, x2, y2); }
    __forceinline static void              Rectdv(const GLdouble *v1, const GLdouble *v2) { glRectdv(v1, v2); }
    __forceinline static void              Rectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) { glRectf(x1, y1, x2, y2); }
    __forceinline static void              Rectfv(const GLfloat *v1, const GLfloat *v2) { glRectfv(v1, v2); }
    __forceinline static void              Recti(GLint x1, GLint y1, GLint x2, GLint y2) { glRecti(x1, y1, x2, y2); }
    __forceinline static void              Rectiv(const GLint *v1, const GLint *v2) { glRectiv(v1, v2); }
    __forceinline static void              Rects(GLshort x1, GLshort y1, GLshort x2, GLshort y2) { glRects(x1, y1, x2, y2); }
    __forceinline static void              Rectsv(const GLshort *v1, const GLshort *v2) { glRectsv(v1, v2); }
    __forceinline static GLint             RenderMode(GLenum mode) { glRenderMode(mode); }
    __forceinline static void              Rotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z) { glRotated(angle, x, y, z); }
    __forceinline static void              Rotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) { glRotatef(angle, x, y, z); }
    __forceinline static void              Scaled(GLdouble x, GLdouble y, GLdouble z) { glScaled(x, y, z); }
    __forceinline static void              Scalef(GLfloat x, GLfloat y, GLfloat z) { glScalef(x, y, z); }
    __forceinline static void              Scissor(GLint x, GLint y, GLsizei width, GLsizei height) { glScissor(x, y, width, height); }
    __forceinline static void              SelectBuffer(GLsizei size, GLuint *buffer) { glSelectBuffer(size, buffer); }
    __forceinline static void              ShadeModel(GLenum mode) { glShadeModel(mode); }
    __forceinline static void              StencilFunc(GLenum func, GLint ref, GLuint mask) { glStencilFunc(func, ref, mask); }
    __forceinline static void              StencilMask(GLuint mask) { glStencilMask(mask); }
    __forceinline static void              StencilOp(GLenum fail, GLenum zfail, GLenum zpass) { glStencilOp(fail, zfail, zpass); }
    __forceinline static void              TexCoord1d(GLdouble s) { glTexCoord1d(s); }
    __forceinline static void              TexCoord1dv(const GLdouble *v) { glTexCoord1dv(v); }
    __forceinline static void              TexCoord1f(GLfloat s) { glTexCoord1f(s); }
    __forceinline static void              TexCoord1fv(const GLfloat *v) { glTexCoord1fv(v); }
    __forceinline static void              TexCoord1i(GLint s) { glTexCoord1i(s); }
    __forceinline static void              TexCoord1iv(const GLint *v) { glTexCoord1iv(v); }
    __forceinline static void              TexCoord1s(GLshort s) { glTexCoord1s(s); }
    __forceinline static void              TexCoord1sv(const GLshort *v) { glTexCoord1sv(v); }
    __forceinline static void              TexCoord2d(GLdouble s, GLdouble t) { glTexCoord2d(s, t); }
    __forceinline static void              TexCoord2dv(const GLdouble *v) { glTexCoord2dv(v); }
    __forceinline static void              TexCoord2f(GLfloat s, GLfloat t) { glTexCoord2f(s, t); }
    __forceinline static void              TexCoord2fv(const GLfloat *v) { glTexCoord2fv(v); }
    __forceinline static void              TexCoord2i(GLint s, GLint t) { glTexCoord2i(s, t); }
    __forceinline static void              TexCoord2iv(const GLint *v) { glTexCoord2iv(v); }
    __forceinline static void              TexCoord2s(GLshort s, GLshort t) { glTexCoord2s(s, t); }
    __forceinline static void              TexCoord2sv(const GLshort *v) { glTexCoord2sv(v); }
    __forceinline static void              TexCoord3d(GLdouble s, GLdouble t, GLdouble r) { glTexCoord3d(s, t, r); }
    __forceinline static void              TexCoord3dv(const GLdouble *v) { glTexCoord3dv(v); }
    __forceinline static void              TexCoord3f(GLfloat s, GLfloat t, GLfloat r) { glTexCoord3f(s, t, r); }
    __forceinline static void              TexCoord3fv(const GLfloat *v) { glTexCoord3fv(v); }
    __forceinline static void              TexCoord3i(GLint s, GLint t, GLint r) { glTexCoord3i(s, t, r); }
    __forceinline static void              TexCoord3iv(const GLint *v) { glTexCoord3iv(v); }
    __forceinline static void              TexCoord3s(GLshort s, GLshort t, GLshort r) { glTexCoord3s(s, t, r); }
    __forceinline static void              TexCoord3sv(const GLshort *v) { glTexCoord3sv(v); }
    __forceinline static void              TexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q) { glTexCoord4d(s, t, r, q); }
    __forceinline static void              TexCoord4dv(const GLdouble *v) { glTexCoord4dv(v); }
    __forceinline static void              TexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q) { glTexCoord4f(s, t, r, q); }
    __forceinline static void              TexCoord4fv(const GLfloat *v) { glTexCoord4fv(v); }
    __forceinline static void              TexCoord4i(GLint s, GLint t, GLint r, GLint q) { glTexCoord4i(s, t, r, q); }
    __forceinline static void              TexCoord4iv(const GLint *v) { glTexCoord4iv(v); }
    __forceinline static void              TexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q) { glTexCoord4s(s, t, r, q); }
    __forceinline static void              TexCoord4sv(const GLshort *v) { glTexCoord4sv(v); }
    __forceinline static void              TexCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) { glTexCoordPointer(size, type, stride, pointer); }
    __forceinline static void              TexEnvf(GLenum target, GLenum pname, GLfloat param) { glTexEnvf(target, pname, param); }
    __forceinline static void              TexEnvfv(GLenum target, GLenum pname, const GLfloat *params) { glTexEnvfv(target, pname, params); }
    __forceinline static void              TexEnvi(GLenum target, GLenum pname, GLint param) { glTexEnvi(target, pname, param); }
    __forceinline static void              TexEnviv(GLenum target, GLenum pname, const GLint *params) { glTexEnviv(target, pname, params); }
    __forceinline static void              TexGend(GLenum coord, GLenum pname, GLdouble param) { glTexGend(coord, pname, param); }
    __forceinline static void              TexGendv(GLenum coord, GLenum pname, const GLdouble *params) { glTexGendv(coord, pname, params); }
    __forceinline static void              TexGenf(GLenum coord, GLenum pname, GLfloat param) { glTexGenf(coord, pname, param); }
    __forceinline static void              TexGenfv(GLenum coord, GLenum pname, const GLfloat *params) { glTexGenfv(coord, pname, params); }
    __forceinline static void              TexGeni(GLenum coord, GLenum pname, GLint param) { glTexGeni(coord, pname, param); }
    __forceinline static void              TexGeniv(GLenum coord, GLenum pname, const GLint *params) { glTexGeniv(coord, pname, params); }
    __forceinline static void              TexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels) { glTexImage1D(target, level, internalformat, width, border, format, type, pixels); }
    __forceinline static void              TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels) { glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels); }
    __forceinline static void              TexParameterf(GLenum target, GLenum pname, GLfloat param) { glTexParameterf(target, pname, param); }
    __forceinline static void              TexParameterfv(GLenum target, GLenum pname, const GLfloat *params) { glTexParameterfv(target, pname, params); }
    __forceinline static void              TexParameteri(GLenum target, GLenum pname, GLint param) { glTexParameteri(target, pname, param); }
    __forceinline static void              TexParameteriv(GLenum target, GLenum pname, const GLint *params) { glTexParameteriv(target, pname, params); }
    __forceinline static void              TexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels) { glTexSubImage1D(target, level, xoffset, width, format, type, pixels); }
    __forceinline static void              TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) { glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels); }
    __forceinline static void              Translated(GLdouble x, GLdouble y, GLdouble z) { glTranslated(x, y, z); }
    __forceinline static void              Translatef(GLfloat x, GLfloat y, GLfloat z) { glTranslatef(x, y, z); }
    __forceinline static void              Vertex2d(GLdouble x, GLdouble y) { glVertex2d(x, y); }
    __forceinline static void              Vertex2dv(const GLdouble *v) { glVertex2dv(v); }
    __forceinline static void              Vertex2f(GLfloat x, GLfloat y) { glVertex2f(x, y); }
    __forceinline static void              Vertex2fv(const GLfloat *v) { glVertex2fv(v); }
    __forceinline static void              Vertex2i(GLint x, GLint y) { glVertex2i(x, y); }
    __forceinline static void              Vertex2iv(const GLint *v) { glVertex2iv(v); }
    __forceinline static void              Vertex2s(GLshort x, GLshort y) { glVertex2s(x, y); }
    __forceinline static void              Vertex2sv(const GLshort *v) { glVertex2sv(v); }
    __forceinline static void              Vertex3d(GLdouble x, GLdouble y, GLdouble z) { glVertex3d(x, y, z); }
    __forceinline static void              Vertex3dv(const GLdouble *v) { glVertex3dv(v); }
    __forceinline static void              Vertex3f(GLfloat x, GLfloat y, GLfloat z) { glVertex3f(x, y, z); }
    __forceinline static void              Vertex3fv(const GLfloat *v) { glVertex3fv(v); }
    __forceinline static void              Vertex3i(GLint x, GLint y, GLint z) { glVertex3i(x, y, z); }
    __forceinline static void              Vertex3iv(const GLint *v) { glVertex3iv(v); }
    __forceinline static void              Vertex3s(GLshort x, GLshort y, GLshort z) { glVertex3s(x, y, z); }
    __forceinline static void              Vertex3sv(const GLshort *v) { glVertex3sv(v); }
    __forceinline static void              Vertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) { glVertex4d(x, y, z, w); }
    __forceinline static void              Vertex4dv(const GLdouble *v) { glVertex4dv(v); }
    __forceinline static void              Vertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) { glVertex4f(x, y, z, w); }
    __forceinline static void              Vertex4fv(const GLfloat *v) { glVertex4fv(v); }
    __forceinline static void              Vertex4i(GLint x, GLint y, GLint z, GLint w) { glVertex4i(x, y, z, w); }
    __forceinline static void              Vertex4iv(const GLint *v) { glVertex4iv(v); }
    __forceinline static void              Vertex4s(GLshort x, GLshort y, GLshort z, GLshort w) { glVertex4s(x, y, z, w); }
    __forceinline static void              Vertex4sv(const GLshort *v) { glVertex4sv(v); }
    __forceinline static void              VertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) { glVertexPointer(size, type, stride, pointer); }
    __forceinline static void              Viewport(GLint x, GLint y, GLsizei width, GLsizei height) { glViewport(x, y, width, height); }
    

    enum GLenum_Core_1_2
    {
        SMOOTH_POINT_SIZE_RANGE             = 0x0B12,
        SMOOTH_POINT_SIZE_GRANULARITY       = 0x0B13,
        SMOOTH_LINE_WIDTH_RANGE             = 0x0B22,
        SMOOTH_LINE_WIDTH_GRANULARITY       = 0x0B23,
        UNSIGNED_BYTE_3_3_2                 = 0x8032,
        UNSIGNED_SHORT_4_4_4_4              = 0x8033,
        UNSIGNED_SHORT_5_5_5_1              = 0x8034,
        UNSIGNED_INT_8_8_8_8                = 0x8035,
        UNSIGNED_INT_10_10_10_2             = 0x8036,
        RESCALE_NORMAL                      = 0x803A,
        TEXTURE_BINDING_3D                  = 0x806A,
        PACK_SKIP_IMAGES                    = 0x806B,
        PACK_IMAGE_HEIGHT                   = 0x806C,
        UNPACK_SKIP_IMAGES                  = 0x806D,
        UNPACK_IMAGE_HEIGHT                 = 0x806E,
        TEXTURE_3D                          = 0x806F,
        PROXY_TEXTURE_3D                    = 0x8070,
        TEXTURE_DEPTH                       = 0x8071,
        TEXTURE_WRAP_R                      = 0x8072,
        MAX_3D_TEXTURE_SIZE                 = 0x8073,
        BGR                                 = 0x80E0,
        BGRA                                = 0x80E1,
        MAX_ELEMENTS_VERTICES               = 0x80E8,
        MAX_ELEMENTS_INDICES                = 0x80E9,
        CLAMP_TO_EDGE                       = 0x812F,
        TEXTURE_MIN_LOD                     = 0x813A,
        TEXTURE_MAX_LOD                     = 0x813B,
        TEXTURE_BASE_LEVEL                  = 0x813C,
        TEXTURE_MAX_LEVEL                   = 0x813D,
        LIGHT_MODEL_COLOR_CONTROL           = 0x81F8,
        SINGLE_COLOR                        = 0x81F9,
        SEPARATE_SPECULAR_COLOR             = 0x81FA,
        UNSIGNED_BYTE_2_3_3_REV             = 0x8362,
        UNSIGNED_SHORT_5_6_5                = 0x8363,
        UNSIGNED_SHORT_5_6_5_REV            = 0x8364,
        UNSIGNED_SHORT_4_4_4_4_REV          = 0x8365,
        UNSIGNED_SHORT_1_5_5_5_REV          = 0x8366,
        UNSIGNED_INT_8_8_8_8_REV            = 0x8367,
        UNSIGNED_INT_2_10_10_10_REV         = 0x8368,
        ALIASED_POINT_SIZE_RANGE            = 0x846D,
        ALIASED_LINE_WIDTH_RANGE            = 0x846E
    };

    __forceinline static void              CopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) { glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height); }
    __forceinline static void              DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices) { glDrawRangeElements(mode, start, end, count, type, indices); }
    __forceinline static void              TexImage3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels) { glTexImage3D(target, level, internalFormat, width, height, depth, border, format, type, pixels); }
    __forceinline static void              TexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels) { glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels); }


    enum GLenum_Core_1_3
    {
        MULTISAMPLE                         = 0x809D,
        SAMPLE_ALPHA_TO_COVERAGE            = 0x809E,
        SAMPLE_ALPHA_TO_ONE                 = 0x809F,
        SAMPLE_COVERAGE                     = 0x80A0,
        SAMPLE_BUFFERS                      = 0x80A8,
        SAMPLES                             = 0x80A9,
        SAMPLE_COVERAGE_VALUE               = 0x80AA,
        SAMPLE_COVERAGE_INVERT              = 0x80AB,
        CLAMP_TO_BORDER                     = 0x812D,
        TEXTURE0                            = 0x84C0,
        TEXTURE1                            = 0x84C1,
        TEXTURE2                            = 0x84C2,
        TEXTURE3                            = 0x84C3,
        TEXTURE4                            = 0x84C4,
        TEXTURE5                            = 0x84C5,
        TEXTURE6                            = 0x84C6,
        TEXTURE7                            = 0x84C7,
        TEXTURE8                            = 0x84C8,
        TEXTURE9                            = 0x84C9,
        TEXTURE10                           = 0x84CA,
        TEXTURE11                           = 0x84CB,
        TEXTURE12                           = 0x84CC,
        TEXTURE13                           = 0x84CD,
        TEXTURE14                           = 0x84CE,
        TEXTURE15                           = 0x84CF,
        TEXTURE16                           = 0x84D0,
        TEXTURE17                           = 0x84D1,
        TEXTURE18                           = 0x84D2,
        TEXTURE19                           = 0x84D3,
        TEXTURE20                           = 0x84D4,
        TEXTURE21                           = 0x84D5,
        TEXTURE22                           = 0x84D6,
        TEXTURE23                           = 0x84D7,
        TEXTURE24                           = 0x84D8,
        TEXTURE25                           = 0x84D9,
        TEXTURE26                           = 0x84DA,
        TEXTURE27                           = 0x84DB,
        TEXTURE28                           = 0x84DC,
        TEXTURE29                           = 0x84DD,
        TEXTURE30                           = 0x84DE,
        TEXTURE31                           = 0x84DF,
        ACTIVE_TEXTURE                      = 0x84E0,
        CLIENT_ACTIVE_TEXTURE               = 0x84E1,
        MAX_TEXTURE_UNITS                   = 0x84E2,
        TRANSPOSE_MODELVIEW_MATRIX          = 0x84E3,
        TRANSPOSE_PROJECTION_MATRIX         = 0x84E4,
        TRANSPOSE_TEXTURE_MATRIX            = 0x84E5,
        TRANSPOSE_COLOR_MATRIX              = 0x84E6,
        SUBTRACT                            = 0x84E7,
        COMPRESSED_ALPHA                    = 0x84E9,
        COMPRESSED_LUMINANCE                = 0x84EA,
        COMPRESSED_LUMINANCE_ALPHA          = 0x84EB,
        COMPRESSED_INTENSITY                = 0x84EC,
        COMPRESSED_RGB                      = 0x84ED,
        COMPRESSED_RGBA                     = 0x84EE,
        TEXTURE_COMPRESSION_HINT            = 0x84EF,
        NORMAL_MAP                          = 0x8511,
        REFLECTION_MAP                      = 0x8512,
        TEXTURE_CUBE_MAP                    = 0x8513,
        TEXTURE_BINDING_CUBE_MAP            = 0x8514,
        TEXTURE_CUBE_MAP_POSITIVE_X         = 0x8515,
        TEXTURE_CUBE_MAP_NEGATIVE_X         = 0x8516,
        TEXTURE_CUBE_MAP_POSITIVE_Y         = 0x8517,
        TEXTURE_CUBE_MAP_NEGATIVE_Y         = 0x8518,
        TEXTURE_CUBE_MAP_POSITIVE_Z         = 0x8519,
        TEXTURE_CUBE_MAP_NEGATIVE_Z         = 0x851A,
        PROXY_TEXTURE_CUBE_MAP              = 0x851B,
        MAX_CUBE_MAP_TEXTURE_SIZE           = 0x851C,
        COMBINE                             = 0x8570,
        COMBINE_RGB                         = 0x8571,
        COMBINE_ALPHA                       = 0x8572,
        RGB_SCALE                           = 0x8573,
        ADD_SIGNED                          = 0x8574,
        INTERPOLATE                         = 0x8575,
        CONSTANT                            = 0x8576,
        PRIMARY_COLOR                       = 0x8577,
        PREVIOUS                            = 0x8578,
        SOURCE0_RGB                         = 0x8580,
        SOURCE1_RGB                         = 0x8581,
        SOURCE2_RGB                         = 0x8582,
        SOURCE0_ALPHA                       = 0x8588,
        SOURCE1_ALPHA                       = 0x8589,
        SOURCE2_ALPHA                       = 0x858A,
        OPERAND0_RGB                        = 0x8590,
        OPERAND1_RGB                        = 0x8591,
        OPERAND2_RGB                        = 0x8592,
        OPERAND0_ALPHA                      = 0x8598,
        OPERAND1_ALPHA                      = 0x8599,
        OPERAND2_ALPHA                      = 0x859A,
        TEXTURE_COMPRESSED_IMAGE_SIZE       = 0x86A0,
        TEXTURE_COMPRESSED                  = 0x86A1,
        NUM_COMPRESSED_TEXTURE_FORMATS      = 0x86A2,
        COMPRESSED_TEXTURE_FORMATS          = 0x86A3,
        DOT3_RGB                            = 0x86AE,
        DOT3_RGBA                           = 0x86AF,

        MULTISAMPLE_BIT                     = 0x20000000
    };

    __forceinline static void              ActiveTexture(GLenum texture) { glActiveTexture(texture); }
    __forceinline static void              ClientActiveTexture(GLenum texture) { glClientActiveTexture(texture); }
    __forceinline static void              CompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data) { glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data); }
    __forceinline static void              CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data) { glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data); }
    __forceinline static void              CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data) { glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data); }
    __forceinline static void              CompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data) { glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data); }
    __forceinline static void              CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data) { glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data); }
    __forceinline static void              CompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data) { glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data); }
    __forceinline static void              GetCompressedTexImage(GLenum target, GLint lod, GLvoid *img) { glGetCompressedTexImage(target, lod, img); }
    __forceinline static void              LoadTransposeMatrixd(const GLdouble m[16]) { glLoadTransposeMatrixd(m); }
    __forceinline static void              LoadTransposeMatrixf(const GLfloat m[16]) { glLoadTransposeMatrixf(m); }
    __forceinline static void              MultTransposeMatrixd(const GLdouble m[16]) { glMultTransposeMatrixd(m); }
    __forceinline static void              MultTransposeMatrixf(const GLfloat m[16]) { glMultTransposeMatrixf(m); }
    __forceinline static void              MultiTexCoord1d(GLenum target, GLdouble s) { glMultiTexCoord1d(target, s); }
    __forceinline static void              MultiTexCoord1dv(GLenum target, const GLdouble *v) { glMultiTexCoord1dv(target, v); }
    __forceinline static void              MultiTexCoord1f(GLenum target, GLfloat s) { glMultiTexCoord1f(target, s); }
    __forceinline static void              MultiTexCoord1fv(GLenum target, const GLfloat *v) { glMultiTexCoord1fv(target, v); }
    __forceinline static void              MultiTexCoord1i(GLenum target, GLint s) { glMultiTexCoord1i(target, s); }
    __forceinline static void              MultiTexCoord1iv(GLenum target, const GLint *v) { glMultiTexCoord1iv(target, v); }
    __forceinline static void              MultiTexCoord1s(GLenum target, GLshort s) { glMultiTexCoord1s(target,  s); }
    __forceinline static void              MultiTexCoord1sv(GLenum target, const GLshort *v) { glMultiTexCoord1sv(target, v); }
    __forceinline static void              MultiTexCoord2d(GLenum target, GLdouble s, GLdouble t) { glMultiTexCoord2d(target, s, t); }
    __forceinline static void              MultiTexCoord2dv(GLenum target, const GLdouble *v) { glMultiTexCoord2dv(target, v); }
    __forceinline static void              MultiTexCoord2f(GLenum target, GLfloat s, GLfloat t) { glMultiTexCoord2f(target,  s,  t); }
    __forceinline static void              MultiTexCoord2fv(GLenum target, const GLfloat *v) { glMultiTexCoord2fv(target, v); }
    __forceinline static void              MultiTexCoord2i(GLenum target, GLint s, GLint t) { glMultiTexCoord2i(target, s, t); }
    __forceinline static void              MultiTexCoord2iv(GLenum target, const GLint *v) { glMultiTexCoord2iv(target, v); }
    __forceinline static void              MultiTexCoord2s(GLenum target, GLshort s, GLshort t) { glMultiTexCoord2s(target,  s,  t); }
    __forceinline static void              MultiTexCoord2sv(GLenum target, const GLshort *v) { glMultiTexCoord2sv(target, v); }
    __forceinline static void              MultiTexCoord3d(GLenum target, GLdouble s, GLdouble t, GLdouble r) { glMultiTexCoord3d(target, s, t, r); }
    __forceinline static void              MultiTexCoord3dv(GLenum target, const GLdouble *v) { glMultiTexCoord3dv(target, v); }
    __forceinline static void              MultiTexCoord3f(GLenum target, GLfloat s, GLfloat t, GLfloat r) { glMultiTexCoord3f(target,  s,  t,  r); }
    __forceinline static void              MultiTexCoord3fv(GLenum target, const GLfloat *v) { glMultiTexCoord3fv(target, v); }
    __forceinline static void              MultiTexCoord3i(GLenum target, GLint s, GLint t, GLint r) { glMultiTexCoord3i(target, s, t, r); }
    __forceinline static void              MultiTexCoord3iv(GLenum target, const GLint *v) { glMultiTexCoord3iv(target, v); }
    __forceinline static void              MultiTexCoord3s(GLenum target, GLshort s, GLshort t, GLshort r) { glMultiTexCoord3s(target,  s,  t,  r); }
    __forceinline static void              MultiTexCoord3sv(GLenum target, const GLshort *v) { glMultiTexCoord3sv(target, v); }
    __forceinline static void              MultiTexCoord4d(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q) { glMultiTexCoord4d(target, s, t, r, q); }
    __forceinline static void              MultiTexCoord4dv(GLenum target, const GLdouble *v) { glMultiTexCoord4dv(target, v); }
    __forceinline static void              MultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) { glMultiTexCoord4f(target,  s,  t,  r,  q); }
    __forceinline static void              MultiTexCoord4fv(GLenum target, const GLfloat *v) { glMultiTexCoord4fv(target, v); }
    __forceinline static void              MultiTexCoord4i(GLenum target, GLint s, GLint t, GLint r, GLint q) { glMultiTexCoord4i(target, s, t, r, q); }
    __forceinline static void              MultiTexCoord4iv(GLenum target, const GLint *v) { glMultiTexCoord4iv(target, v); }
    __forceinline static void              MultiTexCoord4s(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q) { glMultiTexCoord4s(target,  s,  t,  r,  q); }
    __forceinline static void              MultiTexCoord4sv(GLenum target, const GLshort *v) { glMultiTexCoord4sv(target, v); }
    __forceinline static void              SampleCoverage(GLclampf value, GLboolean invert) { glSampleCoverage(value, invert); }



    enum GLenum_Core_1_4
    {
        BLEND_DST_RGB                       = 0x80C8,
        BLEND_SRC_RGB                       = 0x80C9,
        BLEND_DST_ALPHA                     = 0x80CA,
        BLEND_SRC_ALPHA                     = 0x80CB,
        POINT_SIZE_MIN                      = 0x8126,
        POINT_SIZE_MAX                      = 0x8127,
        POINT_FADE_THRESHOLD_SIZE           = 0x8128,
        POINT_DISTANCE_ATTENUATION          = 0x8129,
        GENERATE_MIPMAP                     = 0x8191,
        GENERATE_MIPMAP_HINT                = 0x8192,
        DEPTH_COMPONENT16                   = 0x81A5,
        DEPTH_COMPONENT24                   = 0x81A6,
        DEPTH_COMPONENT32                   = 0x81A7,
        MIRRORED_REPEAT                     = 0x8370,
        FOG_COORDINATE_SRC                  = 0x8450,
        FOG_COORDINATE                      = 0x8451,
        FRAGMENT_DEPTH                      = 0x8452,
        CURRENT_FOG_COORDINATE              = 0x8453,
        FOG_COORDINATE_ARRAY_TYPE           = 0x8454,
        FOG_COORDINATE_ARRAY_STRIDE         = 0x8455,
        FOG_COORDINATE_ARRAY_POINTER        = 0x8456,
        FOG_COORDINATE_ARRAY                = 0x8457,
        COLOR_SUM                           = 0x8458,
        CURRENT_SECONDARY_COLOR             = 0x8459,
        SECONDARY_COLOR_ARRAY_SIZE          = 0x845A,
        SECONDARY_COLOR_ARRAY_TYPE          = 0x845B,
        SECONDARY_COLOR_ARRAY_STRIDE        = 0x845C,
        SECONDARY_COLOR_ARRAY_POINTER       = 0x845D,
        SECONDARY_COLOR_ARRAY               = 0x845E,
        MAX_TEXTURE_LOD_BIAS                = 0x84FD,
        TEXTURE_FILTER_CONTROL              = 0x8500,
        TEXTURE_LOD_BIAS                    = 0x8501,
        INCR_WRAP                           = 0x8507,
        DECR_WRAP                           = 0x8508,
        TEXTURE_DEPTH_SIZE                  = 0x884A,
        DEPTH_TEXTURE_MODE                  = 0x884B,
        TEXTURE_COMPARE_MODE                = 0x884C,
        TEXTURE_COMPARE_FUNC                = 0x884D,
        COMPARE_R_TO_TEXTURE                = 0x884E
    };

    __forceinline static void              BlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) { glBlendColor(red, green, blue, alpha); }
    __forceinline static void              BlendEquation(GLenum mode) { glBlendEquation(mode); }
    __forceinline static void              BlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) { glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha); }
    __forceinline static void              FogCoordPointer(GLenum type, GLsizei stride, const GLvoid *pointer) { glFogCoordPointer(type, stride, pointer); }
    __forceinline static void              FogCoordd(GLdouble coord) { glFogCoordd(coord); }
    __forceinline static void              FogCoorddv(const GLdouble *coord) { glFogCoorddv(coord); }
    __forceinline static void              FogCoordf(GLfloat coord) { glFogCoordf(coord); }
    __forceinline static void              FogCoordfv(const GLfloat *coord) { glFogCoordfv(coord); }
    __forceinline static void              MultiDrawArrays(GLenum mode, GLint *first, GLsizei *count, GLsizei primcount) { glMultiDrawArrays(mode, first, count, primcount); }
    __forceinline static void              MultiDrawElements(GLenum mode, GLsizei *count, GLenum type, const GLvoid **indices, GLsizei primcount) { glMultiDrawElements(mode, count, type, indices, primcount); }
    __forceinline static void              PointParameterf(GLenum pname, GLfloat param) { glPointParameterf(pname, param); }
    __forceinline static void              PointParameterfv(GLenum pname, const GLfloat *params) { glPointParameterfv(pname, params); }
    __forceinline static void              PointParameteri(GLenum pname, GLint param) { glPointParameteri(pname, param); }
    __forceinline static void              PointParameteriv(GLenum pname, const GLint *params) { glPointParameteriv(pname, params); }
    __forceinline static void              SecondaryColor3b(GLbyte red, GLbyte green, GLbyte blue) { glSecondaryColor3b(red, green, blue); }
    __forceinline static void              SecondaryColor3bv(const GLbyte *v) { glSecondaryColor3bv(v); }
    __forceinline static void              SecondaryColor3d(GLdouble red, GLdouble green, GLdouble blue) { glSecondaryColor3d(red, green, blue); }
    __forceinline static void              SecondaryColor3dv(const GLdouble *v) { glSecondaryColor3dv(v); }
    __forceinline static void              SecondaryColor3f(GLfloat red, GLfloat green, GLfloat blue) { glSecondaryColor3f(red, green, blue); }
    __forceinline static void              SecondaryColor3fv(const GLfloat *v) { glSecondaryColor3fv(v); }
    __forceinline static void              SecondaryColor3i(GLint red, GLint green, GLint blue) { glSecondaryColor3i(red, green, blue); }
    __forceinline static void              SecondaryColor3iv(const GLint *v) { glSecondaryColor3iv(v); }
    __forceinline static void              SecondaryColor3s(GLshort red, GLshort green, GLshort blue) { glSecondaryColor3s(red, green, blue); }
    __forceinline static void              SecondaryColor3sv(const GLshort *v) { glSecondaryColor3sv(v); }
    __forceinline static void              SecondaryColor3ub(GLubyte red, GLubyte green, GLubyte blue) { glSecondaryColor3ub(red, green, blue); }
    __forceinline static void              SecondaryColor3ubv(const GLubyte *v) { glSecondaryColor3ubv(v); }
    __forceinline static void              SecondaryColor3ui(GLuint red, GLuint green, GLuint blue) { glSecondaryColor3ui(red, green, blue); }
    __forceinline static void              SecondaryColor3uiv(const GLuint *v) { glSecondaryColor3uiv(v); }
    __forceinline static void              SecondaryColor3us(GLushort red, GLushort green, GLushort blue) { glSecondaryColor3us(red, green, blue); }
    __forceinline static void              SecondaryColor3usv(const GLushort *v) { glSecondaryColor3usv(v); }
    __forceinline static void              SecondaryColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) { glSecondaryColorPointer(size, type, stride, pointer); }
    __forceinline static void              WindowPos2d(GLdouble x, GLdouble y) { glWindowPos2d(x, y); }
    __forceinline static void              WindowPos2dv(const GLdouble *p) { glWindowPos2dv(p); }
    __forceinline static void              WindowPos2f(GLfloat x, GLfloat y) { glWindowPos2f(x, y); }
    __forceinline static void              WindowPos2fv(const GLfloat *p) { glWindowPos2fv(p); }
    __forceinline static void              WindowPos2i(GLint x, GLint y) { glWindowPos2i(x, y); }
    __forceinline static void              WindowPos2iv(const GLint *p) { glWindowPos2iv(p); }
    __forceinline static void              WindowPos2s(GLshort x, GLshort y) { glWindowPos2s(x, y); }
    __forceinline static void              WindowPos2sv(const GLshort *p) { glWindowPos2sv(p); }
    __forceinline static void              WindowPos3d(GLdouble x, GLdouble y, GLdouble z) { glWindowPos3d(x, y, z); }
    __forceinline static void              WindowPos3dv(const GLdouble *p) { glWindowPos3dv(p); }
    __forceinline static void              WindowPos3f(GLfloat x, GLfloat y, GLfloat z) { glWindowPos3f(x, y, z); }
    __forceinline static void              WindowPos3fv(const GLfloat *p) { glWindowPos3fv(p); }
    __forceinline static void              WindowPos3i(GLint x, GLint y, GLint z) { glWindowPos3i(x, y, z); }
    __forceinline static void              WindowPos3iv(const GLint *p) { glWindowPos3iv(p); }
    __forceinline static void              WindowPos3s(GLshort x, GLshort y, GLshort z) { glWindowPos3s(x, y, z); }
    __forceinline static void              WindowPos3sv(const GLshort *p) { glWindowPos3sv(p); }


    enum GLenum_Core_1_5
    {
        BUFFER_SIZE                          = 0x8764,
        BUFFER_USAGE                         = 0x8765,
        QUERY_COUNTER_BITS                   = 0x8864,
        CURRENT_QUERY                        = 0x8865,
        QUERY_RESULT                         = 0x8866,
        QUERY_RESULT_AVAILABLE               = 0x8867,
        ARRAY_BUFFER                         = 0x8892,
        ELEMENT_ARRAY_BUFFER                 = 0x8893,
        ARRAY_BUFFER_BINDING                 = 0x8894,
        ELEMENT_ARRAY_BUFFER_BINDING         = 0x8895,
        VERTEX_ARRAY_BUFFER_BINDING          = 0x8896,
        NORMAL_ARRAY_BUFFER_BINDING          = 0x8897,
        COLOR_ARRAY_BUFFER_BINDING           = 0x8898,
        INDEX_ARRAY_BUFFER_BINDING           = 0x8899,
        TEXTURE_COORD_ARRAY_BUFFER_BINDING   = 0x889A,
        EDGE_FLAG_ARRAY_BUFFER_BINDING       = 0x889B,
        SECONDARY_COLOR_ARRAY_BUFFER_BINDING = 0x889C,
        FOG_COORD_ARRAY_BUFFER_BINDING       = 0x889D,
        WEIGHT_ARRAY_BUFFER_BINDING          = 0x889E,
        VERTEX_ATTRIB_ARRAY_BUFFER_BINDING   = 0x889F,
        READ_ONLY                            = 0x88B8,
        WRITE_ONLY                           = 0x88B9,
        READ_WRITE                           = 0x88BA,
        BUFFER_ACCESS                        = 0x88BB,
        BUFFER_MAPPED                        = 0x88BC,
        BUFFER_MAP_POINTER                   = 0x88BD,
        STREAM_DRAW                          = 0x88E0,
        STREAM_READ                          = 0x88E1,
        STREAM_COPY                          = 0x88E2,
        STATIC_DRAW                          = 0x88E4,
        STATIC_READ                          = 0x88E5,
        STATIC_COPY                          = 0x88E6,
        DYNAMIC_DRAW                         = 0x88E8,
        DYNAMIC_READ                         = 0x88E9,
        DYNAMIC_COPY                         = 0x88EA,
        SAMPLES_PASSED                       = 0x8914,
        FOG_COORD_SRC                        = FOG_COORDINATE_SRC,
        FOG_COORD                            = FOG_COORDINATE,
        CURRENT_FOG_COORD                    = CURRENT_FOG_COORDINATE,
        FOG_COORD_ARRAY_TYPE                 = FOG_COORDINATE_ARRAY_TYPE,
        FOG_COORD_ARRAY_STRIDE               = FOG_COORDINATE_ARRAY_STRIDE,
        FOG_COORD_ARRAY_POINTER              = FOG_COORDINATE_ARRAY_POINTER,
        FOG_COORD_ARRAY                      = FOG_COORDINATE_ARRAY,
        SRC0_RGB                             = SOURCE0_RGB,
        SRC1_RGB                             = SOURCE1_RGB,
        SRC2_RGB                             = SOURCE2_RGB,
        SRC0_ALPHA                           = SOURCE0_ALPHA,
        SRC1_ALPHA                           = SOURCE1_ALPHA,
        SRC2_ALPHA                           = SOURCE2_ALPHA
    };

    __forceinline static void              GenQueries(GLsizei n, GLuint* ids) { glGenQueries(n, ids); }
    __forceinline static void              DeleteQueries(GLsizei n, const GLuint* ids) {  glDeleteQueries(n, ids); }
    __forceinline static GLboolean         IsQuery(GLuint id) { return glIsQuery(id); }
    __forceinline static void              BeginQuery(GLenum target, GLuint id) { glBeginQuery(target, id); }
    __forceinline static void              EndQuery(GLenum target) { glEndQuery(target); }
    __forceinline static void              GetQueryObjectiv(GLuint id, GLenum pname, GLint* params) { glGetQueryObjectiv(id, pname, params); }
    __forceinline static void              GetQueryObjectuiv(GLuint id, GLenum pname, GLuint* params) { glGetQueryObjectuiv(id, pname, params); }
    __forceinline static void              GetQueryiv(GLenum target, GLenum pname, GLint* param) { glGetQueryiv(target, pname, param); }
    __forceinline static void              BindBuffer(GLenum target, GLuint buffer) { glBindBuffer(target, buffer); }
    __forceinline static void              BufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage) { glBufferData(target, size, data, usage); }
    __forceinline static void              BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data) { glBufferSubData(target, offset, size, data); }
    __forceinline static void              DeleteBuffers(GLsizei n, const GLuint* buffers) { glDeleteBuffers(n, buffers); }
    __forceinline static void              GenBuffers(GLsizei n, GLuint* buffers) { glGenBuffers(n, buffers); }
    __forceinline static void              GetBufferParameteriv(GLenum target, GLenum pname, GLint* params) { glGetBufferParameteriv(target, pname, params); }
    __forceinline static void              GetBufferPointerv(GLenum target, GLenum pname, GLvoid** params) { glGetBufferPointerv(target, pname, params); }
    __forceinline static void              GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid* data) { glGetBufferSubData(target, offset, size, data); }
    __forceinline static GLboolean         IsBuffer(GLuint buffer) { glIsBuffer(buffer); }
    __forceinline static GLvoid*           MapBuffer(GLenum target, GLenum access) { glMapBuffer(target, access); }
    __forceinline static GLboolean         UnmapBuffer(GLenum target) { glUnmapBuffer(target); }


    //------------------------------------------
    enum GLenum_framebuffer_object
    {
        INVALID_FRAMEBUFFER_OPERATION                   = 0x0506,
        FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING           = 0x8210,
        FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE           = 0x8211,
        FRAMEBUFFER_ATTACHMENT_RED_SIZE                 = 0x8212,
        FRAMEBUFFER_ATTACHMENT_GREEN_SIZE               = 0x8213,
        FRAMEBUFFER_ATTACHMENT_BLUE_SIZE                = 0x8214,
        FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE               = 0x8215,
        FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE               = 0x8216,
        FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE             = 0x8217,
        FRAMEBUFFER_DEFAULT                             = 0x8218,
        FRAMEBUFFER_UNDEFINED                           = 0x8219,
        DEPTH_STENCIL_ATTACHMENT                        = 0x821A,
        INDEX                                           = 0x8222,
        MAX_RENDERBUFFER_SIZE                           = 0x84E8,
        DEPTH_STENCIL                                   = 0x84F9,
        UNSIGNED_INT_24_8                               = 0x84FA,
        DEPTH24_STENCIL8                                = 0x88F0,
        TEXTURE_STENCIL_SIZE                            = 0x88F1,
        FRAMEBUFFER_BINDING                             = 0x8CA6,
        DRAW_FRAMEBUFFER_BINDING                        = 0x8CA6,
        RENDERBUFFER_BINDING                            = 0x8CA7,
        READ_FRAMEBUFFER                                = 0x8CA8,
        DRAW_FRAMEBUFFER                                = 0x8CA9,
        READ_FRAMEBUFFER_BINDING                        = 0x8CAA,
        RENDERBUFFER_SAMPLES                            = 0x8CAB,
        FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE              = 0x8CD0,
        FRAMEBUFFER_ATTACHMENT_OBJECT_NAME              = 0x8CD1,
        FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL            = 0x8CD2,
        FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE    = 0x8CD3,
        FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER            = 0x8CD4,
        FRAMEBUFFER_COMPLETE                            = 0x8CD5,
        FRAMEBUFFER_INCOMPLETE_ATTACHMENT               = 0x8CD6,
        FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT       = 0x8CD7,
        FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER              = 0x8CDB,
        FRAMEBUFFER_INCOMPLETE_READ_BUFFER              = 0x8CDC,
        FRAMEBUFFER_UNSUPPORTED                         = 0x8CDD,
        MAX_COLOR_ATTACHMENTS                           = 0x8CDF,
        COLOR_ATTACHMENT0                               = 0x8CE0,
        COLOR_ATTACHMENT1                               = 0x8CE1,
        COLOR_ATTACHMENT2                               = 0x8CE2,
        COLOR_ATTACHMENT3                               = 0x8CE3,
        COLOR_ATTACHMENT4                               = 0x8CE4,
        COLOR_ATTACHMENT5                               = 0x8CE5,
        COLOR_ATTACHMENT6                               = 0x8CE6,
        COLOR_ATTACHMENT7                               = 0x8CE7,
        COLOR_ATTACHMENT8                               = 0x8CE8,
        COLOR_ATTACHMENT9                               = 0x8CE9,
        COLOR_ATTACHMENT10                              = 0x8CEA,
        COLOR_ATTACHMENT11                              = 0x8CEB,
        COLOR_ATTACHMENT12                              = 0x8CEC,
        COLOR_ATTACHMENT13                              = 0x8CED,
        COLOR_ATTACHMENT14                              = 0x8CEE,
        COLOR_ATTACHMENT15                              = 0x8CEF,
        DEPTH_ATTACHMENT                                = 0x8D00,
        STENCIL_ATTACHMENT                              = 0x8D20,
        FRAMEBUFFER                                     = 0x8D40,
        RENDERBUFFER                                    = 0x8D41,
        RENDERBUFFER_WIDTH                              = 0x8D42,
        RENDERBUFFER_HEIGHT                             = 0x8D43,
        RENDERBUFFER_INTERNAL_FORMAT                    = 0x8D44,
        STENCIL_INDEX1                                  = 0x8D46,
        STENCIL_INDEX4                                  = 0x8D47,
        STENCIL_INDEX8                                  = 0x8D48,
        STENCIL_INDEX16                                 = 0x8D49,
        RENDERBUFFER_RED_SIZE                           = 0x8D50,
        RENDERBUFFER_GREEN_SIZE                         = 0x8D51,
        RENDERBUFFER_BLUE_SIZE                          = 0x8D52,
        RENDERBUFFER_ALPHA_SIZE                         = 0x8D53,
        RENDERBUFFER_DEPTH_SIZE                         = 0x8D54,
        RENDERBUFFER_STENCIL_SIZE                       = 0x8D55,
        FRAMEBUFFER_INCOMPLETE_MULTISAMPLE              = 0x8D56,
        MAX_SAMPLES                                     = 0x8D57
    };

    typedef GLboolean (APIENTRY *IsRenderbufferFUNC)(GLuint renderbuffer);
    typedef void      (APIENTRY *BindRenderbufferFUNC)(GLenum target, GLuint renderbuffer);
    typedef void      (APIENTRY *DeleteRenderbuffersFUNC)(GLsizei n, const GLuint* renderbuffers);
    typedef void      (APIENTRY *GenRenderbuffersFUNC)(GLsizei n, GLuint* renderbuffers);
    typedef void      (APIENTRY *RenderbufferStorageFUNC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
    typedef void      (APIENTRY *RenderbufferStorageMultisampleFUNC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
    typedef void      (APIENTRY *GetRenderbufferParameterivFUNC)(GLenum target, GLenum pname, GLint* params);
    typedef GLboolean (APIENTRY *IsFramebufferFUNC)(GLuint framebuffer);
    typedef void      (APIENTRY *BindFramebufferFUNC)(GLenum target, GLuint framebuffer);
    typedef void      (APIENTRY *DeleteFramebuffersFUNC)(GLsizei n, const GLuint* framebuffers);
    typedef void      (APIENTRY *GenFramebuffersFUNC)(GLsizei n, GLuint* framebuffers);
    typedef GLenum    (APIENTRY *CheckFramebufferStatusFUNC)(GLenum target);
    typedef void      (APIENTRY *FramebufferTexture1DFUNC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
    typedef void      (APIENTRY *FramebufferTexture2DFUNC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
    typedef void      (APIENTRY *FramebufferTexture3DFUNC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
    typedef void      (APIENTRY *FramebufferTextureLayerFUNC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
    typedef void      (APIENTRY *FramebufferRenderbufferFUNC)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
    typedef void      (APIENTRY *GetFramebufferAttachmentParameterivFUNC)(GLenum target, GLenum attachment, GLenum pname, GLint* params);
    typedef void      (APIENTRY *BlitFramebufferFUNC)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
    typedef void      (APIENTRY *GenerateMipmapFUNC)(GLenum target);
   
    static IsRenderbufferFUNC                      IsRenderbuffer;
    static BindRenderbufferFUNC                    BindRenderbuffer;
    static DeleteRenderbuffersFUNC                 DeleteRenderbuffers;
    static GenRenderbuffersFUNC                    GenRenderbuffers;
    static RenderbufferStorageFUNC                 RenderbufferStorage;
    static RenderbufferStorageMultisampleFUNC      RenderbufferStorageMultisample;
    static GetRenderbufferParameterivFUNC          GetRenderbufferParameteriv;
    static IsFramebufferFUNC                       IsFramebuffer;
    static BindFramebufferFUNC                     BindFramebuffer;
    static DeleteFramebuffersFUNC                  DeleteFramebuffers;
    static GenFramebuffersFUNC                     GenFramebuffers;
    static CheckFramebufferStatusFUNC              CheckFramebufferStatus;
    static FramebufferTexture1DFUNC                FramebufferTexture1D;
    static FramebufferTexture2DFUNC                FramebufferTexture2D;
    static FramebufferTexture3DFUNC                FramebufferTexture3D;
    static FramebufferTextureLayerFUNC             FramebufferTextureLayer;
    static FramebufferRenderbufferFUNC             FramebufferRenderbuffer;
    static GetFramebufferAttachmentParameterivFUNC GetFramebufferAttachmentParameteriv;
    static BlitFramebufferFUNC                     BlitFramebuffer;
    static GenerateMipmapFUNC                      GenerateMipmap;


    //GL_EXT_depth_bounds_test
    enum GLenum_depth_bounds_test
    {
        DEPTH_BOUNDS_TEST                               = 0x8890,
        DEPTH_BOUNDS                                    = 0x8891
    };

    typedef void      (APIENTRY *DepthBoundsFUNC)(GLclampd zmin, GLclampd zmax);

    static DepthBoundsFUNC DepthBounds;



    __forceinline void DrawRectangleArrays(u32 count) { MultiDrawArrays(TRIANGLE_STRIP, rectangle_arrays_i, rectangle_arrays_c, count); }

private:
    void init_occlusion_query();
    void init_vertex_buffer_object();
    void init_framebuffer_object();
    void init_depth_bounds_test();

    static GLint   rectangle_arrays_i[65536/4];
    static GLsizei rectangle_arrays_c[65536/4];
};

extern gl_Core gl;
#endif // gl_Core_h__