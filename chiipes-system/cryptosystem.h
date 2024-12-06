#pragma once 

#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <bitset>
#include <cstring>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string> 
#include <stdexcept>

using namespace std;

const string passwd = "1105";

void printHex(unsigned char* data, size_t length);
// RC6
void rc6_encrypt(unsigned char* data, unsigned char* key, size_t data_len);
void rc6_decrypt(unsigned char* data, unsigned char* key, size_t data_len);


// XTEA
void xtea_encrypt(unsigned char* data, unsigned char* key, size_t data_len);
void xtea_decrypt(unsigned char* data, unsigned char* key, size_t data_len);


// Алгоритм Hughes
void hughes_encrypt(unsigned char* data, unsigned char* key, size_t data_len);
void hughes_decrypt(unsigned char* data, unsigned char* key, size_t data_len);

extern const string passwd;
