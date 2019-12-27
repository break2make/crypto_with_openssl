/**
 * Author: Durga Prasad Sahoo
 * Date: 26/12/2019
 */

#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

/**
 * @param [in] sec_len is secure length in bits
 * @param [in] pub_key is a decimal string (e.g. "65537" to provide the public exponent e = 65537)
 * @param [in] pub_keyfile is a .pem file with path
 * @param [in] pri_keyfile is a .pem file with path
*/

int evp_rsa_keygen_save_to_file(int sec_len, char *pub_key, char *pub_keyfile, char *pri_keyfile){
    
    EVP_PKEY_CTX *ctx;
    EVP_PKEY *key;
    int ret;
    FILE *fp = NULL;
    BIGNUM *pkey_bn = NULL;

    
    const int KEY_TYPE = EVP_PKEY_RSA;

    // Create a EVP_PKEY context for given NID of the key type
    ctx = EVP_PKEY_CTX_new_id(KEY_TYPE, NULL);
    if (!ctx) {
        printf("\nContex creation failed.");
        return -1;
    }

    // Initialize the RSA context structure
    ret = EVP_PKEY_keygen_init(ctx);
    if (ret != 1) {
        printf("\nContext initialization failed.");
        return -1;
    }

    // This is macro call, which calls RSA_pkey_ctx_ctrl(EVP_PKEY_CTX *ctx, int optype, int cmd, int p1, void *p2)
    // https://github.com/openssl/openssl/blob/master/crypto/rsa/rsa_lib.c

    if (1 != EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, sec_len)) {
        printf("\nFailed to set keygen bits");
        return -1;
    }


    if(NULL != pub_key){
        if(!BN_dec2bn(&pkey_bn, pub_key)){
            printf("\n Error in BIGNUM generation from %s.", pub_key);
            return -1;
        } 
        if(1 != EVP_PKEY_CTX_set_rsa_keygen_pubexp(ctx, pkey_bn)){
            printf("\nFailed to set public exponent bits");
            return -1;
        } 
    } 

    // Generate keys
    ret = EVP_PKEY_keygen(ctx, &key);
    if (ret != 1) {
        return -1;
    }

    // Write private key into file with PEM encoding
    fp = fopen(pri_keyfile, "w");
    if (!fp) {
        printf("\n%s creation failed", pri_keyfile);
        return -1;
    }

    ret = PEM_write_PrivateKey(fp, key, NULL, NULL, 0, NULL, NULL);
    if (ret != 1) {
        printf("\nWriting to %s failed", pri_keyfile);
        return -1;
    }

    fclose(fp);

    // Write public key into file
    fp = fopen(pub_keyfile, "w");
    if (!fp) {
        printf("\n%s creation failed", pub_keyfile);
        return -1;
    }

    ret = PEM_write_PUBKEY(fp, key);
    if (ret != 1) {
        printf("\nWriting to %s failed", pub_keyfile);
        return -1;
    }
    
    fclose(fp);

    return 0;

}


int evp_rsa_keygen(int sec_len, char *pub_key, char *pub_keyfile, char *pri_keyfile){
    
    EVP_PKEY_CTX *ctx;
    EVP_PKEY *key;
    int ret;
    FILE *fp = NULL;
    BIGNUM *pkey_bn = NULL;
    RSA *rsa_pkey = NULL;

    const BIGNUM *x;

    
    const int KEY_TYPE = EVP_PKEY_RSA;

    // Create a EVP_PKEY context for given NID of the key type
    ctx = EVP_PKEY_CTX_new_id(KEY_TYPE, NULL);
    if (!ctx) {
        printf("\nContex creation failed.");
        return -1;
    }

    // Initialize the RSA context structure
    ret = EVP_PKEY_keygen_init(ctx);
    if (ret != 1) {
        printf("\nContext initialization failed.");
        return -1;
    }

    // This is macro call, which calls RSA_pkey_ctx_ctrl(EVP_PKEY_CTX *ctx, int optype, int cmd, int p1, void *p2)
    // https://github.com/openssl/openssl/blob/master/crypto/rsa/rsa_lib.c

    if (1 != EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, sec_len)) {
        printf("\nFailed to set keygen bits");
        return -1;
    }


    if(NULL != pub_key){
        if(!BN_dec2bn(&pkey_bn, pub_key)){
            printf("\n Error in BIGNUM generation from %s.", pub_key);
            return -1;
        } 
        if(1 != EVP_PKEY_CTX_set_rsa_keygen_pubexp(ctx, pkey_bn)){
            printf("\nFailed to set public exponent bits");
            return -1;
        } 
    } 

    // Generate keys
    ret = EVP_PKEY_keygen(ctx, &key);
    if (ret != 1) {
        return -1;
    }

    rsa_pkey = EVP_PKEY_get0_RSA(key);
    if (NULL == rsa_pkey){
        printf("\n Conversion to RSA failed.");
        return -1;
    }

    x = RSA_get0_e(rsa_pkey);
    printf("Result is %s\n", BN_bn2dec(x));    


    return 0;

}

int main()
{
    char *pub_keyfile = "./rsa_public_key.pem";
    char *pri_keyfile = "./rsa_private_key.pem";
    int sec_len = 2048;

    if(0 != evp_rsa_keygen(sec_len, "7", pub_keyfile, pri_keyfile)){
        printf("\nKey generation failed!\n");
        return 1;
    }
    printf("\nKey generation is successful!\n");
    return 0;
}