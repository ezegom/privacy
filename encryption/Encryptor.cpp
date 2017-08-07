//
// Created by parallels on 7/26/17.
//
#include <iostream>
#include <boost/array.hpp>
#include "Encryptor.h"
#include "sodium.h"
#include "strutils.h"



NoteCiphertext Encryptor::encrypt(EncryptionKey &key,
                                  NotePlaintext & plaintext) {

    NoteCiphertext ciphertext;
    unsigned long long ciphertext_len;

    unsigned char cipher_nonce[crypto_aead_chacha20poly1305_IETF_NPUBBYTES] = {};

    if (crypto_aead_chacha20poly1305_ietf_encrypt(ciphertext.begin(), &ciphertext_len,
                                              plaintext.begin(), NOTE_PLAINTEXT_BYTES,
                                              NULL, 0,
                                              NULL, cipher_nonce, key.symmetricKey) != 0){
        throw std::runtime_error("Error in note encryption");
    }
    return ciphertext;
}

NotePlaintext Encryptor::decrypt(EncryptionKey &key,
                                 NoteCiphertext & ciphertext) {
    NotePlaintext pText;
    unsigned long long plaintext_len;
    unsigned char cipher_nonce[crypto_aead_chacha20poly1305_IETF_NPUBBYTES] = {};

    if (crypto_aead_chacha20poly1305_ietf_decrypt(pText.begin(), &plaintext_len,
                                                  NULL,
                                                  ciphertext.begin(), CIPHERTEXT_BYTES,
                                                  NULL, 0, cipher_nonce,
                                                  key.symmetricKey) != 0){
        throw new std::runtime_error("note decryption failed");
    }

    return pText;
}


void Encryptor::encryptNote(NoteCiphertext& ciphertext,
                            uint256 &ePk,
                            Note n,
                            uint256 pkEnc,
                            uint256 hSig) {

    NotePlaintext pText = n.noteToCharArray();
    EphemeralKeys eKeyPair;
    eKeyPair.generateKeyPair();
    memcpy(ePk.begin(), eKeyPair.getEphPk().begin(), 32); //copy generated eph key

    auto sharedSecret = EncryptionKey::getDhSharedSecret(eKeyPair.getEphSk(), pkEnc);

    EncryptionKey enckey;
    enckey.deriveKey(sharedSecret, pkEnc, eKeyPair.getEphPk(), hSig);

    auto temp = encrypt(enckey,pText);
    memcpy(ciphertext.begin(), temp.begin(), CIPHERTEXT_BYTES);

}


void Encryptor::decryptNoteCiphertext(NotePlaintext &plaintext,
                                               uint256 & ephPk, NoteCiphertext _cipherText,
                                               uint256 skEnc,
                                               uint256 pkEnc,
                                               uint256 hSig){

    auto sharedSecret = EncryptionKey::getDhSharedSecret(skEnc, ephPk);

    EncryptionKey encKey;
    encKey.deriveKey(sharedSecret, pkEnc, ephPk, hSig);

    auto temp = decrypt(encKey,_cipherText);
    memcpy(plaintext.begin(),temp.begin() , NOTE_PLAINTEXT_BYTES);

}


