#ifndef PRIVATEUTXO_MERKLETREE_H
#define PRIVATEUTXO_MERKLETREE_H

// TODO: merkle tree header
// TODO: test ametsuchi data store + query to find nullifier and cm
//  ==> impossible!!, ametsuchi only takes iroha-specific tx type, not general byte strings.
// TODO: reimplement ametsuchi
// TODO: understand ametsuchi implementation and modify to take just data stroe and query

#include "ametsuchi/merkle_tree/merkle_tree.h"

class MerkleTree {
private:
    ametsuchi::merkle::MerkleTree merkle_tree_;
    
public:
    
};


#endif //PRIVATEUTXO_MERKLETREE_H