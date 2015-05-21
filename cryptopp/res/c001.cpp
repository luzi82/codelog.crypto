// from http://www.cryptopp.com/wiki/User_Guide:_rsa.h

#include <crypto++/rsa.h>
#include <crypto++/osrng.h>
#include <crypto++/base64.h>
#include <crypto++/files.h>
#include <string>
using namespace CryptoPP;
using namespace std;
int main()
{
  string strContents = "A message to be signed";
   //FileSource("tobesigned.dat", true, new StringSink(strContents));
   
   AutoSeededRandomPool rng;
   
   //Read private key
   CryptoPP::ByteQueue bytes;
   FileSource file("privkey.txt", true, new Base64Decoder);
   file.TransferTo(bytes);
   bytes.MessageEnd();
   RSA::PrivateKey privateKey;
   privateKey.Load(bytes);
   
   //Sign message
   RSASSA_PKCS1v15_SHA_Signer privkey(privateKey);
   SecByteBlock sbbSignature(privkey.SignatureLength());
   privkey.SignMessage(
       rng,
       (byte const*) strContents.data(),
       strContents.size(),
       sbbSignature);
   
   //Save result
   FileSink sink("signed.dat");
   sink.Put((byte const*) strContents.data(), strContents.size());
   FileSink sinksig("sig.dat");
   sinksig.Put(sbbSignature, sbbSignature.size());
}
