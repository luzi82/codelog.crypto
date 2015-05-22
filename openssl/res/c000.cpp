#include <openssl/sha.h>
#include <stdio.h>

int main()
{
	FILE* ifp=NULL;
	unsigned char buf[4096];
	size_t s=0;
	
	ifp = fopen("data.jpg","rb");
	if(ifp==NULL){
		return 1;
	}
	
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	unsigned char hash[SHA256_DIGEST_LENGTH];
	
	while(!feof(ifp)){
		s = fread(buf,1,4096,ifp);
		SHA256_Update(&sha256, buf, s);
	}
	
	SHA256_Final(hash, &sha256);
	
	fclose(ifp);
	ifp = NULL;
	
	FILE* ofp = NULL;
	ofp = fopen("data.jpg.c000","wb");
	if(ofp==NULL){
		return 2;
	}
	
	fwrite(hash,SHA256_DIGEST_LENGTH,1,ofp);

	fclose(ofp);
	ofp = NULL;
}
