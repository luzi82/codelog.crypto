// test the exact time of filter/sink delete

#include <crypto++/base64.h>
#include <crypto++/files.h>
#include <crypto++/modes.h>
#include <crypto++/osrng.h>
#include <crypto++/rsa.h>
#include <string>
using namespace CryptoPP;
using namespace std;

bool filterDeleted=false;
class XFilter :
public StreamTransformationFilter
{
public:
	XFilter(
		StreamTransformation & 	c,
		BufferedTransformation * 	attachment = NULL,
		BlockPaddingScheme 	padding = DEFAULT_PADDING,
		bool 	allowAuthenticatedSymmetricCipher = false	 
	):
	StreamTransformationFilter(c,attachment,padding,allowAuthenticatedSymmetricCipher)
	{}	
	virtual ~XFilter(){
		filterDeleted=true;
	}
};

bool sinkDeleted=false;
class XSink :
public FileSink
{
public:
	XSink (const char *filename, bool binary=true):
	FileSink(filename,binary)
	{}
	virtual ~XSink(){
		sinkDeleted=true;
	}
};

int main()
{
    byte key[] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef};
    byte iv[]  = {0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};

	CBC_Mode<AES>::Decryption dec(key, 16, iv);

	FileSource*fs=new FileSource(
   		"data.jpg.openssl-aes",
   		true,
   		new XFilter(
   			dec,
   			new XSink(
   				"tmp"
   			)
   		)
	);
	if(filterDeleted){
		printf("LZtClTeG filterDeleted\n");
		return 1;
	}
	if(sinkDeleted){
		printf("POWWStsJ sinkDeleted\n");
		return 1;
	}
	delete fs;
	fs=NULL;

	if(!filterDeleted){
		printf("TeTDchww !filterDeleted\n");
		return 1;
	}
	if(!sinkDeleted){
		printf("mpulBOrb !sinkDeleted\n");
		return 1;
	}
	return 0;
}
