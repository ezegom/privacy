//
// Created by parallels on 7/26/17.
//
#include <iostream>
#include "Encryptor.h"
#include "sodium.h"


std::array<unsigned char, CIPHERTEXT_LENGTH> Encryptor::encrypt(EncryptionKey &key, unsigned char *plaintext) {
    std::array<unsigned char, CIPHERTEXT_LENGTH> ciphertext;

    unsigned long long ciphertext_len;
    crypto_aead_chacha20poly1305_ietf_encrypt(ciphertext.begin(), &ciphertext_len,
                                              plaintext, MESSAGE_SIZE,
                                              NULL, 0,
                                              NULL, 0,
                                              key.symmetricKey);
    if (ciphertext_len != CIPHERTEXT_LENGTH)
        std::cout<<"error encrypting message"<<std::endl;

    return ciphertext;
}

std::array<unsigned char, MESSAGE_SIZE> Encryptor::decrypt(EncryptionKey &key, unsigned char *ciphertext) {
    std::array<unsigned char, MESSAGE_SIZE> plaintext;
    unsigned long long plaintext_len;
    if (crypto_aead_chacha20poly1305_ietf_decrypt(plaintext.begin(), &plaintext_len,
                                                  NULL,
                                                  ciphertext, CIPHERTEXT_LENGTH,
                                                  NULL, 0, 0,
                                                  key.symmetricKey) != 0){
        throw new std::runtime_error("note decryption failed");
    }
    return plaintext;

}