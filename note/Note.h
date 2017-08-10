//
// Created by parallels on 8/2/17.
//

#ifndef PRIVATEUTXO_NOTE_H
#define PRIVATEUTXO_NOTE_H
#include "uint256.h"
#include "constants.h"
#include <array>
#include <iostream>
#include <boost/array.hpp>
typedef std::array<unsigned char, NOTE_PLAINTEXT_BYTES> NotePlaintext;
class Note {

private:
    uint256 r, rho, pkEnc;
    uint64_t value;

public:

    Note();

    Note(uint64_t _value,
         uint256 pkEnc);

    Note(uint256 r,
         uint64_t value,
         uint256 rho,
         uint256 a_pk) : r(r), value(value), rho(rho), pkEnc(a_pk) {};

    Note(uint64_t _value,
         uint256 _rho,
         uint256 _r): value(_value), rho(_rho), r(_r) {};

    static Note plaintextToNote(std::array<unsigned char, NOTE_PLAINTEXT_BYTES> blob);

    std::array<unsigned char, NOTE_PLAINTEXT_BYTES> noteToCharArray();


};


#endif //PRIVATEUTXO_NOTE_H
