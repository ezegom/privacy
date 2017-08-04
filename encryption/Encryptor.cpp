//
// Created by parallels on 7/26/17.
//
#include <iostream>
#include <boost/array.hpp>
#include "Encryptor.h"
#include "sodium.h"


Encryptor::noteCiphertext Encryptor::encrypt(EncryptionKey &key, const unsigned char *plaintext) {

    noteCiphertext ciphertext;
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

Encryptor::notePlaintext Encryptor::decrypt(EncryptionKey &key, const unsigned char *ciphertext) {
    notePlaintext pText;
    unsigned long long plaintext_len;
    unsigned char cipher_nonce[crypto_aead_chacha20poly1305_IETF_NPUBBYTES] = {};

    if (crypto_aead_chacha20poly1305_ietf_decrypt(pText.begin(), &plaintext_len,
                                                  NULL,
                                                  ciphertext, CIPHERTEXT_LENGTH,
                                                  NULL, 0, cipher_nonce,
                                                  key.symmetricKey) != 0){
        throw new std::runtime_error("note decryption failed");
    }
    return pText;

}

Encryptor::notePlaintext Encryptor::decryptNoteCiphertext(noteCiphertext _cipherText, uint256 ePk, uint256 hSig){
    notePlaintext pText;

    return pText;

}

Encryptor::noteCiphertext Encryptor::encryptNote(Note n, uint256 pkEnc, uint256 &ePk, uint256 hSig) {
    EphemeralKeys eKeyPair;
    eKeyPair.generateKeyPair();
    ePk = eKeyPair.getEphPk();


}
