// test free and free_all

#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <stdio.h>
#include <sys/stat.h>

int t_write(BIO *b, const char *in, int inl){
	//printf("t_write\n");
	return BIO_write(b->next_bio, in, inl);
}

int t_read(BIO *b, char *out, int outl){
	//printf("t_read %d\n",outl);
	return BIO_read(b->next_bio, out, outl);
}

int t_puts(BIO *bp, const char *str){
	//printf("t_read\n");
	return BIO_puts(bp->next_bio,str);
}

int t_gets(BIO *bp, char *buf, int size){
	//printf("t_gets\n");
	return BIO_gets(bp->next_bio,buf,size);
}

long t_ctrl(BIO *b, int cmd, long num, void *ptr){
	//printf("t_ctrl %d\n",cmd);
	return BIO_ctrl(b->next_bio, cmd, num, ptr);
}

long t_callback_ctrl(BIO *b, int cmd, bio_info_cb *fp)
{
	//printf("t_callback_ctrl %d\n",cmd);

    if (b->next_bio == NULL)
        return (0);

    return BIO_callback_ctrl(b->next_bio, cmd, fp);
}

int t_new(BIO *bi){
	//printf("t_new\n");
	bi->init=1;
	bi->ptr=NULL;
	bi->flags=0;
	return 1;
}

int free_called = 0;

int t_free(BIO *a){
	printf("t_free\n");
	++free_called;
	return 1;
}

BIO_METHOD methods_t = {
    (50|BIO_TYPE_FILTER),
    "c008",
    t_write,
    t_read,
    t_puts,
    t_gets,
    t_ctrl,
    t_new,
    t_free,
    t_callback_ctrl,
};

int main()
{
	const char* inFilename="data.jpg.enc";
    unsigned char key[] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef};
    unsigned char iv[]  = {0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};

	BIO* fileBio=BIO_new_file(inFilename,"rb");
	
	BIO* tBio=BIO_new(&methods_t);
	
	BIO* cipherBio = BIO_new(BIO_f_cipher ());
	BIO_set_cipher (cipherBio, EVP_aes_128_cbc (), key, iv, 0);
	
	BIO_push(cipherBio,tBio);
	BIO_push(tBio,fileBio);

    BIO_free(cipherBio);

	if(free_called!=0){
		printf("free_called!=0\n");
		return 1;
	}
	
	BIO_free(tBio);

	if(free_called!=1){
		printf("free_called!=1\n");
		return 1;
	}

	BIO_free(fileBio);

	if(free_called!=1){
		printf("free_called!=1\n");
		return 1;
	}

	fileBio=BIO_new_file(inFilename,"rb");
	tBio=BIO_new(&methods_t);
	cipherBio = BIO_new(BIO_f_cipher ());
	BIO_set_cipher (cipherBio, EVP_aes_128_cbc (), key, iv, 0);
	
	BIO_push(cipherBio,tBio);
	BIO_push(tBio,fileBio);
	
	free_called = 0;
	
	BIO_free_all(cipherBio);
	
	if(free_called!=1){
		printf("free_called!=1\n");
		return 1;
	}

    return 0;
}
