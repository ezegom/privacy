//
// Created by parallels on 7/20/17.
//

#include <fstream>
#include<boost/filesystem.hpp>
#include "PublicKeys.h"
#include "sodium.h"
#include "strutils.h"
#include "prf.h"


/*
Purpose: Generate encryption public key from secret key.
    crypto_scalarmult_base(q,n);
    The crypto_scalarmult_base function computes the scalar product of a standard group element and an integer n[0], ..., n[crypto_scalarmult_SCALARBYTES-1]. It puts the resulting group element into q[0], ..., q[crypto_scalarmult_BYTES-1] and returns 0.
*/
uint256 PublicKeys::generatePkEnc(const uint256 &skEnc)
{
    uint256 pk;
    if (crypto_scalarmult_base(pk.begin(), skEnc.begin()) != 0) {
        throw std::logic_error("Error creating encryption public key");
    }
    return pk;
}

/*
 * Uses PRF function and secret key to generate address public key
 */
uint256 PublicKeys::generatePkAddr(const uint252 &skAddr) {
    uint256 temp;
    temp = PRF_addr_a_pk(skAddr);
    return temp;
}

/*
 * TODO: Encodes Address public key and encryptin public key as a payment address
 */
void PublicKeys::paymentAddress() const{

}

/*
 * Returns a string with the hexadecimal of the address public key and encryption public key. Separated by a space.
 */
std::string PublicKeys::toHexString() const{
    std::string aSkHex = HexStr(addrPk.begin(),addrPk.end());
    std::string encSkHex = HexStr(pkEnc.begin(), pkEnc.end());
    std::string temp = aSkHex;
    temp.append(" ");
    temp.append(encSkHex);
    std::cout<<"Public keys"<<std::endl;
    std::cout<<temp<<std::endl;
    return temp;
}
/*
 * Public function:
 *  Once called generates the address and encryption public key and stores them both in a .pub file.
 *  Call this function from wallet to generate the public keys.
 *  Note: This function must be called after the secret keys have been initialized.
 */
void PublicKeys::generateKeys(SecretKeys& sk) {
    //Secret keys must be created first
    //If encryption secret key is set, addrSk must be set too.
    if (sk.getEncSk().IsNull())
        throw std::logic_error("Secret keys must be generated");

    if (boost::filesystem::exists(accName+".pub"))
        throw std::logic_error("An account with that name already exists");

    pkEnc = generatePkEnc(sk.getEncSk());
    addrPk = generatePkAddr(sk.getAddrSk());
    //storeKeys();
}
/*
 * Creates a .pub file containing the address public key followed by the encryption public key in hexadecimal.
 * both keys are separated by a space.
 */
void PublicKeys::storeKeys() {
    std::ofstream pubKeys(accName+".pub");
    pubKeys << toHexString();
    pubKeys.close();
}