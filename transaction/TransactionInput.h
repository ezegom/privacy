//
// Created by parallels on 8/28/17.
//

#ifndef PRIVATEUTXO_INPUT_H
#define PRIVATEUTXO_INPUT_H

#include "uint252.h"
#include "Note.h"
class TransactionInput {
public:
    uint252 spendingKey;
    Note note;
    //Todo: add IncrementalWitness
    TransactionInput();
    TransactionInput(Note note, uint252 spendingKey) : note(note), spendingKey(spendingKey) {}

    uint256 getNoteNullifier(){
        return note.nullifier(spendingKey);
    }
};


#endif //PRIVATEUTXO_INPUT_H
