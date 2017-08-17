#include <string.h>
#include <stdint.h>
#include <error.h>
#include <iostream>
#include <string>
#include <array>
#include <sys/stat.h>
#include "sodium.h"
#include "uint256.h"
#include "strutils.h"
#include "PublicKeys.h"
#include "SecretKeys.h"
#include "Note.h"
#include "debugPrint.h"
#include "ametsuchi/merkle_tree/merkle_tree.h"
#include "ametsuchi/ametsuchi.h"

Note generateNote(){
    std::string name = "test";
    SecretKeys sks(name);
    sks.generateKeys();
    PublicKeys pks(name);
    pks.generateKeys(sks);
    auto addrPk = pks.getAddrPk();  
    return Note(1000u,addrPk);
}

void test1(){
    print("*****************");
    print("******test1******");
    print("*****************");
    std::string name = "note_test";
    SecretKeys sks(name);
    sks.generateKeys();
    PublicKeys pks(name);
    pks.generateKeys(sks);    
    
    auto addrSk = sks.getAddrSk();
    auto addrPk = pks.getAddrPk();   
    print("address secretKey",addrSk);
    print("address publicKey",addrPk);

    Note note(1000u,addrPk);
    
    auto cm = note.cm();
    print("[CM]", cm);
    auto nullifier = note.nullifier(addrSk);
    print("[Nullifier]", nullifier);

    ametsuchi::merkle::MerkleTree merkle(4,2);
    print("merkle tree initialized in 4 leafs and 2 blocks!!");
    auto cm_hash_t = toHash_t(cm);
    auto nullifier_hash_t = toHash_t(nullifier);
}

void test2(const std::string& db_folder,const int& t)
{
    print("*****************");
    print("******test2******");
    print("*****************");
    if (mkdir( db_folder.c_str(),S_IRWXU|S_IRWXG|S_IXOTH)<0){
        perror("mkdir in test");
        return;
    }
    ametsuchi::Ametsuchi amet(db_folder);
    for(auto i=0; i<t; i++){
        auto note = generateNote();
        auto vec = toVectoerUint8(note.cm());
        amet.append(vec);
    }
}

int main(int argc, char** argv)
{
    if (argc!=2){
        std::cout<<"usage ./MerkleTest [folder name]" << std::endl;
        return 1;
    }
    if (sodium_init() == -1 ){
        throw std::runtime_error("Sodium init failed");
    }
    
    test1();
    test2(argv[1],100);

    return 0;
}