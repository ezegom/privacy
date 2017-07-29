//
// Created by parallels on 7/26/17.
//

#ifndef PRIVATEUTXO_STRUTILS_H
#define PRIVATEUTXO_STRUTILS_H
#include <iostream>

template<typename T>
static std::string HexStr(const T itbegin, const T itend) {
    std::string rv;
    static const char hexmap[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    rv.reserve((itend - itbegin) * 3);
    for (T it = itbegin; it < itend; ++it) {
        unsigned char val = (unsigned char) (*it);
        rv.push_back(hexmap[val >> 4]);
        rv.push_back(hexmap[val & 15]);
    }
    return rv;
}
#endif //PRIVATEUTXO_STRUTILS_H
