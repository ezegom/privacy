//
// Created by parallels on 8/2/17.
//

#ifndef PRIVATEUTXO_NOTE_H
#define PRIVATEUTXO_NOTE_H
#include "uint256.h"
#include <iostream>
//typedef std::array<unsigned char, 5> ciphertext;
#define NOTE_SIZE 96
class Note {
public:
    uint256 r;
    uint256 value;
    uint256 rho;
    uint256 a_pk;
    std::array<unsigned char, NOTE_SIZE> noteToCharArray();
    Note(uint256 vallue);
    static Note createNote(uint256 value);
    Note(uint256 r, uint256 value, uint256 rho, uint256 a_pk): r(r), value(value), rho(rho), a_pk(a_pk) {};
};


#endif //PRIVATEUTXO_NOTE_H
