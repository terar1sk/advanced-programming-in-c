#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bmp.h"

int main(){
    unsigned char *bmp_encrypted; 
    char *bmp_decrypted;
    bmp_encrypted = bmp_encrypt("Wow", "Hello world!");
    for(int i=0; i < 12;i++) {
        printf("%x ", bmp_encrypted[i]);
    }
    putchar('\n');
    bmp_decrypted = bmp_decrypt("Wow", bmp_encrypted);
    printf("%s\n", bmp_decrypted);
    free(bmp_encrypted);
    free(bmp_decrypted);
}
