//
// Created by parallels on 7/26/17.
//

#ifndef PRIVATEUTXO_ENCRYPTOR_H
#define PRIVATEUTXO_ENCRYPTOR_H

#include "uint252.h"
#include "uint256.h"
#include "EncryptionKey.h"
#define MESSAGE_SIZE 512
#define ENCRYPTION_AUTH_BYTES 16
#define CIPHERTEXT_LENGTH  528



//TODO: Make EphemeralKeys private. Kept in public for testing.
class Encryptor{
private:

public:
    std::array<unsigned char, MESSAGE_SIZE> decrypt(EncryptionKey & key, unsigned char* ciphertext);
    std::array<unsigned char, CIPHERTEXT_LENGTH> encrypt(EncryptionKey & key, unsigned char* plaintext);

};



#endif //PRIVATEUTXO_ENCRYPTOR_H
