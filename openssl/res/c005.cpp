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

	struct stat st;
	stat(inFilename, &st);
	int inputSize = st.st_size;

	int inputBufSize = inputSize+100;
	unsigned char* inputBuf=new unsigned char[inputBufSize];
	int inputLen=0;

	int outputBufSize = inputSize+100;
	unsigned char* outputBuf=new unsigned char[outputBufSize];
	int outputLen=0;
	
	int tmpInt;
	
	FILE* inFile = fopen(inFilename,"rb");
	if(inFile==NULL){
		return 1;
	}
	while(!feof(inFile)){
		inputLen += fread(inputBuf+inputLen,1,4096,inFile);
	}
	fclose(inFile);inFile = NULL;

    EVP_CIPHER_CTX ctx;

    EVP_CIPHER_CTX_init(&ctx);
    EVP_DecryptInit_ex(&ctx, EVP_aes_128_cbc(), NULL, key, iv);

    if(!EVP_DecryptUpdate(&ctx, outputBuf, &outputLen, inputBuf, inputLen))
    {
	    return 1;
    }
    if(!EVP_DecryptFinal_ex(&ctx, outputBuf + outputLen, &tmpInt))
    {
        return 1;
    }
    outputLen += tmpInt;
    EVP_CIPHER_CTX_cleanup(&ctx);

    FILE* out = fopen("data.jpg.enc.dec.1", "wb");
    fwrite(outputBuf, 1, outputLen, out);
    fclose(out);

    return 0;
}
