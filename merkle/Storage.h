/**
 * @file MerkleTree.h
 * @date 2017/08/17
 * @author EunsooSheen(eunsoo.sheen@gmail.com)
 * @brief header for storing cm and nullifier
 */
#ifndef PRIVATEUTXO_MERKLETREE_H
#define PRIVATEUTXO_MERKLETREE_H

#include <stdint.h>
#include <string>
#include "ametsuchi/merkle_tree/merkle_tree.h"
#include "uint256.h"

/**
 * @class Storage
 * @date 2017/08/17
 * @author EunsooSheen(eunsoo.sheen@gmail.com)
 * @brief a class for storing cm and nullifier
 */
class Storage {
private:
    std::string path_;
    MDB_env *env;
    MDB_stat mst;
    MDB_txn *append_tx_;  // pointer to db transaction
    
    TxStore tx_store;
    
    uint32_t AMETSUCHI_TREES_TOTAL;
    void init();
    void init_append_tx();
    void abort_append_tx();
public:
    explicit Storage(const std::string& path):path_(path){}
    virtual ~Storage(){}
    merkle::hash_t append(const uint256 const * data);
    void commit();
    void rollback();
    // TODO: queries
};


#endif //PRIVATEUTXO_MERKLETREE_H