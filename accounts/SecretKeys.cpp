#include <fstream>
#include <boost/filesystem.hpp>
#include <sodium.h>
#include "SecretKeys.h"
#include "strutils.h"



/*
 * Creates the Address Secret key. Uses Sodium's randombytes_buf to generate 32 random bytes.
 * Since key is 252 bits, clears the most significant 4 bits and returns a uint252
 */
uint252 SecretKeys::random252() {
    uint256 a_sk;
    randombytes_buf(a_sk.begin(),32);
    (*a_sk.begin()) &= 0x0F;
    return uint252(a_sk);
}
/*
 * Creates encryption secret key for the Elliptic Curve Diffie-Hellman Key Exchange
 * The encryption secret key is derived from the Address Secret Key.
 *  Uses PRF (SHA256) with the address secret key.
 */

uint256 SecretKeys::encSecretKey() {
    auto sk_enc = PRF_addr_sk_enc(addrSk);
// [Bern2006] https://cr.yp.to/ecdh/curve25519-20060209.pdf
    /*
     * "clear bits 0, 1, 2 of the first byte, clear bit 7 of the last byte, and set bit 6 of the last byte."
     * Clamping :
     *  the first three bits are clamped to eliminate the torsion component
     *  the upper two bits are clamped for efficiency and implementation security IIRC
     */
    sk_enc.begin()[0] &= 248;
    sk_enc.begin()[31] &= 127;
    sk_enc.begin()[31] |= 64;

    return sk_enc;
}
/*
 * Public function:
 *  Once called generates the address and encryption secret keys and stores them both in a .priv file.
 *  Call this function from wallet to generate the private keys.
 *  Note: This function must be called before the public key generation function.
 *  TODO: Check if account name already exists before overwriting previous .priv files.
 */
void SecretKeys::generateKeys() {
    if (boost::filesystem::exists(accName+".priv"))
        throw std::logic_error("An account with that name already exists");
    addrSk = random252();
    encSk = encSecretKey();
    //storeKeys();
}

/*
 * Returns a string with the hexadecimal of the address secret key and encryption secret key. Separated by a space.
 */
std::string SecretKeys::toHexString() const{
    std::string aSkHex = HexStr(addrSk.begin(),addrSk.end());
    std::string encSkHex = HexStr(encSk.begin(), encSk.end());
    std::string temp = aSkHex;
    temp.append(" ");
    temp.append(encSkHex);
    std::cout<<"Private keys"<<std::endl;
    std::cout<<temp<<std::endl;
    return temp;
}

/*
 * Stores the secret keys in .priv file.
 * If such file already exists, throw error.
 */
void SecretKeys::storeKeys() const{

    std::ofstream privKeys(accName+".priv");
    privKeys << toHexString();
    privKeys.close();
}