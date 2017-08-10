//
// Created by parallels on 8/2/17.
//

#ifndef PRIVATEUTXO_NOTE_H
#define PRIVATEUTXO_NOTE_H
#include "uint256.h"
#include "uint252.h"
#include "constants.h"
#include <array>
#include <iostream>
#include <boost/array.hpp>
typedef std::array<unsigned char, NOTE_PLAINTEXT_BYTES> NotePlaintext;
class Note {

private:
    uint256 r, rho, a_pk;
    uint64_t value;

public:

    Note();

    Note(uint64_t _value, uint256 a_pk);

    Note(uint256 _r,
         uint64_t _value,
         uint256 _rho,
         uint256 _a_pk) : r(_r), value(_value), rho(_rho), a_pk(_a_pk) {};

    Note(uint64_t _value,
         uint256 _rho,
         uint256 _r): value(_value), rho(_rho), r(_r) {};

    static Note plaintextToNote(std::array<unsigned char, NOTE_PLAINTEXT_BYTES> blob);

    std::array<unsigned char, NOTE_PLAINTEXT_BYTES> noteToCharArray();

    uint256 cm();

    uint256 nullifier(uint252 aSk);

};


#endif //PRIVATEUTXO_NOTE_H
