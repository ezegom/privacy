//
// Created by parallels on 8/28/17.
//

#include "TransactionOutput.h"
#include "prf.h"


TransactionOutput::TransactionOutput(): address(PublicKeys()), value(0){
}

/*
 * Generates note for output. First derives rho from phi, i and hSig.
 */
Note TransactionOutput::getNote(const uint252 &phi, size_t i, const uint256 &r, const uint256 &hsig) {
    uint256 rho = PRF_rho(phi,i,hsig);
    return Note(r, value, rho, address.getAddrPk());
}
