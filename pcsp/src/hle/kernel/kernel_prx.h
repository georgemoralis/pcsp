#define PRX_MODULE_MAX_NAME     28
#define PRX_LIB_MAX_NAME        128
#define PRX_ENTRY_MAX_NAME      128

/* Define the maximum number of permitted entries per lib */
#define PRX_MAX_V_ENTRIES 255
#define PRX_MAX_F_ENTRIES 65535

#define PRX_MODULE_INFO_NAME ".rodata.sceModuleInfo"

/* Remove the .rel.sceStub.text section as it shouldn't have been there */
#define PRX_MODULE_REMOVE_REL ".rel.sceStub.text"

/* Define a name for the unnamed first export */
#define PRX_SYSTEM_EXPORT "syslib"

enum PrxEntryType
{
    PRX_ENTRY_FUNC = 0,
    PRX_ENTRY_VAR  = 1
};

/* Structure to hold the module export information */
struct PrxModuleExport
{
    u32                 name;
    u32                 flags;
    u32                 counts;
    u32                 exports;
};

/* Structure to hold the module import information */
struct PrxModuleImport
{
    u32                 name;
    u32                 flags;
    u8                  entry_size;
    u8                  var_count;
    u16                 func_count;
    u32                 nids;
    u32                 funcs;
} ;

/* Structure to hold the module info */
struct PrxModuleInfo
{
    u32                 flags;
    char                name[PSP_MODULE_MAX_NAME];
    u32                 gp;
    u32                 exports;
    u32                 exp_end;
    u32                 imports;
    u32                 imp_end;
};

/* Define the loaded prx types */
struct PrxEntry
{
    char                name[PSP_ENTRY_MAX_NAME];
    u32                 nid;
    enum PrxEntryType   type;
    u32                 addr;
    u32                 nid_addr;
};

