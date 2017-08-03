//
// Created by parallels on 7/27/17.
//
#include<iostream>
#include "EncryptionKey.h"
#include "sodium.h"
#include "strutils.h"


/*
 * Uses the D-H Shared secret, public keys used in the D-H key exchange and hSig to derive a symmetric key used for
 * encryption.
 * Usage:
 *  - pkEnc refers to the public key of the user decrypting the message.
 *  - ephPk refers to the public key of the user who encrypted the message.
 */
void EncryptionKey::deriveKey(uint256 sharedSecret, uint256 pkEnc, uint256 ephPk, uint256 hSig){

    unsigned char sym_key[SYMMETRIC_KEY_SIZE];
    unsigned char _blob[96];

    memcpy(_blob+0, pkEnc.begin(),32);
    memcpy(_blob+32, hSig.begin(),32);
    memcpy(_blob+64, ephPk.begin(),32);



    if (crypto_generichash_blake2b_salt_personal(sym_key, sizeof sym_key,
                                             _blob, sizeof _blob,
                                             sharedSecret.begin(), 32,
                                             0, NULL) != 0){
        throw new std::runtime_error("Symmetric encryption key derivation failed");
    }

    memcpy(symmetricKey+0,sym_key+0, SYMMETRIC_KEY_SIZE);

}


/*
 * Computes the Diffie-Hellman key exchange Shared Secret.
 * If the user is encrypting a message _sk refers to the ephemeral secret key, and _pk refers to the receiver's pk
 * If the user is decrypting a message _sk refers to his EncSk (account), and _pk refers to the sender's ephemeral pk.
 */
uint256 EncryptionKey::getDhSharedSecret(const uint256 & _sk, uint256& _pk){
    uint256 dh;
    if (crypto_scalarmult(dh.begin(), _sk.begin(), _pk.begin()) != 0){
        throw std::runtime_error("Error computing DH Shared Secret");
    }
    return dh;
}

/*
 * Generates Ephemeral key pair
 * TODO: Clamp the private key?
 */
void EphemeralKeys::generateKeyPair(){
    esk = random_uint256();
    epk = getEpk(esk);
}

/*
 * Generates ephemeral public key from secret key
 */
uint256 EphemeralKeys::getEpk(uint256 &sk){
    uint256 temp;
    if (crypto_scalarmult_base(temp.begin(), sk.begin()) != 0){
        throw std::logic_error("Could not create public key");
    }
    return temp;
}

/*
 * Creates the ephemeral secret key
 */
uint256 EphemeralKeys::random_uint256(){
    uint256 ret;
    randombytes_buf(ret.begin(), 32);
    return ret;
}