#ifndef KIRK
#define KIRK

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned int u32;

#define KIRK_OPERATION_SUCCESS 0
#define KIRK_NOT_ENABLED 1
#define KIRK_INVALID_MODE 2
#define KIRK_HEADER_HASH_INVALID 3
#define KIRK_DATA_HASH_INVALID 4
#define KIRK_SIG_CHECK_INVALID 5
#define KIRK_UNK_1 6
#define KIRK_UNK_2 7
#define KIRK_UNK_3 8
#define KIRK_UNK_4 9
#define KIRK_UNK_5 0xA
#define KIRK_UNK_6 0xB
#define KIRK_NOT_INITIALIZED 0xC
#define KIRK_INVALID_OPERATION 0xD
#define KIRK_INVALID_SEED_CODE 0xE
#define KIRK_INVALID_SIZE 0xF
#define KIRK_DATA_SIZE_ZERO 0x10 

typedef struct {
	int data_size;
    u8 data[];
} KIRK_SHA1_HEADER;

typedef struct  {
	int mode;    
	int unk_4;   
	int unk_8;  
	int keyseed; 
	int data_size;   
} KIRK_AES128CBC_HEADER; 

typedef struct  {       
	u8 AES_key[16];         
	u8 CMAC_key[16];                  
	u8 CMAC_header_hash[16];        
	u8 CMAC_data_hash[16];     
	u8 unused[32];            
	u32 mode;                 
	u8 unk3[12];            
	u32 data_size;           
	u32 data_offset;         
	u8 unk4[8];              
	u8 unk5[16];              
} KIRK_CMD1_HEADER; 

#define KIRK_CMD_DECRYPT_PRIVATE 1  
#define KIRK_CMD_ENCRYPT_IV_0 4  
#define KIRK_CMD_ENCRYPT_IV_FUSE 5  
#define KIRK_CMD_ENCRYPT_IV_USER 6  
#define KIRK_CMD_DECRYPT_IV_0 7  
#define KIRK_CMD_DECRYPT_IV_FUSE 8  
#define KIRK_CMD_DECRYPT_IV_USER 9  
#define KIRK_CMD_PRIV_SIG_CHECK 10
#define KIRK_CMD_SHA1_HASH 11

#define KIRK_MODE_CMD1 1  
#define KIRK_MODE_CMD2 2  
#define KIRK_MODE_CMD3 3  
#define KIRK_MODE_ENCRYPT_CBC 4  
#define KIRK_MODE_DECRYPT_CBC 5    

int cmd1(void* out, void* in, int size);
int cmd4(void* out, void* in, int size);
int cmd7(void* out, void* in, int size); 
int cmd10(void* in, int size);
int cmd11(void *out, void *in, int size);
u8* get_key(int key_type);
int kirk_init(); 
int sceUtilsSetFuseID(void* fuseaddr);
int sceUtilsBufferCopyWithRange(void* out, int outsize, void* in, int insize, int cmd);
#endif 
