//
// Created by parallels on 7/26/17.
//
#include "Encryptor.h"
#include "EncryptionKey.h"
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

    std::cout<<"Generating D-H Shared Secret, match?: ";
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

void testKDF(){
    EncryptionKey key;
    key.deriveKey(key.eKeys.epk);
}


int main (int argc, char ** argsv){

    //Test DH-SharedSecret
    //testDHSharedSecret();
    testKDF();
}
