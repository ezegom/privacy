//
// Created by parallels on 7/26/17.
//

#ifndef PRIVATEUTXO_ENCRYPTOR_H
#define PRIVATEUTXO_ENCRYPTOR_H

#include "uint252.h"
#include "uint256.h"
#include "EncryptionKey.h"
#include "note/Note.h"
#include "constants.h"
#include <array>

#define MESSAGE_SIZE 4
#define ENCRYPTION_AUTH_BYTES 16
#define CIPHERTEXT_LENGTH  20

typedef std::array<unsigned char, CIPHERTEXT_BYTES> NoteCiphertext;
typedef std::array<unsigned char, NOTE_PLAINTEXT_BYTES> NotePlaintext;

class Encryptor{

public:
    static void encryptNote(NoteCiphertext &ciphertext,
                            uint256 &ePk,
                            Note n,
                            uint256 pkEnc,
                            uint256 hSig);

    static void decryptNoteCiphertext(NotePlaintext &pText,
                                      uint256 & ePk,
                                      NoteCiphertext _cipherText,
                                      uint256 skEnc,
                                      uint256 pkEnc,
                                      uint256 hSig);

private:
    static NoteCiphertext encrypt(EncryptionKey& key, NotePlaintext& plaintext);
    static NotePlaintext decrypt(EncryptionKey& key, NoteCiphertext& ciphertext);

};



#endif //PRIVATEUTXO_ENCRYPTOR_H
