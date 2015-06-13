// from http://www.cryptopp.com/wiki/User_Guide:_rsa.h

#include <crypto++/base64.h>
#include <crypto++/files.h>
#include <crypto++/modes.h>
#include <crypto++/osrng.h>
#include <crypto++/rsa.h>
#include <string>
using namespace CryptoPP;
using namespace std;
int main()
{
    byte key[] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef};
    byte iv[]  = {0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};

	CBC_Mode<AES>::Encryption enc(key, 16, iv);
	
	FileSource(
   		"data.jpg",
   		true,
   		new StreamTransformationFilter(
   			enc,
   			new FileSink(
   				"data.jpg.aes"
   			)
   		)
	);

	CBC_Mode<AES>::Decryption dec(key, 16, iv);

	FileSource(
   		"data.jpg.aes",
   		true,
   		new StreamTransformationFilter(
   			dec,
   			new FileSink(
   				"data.jpg.aes.-"
   			)
   		)
	);
}
