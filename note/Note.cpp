//
// Created by parallels on 8/2/17.
//

#include "Note.h"
#include "sodium.h"
#include "sha256.h"
#include "strutils.h"

#define ToCharArr(val) (reinterpret_cast<uint8_t*> (&val))
#define charArrToUint64(val) (reinterpret_cast<uint64_t> (&val))


uint256 random256(){
    uint256 rand;
    randombytes_buf(rand.begin(),32);
    return rand;
}

Note::Note(){
    value = 0;
    rho = uint256();
    r = uint256();
    a_pk = uint256();
}
/*
 * Main constructor for Note class
 * Use this when creating a new note.
 * A_pk is the public key address of the note's receiver.
 */
Note::Note(uint64_t _value, uint256 _a_pk): value(_value), a_pk(_a_pk){
    rho = random256();
    r = random256();
}

//TODO: Check if correctly casting from valArr to uint64_t
// - Does reinterpret_cast know (because resulting type is uint64_t) that the uint64_t is stored at valArr[0] to valArray[7]
/*
 * Constructor used when ciphertext containing note is decrypted.
 */
Note Note::plaintextToNote(NotePlaintext blob) {
    std::array<unsigned char, 8> valArr;
    uint256 _rho, _r;

    if (blob[0])
        throw std::runtime_error("Invalid leading byte for note plaintext");

    memcpy(valArr.begin(), blob.begin()+1, 8);
    memcpy(_rho.begin(),blob.begin()+9,32);
    memcpy(_r.begin(),blob.begin()+41,32);

    uint64_t val = charArrToUint64(valArr);

    return Note(val,_rho,_r);
}

/*
 * Used to convert note to plaintext before encrypting the note.
 */
std::array<unsigned char, NOTE_PLAINTEXT_BYTES> Note::noteToCharArray(){

    uint8_t *valArr = ToCharArr(value);

    std::array<unsigned char, NOTE_PLAINTEXT_BYTES> blob;

    unsigned char firstByte = 0x00;
    blob[0] = firstByte;

    memcpy(blob.begin()+1, valArr, 8);
    memcpy(blob.begin()+9, rho.begin(),32);
    memcpy(blob.begin()+41, r.begin(), 32);

    return blob;
};

uint256 Note::cm(){
    if(a_pk.IsNull()){
        throw new std::logic_error("computing the note commitment requires the a_pk of receiver");
    }
    uint256 noteCommitment;
    unsigned char leadingByte = 0xB0;
    unsigned char blob[105];

    blob[0] = leadingByte;
    memcpy(&blob[1], a_pk.begin(),32);
    memcpy(&blob[33], ToCharArr(value), 8);
    memcpy(&blob[41], rho.begin(),32);
    memcpy(&blob[73], r.begin(), 32);
    CSHA256 sha256Hasher;

    // sha256Hasher.byte is 105
    sha256Hasher.Write(blob, 105);
    // FinalizeNoPadding throw exception (byte!=64 --> true)
    // changed to Finalize
    sha256Hasher.Finalize(noteCommitment.begin());

    return noteCommitment;
}

uint256 Note::nullifier(uint252 aSk) {
    unsigned char blob[64];
    uint256 nullifier;
    memcpy(&blob[0], aSk.begin(),32);
    memcpy(&blob[32],rho.begin(),32);
    blob[0] &= 0x0F;
    blob[0] |= (1 << 7) | (1 << 6) | (1 << 5);
    CSHA256 sha256Hasher;
    sha256Hasher.Write(blob,64);
    sha256Hasher.FinalizeNoPadding(nullifier.begin());
    return nullifier;
}
