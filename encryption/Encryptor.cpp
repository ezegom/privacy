//
// Created by parallels on 7/26/17.
//
#include <iostream>
#include "Encryptor.h"
#include "sodium.h"


std::array<unsigned char, CIPHERTEXT_LENGTH> Encryptor::encrypt(EncryptionKey &key, const unsigned char *plaintext) {

    std::array<unsigned char, CIPHERTEXT_LENGTH> ciphertext;
    unsigned long long ciphertext_len;

    unsigned char cipher_nonce[crypto_aead_chacha20poly1305_IETF_NPUBBYTES] = {};

    if (crypto_aead_chacha20poly1305_ietf_encrypt(ciphertext.begin(), &ciphertext_len,
                                              plaintext, 4,
                                              NULL, 0,
                                              NULL, cipher_nonce, key.symmetricKey) != 0){
        throw std::runtime_error("Error in note encryption");
    }
    return ciphertext;
}

std::array<unsigned char, MESSAGE_SIZE> Encryptor::decrypt(EncryptionKey &key, const unsigned char *ciphertext) {
    std::array<unsigned char, MESSAGE_SIZE> plaintext;
    unsigned long long plaintext_len;
    unsigned char cipher_nonce[crypto_aead_chacha20poly1305_IETF_NPUBBYTES] = {};

    if (crypto_aead_chacha20poly1305_ietf_decrypt(plaintext.begin(), &plaintext_len,
                                                  NULL,
                                                  ciphertext, CIPHERTEXT_LENGTH,
                                                  NULL, 0, cipher_nonce,
                                                  key.symmetricKey) != 0){
        throw new std::runtime_error("note decryption failed");
    }
    return plaintext;

}