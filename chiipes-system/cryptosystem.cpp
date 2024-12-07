int main() {
    system("cls");
    srand(time(0));

    string password;
    cout << "Enter the password: ";
    cin >> password;

    // Проверка пароля
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

    string user_input;
    unsigned char key[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

    while (true) {
        int choice;
        cout << "\nWelcome!\n" << "------------------------------\n";
        cout << "1. RC6\n";
        cout << "2. XTEA\n";
        cout << "3. Hughes\n";
        cout << "0. Exit the program\n";
        cout << "------------------------------\n";
        cout << "\nSelect the cipher number: ";
        cin >> choice;

        if (choice < 0 || choice > 3) {
            cout << "Error: No such cipher number! Please enter a valid number (1, 2, 3, or 0 to exit).\n";
            continue;
        }

        if (choice == 0) {
            cout << "Exiting the program...\n";
            break;
        }

        cout << "Enter a string to encrypt: ";
        cin.ignore();
        getline(cin, user_input);

        unsigned char* data = (unsigned char*)user_input.c_str();
        size_t data_len = user_input.length();

        vector<unsigned char> data_copy(data, data + data_len);

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
                continue;
        }

        cout << "Encrypted data: ";
        printHex(data_copy.data(), data_len);

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
                continue;
        }

        cout << "Decrypted data: ";
        printHex(data_copy.data(), data_len);
        cout << "Decrypted text: " << data_copy.data() << endl;

        // *** Новая часть: выбор файла для сохранения данных ***
        string filename;
        cout << "Enter the filename to save encrypted and decrypted data: ";
        cin >> filename;

        // Открываем файл в режиме записи с заменой содержимого
        ofstream file(filename, ios::trunc);  // <-- Изменено на ios::trunc
        if (file) {
            // Сохраняем зашифрованные данные
            file << "Encrypted data (in hex):\n";
            for (size_t i = 0; i < data_len; i++) {
                file << hex << setw(2) << setfill('0') << (int)data_copy[i] << " ";
            }
            file << "\n\n";

            // Сохраняем расшифрованные данные
            file << "Decrypted data (in text):\n" << data_copy.data() << "\n\n";
            file.close();

            cout << "Encrypted and decrypted data successfully saved to '" << filename << "'.\n";
        } else {
            cout << "Error opening file for writing.\n";
        }
    }

    return 0;
}
