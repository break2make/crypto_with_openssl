#include<stdio.h>
#include<openssl/err.h>
#include<openssl/cms.h>
 #include <openssl/asn1.h>

int main(){

    //char* in_file = "cst_output1";
    ASN1_OCTET_STRING **pconf = NULL;
    ASN1_OCTET_STRING *z;
    const ASN1_OBJECT *x;

    BIO *in = NULL;
    BIO *out = NULL;
    char buf[1024];
    int buf_len = 1024;
    int d = 0;
    unsigned char *y;
    
    CMS_ContentInfo *cms = NULL;
    //printf("Here");

    in  = BIO_new_file("./cst_output1.der","r");
    if (NULL == in){
        printf("Could not open the file for bio creation");
        return EXIT_FAILURE;
    }

    //printf("Here");
    cms = d2i_CMS_bio(in, NULL); 
    x = CMS_get0_type(cms);
    //x = CMS_get0_eContentType(cms);

    OBJ_obj2txt(buf, buf_len,x,0);
    buf[buf_len] = '\0';
    printf("%s\n",buf);


    if(NULL == pconf){
        printf("pconf is NULL\n");
    }

    pconf = CMS_get0_content(cms);
    //printf("%p",pconf);
    
    z = *pconf;
    printf("%d", ASN1_STRING_length(z));

    if(NULL == pconf){
        printf("pconf is not valid\n");
        return 0;
    }
    
    

    d = ASN1_STRING_length(*pconf);
    printf("--%d",d);
    //y = ASN1_STRING_data(*pconf);
    //y = ASN1_STRING_get0_data(*pconf);

    //(**pconf).data[20] = '\0';
    //printf("%s",(**pconf).data);
    
    return 0;
}