//
// Created by parallels on 7/26/17.
//
#include "Encryptor.h"
#include "EncryptionKey.h"
#include "accounts/SecretKeys.h"
#include "accounts/PublicKeys.h"
#include "strutils.h"

void testDHSharedSecret(){
    EphemeralKeys keys1;
    keys1.generateKeyPair();
    std::cout<<"Key pair 1: "<<std::endl;
    std::cout<<HexStr(keys1.esk.begin(),keys1.esk.end())<<std::endl;
    std::cout<<HexStr(keys1.epk.begin(),keys1.epk.end())<<std::endl;

    EphemeralKeys keys2;
    keys2.generateKeyPair();
    std::cout<<"Key pair 2: "<<std::endl;
    std::cout<<HexStr(keys2.esk.begin(),keys2.esk.end())<<std::endl;
    std::cout<<HexStr(keys2.epk.begin(),keys2.epk.end())<<std::endl;

    std::cout<<"Generating D-H Shared Secret: ";
    uint256 sharedSecret1;
    sharedSecret1 = EncryptionKey::getDhSharedSecret(keys1.esk, keys2.epk);
    uint256 sharedSecret2;
    sharedSecret2 = EncryptionKey::getDhSharedSecret(keys2.esk, keys1.epk);

    if (sharedSecret1 == sharedSecret2){
        std::cout<<"[SUCCESS]"<<std::endl;
    }else{
        std::cout<<"[FAIL]"<<std::endl;
    }
}
/*
 * KDF Test:
 * Alice sends encrypted message to Bob
 */
#define MESSAGE (const unsigned char *) "test"
#define MESSAGE_LEN 4


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
    uint256 aliceSharedSecret = EncryptionKey::getDhSharedSecret(AliceEphemeralKeys.esk, BobPublicKeys.encPk);

    //Bob's shared secret
    uint256 BobSharedSecret = EncryptionKey::getDhSharedSecret(BobSecretKeys.encSk, AliceEphemeralKeys.epk);

    //Get symmetric key with Alice's info
    EncryptionKey AliceSymKey;
    AliceSymKey.deriveKey(aliceSharedSecret,BobPublicKeys.encPk,AliceEphemeralKeys.epk,uint256());

    //Note Bob has Alice's public ephemeral key as it is published with the encrypted messages.
    EncryptionKey BobSymKey;
    BobSymKey.deriveKey(BobSharedSecret, BobPublicKeys.encPk, AliceEphemeralKeys.epk, uint256());

   if (memcmp(BobSymKey.symmetricKey, AliceSymKey.symmetricKey, 32) == 0 ){
        std::cout<<"success in sym key derivation"<<std::endl;
   }

    auto ciphertext = Encryptor::encrypt(AliceSymKey, MESSAGE);
    //std::cout<<HexStr(ciphertext.begin(),ciphertext.end())<<std::endl;

    auto plaintext = Encryptor::decrypt(BobSymKey,(const unsigned char *)(ciphertext.begin()));

    if (memcmp((void*)MESSAGE, plaintext.begin(),MESSAGE_LEN) == 0){
        std::cout<<"success in sym key encryption and decryption"<<std::endl;
    }
}


int main (int argc, char ** argsv){

    //Test DH-SharedSecret
    testEncryption();
}
