#include "Cryptosystem.h"
#include "hughes.h"
#include "rc6.h"
#include "xtea.h"

const string passwd = "110205";

string FileInput(string &filename) { // �-�� ������ �� �����
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

string FileOutput(string &filename, string &str) { // �-�� ����� � ����
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

void input_and_check(string& message, const string &choice_cipher) { // �-�� ����� ��������� � ���������� � ��� ��������
    cout << "Enter the message: ";
    cin.ignore();
    while (true) {
        getline(cin, message);
        vector<char> errorinput;
        if (choice_cipher == "RC6") {
            errorinput = checkinputrc6(message);
        } else if (choice_cipher == "Hughes") {
            for (char c : message) { //���������� ������ ������
                uc character = static_cast<uc>(c);
                if (toInt(character) < 0) { // ��������� �� ���������� ��������
                    errorinput.push_back(c);
                }
            }
        } else {
            // ��� ����� ������ �������� ����� ���� ����
            errorinput = checkinputXtea(message);
        }
        if (!errorinput.empty()) {
            cout << "Error, invalid characters entered: ";
            for (const auto elem : errorinput) {
                cout << elem << " ";
            }
            cout << endl << "Please try again: ";
        } else {
            if (message == "message") {
                cout << "Message accepted!" << endl;
            }
            break;
        }
    }
}

void Enc_and_Desc(const string &choice_cipher) {
    string message, filename;

    if (choice_cipher == "Hughes") {
        input_and_check(message, "Hughes");
    } else if (choice_cipher == "RC6") {
        input_and_check(message, "RC6");
    } else if (choice_cipher == "XTEA") {
        input_and_check(message, "XTEA");
        // ��������� ������ ��� ����� ������
        generateXteaKeys();
    }
    cout << "Enter the filename to save the message: ";
    cin >> filename;
    FileOutput(filename, message);

    // �������� //
    message = FileInput(filename);
    string Encrypted;
    if (choice_cipher == "RC6") {
        Encrypted = rc6Encryption(message);
    } else if (choice_cipher == "A1Z26") {
        Encrypted = hughesEncryption(message);
    } else if (choice_cipher == "Shamir") {
        Encrypted = xteaEncryption(message);
    }
    cout << "Encrypted message: " << Encrypted << endl;
    cout << "Enter the filename to save the encrypted message: ";
    cin >> filename;
    string check = FileOutput(filename, Encrypted); // ���������� � ����
    if (check != "Completed") {
        cout << "Error, unable to open the file " << filename << "!" << endl;
    } else {
        cout << "Message saved to file " << filename << "!" << endl;

        // ����������� //
        cout << "Decrypt the message? Enter /y/ or /Y/ to confirm: ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            Encrypted.clear();
            cout << "Enter the filename where the encrypted message is stored: ";
            cin >> filename;
            Encrypted = FileInput(filename);
            if (Encrypted != "Error: Unable to open the file") {
                string Decrypted;
                if (choice_cipher == "RC6") {
                    Decrypted = rc6Decrypt(Encrypted);
                } else if (choice_cipher == "Hughes") {
                    Decrypted = hughesDecrypt(Encrypted);
                } else if (choice_cipher == "XTEA") {
                    Decrypted = xteaDecryption(Encrypted);
                }
                cout << "Decrypted message: " << Decrypted << endl;
                cout << "Enter the filename to save the decrypted message: ";
                cin >> filename;
                check = FileOutput(filename, Decrypted); // ���������� � ����
                if (check != "Completed") {
                    cout << "Error, unable to open the file " << filename << "!" << endl;
                } else {
                    cout << "Message saved to file " << filename << "!" << endl;
                }
            } else {
                cout << "Error, unable to open the file " << filename << "!" << endl;
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
            try { // ��������� ������
                cout << "\nSelect the cipher number: ";
                cin >> choice;
                if (cin.fail()) {
                    throw invalid_argument("Enter a number only!");
                }
                break;
            } catch (invalid_argument& ex) { // ����� ������, ������� � ������������ � ����������� ���� ������
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
