#ifndef XTEA_H
#define XTEA_H

#include <iostream>
#include <cstdint>
#include <vector>
#include <cstring>

void xteaEncryption(uint32_t v[2], const uint32_t key[4]);
void xteaDecryption(uint32_t v[2], const uint32_t key[4]);
vector<uint32_t> text_to_blocks(const string& text);
string blocks_to_text(const vector<uint32_t>& blocks);
vector<char> checkinputxtea(const string& message);
void generateXteaKeys();
string xteaEncryption(string& message);
string xteaDecryption(const string& message);





#include "xtea.cpp"

#endif
