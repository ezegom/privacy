#include <iostream>
#include <string>
#include "accounts/SecretKeys.h"
#include "accounts/PublicKeys.h"
#include "note/Note.h"
#include "strutils.h"
#include "uint256.h"
#include "IncrementalMerkleTree.h"


#define INCREMENTAL_MERKLE_TREE_DEPTH_TEST 5

Note generateNote(const std::string& name){
    SecretKeys sks(name);
    sks.generateKeys();
    PublicKeys pks(name);
    pks.generateKeys(sks);
    auto addrPk = pks.getAddrPk();  
    return Note(1000u,addrPk);
}

void test_witness(){
    ZCIncrementalMerkleTree tree;

    auto note = generateNote("merkle_test_zcash");
    auto cm_compressed = SHA256Compress(note.cm());
    
    for (auto i=0 ; i<32; ++i){
        tree.append(cm_compressed);
    }

    auto rt = tree.root();
    auto witness = tree.witness();

    // The witness root must equal the input root.
    if (witness.root() != rt) {
        throw std::invalid_argument("joinsplit not anchored to the correct root");
    }

    // The tree must witness the correct element
    if (note.cm() != witness.element()) {
        throw std::invalid_argument("witness of wrong element for joinsplit input");
    }
    std::cout << "success" << std::endl;
}

void test_full_merkle_tree(){
    // Depth=5
    ZCTestingIncrementalMerkleTree tree; 
    
    auto note = generateNote("merkle_test_zcash");
    auto cm_compressed = SHA256Compress(note.cm());
    
    for (auto i=0 ; i<32; ++i){
        tree.append(cm_compressed);
    }
    std::cout<<"size: " << tree.size()<<std::endl;
    // tree.append(cm_compressed);//it will throw exception
}

void test_witness_path(size_t appended){
    ZCTestingIncrementalMerkleTree tree;

    auto note = generateNote("merkle_test_zcash");
    auto cm_compressed = SHA256Compress(note.cm());
    
    for (auto i=0 ; i<appended; ++i) {
        tree.append(cm_compressed);
    }

    auto rt = tree.root();
    auto witness = tree.witness();
    auto path = witness.path();
    
    std::cout << appended<< " CMs appended: ";
    for (const bool& index : path.index) {
        std::cout<<(index?'T':'F') << " ";
    }
    std::cout<<std::endl;
} 

int main(int argc, char** argv){
    test_witness();
    test_full_merkle_tree();
    test_witness_path(15);
    return 0;
}