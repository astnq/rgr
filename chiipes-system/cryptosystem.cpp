#include "cryptosystem.h"
#include "hughes.h"
#include "rc6.h"
#include "xtea.h"

string FileInput(string &filename) { // Ф-ия вывода из файла
    string str;
    ifstream input;
    input.open(filename);
    if (input.is_open()) {
        getline(input, str);
        input.close();
        return str;
    } else {
        return "Error: Unable to open the file";
    }
}

string FileOutput(string &filename, string &str) { // ф-ия ввода в файл
    ofstream output;
    output.open(filename);
    if (output.is_open()) {
        output << str;
        output.close();
        return "Completed";
    } else {
        return "Error: Unable to open the file";
    }
}

void input_and_check(string& message, string choice_shifr, string message_or_key) { // ф-ия ввода сообщения с клавиатуры и его проверка
    if (message_or_key == "message") {
        cout << "Введите сообщение: ";
    } else {
        cout << "Введите кодовое слово: ";
    }
    cin.ignore();
    while (true) {
        getline(cin, message);
        vector<char> errorinput;
        if (choice_shifr == "Hughes") {
            errorinput = checkinputhughes(message);
        } else {
            errorinput = checkinputrc6(message);
        }
        if (!errorinput.empty()) {
            cout << "Ошибка, введены некорректные символы: ";
            for (auto elem : errorinput) {
                cout << elem << " ";
            }
            cout << endl << "Повторите попытку ввода: ";
        } else {
            if (message_or_key == "message") {
                cout << "Сообщение принято!" << endl;
            } else {
                cout << "Кодовое слово принято!" << endl;
            }
            break;
        }
    }

}



void Enc_and_Desc(const string &choice_shifr) {
    string message, wordkey, filename;
    int key;

    if (choice_shifr == "RC6") {
        input_and_check(message, "rc6", "message");
    } else if (choice_shifr == "XTEA") {
        input_and_check(message, "xtea", "message");
        input_and_check(wordkey, "XTEA", "key");
    } else if (choice_shifr == "Hughes") {
        input_and_check(message, "hughes", "message");
        key = GenerateKey();
    }
    cout << "Enter the filename to save the message: ";
    cin >> filename;
    FileOutput(filename, message);

    // ШИФРОВКА //
    message = FileInput(filename);
    string Encrypted, Descrypted;
    if (choice_shifr == "Hughes") {
        Encrypted = rc6Encryption(message);
    } else if (choice_shifr == "RC6") {
        Encrypted = xteaEncryption(message);
    } else if (choice_shifr == "XTEA") {
        Encrypted = hughesEncDesc(message, key);
    }
    cout << "Encrypted message: " << Encrypted << endl;
    cout << "Enter the filename to save the encrypted message: ";
    cin >> filename;
    string check = FileOutput(filename, Encrypted); // записываем в файл
    if (check != "Completed") {
        cout << "Error, unable to open the file " << filename << "!" << endl;
    } else {
        cout << "Message saved to file " << filename << "!" << endl;

        // Расшифровка //
        cout << "Расшифровать сообщение? Для подтверждения введите /y/ или /Y/: ";
        
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            Encrypted.clear();
            cout << "Введите название файла, в котором хранится зашифрованное сообщение: ";
            cin >> filename;
            Encrypted = FileInput(filename);
            if (Encrypted != "Error: Unable to open the file") {
                if (choice_shifr == "Hughes") {
                    Descrypted = rc6Decryption(Encrypted);
                } else if (choice_shifr == "Vijener") {
                    Descrypted = xteaDecryption(Encrypted);
                } else if (choice_shifr == "Hughes") {
                    Descrypted = hughesEncDesc(Encrypted, key);
                }
                cout << "Расшифрованное сообщение: " << Descrypted << endl;
                cout << "Введите название файла, в котором будет хранится зашифрованный файл: ";
                cin >> filename;
                check = FileOutput(filename, Descrypted); // записываем в файл
                if (check != "Completed") {
                    cout << "Ошибка, невозможно открыть файл " << filename << "!" << endl;
                } else {
                    cout << "Сообщение записано в файл " << filename << "!" << endl;
                }
            } else {
                cout << "Ошибка, невозможно открыть файл " << filename << "!" << endl;
            }
        }
    }
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

    system("cls");
    cout << "\nWelcome!\n" << "------------------------------\n"
         << "1 - Encryption using RC6 cipher\n"
         << "2 - Hughes cipher\n"
         << "3 - Encryption using XTEA algorithm\n"
         << "0 - Exit the program\n"
         << "------------------------------\n";

    while (true) {
        int choice;
        while (true) {
            try { // обработка ошибки
                cout << "\nSelect the cipher number: ";
                cin >> choice;
                if (cin.fail()) {
                    throw invalid_argument("Enter a number only!");
                }
                break;
            } catch (invalid_argument& ex) { // ловим ошибку, выводим её пользователю и запрашиваем ввод заново
                cin.clear();
                cin.ignore();
                cout << "Error: " << ex.what() << endl;
            }
        }

        if (choice == 1) {
            Enc_and_Desc("RC6");
        } else if (choice == 2) {
            Enc_and_Desc("Hughes");
        } else if (choice == 3) {
            Enc_and_Desc("XTEA");
        } else if (choice == 0) {
            cout << "Exiting the program...";
            exit(0);
        } else {
            cout << "Invalid cipher number selected!" << endl;
        }
    }
}
