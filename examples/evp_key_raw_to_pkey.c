#include<stdio.h>
#include<string.h>
#include<openssl/err.h>
#include<openssl/cms.h>
#include <openssl/evp.h>
#include <openssl/asn1.h>

void print_str(unsigned char *s, size_t len){
/**
 * Print a charecter array in string
 * @param [in] s is the string to be printed 
 * @param [in] len is the number of character to be printed
 * 
 * @pre @a s and @b must not be NULL 
*/
  size_t i;
  printf("\n");
  for(i=0; i< len; i++)
    printf("%c", s[i]);
  printf("\n");
}


void print_hex(unsigned char *s, size_t len){
/**
 * Print a charecter array in string
 * @param [in] s is the string to be printed 
 * @param [in] len is the number of character to be printed
 * 
 * @pre @a s and @b must not be NULL 
*/
  size_t i;
  printf("\n");
  for(i=0; i< len; i++)
    printf("%02x", s[i]);
  printf("\n");
}


int main(){

    int i=0;
    EVP_PKEY *key = NULL;
    EVP_PKEY_CTX *ctx;
    unsigned char key_val[] = "fdsf dshfsdkahf  asdhf";
    size_t key_len = strlen(key_val);

    unsigned char *key_dis;
    size_t key_dis_len;

    // Create a empty EVP_PKEY structure
    //key = EVP_PKEY_new();

    /*
    type: should be NID of the following:
       EVP_PKEY_HMAC, EVP_PKEY_POLY1305, EVP_PKEY_SIPHASH, EVP_PKEY_X25519, EVP_PKEY_ED25519, EVP_PKEY_X448 or EVP_PKEY_ED448
    */
   printf("size xx: %ld\n", key_len);

    key = EVP_PKEY_new_raw_private_key(EVP_PKEY_HMAC, NULL, key_val, key_len);

    if(NULL == key){
        printf("PKEY generation failed\n");
        return 1;
    }

    // Buffer key_dis is set to NULL to get the size of key in key_dis_len
    if(!EVP_PKEY_get_raw_private_key(key, NULL, &key_dis_len)){
        printf("Something goes wrong\n");
        printf("size = %ld", key_dis_len);
        return 1;
    }

    // Allocate the memory for buffer key_dis 
    key_dis = (unsigned char*) malloc(key_dis_len*sizeof(unsigned char));
    if(NULL == key_dis){
        printf("\nMemory allocation failed!");
        return 1;
    }

    // Get the key in key_val. This is a sequence of byte, not null terminated
    if(!EVP_PKEY_get_raw_private_key(key, key_dis, &key_dis_len)){
        printf("Something goes wrong\n");
        printf("size = %ld", key_dis_len);
        return 1;
    }
 
    print_str(key_dis, key_dis_len);

    return 0;
}