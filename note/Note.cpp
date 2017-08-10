//
// Created by parallels on 8/2/17.
//

#include "Note.h"
#include "sodium.h"
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
}


Note::Note(uint64_t _value, uint256 _pkEnc): value(_value), pkEnc(_pkEnc){
    rho = random256();
    r = random256();
}

//TODO: Check if correctly casting from valArr to uint64_t
// - Does reinterpret_cast know (because resulting type is uint64_t) that the uint64_t is stored at valArr[0] to valArray[7]

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

