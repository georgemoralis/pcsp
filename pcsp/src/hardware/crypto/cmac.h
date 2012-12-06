#ifndef CMAC_AES_H
#define CMAC_AES_H

#include <string.h>
#include <openssl/aes.h>

void AES_CMAC(unsigned char *key, unsigned char *input, int length, unsigned char *mac);

#endif