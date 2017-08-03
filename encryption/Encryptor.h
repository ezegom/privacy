//
// Created by parallels on 7/26/17.
//

#ifndef PRIVATEUTXO_ENCRYPTOR_H
#define PRIVATEUTXO_ENCRYPTOR_H

#include "uint252.h"
#include "uint256.h"
#include "EncryptionKey.h"
#include "note/Note.h"
#define MESSAGE_SIZE 4
#define ENCRYPTION_AUTH_BYTES 16
#define CIPHERTEXT_LENGTH  20



class Encryptor{
public:
    static std::array<unsigned char, MESSAGE_SIZE> decrypt(EncryptionKey & key, const unsigned char* ciphertext);
    static std::array<unsigned char, CIPHERTEXT_LENGTH> encrypt(EncryptionKey & key, const unsigned char* plaintext);
    static std::array<unsigned char, CIPHERTEXT_LENGTH> encryptNote(Note n, uint256 pkEnc, uint256 &ePk, uint256 hSig);
};



#endif //PRIVATEUTXO_ENCRYPTOR_H
