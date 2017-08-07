//
// Created by parallels on 8/2/17.
//

#include "Note.h"
#include "sodium.h"
#include "strutils.h"
#define ToCharArr(val) (reinterpret_cast<uint8_t*> (&val))



uint256 random256(){
    uint256 rand;
    randombytes_buf(rand.begin(),32);
    return rand;
}

Note::Note(){
    value = 0;
    rho = random256();
    r = random256();
}

Note::Note(uint64_t _value) : value(_value){
    rho = random256();
    r = random256();
}

std::array<unsigned char, NOTE_PLAINTEXT_BYTES> Note::noteToCharArray(){

    uint8_t *valArr = ToCharArr(value);

    std::array<unsigned char, NOTE_PLAINTEXT_BYTES> blob;

    unsigned char firstByte = 0x00;
    blob[0] = firstByte;

    memcpy(blob.begin()+1, valArr, sizeof(valArr));
    memcpy(blob.begin()+9, rho.begin(),32);
    memcpy(blob.begin()+41, r.begin(), 32);

    return blob;
};

