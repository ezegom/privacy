//
// Created by parallels on 7/26/17.
//
#include "Encryptor.h"
#include "EncryptionKey.h"
#include "accounts/SecretKeys.h"
#include "accounts/PublicKeys.h"
#include "strutils.h"

#include "note/Note.h"
#include "strutils.h"


/*
 * KDF Test:
 * Alice sends encrypted message to Bob
 */
int testKeyDerivation(){
    //Alice generate ephemeral key pair
    EphemeralKeys AliceEphemeralKeys;
    AliceEphemeralKeys.generateKeyPair();

    //Bob's keys
    std::string name = "Bob";
    SecretKeys BobSecretKeys(name);
    BobSecretKeys.generateKeys();
    PublicKeys BobPublicKeys(name);
    BobPublicKeys.generateKeys(BobSecretKeys);

    //Alice's shared secret
    auto bobPkEnc = BobPublicKeys.getPkEnc();
    uint256 aliceSharedSecret = EncryptionKey::getDhSharedSecret(AliceEphemeralKeys.getEphSk(), bobPkEnc);

    //Bob's shared secret
    uint256 ephPkAlice = AliceEphemeralKeys.getEphPk();
    uint256 BobSharedSecret = EncryptionKey::getDhSharedSecret(BobSecretKeys.getEncSk(), ephPkAlice );

    //Get symmetric key with Alice's info
    EncryptionKey AliceSymKey;
    AliceSymKey.deriveKey(aliceSharedSecret,BobPublicKeys.getPkEnc(),AliceEphemeralKeys.getEphPk(),uint256());

    //Note Bob has Alice's public ephemeral key as it is published with the encrypted messages.
    EncryptionKey BobSymKey;
    BobSymKey.deriveKey(BobSharedSecret, BobPublicKeys.getPkEnc(), AliceEphemeralKeys.getEphPk(), uint256());

   if (memcmp(BobSymKey.symmetricKey, AliceSymKey.symmetricKey, 32) == 0 ){
        std::cout<<"success in sym key derivation "<<std::endl;
       return 1;
   }
    return 0;

}

int testEncryption(){
    //Create note, with value = 100.

    SecretKeys BobSecretKeys("Bob");
    BobSecretKeys.generateKeys();
    PublicKeys BobPublicKeys("Bob");
    BobPublicKeys.generateKeys(BobSecretKeys);

    Note _note((uint64_t)100, BobPublicKeys.getPkEnc());


    auto noteCharArray = _note.noteToCharArray();
    auto BobPkEnc = BobPublicKeys.getPkEnc();

    uint256 ephPk; //Ephemeral public key used to encrypt


    NoteCiphertext cipherText;
    Encryptor::encryptNote(cipherText, ephPk,
                           _note,
                           BobPkEnc,
                           uint256());



    NotePlaintext plainText;

    Encryptor::decryptNoteCiphertext(plainText,
                                     ephPk, cipherText,
                                     BobSecretKeys.getEncSk(),
                                     BobPkEnc,
                                     uint256());

    if (!memcmp(plainText.begin(), noteCharArray.begin(), NOTE_PLAINTEXT_BYTES)){
        std::cout<<"success in not encryption and decryption "<<std::endl;
        return 1;
    }

    Note newNote = Note::plaintextToNote(plainText);

    Note emptyNote;
    newNote.nullifier(BobSecretKeys.getAddrSk());

    return 0;
}


int main (int argc, char ** argsv){
    //Test DH-SharedSecret
  if ( testKeyDerivation() && testEncryption() ) {
    std::cout<<"Sucess!"<<std::endl;;
  } else {
    std::cout<<"Fail"<<std::endl;;
  }

}
