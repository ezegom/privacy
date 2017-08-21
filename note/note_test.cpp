#include <iostream>
#include "Note.h"
#include "uint256.h"
#include "PublicKeys.h"
#include "SecretKeys.h"
#include "strutils.h"

void test(){
    std::string name = "note_test";
    SecretKeys sks(name);
    sks.generateKeys();
    PublicKeys pks(name);
    pks.generateKeys(sks);    
        
    auto addrSk = sks.getAddrSk();
    auto addrPk = pks.getAddrPk();   

    Note note(1000u,addrPk);
    
    auto cm = note.cm();
    std::cout << "[cm       ] " << HexStr(cm.begin(),cm.end())<< std::endl;
    auto nullifier = note.nullifier(addrSk);
    std::cout << "[nullifier] " << HexStr(nullifier.begin(),nullifier.end())<< std::endl;
}

int main (int argc, char** argv){
    test();
    return 0;
}