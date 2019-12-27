
 BIO *bio_out;
 bio_out = BIO_new_fp(stdout, BIO_NOCLOSE);
 BIO_printf(bio_out, "Hello World\n");


     in = BIO_new_file(argv[1], "r");
    if (!in)
        goto err;

//    cms = PEM_read_bio_CMS(in, NULL, NULL, NULL);   //PEM
    cms = d2i_CMS_bio(in, NULL);  



    https://stackoverflow.com/questions/55654448/using-openssl-api-how-can-i-access-a-signers-certificate-info-from-a-signed-fil