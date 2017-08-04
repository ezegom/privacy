//
// Created by parallels on 7/26/17.
//
#include "Encryptor.h"
#include "EncryptionKey.h"
#include "accounts/SecretKeys.h"
#include "accounts/PublicKeys.h"
#include "strutils.h"


/*
 * KDF Test:
 * Alice sends encrypted message to Bob
 */

void testEncryption(){
    //Alice generate ephemeral key pair
    EphemeralKeys AliceEphemeralKeys;
    AliceEphemeralKeys.generateKeyPair();

    //Bob's keys
    std::string name = "Bob";
    SecretKeys BobSecretKeys(name);
    BobSecretKeys.generateKeys();
    PublicKeys BobPublicKeys(name);
    BobPublicKeys.generateKeys(BobSecretKeys);

    //Alice's shared secret
    uint256 aliceSharedSecret = EncryptionKey::getDhSharedSecret(AliceEphemeralKeys.getEphSk(), BobPublicKeys.encPk);

    //Bob's shared secret
    uint256 ephPkAlice = AliceEphemeralKeys.getEphPk();
    uint256 BobSharedSecret = EncryptionKey::getDhSharedSecret(BobSecretKeys.encSk, ephPkAlice );

    //Get symmetric key with Alice's info
    EncryptionKey AliceSymKey;
    AliceSymKey.deriveKey(aliceSharedSecret,BobPublicKeys.encPk,AliceEphemeralKeys.getEphPk(),uint256());

    //Note Bob has Alice's public ephemeral key as it is published with the encrypted messages.
    EncryptionKey BobSymKey;
    BobSymKey.deriveKey(BobSharedSecret, BobPublicKeys.encPk, AliceEphemeralKeys.getEphPk(), uint256());

   if (memcmp(BobSymKey.symmetricKey, AliceSymKey.symmetricKey, 32) == 0 ){
        std::cout<<"success in sym key derivation"<<std::endl;
   }
/*
    auto ciphertext = Encryptor::encrypt(AliceSymKey, MESSAGE);
    //std::cout<<HexStr(ciphertext.begin(),ciphertext.end())<<std::endl;

    auto plaintext = Encryptor::decrypt(BobSymKey,(const unsigned char *)(ciphertext.begin()));

    if (memcmp((void*)MESSAGE, plaintext.begin(),MESSAGE_LEN) == 0){
        std::cout<<"success in sym key encryption and decryption"<<std::endl;
    }
*/
}


int main (int argc, char ** argsv){

    //Test DH-SharedSecret
    testEncryption();
}
