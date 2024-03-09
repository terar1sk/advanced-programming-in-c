#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "bmp.h"

char* reverse(const char* text){
    if(text == NULL){
        return NULL;
    }

    int lgh = strlen(text);
    char* reversed = (char*)malloc((lgh + 1) * sizeof(char)); 
    if(reversed == NULL){
        return NULL;
    }

    for(int a = 0; a < lgh; a++){
        reversed[a] = toupper(text[lgh - a - 1]);
    }
    reversed[lgh] = '\0';
    return reversed;
}


char* vigenere_encrypt(const char* key, const char* text){
    if(key == NULL || text == NULL || key[0] == '\0' || text[0] == '\0'){
        return NULL;
    }
    int kl = strlen(key);
    int tl = strlen(text);

    char* encrypted = (char*)malloc((tl + 1) * sizeof(char));
    if(encrypted == NULL){
        return NULL;
    }
    
    int keyi = 0;
    for(int a = 0; a < tl; ++a){
        char key_char = toupper(key[keyi % kl]);
        ++keyi;
        if(isalpha(key_char)){
            if(isalpha(text[a])){
                encrypted[a] = ((toupper(text[a]) - 'A' + (key_char - 'A')) % 26) + 'A';
            }
            else{
                encrypted[a] = text[a]; 
                --keyi;
            }
        }
        else{
            encrypted[a] = text[a];
            --keyi;
        }
    }
    encrypted[tl] = '\0';
    return encrypted;
}

char* vigenere_decrypt(const char* key, const char* text){
    if(key == NULL || text == NULL || key[0] == '\0' || text[0] == '\0'){
        return NULL;
    }
    int kl = strlen(key);
    int tl = strlen(text);

    char* decrypted = (char*)malloc((tl + 1) * sizeof(char));
    if(decrypted == NULL){
        return NULL;
    }
    for(int a = 0, b = 0; a < tl; ++a, ++b){
        if(b == kl){
            b = 0;
        }
        char key_char = toupper(key[b]) - 'A';
        char text_char = toupper(text[a]);
        if(isalpha(text_char)){
            decrypted[a] = ((text_char - 'A' - key_char + 26) % 26) + 'A';
        }
        else{
            decrypted[a] = text_char;
            --b;
        }
    }
    decrypted[tl] = '\0';
    return decrypted;
}


unsigned char* bit_encrypt(const char* text){
   if(text == NULL){
        return NULL;
   }
    unsigned char* encrypted = (unsigned char*)malloc((strlen(text) + 1) * sizeof(unsigned char));
    if(encrypted == NULL){
        return NULL;
    }
    for(size_t a = 0; a < strlen(text); ++a){
        unsigned char fst = text[a] >> 4;
        unsigned char sec = text[a] & 0x0F;

        fst = ((fst & 0x0A) >> 1) | ((fst & 0x05) << 1);
        encrypted[a] = (fst << 4) ^ sec;
    }

    return encrypted;
}

char* bit_decrypt(const unsigned char* text){
    if(text == NULL){
        return NULL;
    }
    char* decrypted = (char*)malloc((strlen((char*)text) + 1) * sizeof(char));
    if(decrypted == NULL){
        return NULL;
    }
    for(size_t a = 0; a < strlen((char*)text); ++a){
        unsigned char fst = text[a] >> 4;
        unsigned char sec = text[a] & 0x0F;

        fst = ((fst & 0x0A) >> 1) | ((fst & 0x05) << 1);
        decrypted[a] = (fst << 4) ^ sec;
    }

    decrypted[strlen((char*)text)] = '\0';

    return decrypted;
}



unsigned char* bmp_encrypt(const char* key, const char* text){
    if(key == NULL || text == NULL || key[0] == '\0' || text[0] == '\0'){
        return NULL;
    }

    char* reversed_text = reverse(text);
    if(reversed_text == NULL){
        return NULL;
    }

    char* vigenere_encrypted = vigenere_encrypt(key, reversed_text);
    free(reversed_text);
    if(vigenere_encrypted == NULL){
        return NULL;
    }

    unsigned char* bit_encrypted = bit_encrypt(vigenere_encrypted);
    free(vigenere_encrypted);
    return bit_encrypted;
}

char* bmp_decrypt(const char* key, const unsigned char* text){
    if(key == NULL || text == NULL || key[0] == '\0' || text[0] == '\0'){
        return NULL;
    }

    char* bit_decrypted = bit_decrypt(text);
    if(bit_decrypted == NULL){
        return NULL;
    }

    char* vigenere_decrypted = vigenere_decrypt(key, bit_decrypted);
    free(bit_decrypted);
    if(vigenere_decrypted == NULL){
        return NULL;
    }

    char* reversed_decrypted = reverse(vigenere_decrypted);
    free(vigenere_decrypted);
    return reversed_decrypted;
}
