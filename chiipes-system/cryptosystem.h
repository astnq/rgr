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

using namespace std;

// Обьявляем функцию для работы с файлами
string FileInput(string &filename);
string FileOutput(string &filename, string &str);

// Функция для ввода и проверки сообщения или ключа
void input_and_check(string& message, const string &choice_cipher);

// Функция для шифрования и дешифрования
void Enc_and_Desc(const string &choice_cipher);

// Объявление переменной пароля
extern const string passwd;

#endif