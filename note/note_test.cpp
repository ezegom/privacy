#include "Note.h"
#include "uint256.h"
#include "PublicKeys.h"
#include "SecretKeys.h"
#include "sodium.h"
#include "strutils.h"
#include <iostream>
#include <string>

inline void print(const char* s){
    std::cout << s << std::endl;
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
    auto end=s.end();
    std::cout<<name<<": ";
    print(s);
}

inline void print(const char* name, const uint252& s){
    auto end=s.end();
    std::cout<<name<<": ";
    print(s);
}

void test(){
    if (sodium_init() == -1 ){
        throw std::runtime_error("Sodium init failed");
    }
    
    std::string name = "note_test";
    // creating key pairs
    SecretKeys sks(name);
    sks.generateKeys();
    PublicKeys pks(name);
    pks.generateKeys(sks);    
    
    auto addrSk = sks.getAddrSk();
    auto addrPk = pks.getAddrPk();   

    Note note(1000u,addrPk);
    
    auto cm = note.cm();
    print("[CM]", cm);
    auto nullifier = note.nullifier(addrSk);
    print("[Nullifier]", nullifier);
    // TODO ametsuchi 
}

int main (int argc, char** argv){
    test();
    return 0;
}