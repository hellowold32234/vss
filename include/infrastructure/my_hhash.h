#ifndef __hhash
#define __hhash

/**extra 'h' before hhash can avoid some strange error by the compiler*/

#include <immintrin.h>
#include <wmmintrin.h>
#include <cassert>
#include "flo-shani-aesni/sha256/flo-shani.h"
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <string>


class __hhash_digest
{
public:
    unsigned char data[256 / 8];
};

inline bool equals(const __hhash_digest &a, const __hhash_digest &b)
{
    bool result = true;
    for(int i = 0; i < 256 / 8; ++i)
    {
        result &= (a.data[i] == b.data[i]);
    }
    return result;
}

inline void my_hhash(const void* src, void* dst)
{
unsigned int digestLength;

    EVP_MD_CTX *mdctx;

    // 创建 SM3 哈希算法上下文
    mdctx = EVP_MD_CTX_new();
    // 初始化上下文
    EVP_DigestInit_ex(mdctx, EVP_sm3(), NULL);
    // 更新消息数据
    EVP_DigestUpdate(mdctx, (char*)src, 64);
    // 计算哈希值
    EVP_DigestFinal_ex(mdctx, (unsigned char*)dst, &digestLength);
    // 释放上下文
    EVP_MD_CTX_free(mdctx);
}

#endif
