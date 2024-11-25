#ifndef HUGHES_H
#define HUGHES_H

using namespace std;

#include <iostream>
#include <string>
#include <bitset>

string leftShift(string str);
string hughesEncrypt(const string& input, const string& key);
string hughesDecrypt(const string& input, const string& key);

#include "hughes.cpp"

#endif