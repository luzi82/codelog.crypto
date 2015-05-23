// from http://www.cryptopp.com/wiki/User_Guide:_rsa.h

#include <crypto++/rsa.h>
#include <crypto++/osrng.h>
#include <crypto++/base64.h>
#include <crypto++/files.h>
using namespace CryptoPP;
int main()
{
 
 // InvertibleRSAFunction is used directly only because the private key
 // won't actually be used to perform any cryptographic operation;
 // otherwise, an appropriate typedef'ed type from rsa.h would have been used.
 AutoSeededRandomPool rng;
 InvertibleRSAFunction privkey;
 privkey.Initialize(rng, 1024);
 
 // With the current version of Crypto++, MessageEnd() needs to be called
 // explicitly because Base64Encoder doesn't flush its buffer on destruction.
 Base64Encoder privkeysink(new FileSink("privkey.txt"),false);
 privkey.DEREncode(privkeysink);
 privkeysink.MessageEnd();
 
 // Suppose we want to store the public key separately,
 // possibly because we will be sending the public key to a third party.
 RSAFunction pubkey(privkey);
 
 Base64Encoder pubkeysink(new FileSink("pubkey.txt"),false);
 pubkey.DEREncode(pubkeysink);
 pubkeysink.MessageEnd();
}
