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

class Note {
private:
    uint256 r;
    uint64_t value;
    uint256 rho;
    uint256 a_pk;
public:
    std::array<unsigned char, NOTE_PLAINTEXT_BYTES> noteToCharArray();
    Note();
    Note(uint64_t _value);
    static Note createNote(uint64_t value);
    Note(uint256 r, uint64_t value, uint256 rho, uint256 a_pk): r(r), value(value), rho(rho), a_pk(a_pk) {};
};


#endif //PRIVATEUTXO_NOTE_H
