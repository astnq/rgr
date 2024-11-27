#ifndef RC6_H
#define RC6_H

#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

inline uint32_t ROTL(uint32_t x, uint32_t y);
inline uint32_t ROTR(uint32_t x, uint32_t y);
void keySchedule(const vector<uint8_t>& key);
void Encryption(uint32_t& A, uint32_t& B, uint32_t& C, uint32_t& D);
void Decryption(uint32_t& A, uint32_t& B, uint32_t& C, uint32_t& D);
vector<char> checkinputrc6(const string& message);
string rc6Encryption(string& message);
string rc6Decryption(const string& message);

#include "rc6.cpp"

#endif
