/* 
 * File:   sha512.cpp
 * Author: Kiner Shah
 *
 * Created on 21 December, 2017, 6:23 PM
 * 
 * References:
 * [1]  http://www.iwar.org.uk/comsec/resources/cipher/sha256-384-512.pdf
 */
#include <vector>

#include "sha512.h"

//#define __DEBUG_SHA512__
using namespace std;
//const uint64_t addmod = (1ULL << 64 - 1);
void initialize_hashes(uint64_t (&x)[8]) {
    x[0] = 0x6a09e667f3bcc908;
    x[1] = 0xbb67ae8584caa73b;
    x[2] = 0x3c6ef372fe94f82b;
    x[3] = 0xa54ff53a5f1d36f1;
    x[4] = 0x510e527fade682d1;
    x[5] = 0x9b05688c2b3e6c1f;
    x[6] = 0x1f83d9abfb41bd6b;
    x[7] = 0x5be0cd19137e2179;
}

uint64_t rotr64 (uint64_t x, unsigned int n) {
    return (((x & 0xFFFFFFFFFFFFFFFFULL) >> n) | (x << (64 - n)));
}

uint64_t Ch(uint64_t x, uint64_t y, uint64_t z) {
    return ((x & y) ^ (~x & z));
}

uint64_t Maj(uint64_t x, uint64_t y, uint64_t z) {
    return ((x & y) ^ (x & z) ^ (y & z));
}

uint64_t BigSigma0(uint64_t x) {
    return ((rotr64(x, 28)) ^ (rotr64(x, 34)) ^ (rotr64(x, 39)));
}

uint64_t BigSigma1(uint64_t x) {
    return ((rotr64(x, 14)) ^ (rotr64(x, 18)) ^ (rotr64(x, 41)));
}

uint64_t Sigma0(uint64_t x) {
    return ((rotr64(x, 1)) ^ (rotr64(x, 8)) ^ (x >> 7));
}

uint64_t Sigma1(uint64_t x) {
    return ((rotr64(x, 19)) ^ (rotr64(x, 61)) ^ (x >> 6));
}

vector<vector<uint64_t> > preprocessing(string message) {
    int len = message.length();
    int l = len * 8;  // result in bits is required
    unsigned char M[l + 1];
    memset(M, '0', l + 1);
    /* Converting message to binary */
    for(int i = 0 ; i < len; i++) {
        string temp = "";
        for(int j = 7; j >= 0; j--) {
            temp += ((1 << j) & message[i] ? '1' : '0');
        }
        int len = i * 8;
        memcpy(M + len, temp.c_str(), 8);
    }
    M[l] = '\0';
    string len_str = bitset<16>(l).to_string();
    ostringstream o;
    bool flag = false;
    for(int i = 0; i < 16; i++) {
        if(len_str[i] == '1') flag = true;
        if(flag) o << len_str[i];
    }
    string new_len_str = o.str();
    unsigned char *mes_length = (unsigned char*) new_len_str.c_str();
#ifdef __DEBUG_SHA512__
    printf("M = %s len_str = %s\n", M, mes_length);
#endif
    int no_of_zeros = (896 - l - 1);    // (896 - length_of_message - 1) % 1024
    if(no_of_zeros < 0) no_of_zeros = 1024 - (-no_of_zeros % 1024);
    ostringstream o1;
    o1 << M << '1' << setw(no_of_zeros) << setfill('0') << '0' << setw(128) << setfill('0') << mes_length;
    string pad_temp = o1.str();
    unsigned char *padded_message = (unsigned char*) pad_temp.c_str();
#ifdef __DEBUG_SHA512__
    printf("padded = %s, len_of_padded = %d, no_of_zeros = %d\n", padded_message, strlen((const char*)padded_message), no_of_zeros);
#endif   
    int len_padded_mes = strlen((const char*)padded_message), j = 0;
    int no_of_blocks = len_padded_mes / 1024;
    vector<vector<uint64_t> > block_subblock;
    vector<uint64_t> temp_vect;
    block_subblock.reserve(no_of_blocks);
    temp_vect.reserve(16);
    // Making 16 64-bit blocks from 1024-bit block, for each 1024-bit block
    for(int i = 0; i < len_padded_mes; i += 64) {
        if(j == 16) {
            block_subblock.push_back(temp_vect);
            temp_vect.clear();
            j = 0;
        }
        else {
            char temp_char_arr[65];
            memset(temp_char_arr, '\0', sizeof(temp_char_arr));
            memcpy(temp_char_arr, padded_message + i, 64);
            string temp_char_arr_str(temp_char_arr);
#ifdef __DEBUG_SHA512__            
            printf("64 bit = %s, %d\n", temp_char_arr_str.c_str(), j);
#endif 
            try {
                uint64_t temp_long_long = stoull(temp_char_arr_str, NULL, 2);
                temp_vect.push_back(temp_long_long);
#ifdef __DEBUG_SHA512__ 
                printf("LONG = %llx\n", temp_long_long);
#endif
            }
            catch(const std::invalid_argument& ia) { perror(ia.what()); }
            catch(const std::out_of_range &oor) { perror(oor.what()); }       
            j++;
        }
    }
    if(j == 16) {
        block_subblock.push_back(temp_vect);
#ifdef __DEBUG_SHA512__         
        printf("%d\n", temp_vect.size());
#endif
        temp_vect.clear();
        j = 0;
    }
#ifdef __DEBUG_SHA512__     
    for(int i = 0; i < no_of_blocks; i++) {
        for(j = 0; j < 16; j++) printf("%lld ", block_subblock[i][j]);
        printf("\n");
    }
#endif
    assert(block_subblock.size() == no_of_blocks);
    return block_subblock;
}

string computeSHA512(string input_message) {
    vector<vector<uint64_t > > extracted_blocks = preprocessing(input_message);
    uint64_t hashes[8], w[80];
    uint64_t initial_keys[80] = {0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
         0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 
         0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 
         0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694, 
         0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 
         0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 
         0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 
         0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70, 
         0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df, 
         0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b, 
         0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 
         0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 
         0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 
         0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 
         0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec, 
         0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 
         0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 
         0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b, 
         0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c, 
         0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};
    initialize_hashes(hashes);
    int no_of_blocks = extracted_blocks.size();
#ifdef __DEBUG_SHA512__ 
    printf("ROTR %llu = %llu\n", (1ULL << 64 - 1), rotr64(1ULL << 64 - 1, 1));
    for(int i = 0; i < no_of_blocks; i++) {
        for(int j = 0; j < 16; j++) printf("%llx %llu\n", extracted_blocks[i][j], extracted_blocks[i][j]);
    }
    for(int i = 0; i < 8; i++) printf("Hash %d = %llx\n", i, hashes[i]);
    for(int i = 0; i < 80; i++) printf("Key %d = %llx\n", i, initial_keys[i]);
#endif
    register uint64_t a, b, c, d, e, f, g, h;   // the eight registers
    for(int i = 0; i < no_of_blocks; i++) {
        a = hashes[0]; b = hashes[1];
        c = hashes[2]; d = hashes[3];
        e = hashes[4]; f = hashes[5];
        g = hashes[6]; h = hashes[7];
#ifdef __DEBUG_SHA512__ 
        printf("%llx %llx %llx %llx %llx %llx %llx %llx\n", a, b, c , d, e, f, g, h);
#endif
        for(int j = 0; j < 80; j++) {
            if(j <= 15) {
                w[j] = extracted_blocks[i][j];
            }
            else {
                w[j] = (Sigma1(w[j - 2]) + w[j - 7] + Sigma0(w[j - 15]) + w[j - 16]);
            }
            uint64_t ch_var = Ch(e, f, g);
            uint64_t maj_var = Maj(a, b, c);
            uint64_t bigsigma0_var = BigSigma0(a);
            uint64_t bigsigma1_var = BigSigma1(e);
            uint64_t t1 = (h + bigsigma1_var + ch_var + initial_keys[j] + w[j]);
            uint64_t t2 = (bigsigma0_var + maj_var);
            h = g; g = f; f = e;
            e = (d + t1);
            d = c; c = b; b = a;
            a = (t1 + t2);
        }
        hashes[0] = (hashes[0] + a);
        hashes[1] = (hashes[1] + b);
        hashes[2] = (hashes[2] + c);
        hashes[3] = (hashes[3] + d);
        hashes[4] = (hashes[4] + e);
        hashes[5] = (hashes[5] + f);
        hashes[6] = (hashes[6] + g);
        hashes[7] = (hashes[7] + h);
    }
#ifdef __DEBUG_SHA512__
    for(int i = 0; i < 8; i++) printf("%llx ", hashes[i]); printf("\n");
#endif
    ostringstream o2; 
    for(int i = 0; i < 8; i++) {
        o2 << std::hex << hashes[i];
    }
    return o2.str();
}

/*
 * Test:
 * Input: abc
 * Output: ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f
 * Input: I am a dog
 * Output: C96E7C680A303627214F8B136F5B8CCD674E12A5D200F6F64BEEC1B8764FAE76371078FF5204FED54A5328E29817C50D36040D1E561557B5899D377B79B5C339
 */