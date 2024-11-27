#ifndef CRYPTOSYSTEM_H
#define CRYPTOSYSTEM_H

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

using namespace std;

const string passwd = "110205";

// Обьявляем функцию для работы с файлами
string FileInput(string &filename);
string FileOutput(string &filename, string &str);

// Функция для ввода и проверки сообщения или ключа
void input_and_check(string& message, string choice_shifr, string message_or_key);
vector<char> checkinputhughes(const string& messagee);
vector<char> checkinputrc6(const string& messagee);


// Функция для шифрования и дешифрования
void Enc_and_Desc(const string &choice_cipher);

// Объявление переменной пароля
extern const string passwd;

#endif
