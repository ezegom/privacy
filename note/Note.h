//
// Created by parallels on 8/2/17.
//

#ifndef PRIVATEUTXO_NOTE_H
#define PRIVATEUTXO_NOTE_H
#include "uint256.h"
#include <array>
#include <iostream>
#include <boost/array.hpp>
#define NOTE_SIZE 73

typedef boost::array<unsigned char, 5> ciphertext;
class Note {
public:
    uint256 r;
    uint64_t value;
    uint256 rho;
    uint256 a_pk;
    std::array<unsigned char, NOTE_SIZE> noteToCharArray();
    Note();
    Note(uint64_t _value);
    static Note createNote(uint256 value);
    Note(uint256 r, uint64_t value, uint256 rho, uint256 a_pk): r(r), value(value), rho(rho), a_pk(a_pk) {};
};


#endif //PRIVATEUTXO_NOTE_H
