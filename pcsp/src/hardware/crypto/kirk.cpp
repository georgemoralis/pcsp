#include "stdafx.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/sha.h>
#include "kirk.h"
#include "cmac.h"
#include <QtCore>
#include <QtGui>

u8 cmd1_key[] = {0x98, 0xC9, 0x40, 0x97, 0x5C, 0x1D, 0x10, 0xE8, 0x7F, 0xE6, 0x0E, 0xA3, 0xFD, 0x03, 0xA8, 0xBA};

u8 cmd7_key1[] = {0x98, 0x02, 0xC4, 0xE6, 0xEC, 0x9E, 0x9E, 0x2F, 0xFC, 0x63, 0x4C, 0xE4, 0x2F, 0xBB, 0x46, 0x68};
u8 cmd7_key2[] = {0x99, 0x24, 0x4C, 0xD2, 0x58, 0xF5, 0x1B, 0xCB, 0xB0, 0x61, 0x9C, 0xA7, 0x38, 0x30, 0x07, 0x5F};
u8 cmd7_key3[] = {0x02, 0x25, 0xD7, 0xBA, 0x63, 0xEC, 0xB9, 0x4A, 0x9D, 0x23, 0x76, 0x01, 0xB3, 0xF6, 0xAC, 0x17};
u8 cmd7_key4[] = {0x84, 0x85, 0xC8, 0x48, 0x75, 0x08, 0x43, 0xBC, 0x9B, 0x9A, 0xEC, 0xA7, 0x9C, 0x7F, 0x60, 0x18};
u8 cmd7_key5[] = {0xB5, 0xB1, 0x6E, 0xDE, 0x23, 0xA9, 0x7B, 0x0E, 0xA1, 0x7C, 0xDB, 0xA2, 0xDC, 0xDE, 0xC4, 0x6E};
u8 cmd7_key6[] = {0xC8, 0x71, 0xFD, 0xB3, 0xBC, 0xC5, 0xD2, 0xF2, 0xE2, 0xD7, 0x72, 0x9D, 0xDF, 0x82, 0x68, 0x82};
u8 cmd7_key7[] = {0x0A, 0xBB, 0x33, 0x6C, 0x96, 0xD4, 0xCD, 0xD8, 0xCB, 0x5F, 0x4B, 0xE0, 0xBA, 0xDB, 0x9E, 0x03};
u8 cmd7_key8[] = {0x32, 0x29, 0x5B, 0xD5, 0xEA, 0xF7, 0xA3, 0x42, 0x16, 0xC8, 0x8E, 0x48, 0xFF, 0x50, 0xD3, 0x71};
u8 cmd7_key9[] = {0x46, 0xF2, 0x5E, 0x8E, 0x4D, 0x2A, 0xA5, 0x40, 0x73, 0x0B, 0xC4, 0x6E, 0x47, 0xEE, 0x6F, 0x0A};
u8 cmd7_key10[] = {0x5D, 0xC7, 0x11, 0x39, 0xD0, 0x19, 0x38, 0xBC, 0x02, 0x7F, 0xDD, 0xDC, 0xB0, 0x83, 0x7D, 0x9D};
u8 cmd7_key11[] = {0x12, 0x46, 0x8D, 0x7E, 0x1C, 0x42, 0x20, 0x9B, 0xBA, 0x54, 0x26, 0x83, 0x5E, 0xB0, 0x33, 0x03};
u8 cmd7_key12[] = {0xC4, 0x3B, 0xB6, 0xD6, 0x53, 0xEE, 0x67, 0x49, 0x3E, 0xA9, 0x5F, 0xBC, 0x0C, 0xED, 0x6F, 0x8A};
u8 cmd7_key13[] = {0x2C, 0xC3, 0xCF, 0x8C, 0x28, 0x78, 0xA5, 0xA6, 0x63, 0xE2, 0xAF, 0x2D, 0x71, 0x5E, 0x86, 0xBA};
u8 cmd7_key14[] = {0x0C, 0xFD, 0x67, 0x9A, 0xF9, 0xB4, 0x72, 0x4F, 0xD7, 0x8D, 0xD6, 0xE9, 0x96, 0x42, 0x28, 0x8B};
u8 cmd7_key15[] = {0xAF, 0xFE, 0x8E, 0xB1, 0x3D, 0xD1, 0x7E, 0xD8, 0x0A, 0x61, 0x24, 0x1C, 0x95, 0x92, 0x56, 0xB6};
u8 cmd7_key16[] = {0x1C, 0x9B, 0xC4, 0x90, 0xE3, 0x06, 0x64, 0x81, 0xFA, 0x59, 0xFD, 0xB6, 0x00, 0xBB, 0x28, 0x70};
u8 cmd7_key17[] = {0x11, 0x5A, 0x5D, 0x20, 0xD5, 0x3A, 0x8D, 0xD3, 0x9C, 0xC5, 0xAF, 0x41, 0x0F, 0x0F, 0x18, 0x6F};
u8 cmd7_key18[] = {0x9C, 0x9B, 0x13, 0x72, 0xF8, 0xC6, 0x40, 0xCF, 0x1C, 0x62, 0xF5, 0xD5, 0x92, 0xDD, 0xB5, 0x82};
u8 cmd7_key19[] = {0x03, 0xB3, 0x02, 0xE8, 0x5F, 0xF3, 0x81, 0xB1, 0x3B, 0x8D, 0xAA, 0x2A, 0x90, 0xFF, 0x5E, 0x61};  

typedef struct header_keys  {
	u8 aes[16];      
	u8 cmac[16];  
} header_keys;

u8 fuseID[16];
u8 ivec[16];
AES_KEY aes_cmd1;
int init;  

int cmd1(void *out, void* in, int size)
{
	if(init == 0)
	{
		return KIRK_NOT_INITIALIZED;
	}

	KIRK_CMD1_HEADER* header = (KIRK_CMD1_HEADER*)in;
	if(header->mode != KIRK_MODE_CMD1) 
	{ 
		return KIRK_INVALID_MODE;
	}

	header_keys keys;
	AES_cbc_encrypt((unsigned char *)in, (u8*)&keys, 16*2, &aes_cmd1, ivec, AES_DECRYPT);

	// Currently ignore the signcheck.
	/*int ret = cmd10(in, size); 
	if (ret != KIRK_OPERATION_SUCCESS) {
		return ret;   
	}*/

	AES_KEY dec_key;        
	AES_set_decrypt_key(keys.aes, 128, &dec_key);
	AES_cbc_encrypt((unsigned char *)in + 144 + header->data_offset, (unsigned char *)out, header->data_size, &dec_key, ivec, AES_DECRYPT); 

	return KIRK_OPERATION_SUCCESS; 
}

int cmd4(void* out, void* in, int size)  
{
	if(init == 0) 
	{
		return KIRK_NOT_INITIALIZED;
	}

	KIRK_AES128CBC_HEADER *header = (KIRK_AES128CBC_HEADER*)in;
	if(header->mode != KIRK_MODE_ENCRYPT_CBC) 
	{
		return KIRK_INVALID_MODE;
	}

	if(header->data_size == 0) 
	{
		return KIRK_DATA_SIZE_ZERO; 
	}

	u8* key = get_key(header->keyseed);
	if(key == (u8*)KIRK_INVALID_SIZE) 
	{
		return KIRK_INVALID_SIZE;  
	}

	u8 ivec[16];       
	memset(ivec, 0, sizeof(ivec));  

	AES_KEY aesKey;     
	AES_set_encrypt_key(key, 128, &aesKey);
	AES_cbc_encrypt((unsigned char *)in + 20, (unsigned char *)out, size, &aesKey, ivec, AES_ENCRYPT);   
	
	return KIRK_OPERATION_SUCCESS;  
}

int cmd7(void* out, void* in, int size)  
{
	if(init == 0) 
	{
		return KIRK_NOT_INITIALIZED;
	}

	KIRK_AES128CBC_HEADER *header = (KIRK_AES128CBC_HEADER*)in;
	if(header->mode != KIRK_MODE_DECRYPT_CBC) 
	{
		return KIRK_INVALID_MODE;
	}

	if(header->data_size == 0) 
	{
		return KIRK_DATA_SIZE_ZERO; 
	}

	u8* key = get_key(header->keyseed);
	if(key == (u8*)KIRK_INVALID_SIZE) 
	{
		return KIRK_INVALID_SIZE;  
	}

	u8 ivec[16];       
	memset(ivec, 0, sizeof(ivec));  

	AES_KEY aesKey;     
	AES_set_decrypt_key(key, 128, &aesKey);
	AES_cbc_encrypt((unsigned char *)in + 20, (unsigned char *)out, size, &aesKey, ivec, AES_DECRYPT);   
	
	return KIRK_OPERATION_SUCCESS;  
} 

int cmd10(void* in, int size)
{   
	if(init == 0) 
	{
		return KIRK_NOT_INITIALIZED;
	}	

	KIRK_CMD1_HEADER* header = (KIRK_CMD1_HEADER*)in;    	
	if(!(header->mode == KIRK_MODE_CMD1 || header->mode == KIRK_MODE_CMD2 || header->mode == KIRK_MODE_CMD3)) 
	{
		return KIRK_INVALID_MODE;     
	}

	if(header->data_size == 0) 
	{
		return KIRK_DATA_SIZE_ZERO;  
	}

	if(header->mode == KIRK_MODE_CMD1) 
	{      
		header_keys keys;
		AES_cbc_encrypt((unsigned char *)in, (u8*)&keys, 32, &aes_cmd1, ivec, AES_DECRYPT);         
		u8 cmac_header_hash[16];          
		AES_CMAC(keys.cmac, (unsigned char *)in + 0x60, 0x30, cmac_header_hash);   
		u8 cmac_data_hash[16];         
   
		int chk_size = header->data_size;       
		if(chk_size % 16) 
		{
			chk_size += 16 - (chk_size % 16);
		}

		AES_CMAC(keys.cmac, (unsigned char *)in + 0x60, 0x30 + chk_size + header->data_offset, cmac_data_hash);     
		if(memcmp(cmac_header_hash, header->CMAC_header_hash, 16) != 0)   
		{            
			printf("KIRK cmd10: AES CMAC header hash invalid.\n");       
			return KIRK_HEADER_HASH_INVALID;        
		}               
		if(memcmp(cmac_data_hash, header->CMAC_data_hash, 16) != 0)   
		{         
			printf("KIRK cmd10: AES CMAC data hash invalid.\n");   
			return KIRK_DATA_HASH_INVALID;  
		}       

		return KIRK_OPERATION_SUCCESS;    
	}     

	return KIRK_SIG_CHECK_INVALID;
}

int cmd11(void *out, void *in, int size)
{
	if(init == 0) 
	{
		return KIRK_NOT_INITIALIZED;
	}	

    KIRK_SHA1_HEADER *header;
    SHA_CTX Sha1_Ctx;
    char SHA1_Key[SHA_DIGEST_LENGTH];

    size <<= 4;
    size >>= 4;
    header = (KIRK_SHA1_HEADER *) in;
    size = size < header->data_size ? size : header->data_size;

    SHA1_Init(&Sha1_Ctx);
    SHA1_Update(&Sha1_Ctx, header->data, size);
    SHA1_Final((u8 *)SHA1_Key, &Sha1_Ctx);

    memcpy(out, SHA1_Key, SHA_DIGEST_LENGTH);

    return KIRK_OPERATION_SUCCESS;
}

int kirk_init()  
{ 
	AES_set_decrypt_key(cmd1_key, 128, &aes_cmd1);     
	init = 1; 
	return 0; 
}   

int sceUtilsSetFuseID(void* fuseaddr)  
{  
	memcpy(fuseID, fuseaddr, 16);      
	return 0;  
}  

int sceUtilsBufferCopyWithRange(void* out, int outsize, void* in, int insize, int cmd)
{  
	switch(cmd)    
	{                 
	case KIRK_CMD_DECRYPT_PRIVATE: 
		return cmd1(out, in, insize);
		break;
	case KIRK_CMD_ENCRYPT_IV_0: 
		return cmd4(out, in, insize);
		break;
	case KIRK_CMD_DECRYPT_IV_0: 
		return cmd7(out, in, insize);
		break;
	case KIRK_CMD_PRIV_SIG_CHECK:
		return cmd10(in, insize); 
		break;
	case KIRK_CMD_SHA1_HASH: 
		return cmd11(out, in, insize);
		break;
	}          
	return -1;  
}  

u8* get_key(int key_type)
{
	switch(key_type)         
	{  
	case(0x03): return cmd7_key1; break;     
	case(0x04): return cmd7_key2; break;   
	case(0x05): return cmd7_key3; break;     
	case(0x0C): return cmd7_key4; break; 
	case(0x0D): return cmd7_key5; break;   
	case(0x0E): return cmd7_key6; break;       
	case(0x0F): return cmd7_key7; break;      
	case(0x10): return cmd7_key8; break;        
	case(0x11): return cmd7_key9; break;        
	case(0x12): return cmd7_key10; break;       
	case(0x38): return cmd7_key11; break;      
	case(0x39): return cmd7_key12; break;       
	case(0x3A): return cmd7_key13; break;        
	case(0x4B): return cmd7_key14; break;        
	case(0x53): return cmd7_key15; break;         
	case(0x57): return cmd7_key16; break;         
	case(0x5D): return cmd7_key17; break;           
	case(0x63): return cmd7_key18; break;          
	case(0x64): return cmd7_key19; break;        
	default: return (u8*)KIRK_INVALID_SIZE; break; 
	} 
}  