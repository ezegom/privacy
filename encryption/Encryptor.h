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
#define CIPHERTEXT_LENGTH = MESSAGE_SIZE + ENCRYPTION_AUTH_BYTES



//TODO: Make EphemeralKeys private. Kept in public for testing.
class Encryptor{
private:

public:

};



#endif //PRIVATEUTXO_ENCRYPTOR_H
