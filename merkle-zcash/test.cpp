#include <string>
#include "zcash/IncrementalMerkleTree.hpp"
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

void test(){
    ZCIncrementalMerkleTree merkle;
    auto note = generateNote("merkle_test_zcash");
    auto note_compressed = libzcash::SHA256Compress(note.cm());
    merkle.append(note_compressed);
    // TODO: more tests!! append good
}

int main(int argc, char** argv){
    test();
    return 0;
}