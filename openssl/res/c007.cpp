// test BIO_f_cipher

#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <stdio.h>
#include <sys/stat.h>

int main()
{
	const char* inFilename="data.jpg.enc";
    unsigned char key[] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef};
    unsigned char iv[]  = {0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};

	BIO* fileBio=BIO_new_file(inFilename,"rb");
	
	BIO* cipherBio = BIO_new(BIO_f_cipher ());
	BIO_set_cipher (cipherBio, EVP_aes_128_cbc (), key, iv, 0);
	
	BIO_push(cipherBio,fileBio);

	unsigned char* buffer[4096];

    FILE* out = fopen("data.jpg.enc.-.c007", "wb");
    // warning: do not use BIO_eof
    while(true){
    	int len=BIO_read(cipherBio,buffer,4096);
    	if(len>0){
    		fwrite(buffer, 1, len, out);
    	}else if(len==0){
    		break;
    	}else{
    		return 1;
    	}
    }
    BIO_free(cipherBio);

    fclose(out);

    return 0;
}
