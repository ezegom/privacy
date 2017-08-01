//
// Created by parallels on 7/27/17.
//

#ifndef PRIVATEUTXO_ENCRYPTIONKEY_H
#define PRIVATEUTXO_ENCRYPTIONKEY_H

#include "uint256.h"

#define SYMMETRIC_KEY_SIZE 32

class EphemeralKeys{
private:
    uint256 getEpk(uint256 &sk);
    uint256 random_uint256();
public:
    uint256 esk;
    uint256 epk;
    void generateKeyPair();
};

class EncryptionKey {
private:
public:
    unsigned char symmetricKey[SYMMETRIC_KEY_SIZE];
    void deriveKey(uint256 sharedSecret, uint256 pkEnc, uint256 ephPk, uint256 hSig);
    static uint256 getDhSharedSecret(const uint256& sk, uint256& _pk); //make private, public for testing only.
};


#endif //PRIVATEUTXO_ENCRYPTIONKEY_H
