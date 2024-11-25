#include "Cryptosystem.h"

typedef unsigned char uc;

// Функция для сдвига бита влево
string leftShift(string str) {
    char first = str[0];
    for (size_t i = 0; i < str.size() - 1; ++i) {
        str[i] = str[i + 1];
    }
    str[str.size() - 1] = first;
    return str;
}

// Функция шифрования Хьюза
string hughesEncrypt(const string& input, const string& key) {
    // Сначала проверим, чтобы длина ключа была корректной
    if (key.size() != 8) {
        cerr << "Ключ должен быть длиной 8 символов!" << endl;
        return "";
    }

    string encrypted;
    string keyReg = key;

    for (size_t i = 0; i < input.size(); ++i) {
        bitset<8> block(input[i]);

        // XOR с текущим ключом
        block ^= bitset<8>(keyReg);

        // Сдвиг ключа влево
        keyReg = leftShift(keyReg);

        // Преобразуем битсет в строку
        encrypted += char(block.to_ulong());
    }
    return encrypted;
}

// Функция дешифрования Хьюза
string hughesDecrypt(const string& input, const string& key) {
    return hughesEncrypt(input, key);  // Шифрование и дешифрование идентичны
}

int main() {
    string key = "11110000";  // Пример ключа
    string message = "Hello!"; // Сообщение для шифрования

    string encrypted = hughesEncrypt(message, key);
    string decrypted = hughesDecrypt(encrypted, key);

    cout << "Original message: " << message << endl;
    cout << "Encrypted message: " << encrypted << endl;
    cout << "Decrypted message: " << decrypted << endl;

    return 0;
}
 

