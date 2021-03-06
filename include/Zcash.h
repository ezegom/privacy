// Copyright (c) 2016 The Zcash developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef _ZCCONSTANTS_H_
#define _ZCCONSTANTS_H_

#define ZC_NUM_JS_INPUTS 2
#define ZC_NUM_JS_OUTPUTS 2
// #define INCREMENTAL_MERKLE_TREE_DEPTH 29
#define INCREMENTAL_MERKLE_TREE_DEPTH_TESTING 4

#define ZC_NOTEPLAINTEXT_LEADING 1
#define ZC_V_SIZE 8
#define ZC_RHO_SIZE 32
#define ZC_R_SIZE 32
#define ZC_MEMO_SIZE 512

#define ZC_NOTEPLAINTEXT_SIZE (ZC_NOTEPLAINTEXT_LEADING + ZC_V_SIZE + ZC_RHO_SIZE + ZC_R_SIZE + ZC_MEMO_SIZE)

#endif // _ZCCONSTANTS_H_
