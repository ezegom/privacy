//
// Created by parallels on 7/27/17.
//
#include<iostream>
#include "EncryptionKey.h"
#include "sodium.h"
#include "strutils.h"


EncryptionKey::EncryptionKey(uint256 _hSig): hSig(_hSig) {
    eKeys.generateKeyPair();
}
//TODO: REMOVE ONLY FOR TESTING
EncryptionKey::EncryptionKey() {
    eKeys.generateKeyPair();
}

/*
 *  TODO: Master Key unsigned char array size to be computed from the size of pkEnc+hSig+sharedSecret
 *  TODO: Add to the master key the hSig
 */
void EncryptionKey::deriveKey(uint256 pkEnc) {
    uint256 sharedSecret = getDhSharedSecret(eKeys.esk, pkEnc);
    unsigned char master_key[32];
    unsigned char sym_key[SYMMETRIC_KEY_SIZE];

    unsigned char _blob[96];

    //Copy the shared secret into master_key
    memcpy(master_key+0,sharedSecret.begin(),32);

    //Copy the data to be hashed into blob
    memcpy(_blob+0, pkEnc.begin(),32);
    memcpy(_blob+32, hSig.begin(),32);
    memcpy(_blob+64, eKeys.epk.begin(),32);


    //TODO: Check that the encryption was executed correctly. If it doesnt return 0, error.
    //TODO: For now hsig passed in is all zeros.
    crypto_generichash_blake2b_salt_personal(sym_key, sizeof sym_key,
                                             _blob, sizeof _blob,
                                             master_key, sizeof master_key,
                                             0, NULL);

    std::cout<<"The derived symmetric key is :"<<std::endl;
    memcpy(symmetricKey+0,sym_key+0,SYMMETRIC_KEY_SIZE);
    std::cout<<HexStr(symmetricKey+0,symmetricKey+32)<<std::endl;
}


/*
 * Computes the Diffie-Hellman key exchange Shared Secret from the ephemeral secret key and the transmission pk of the
 * ciphertext's receiver.
 * Pk_enc refers to the receiver's transmission key.
 */
uint256 EncryptionKey::getDhSharedSecret(const uint256 & _esk, uint256& pk_enc){
    uint256 dh;
    if (crypto_scalarmult(dh.begin(), _esk.begin(), pk_enc.begin()) != 0){
        throw std::runtime_error("Error computing DH Shared Secret");
    }
    return dh;
}

/*
 * Generates Ephemeral key pair
 */
void EphemeralKeys::generateKeyPair(){
    esk = random_uint256();
    epk = getEpk(esk);
}

uint256 EphemeralKeys::getEpk(uint256 &sk){
    uint256 temp;
    if (crypto_scalarmult_base(temp.begin(), sk.begin()) != 0) {
        throw std::logic_error("Could not create public key");
    }
    return temp;
}

uint256 EphemeralKeys::random_uint256(){
    uint256 ret;
    randombytes_buf(ret.begin(), 32);
    return ret;
}