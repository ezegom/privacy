//
// Created by parallels on 8/28/17.
//

#ifndef PRIVATEUTXO_OUTPUT_H
#define PRIVATEUTXO_OUTPUT_H

#include "PublicKeys.h"
#include "constants.h"
#include "Note.h"
#include <array>
class TransactionOutput{
public:
    PublicKeys address;
    uint64_t value;
    std::array<unsigned char, NOTE_MEMO_BYTES> memo = {{0x00}};

    TransactionOutput();
    TransactionOutput(PublicKeys address,
                      uint64_t value,
                      std::array<unsigned char, NOTE_MEMO_BYTES> _memo): address(address), value(value){
        memcpy(memo.begin(),_memo.begin(),NOTE_MEMO_BYTES);
    }

    Note getNote(const uint252& phi, size_t i, const uint256& r, const uint256& hsig);
};


#endif //PRIVATEUTXO_OUTPUT_H
