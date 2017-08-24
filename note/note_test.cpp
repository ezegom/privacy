#include <iostream>
#include <string>
#include "Note.h"
#include "uint256.h"
#include "accounts/PublicKeys.h"
#include "accounts/SecretKeys.h"
#include "sodium.h"
#include "strutils.h"

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
    std::cout<<"[CM]"<< HexStr(cm.begin(),cm.end())<<std::endl;
    auto nullifier = note.nullifier(addrSk);
    std::cout<<"[Nullifier]"<< HexStr(nullifier.begin(),nullifier.end())<<std::endl;
}

int main (int argc, char** argv){
    test();
    return 0;
}