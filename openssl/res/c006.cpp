// test BIO_new_file

#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <stdio.h>
#include <sys/stat.h>

int main()
{
	const char* inFilename="data.jpg";

	BIO* fileBio=BIO_new_file(inFilename,"rb");
	
	unsigned char* buffer[4096];

    FILE* out = fopen("data.jpg.c006", "wb");
    // warning: do not use BIO_eof
    while(true){
    	int len=BIO_read(fileBio,buffer,1000);
    	if(len>0){
    		fwrite(buffer, 1, len, out);
    	}else if(len==0){
    		break;
    	}else{
    		return 1;
    	}
    }
    BIO_free(fileBio);

    fclose(out);

    return 0;
}
