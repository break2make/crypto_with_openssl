#include<stdio.h>
#include<openssl/err.h>
#include<openssl/cms.h>
#include <openssl/asn1.h>


int main(){

    CMS_ContentInfo *cms;
    const ASN1_OBJECT *x;
    char buf[1024];
    int buf_len = 1024;

    cms = CMS_ContentInfo_new();
    // Set the CMS type
    if(!CMS_SignedData_init(cms)){
        printf("CMS initialization error");
    }




    x = CMS_get0_type(cms);
    //x = CMS_get0_eContentType(cms);

    OBJ_obj2txt(buf, buf_len,x,0);
    buf[buf_len] = '\0';
    printf("%s\n",buf);

    return 0;
}
