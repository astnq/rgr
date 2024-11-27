#ifndef HUGHES_H
#define HUGHES_H

using namespace std;

#include <iostream>
#include <string>
#include <bitset>

int VzaimProst(int a, int b);
bool CheckPrime(int num);
int fi(int num);
int Pow(int a, int x, int p);
int inversia(int c, int m);
int GenerateKey();
string hughesEncDesc(string message, int key);

#include "hughes.cpp"

#endif
