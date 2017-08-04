//
// Created by parallels on 7/26/17.
//

#ifndef PRIVATEUTXO_ENCRYPTOR_H
#define PRIVATEUTXO_ENCRYPTOR_H

#include "uint252.h"
#include "uint256.h"
#include "EncryptionKey.h"
#include "note/Note.h"
#include <array>

#define MESSAGE_SIZE 4
#define ENCRYPTION_AUTH_BYTES 16
#define CIPHERTEXT_LENGTH  20



class Encryptor{
    typedef std::array<unsigned char, CIPHERTEXT_BYTES> noteCiphertext;
    typedef std::array<unsigned char, NOTE_PLAINTEXT_BYTES> notePlaintext;
private:
    static notePlaintext decrypt(EncryptionKey & key, const unsigned char* ciphertext);
    static noteCiphertext encrypt(EncryptionKey & key, const unsigned char* plaintext);

public:

    static notePlaintext decryptNoteCiphertext(noteCiphertext _cipherText, uint256 ePk, uint256 hSig);
    static noteCiphertext encryptNote(Note n, uint256 pkEnc, uint256 &ePk, uint256 hSig);

};



#endif //PRIVATEUTXO_ENCRYPTOR_H
