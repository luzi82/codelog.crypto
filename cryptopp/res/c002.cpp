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
   //Read public key
   CryptoPP::ByteQueue bytes;
   FileSource file("pubkey.txt", true, new Base64Decoder);
   file.TransferTo(bytes);
   bytes.MessageEnd();
   RSA::PublicKey pubKey;
   pubKey.Load(bytes);
   
   RSASSA_PKCS1v15_SHA_Verifier verifier(pubKey);

   //Read signed message
   string signedTxt;
   FileSource("signed.dat", true, new StringSink(signedTxt));
   string sig;
   FileSource("sig.dat", true, new StringSink(sig));

   string combined(signedTxt);
   combined.append(sig);

   //Verify signature
   try
   {
       StringSource(combined, true,
           new SignatureVerificationFilter(
               verifier, NULL,
               SignatureVerificationFilter::THROW_EXCEPTION
          )
       );
       cout << "Signature OK" << endl;
   }
   catch(SignatureVerificationFilter::SignatureVerificationFailed &err)
   {
       cout << err.what() << endl;
   }
}
