#include "Cryptosystem.h"

typedef unsigned char uc;

const int w = 32;                // Размер слова в битах
const int r = 20;                // Количество раундов
const uint32_t Pw = 0xb7e15163;  // Константа P для 32-битного RC6
const uint32_t Qw = 0x9e3779b9;  // Константа Q для 32-битного RC6
vector<uint32_t> S;              // Таблица ключей

// Функция циклического сдвига влево
inline uint32_t ROTL(uint32_t x, uint32_t y) {
    return (x << (y & (w - 1))) | (x >> (w - (y & (w - 1))));
}

// Функция циклического сдвига вправо
inline uint32_t ROTR(uint32_t x, uint32_t y) {
    return (x >> (y & (w - 1))) | (x << (w - (y & (w - 1))));
}

// Инициализация расширенного ключа
void keySchedule(const vector<uint8_t>& key) {
    int c = (key.size() + 3) / 4;
    vector<uint32_t> L(c);

    // Загружаем ключ в массив слов L
    for (int i = key.size() - 1; i >= 0; i--) {
        L[i / 4] = (L[i / 4] << 8) + key[i];
    }

    // Инициализация массива S
    S.resize(2 * r + 4);
    S[0] = Pw;
    for (int i = 1; i < 2 * r + 4; i++) {
        S[i] = S[i - 1] + Qw;
    }

    // Объединение L и S
    uint32_t A = 0, B = 0;
    int i = 0, j = 0;
    int v = 3 * max(c, 2 * r + 4);
    for (int s = 0; s < v; s++) {
        A = S[i] = ROTL(S[i] + A + B, 3);
        B = L[j] = ROTL(L[j] + A + B, (A + B));
        i = (i + 1) % (2 * r + 4);
        j = (j + 1) % c;
    }
}

// Шифрование одного блока данных
void encrypt(uint32_t& A, uint32_t& B, uint32_t& C, uint32_t& D) {
    B += S[0];
    D += S[1];
    for (int i = 1; i <= r; i++) {
        uint32_t t = ROTL(B * (2 * B + 1), 5);
        uint32_t u = ROTL(D * (2 * D + 1), 5);
        A = ROTL(A ^ t, u) + S[2 * i];
        C = ROTL(C ^ u, t) + S[2 * i + 1];
        swap(A, B);
        swap(C, D);
        swap(A, C);
    }
    A += S[2 * r + 2];
    C += S[2 * r + 3];
}

// Расшифровка одного блока данных
void decrypt(uint32_t& A, uint32_t& B, uint32_t& C, uint32_t& D) {
    C -= S[2 * r + 3];
    A -= S[2 * r + 2];
    for (int i = r; i >= 1; i--) {
        swap(A, C);
        swap(C, D);
        swap(A, B);
        uint32_t u = ROTL(D * (2 * D + 1), 5);
        uint32_t t = ROTL(B * (2 * B + 1), 5);
        C = ROTR(C - S[2 * i + 1], t) ^ u;
        A = ROTR(A - S[2 * i], u) ^ t;
    }
    D -= S[1];
    B -= S[0];
}

int main() {
    vector<uint8_t> key = { 0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
    keySchedule(key);

    uint32_t A = 0x01234567;
    uint32_t B = 0x89abcdef;
    uint32_t C = 0xfedcba98;
    uint32_t D = 0x76543210;

    cout << "Original: " << hex << A << " " << B << " " << C << " " << D << endl;

    encrypt(A, B, C, D);
    cout << "Encrypted: " << hex << A << " " << B << " " << C << " " << D << endl;

    decrypt(A, B, C, D);
    cout << "Decrypted: " << hex << A << " " << B << " " << C << " " << D << endl;

    return 0;
}
 

