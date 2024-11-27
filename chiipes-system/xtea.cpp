#include "Cryptosystem.h"

const uint32_t NUM_ROUNDS = 32;
const uint32_t DELTA = 0x9E3779B9;

void xteaEncryption(uint32_t v[2], const uint32_t key[4]) {
    uint32_t v0 = v[0], v1 = v[1];
    uint32_t sum = 0;
    for (uint32_t i = 0; i < KP_ROUNDS; i++) {
        v0 += ((v1 << 4 ^ v1 >> 5) + v1) ^ (sum + key[sum & 3]);
        sum += DELTA;
        v1 += ((v0 << 4 ^ v0 >> 5) + v0) ^ (sum + key[(sum >> 11) & 3]);
    }
    v[0] = v0;
    v[1] = v1;
}

void xteaDecryption(uint32_t v[2], const uint32_t key[4]) {
    uint32_t v0 = v[0], v1 = v[1];
    uint32_t sum = DELTA * KP_ROUNDS;
    for (uint32_t i = 0; i < KP_ROUNDS; i++) {
        v1 -= ((v0 << 4 ^ v0 >> 5) + v0) ^ (sum + key[(sum >> 11) & 3]);
        sum -= DELTA;
        v0 -= ((v1 << 4 ^ v1 >> 5) + v1) ^ (sum + key[sum & 3]);
    }
    v[0] = v0;
    v[1] = v1;
}

vector<uint32_t> text_to_blocks(const string& text) {
    vector<uint32_t> blocks;
    for (size_t i = 0; i < text.size(); i += 8) {
        uint32_t block[2] = { 0, 0 };
        memcpy(block, text.data() + i, min(size_t(8), text.size() - i));
        blocks.push_back(block[0]);
        blocks.push_back(block[1]);
    }
    return blocks;
}

string blocks_to_text(const vector<uint32_t>& blocks) {
    string text;
    for (size_t i = 0; i < blocks.size(); i += 2) {
        char block[8] = { 0 };
        uint32_t tmp[2] = { blocks[i], blocks[i + 1] };
        memcpy(block, tmp, 8);
        text.append(block, 8);
    }
    return text;
}
