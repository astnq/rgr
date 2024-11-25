#ifndef RC6_H
#define RC6_H

#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

inline uint32_t ROTL(uint32_t x, uint32_t y);
inline uint32_t ROTR(uint32_t x, uint32_t y);
void keySchedule(const vector<uint8_t>& key);
void encrypt(uint32_t& A, uint32_t& B, uint32_t& C, uint32_t& D);
void decrypt(uint32_t& A, uint32_t& B, uint32_t& C, uint32_t& D);

#include "rc6.cpp"

#endif