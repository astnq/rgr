#include "xtea.cpp"
#include "rc6.cpp"
#include "hughes.cpp"
#include "Cryptosystem.h"

using namespace std;

// Вспомогательная функция для представления чисел в 16-ричном виде
void printHex(unsigned char* data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        cout << hex << setw(2) << setfill('0') << (int)data[i] << " ";
    }
    cout << endl;
}

// RC6
void rc6_encrypt(unsigned char* data, unsigned char* key, size_t data_len) {
    for (size_t i = 0; i < data_len; i++) {
        data[i] ^= key[i % 16]; // Простой XOR с ключом
    }
}

void rc6_decrypt(unsigned char* data, unsigned char* key, size_t data_len) {
    for (size_t i = 0; i < data_len; i++) {
        data[i] ^= key[i % 16]; // Простой XOR с ключом (обратная операция)
    }
}

// XTEA
void xtea_encrypt(unsigned char* data, unsigned char* key, size_t data_len) {
    uint32_t v0 = *(uint32_t*)&data[0];
    uint32_t v1 = *(uint32_t*)&data[4];
    uint32_t sum = 0;
    uint32_t delta = 0x9e3779b9;
    uint32_t key0 = *(uint32_t*)&key[0];
    uint32_t key1 = *(uint32_t*)&key[4];
    uint32_t key2 = *(uint32_t*)&key[8];
    uint32_t key3 = *(uint32_t*)&key[12];
    
    for (int i = 0; i < 32; i++) {
        v0 += (((v1 << 4) + key0) ^ (v1 + sum) ^ ((v1 >> 5) + key1));
        sum += delta;
        v1 += (((v0 << 4) + key2) ^ (v0 + sum) ^ ((v0 >> 5) + key3));
    }

    *(uint32_t*)&data[0] = v0;
    *(uint32_t*)&data[4] = v1;
}

void xtea_decrypt(unsigned char* data, unsigned char* key, size_t data_len) {
    uint32_t v0 = *(uint32_t*)&data[0];
    uint32_t v1 = *(uint32_t*)&data[4];
    uint32_t sum = 0xC6EF3720; // Начальное значение суммы для расшифровки
    uint32_t delta = 0x9e3779b9;
    uint32_t key0 = *(uint32_t*)&key[0];
    uint32_t key1 = *(uint32_t*)&key[4];
    uint32_t key2 = *(uint32_t*)&key[8];
    uint32_t key3 = *(uint32_t*)&key[12];
    
    for (int i = 0; i < 32; i++) {
        v1 -= (((v0 << 4) + key2) ^ (v0 + sum) ^ ((v0 >> 5) + key3));
        sum -= delta;
        v0 -= (((v1 << 4) + key0) ^ (v1 + sum) ^ ((v1 >> 5) + key1));
    }

    *(uint32_t*)&data[0] = v0;
    *(uint32_t*)&data[4] = v1;
}

// Алгоритм Hughes
void hughes_encrypt(unsigned char* data, unsigned char* key, size_t data_len) {
    for (size_t i = 0; i < data_len; i++) {
        data[i] = (data[i] + key[i % 16]) % 256; // Простая операция с ключом
    }
}

void hughes_decrypt(unsigned char* data, unsigned char* key, size_t data_len) {
    for (size_t i = 0; i < data_len; i++) {
        data[i] = (data[i] - key[i % 16] + 256) % 256; // Обратная операция (вычитание)
    }
}

int main() {
    system("cls");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));

    string password;
    cout << "Введите пароль: ";
    cin >> password;
    if (password != passwd) {
        cout << "Пароль неверный! Попробуйте еще раз: ";
        cin >> password;
        if (password != passwd) {
            cout << "Вы вводите неверный пароль! Последняя попытка: ";
            cin >> password;
            if (password != passwd) {
                cout << "Вы использовали все попытки! Завершение программы...";
                exit(0);
            }
        }
    }

    string user_input;
    unsigned char key[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

    // Ввод строки пользователем
    cout << "Enter a string to encrypt: ";
    getline(cin, user_input);

    unsigned char* data = (unsigned char*)user_input.c_str();
    size_t data_len = user_input.length();  

    int choice;
    cout << "Welcome!\n" << "------------------------------\n";
    cout << "1. RC6\n";
    cout << "2. XTEA\n";
    cout << "3. Hughes\n";
    cout << "0. Exit the program\n"
    << "------------------------------\n";
    cout << "\nSelect the cipher number: ";
    cin >> choice;

    // Использование vector вместо массива
    vector<unsigned char> data_copy(data, data + data_len);

    // Шифрование
    switch (choice) {
        case 1:
            cout << "Encrypting using RC6...\n";
            rc6_encrypt(data_copy.data(), key, data_len);
            break;
        case 2:
            cout << "Encrypting using XTEA...\n";
            xtea_encrypt(data_copy.data(), key, data_len);
            break;
        case 3:
            cout << "Encrypting using Hughes...\n";
            hughes_encrypt(data_copy.data(), key, data_len);
            break;
        default:
            cout << "Invalid choice.\n";
            return 1;
    }

    cout << "Encrypted data: ";
    printHex(data_copy.data(), data_len);

    // Расшифровка
    switch (choice) {
        case 1:
            cout << "Decrypting using RC6...\n";
            rc6_decrypt(data_copy.data(), key, data_len);
            break;
        case 2:
            cout << "Decrypting using XTEA...\n";
            xtea_decrypt(data_copy.data(), key, data_len);
            break;
        case 3:
            cout << "Decrypting using Hughes...\n";
            hughes_decrypt(data_copy.data(), key, data_len);
            break;
        default:
            cout << "Invalid choice.\n";
            return 1;
    }

    cout << "Decrypted data: ";
    printHex(data_copy.data(), data_len);
    cout << "Decrypted text: " << data_copy.data() << endl;

    // Запись в файл (зашифрованный и расшифрованный текст)
    ofstream outfile("encrypted_decrypted_data.txt", ios::binary);
    if (outfile) {
        // Запись зашифрованных данных
        outfile << "Encrypted data (in hex):\n";
        for (size_t i = 0; i < data_len; i++) {
            outfile << hex << setw(2) << setfill('0') << (int)data_copy[i] << " ";
        }
        outfile << endl;

        // Запись расшифрованных данных
        outfile << "\nDecrypted data (in text): " << data_copy.data() << endl;

        cout << "Encrypted and decrypted data saved to 'encrypted_decrypted_data.txt'.\n";
    } else {
        cout << "Error opening file for writing.\n";
    }

    return 0;
}

