//
// Created by parallels on 8/2/17.
//

#include "Note.h"
#include "sodium.h"


uint256 random256(){
    uint256 rand;
    randombytes_buf(rand.begin(),32);
    return rand;
}

Note::Note(uint256 _value) : value(_value){
    rho = random256();
    r = random256();

}


int main (int argsc, char **arsgv){
    std::cout<<"hello"<<std::endl;
}