#include "xtea.cpp"
#include "rc6.cpp"
#include "hughes.cpp"
#include "Cryptosystem.h"

using namespace std;

// Функция для вывода данных в шестнадцатеричном формате
void printHex(const unsigned char* data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        cout << hex << setw(2) << setfill('0') << static_cast<int>(data[i]) << " ";
    }
    cout << endl;
}

// RC6
void rc6_encrypt(unsigned char* data, unsigned char* key, size_t data_len) {
    for (size_t i = 0; i < data_len; i++) {
        data[i] ^= key[i % 16]; // РџСЂРѕСЃС‚РѕР№ XOR СЃ РєР»СЋС‡РѕРј
    }
}

void rc6_decrypt(unsigned char* data, unsigned char* key, size_t data_len) {
    for (size_t i = 0; i < data_len; i++) {
        data[i] ^= key[i % 16]; // РџСЂРѕСЃС‚РѕР№ XOR СЃ РєР»СЋС‡РѕРј (РѕР±СЂР°С‚РЅР°СЏ РѕРїРµСЂР°С†РёСЏ)
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
    uint32_t sum = 0xC6EF3720; // РќР°С‡Р°Р»СЊРЅРѕРµ Р·РЅР°С‡РµРЅРёРµ СЃСѓРјРјС‹ РґР»СЏ СЂР°СЃС€РёС„СЂРѕРІРєРё
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

// РђР»РіРѕСЂРёС‚Рј Hughes
void hughes_encrypt(unsigned char* data, unsigned char* key, size_t data_len) {
    for (size_t i = 0; i < data_len; i++) {
        data[i] = (data[i] + key[i % 16]) % 256; // РџСЂРѕСЃС‚Р°СЏ РѕРїРµСЂР°С†РёСЏ СЃ РєР»СЋС‡РѕРј
    }
}

void hughes_decrypt(unsigned char* data, unsigned char* key, size_t data_len) {
    for (size_t i = 0; i < data_len; i++) {
        data[i] = (data[i] - key[i % 16] + 256) % 256; // РћР±СЂР°С‚РЅР°СЏ РѕРїРµСЂР°С†РёСЏ (РІС‹С‡РёС‚Р°РЅРёРµ)
    }
}
// Функция для считывания содержимого файла
string FileInput(const string& filename) {
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        return "Error: Unable to open the file";
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

// Функция для записи в файл
string FileOutput(const string& filename, const string& content) {
    ofstream file(filename, ios::out | ios::binary);
    if (!file.is_open()) {
        return "Error: Unable to open the file";
    }
    file.write(content.c_str(), content.size());
    file.close();
    return "Completed";
}

int main() {
    system("cls");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));

    string password;
    cout << "Enter the password: ";
    cin >> password;
    if (password != passwd) {
        cout << "Incorrect password! Try again: ";
        cin >> password;
        if (password != passwd) {
            cout << "You are entering the wrong password! Last attempt: ";
            cin >> password;
            if (password != passwd) {
                cout << "All attempts used! Exiting the program...";
                exit(0);
            }
        }
    }

    unsigned char key[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    
    while (true) {
        // Выбор алгоритма шифрования
        cout << "\nWelcome!\n";
        cout << "------------------------------\n";
        cout << "1. RC6\n";
        cout << "2. XTEA\n";
        cout << "3. Hughes\n";
        cout << "0. Exit the program\n";
        cout << "------------------------------\n";
        cout << "\nSelect the cipher number: ";
        
        int algorithm_choice;
        cin >> algorithm_choice;

        if (algorithm_choice == 0) {
            cout << "See you next time\n";
            cout << "Exiting the program...\n";
            break;
        }

        if (algorithm_choice < 1 || algorithm_choice > 3) {
            cout << "Invalid choice. Please choose a valid number.\n";
            continue;
        }

        char action_choice;
        cout << "Encrypt or decrypt? (e/d): ";
        cin >> action_choice;

        if (action_choice != 'e' && action_choice != 'd') {
            cout << "Invalid choice, please enter 'e' for encrypt or 'd' for decrypt.\n";
            continue;
        }

        if (action_choice == 'e') {
            // Шифрование
            string user_input;
            cout << "Enter the string to encrypt: ";
            cin.ignore();  // Сбросить оставшийся символ новой строки в буфере ввода
            getline(cin, user_input);  // Ввод строки для шифрования

            unsigned char* data = (unsigned char*)user_input.c_str();
            size_t data_len = user_input.length();

            // Шифрование с выбранным алгоритмом
            if (algorithm_choice == 1) {
                cout << "Encrypting using RC6...\n";
                rc6_encrypt(data, key, data_len);
            } else if (algorithm_choice == 2) {
                cout << "Encrypting using XTEA...\n";
                xtea_encrypt(data, key, data_len);
            } else if (algorithm_choice == 3) {
                cout << "Encrypting using Hughes...\n";
                hughes_encrypt(data, key, data_len);
            }

            cout << "Encrypted data: ";
            printHex(data, data_len);

            // Сохраняем зашифрованные данные в новый файл
            string encrypted_filename;
            cout << "Enter the filename to save encrypted data: ";
            cin >> encrypted_filename;
            FileOutput(encrypted_filename, user_input);  // Запись в файл
            cout << "Encrypted data successfully saved to '" << encrypted_filename << "'\n";

            // Запрос на расшифровку
            char decrypt_choice;
            cout << "Do you want to decrypt this file? (y/n): ";
            cin >> decrypt_choice;
            
            if (decrypt_choice == 'y' || decrypt_choice == 'Y') {
                // Расшифровка того же файла
                string encrypted_data = FileInput(encrypted_filename);
                if (encrypted_data.find("Error") != string::npos) {
                    cout << encrypted_data << endl;
                    continue;
                }

                unsigned char* data = (unsigned char*)encrypted_data.c_str();
                size_t data_len = encrypted_data.length();

                // Расшифровываем с выбранным алгоритмом
                if (algorithm_choice == 1) {
                    cout << "Decrypting using RC6...\n";
                    rc6_decrypt(data, key, data_len);
                } else if (algorithm_choice == 2) {
                    cout << "Decrypting using XTEA...\n";
                    xtea_decrypt(data, key, data_len);
                } else if (algorithm_choice == 3) {
                    cout << "Decrypting using Hughes...\n";
                    hughes_decrypt(data, key, data_len);
                }

                cout << "Decrypted data: ";
                printHex(data, data_len);
                cout << "Decrypted text: " << data << endl;

                // Сохраняем расшифрованные данные в новый файл
                string decrypted_filename;
                cout << "Enter the filename to save decrypted data: ";
                cin >> decrypted_filename;
                FileOutput(decrypted_filename, string((char*)data, data_len));  // Запись в файл
                cout << "Decrypted data successfully saved to '" << decrypted_filename << "'\n";
            }
        }

        // Запрос на повторение действия
        char continue_choice;
        cout << "Do you want to switch to other ciphers? (y/n): ";
        cin >> continue_choice;
        if (continue_choice != 'y' && continue_choice != 'Y') {
            cout << "See you next time\n";
            cout << "Exiting the program...\n";
            break;
        }
    }

    return 0;
}
