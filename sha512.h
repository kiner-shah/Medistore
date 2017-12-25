/* 
 * File:   sha512.h
 * Author: Kiner Shah
 *
 * Created on 21 December, 2017, 6:23 PM
 */

#ifndef SHA512_H
#define	SHA512_H

#include <string>
#include <bitset>
#include <iomanip>
#include <cstring>
#include <cassert>
#include <vector>
#include <climits>

std::vector<std::vector<uint64_t> > preprocessing(std::string);
std::string computeSHA512(std::string input_message);
void initialize_hashes(uint64_t (&x)[8]);

uint64_t Ch(uint64_t , uint64_t, uint64_t);     // Ch(x, y, z);
uint64_t Maj(uint64_t , uint64_t, uint64_t);    // Maj(x, y, z);
uint64_t BigSigma0(uint64_t);                     // BigSigma0(x);
uint64_t BigSigma1(uint64_t);                     // BigSigma1(x);
uint64_t Sigma0(uint64_t);                        // Sigma0(x);
uint64_t Sigma0(uint64_t);                        // Sigma0(x);
#endif	/* SHA512_H */

