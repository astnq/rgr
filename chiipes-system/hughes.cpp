#include "Cryptosystem.h"

typedef unsigned char uc;

// ������� ��� ������ ���� �����
string leftShift(string str) {
    char first = str[0];
    for (size_t i = 0; i < str.size() - 1; ++i) {
        str[i] = str[i + 1];
    }
    str[str.size() - 1] = first;
    return str;
}

// ������� ���������� �����
string hughesEncrypt(const string& input, const string& key) {
    // ������� ��������, ����� ����� ����� ���� ����������
    if (key.size() != 8) {
        cerr << "���� ������ ���� ������ 8 ��������!" << endl;
        return "";
    }

    string encrypted;
    string keyReg = key;

    for (size_t i = 0; i < input.size(); ++i) {
        bitset<8> block(input[i]);

        // XOR � ������� ������
        block ^= bitset<8>(keyReg);

        // ����� ����� �����
        keyReg = leftShift(keyReg);

        // ����������� ������ � ������
        encrypted += char(block.to_ulong());
    }
    return encrypted;
}

// ������� ������������ �����
string hughesDecrypt(const string& input, const string& key) {
    return hughesEncrypt(input, key);  // ���������� � ������������ ���������
}

int main() {
    string key = "11110000";  // ������ �����
    string message = "Hello!"; // ��������� ��� ����������

    string encrypted = hughesEncrypt(message, key);
    string decrypted = hughesDecrypt(encrypted, key);

    cout << "Original message: " << message << endl;
    cout << "Encrypted message: " << encrypted << endl;
    cout << "Decrypted message: " << decrypted << endl;

    return 0;
}
 

