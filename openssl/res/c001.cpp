#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
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
	
	ifp = fopen("public.pem","rb");
	if(ifp==NULL){
		return 2;
	}
	
	unsigned char public_pem_buf[4096];
	size_t public_pem_buf_len = 0;
	public_pem_buf_len = fread(public_pem_buf,1,4096,ifp);
	fclose(ifp);
	ifp = NULL;
	
	BIO* public_pem_bio=NULL;
	public_pem_bio = BIO_new_mem_buf(public_pem_buf,public_pem_buf_len);
	
	RSA * public_rsa = NULL;
	public_rsa = PEM_read_bio_RSA_PUBKEY(public_pem_bio, NULL, NULL, NULL);
	if(public_rsa==NULL){
		printf("public_rsa==NULL\n");
		return 4;
	}
	
	ifp = fopen("data.jpg.pem.sig","rb");
	if(ifp==NULL){
		return 3;
	}
	
	unsigned char data_sig_buf[4096];
	size_t data_sig_buf_len = 0;
	data_sig_buf_len = fread(data_sig_buf,1,4096,ifp);
	fclose(ifp);
	ifp = NULL;
	
	int verify_good = RSA_verify(NID_sha256, hash, SHA256_DIGEST_LENGTH, data_sig_buf, data_sig_buf_len, public_rsa);
	
	RSA_free(public_rsa);
	
	if(!verify_good){
		printf("!verify_good\n");
		return 1;
	}
	printf("verify_good\n");
}
