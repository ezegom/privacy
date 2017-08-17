#ifndef PRIVATEUTXO_DEBUGPRINT_H
#define PRIVATEUTXO_DEBUGPRINT_H

#include <stdint.h>
#include <iostream>
#include <vector>
#include <memory>
#include "uint256.h"
#include "strutils.h"
#include "Note.h"
#include "ametsuchi/merkle_tree/merkle_tree.h"
#include "ametsuchi/ametsuchi.h"

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

inline void print(const char* name, const ametsuchi::merkle::hash_t& s){
    std::cout<<name<<": ";
    print(s.begin(),s.end());
}

ametsuchi::merkle::hash_t toHash_t(const uint256& _uint256){
    ametsuchi::merkle::hash_t _hash_t;
    memcpy(_hash_t.begin(),_uint256.begin(),ametsuchi::merkle::HASH_LEN);
    return _hash_t;
}

uint256 toUint256(const ametsuchi::merkle::hash_t& _hash_t){
    uint256 _uint256;
    memcpy(_uint256.begin(),_hash_t.begin(),ametsuchi::merkle::HASH_LEN);
    return _uint256;
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

void print_merkle_status(ametsuchi::merkle::MerkleTree& merkle)
{
    print(" * root ",merkle.root());
    print(" * last_block_begin",merkle.last_block_begin());
    print(" * last_block_end",merkle.last_block_end());
    print(" * size_",merkle.get_size());
    print(" * max_blocks_",merkle.get_max_blocks());
    print(" * leafs_",merkle.get_leafs());
    print(" * i_current_",merkle.get_curr_index());
    print(" * i_root_",merkle.get_root_index());
}

#endif // PRIVATEUTXO_DEBUGPRINT_H