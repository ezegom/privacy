#include <string>
#include <iostream>
#include "IncrementalMerkleTree.h"
#include "uint256.h"
#include "accounts/SecretKeys.h"
#include "accounts/PublicKeys.h"
#include "note/Note.h"

Note generateNote(const std::string& name){
    SecretKeys sks(name);
    sks.generateKeys();
    PublicKeys pks(name);
    pks.generateKeys(sks);
    auto addrPk = pks.getAddrPk();  
    return Note(1000u,addrPk);
}
SHA256Compress toSHA256Compress(const uint256& n){
    return SHA256Compress(n);
}
void test(){
    ZCIncrementalMerkleTree merkle;
    auto note = generateNote("merkle_test_zcash");
    auto note_compressed = toSHA256Compress(note.cm());
    
    // TODO: more tests!! append good
    for (auto i=0 ; i<100000; ++i){
        merkle.append(note_compressed);
        if(i%10000==0){
            std::cout << "[Loop " <<i << "]" << std::endl;
            std::cout <<"size: "<<merkle.size()<<std::endl;
            std::cout << "Dynamic Memory Usage: " 
            <<merkle.DynamicMemoryUsage()<< std:: endl;
        }
    }
    // TODO: 종속성 최소화해서 라이브러리 만들기
}

int main(int argc, char** argv){
    test();
    return 0;
}