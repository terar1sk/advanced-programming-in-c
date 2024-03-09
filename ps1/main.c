#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include "bmp.h"

int main(){
    char* reversed = reverse("Hello world!");
    if(reversed == NULL){
        return 1;
    }
    printf("%s\n", reversed);
    free(reversed);

    
    char* encrypted_vigenere;
    encrypted_vigenere = vigenere_encrypt("CoMPuTeR", "Hello world!");
    if(encrypted_vigenere != NULL){
        printf("%s\n", encrypted_vigenere);
        free(encrypted_vigenere);
    }
    
    char* decrypted_vigenere;
    decrypted_vigenere = vigenere_decrypt("CoMPuTeR", "Hello world!");
    if(decrypted_vigenere != NULL){
        printf("%s\n", decrypted_vigenere);
        free(decrypted_vigenere);
    }
    
    unsigned char* encrypted_bit;
    char* decrypted_bit;

    encrypted_bit = bit_encrypt("Hello world!");
    for(int i=0; i < 12;i++) {
        printf("%x ", encrypted_bit[i]);
    }
    printf("\n");
    
    decrypted_bit = bit_decrypt(encrypted_bit);
    printf("%s\n", decrypted_bit);

    free(encrypted_bit);
    free(decrypted_bit);

    return 0;
}
