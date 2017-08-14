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
    print("sodium was initialized!");
    std::string name = "note_test";
    SecretKeys sks(name);
    sks.generateKeys();
    print("secret key was generated");
    PublicKeys pks(name);
    pks.generateKeys(sks);    
    print("public key was generated");
    
    auto addrSk = sks.getAddrSk();
    auto addrPk = pks.getAddrPk();   
    print("address secretKey",addrSk);
    print("address publicKey",addrPk);

    Note note(1000u,addrPk);
    print("Note created");
    
    auto cm = note.cm();
    // TODO debug
    // In sha256.cpp 
    //  in sha256Hasher.FinalizeNoPadding(noteCommitment.begin())
    //      terminate called after throwing an instance of 'std::length_error'
    //          what():  SHA256Compress should be invoked with a 512-bit block
    // 
    // In sha256.cpp
    //  in sha256Hasher.Write(blob, 105);
    //  in CSHA256::Write(const unsigned char* data, size_t len)
    //    if (end > data) {
    //      memcpy(buf + bufsize, data, end - data); <- error
    //      bytes += end - data;
    //    }
    print("CM:", cm);
    auto nullifier = note.nullifier(addrSk);
    print("Nullifier: ", nullifier);
    // TODO ametsuchi 
}

int main (int argc, char** argv){
    test();
    return 0;
}