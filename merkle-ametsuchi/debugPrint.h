#ifndef PRIVATEUTXO_DEBUGPRINT_H
#define PRIVATEUTXO_DEBUGPRINT_H

#include <stdint.h>
#include <iostream>
#include <vector>
#include <memory>
#include "uint256.h"
#include "strutils.h"
#include "Note.h"

inline void print(const char* s){
    std::cout << s << std::endl;
}

inline void print(const char* s, const unsigned int& i){
    std::cout << s << ": " << i <<std::endl;
}

inline void print(const unsigned char* begin, const unsigned char* end){
    std::cout<< HexStr(begin,end) <<std::endl;
}

inline void print(const uint256& s){
    print(s.begin(), s.end());
}

inline void print(const uint252& s){
    print(s.begin(), s.end());
}

inline void print(const char* name, const uint256& s){
    std::cout<<name<<": ";
    print(s);
}

inline void print(const char* name, const uint252& s){
    std::cout<<name<<": ";
    print(s);
}

std::vector<uint8_t>* toVectoerUint8(const uint256& _uint256){
    std::vector<uint8_t>* vec = new std::vector<uint8_t>(32);
    auto end = _uint256.end();
    int i_vec = 0;
    for (auto i=_uint256.begin();i!=end;++i){
        vec->operator[](i_vec)=*i;
    }
    return vec;
}

#endif // PRIVATEUTXO_DEBUGPRINT_H