//
// Created by parallels on 8/2/17.
//

#include "Note.h"
#include "sodium.h"
#include "strutils.h"



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













#define ToCharArr(val) (reinterpret_cast<uint8_t*> (&val))
/*
template <class T>
uint8_t * toChar(T data){
    uint64_t val = 0;
    uint8_t *b = reinterpret_cast<uint8_t*> (&val);
    return b;
}
*/

std::array<unsigned char, NOTE_SIZE> Note::noteToCharArray(){

    uint8_t *valArr = ToCharArr(value);

    std::array<unsigned char, NOTE_SIZE> blob;

    unsigned char firstByte = 0x00;
    blob[0] = firstByte;

    memcpy(blob.begin()+1, valArr, sizeof(valArr));
    memcpy(blob.begin()+9, rho.begin(),32);
    memcpy(blob.begin()+41, r.begin(), 32);
    std::cout<<"00";
    std::cout<<HexStr(valArr+0,valArr+8);
    std::cout<<HexStr(rho.begin(),rho.end());
    std::cout<<HexStr(r.begin(),r.end())<<std::endl;
    std::cout<<HexStr(blob.begin(),blob.end())<<std::endl;
    return blob;
};


int main (int argsc, char **arsgv){
    Note _note(10);
    _note.noteToCharArray();



}