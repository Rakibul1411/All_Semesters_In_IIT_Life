#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <iomanip>

using namespace std;

#define BUFFER_COUNT 8
#define SHA_512_INPUT_REPRESENTATION_LENGTH 128
#define BLOCK_SIZE 1024
#define WORD_LENGTH 64
#define ROUND_COUNT 80
//#define BOUNDARY 0xFFFFFFFFFFFFFFFF

//vector<uint64_t> sha512(const string& user_input);

uint64_t rotr64(uint64_t x, uint64_t n) {
    return ((x >> n) | (x << (64 - n)));
}

string sha512Padding(const string& user_input) {
    string finalPlainText;

    for (char c : user_input) {
        finalPlainText += bitset<8>(c).to_string();
    }

    finalPlainText += '1';
    size_t plainTextSize = user_input.length() * 8;
    size_t numberOfZeros = BLOCK_SIZE - ((plainTextSize + SHA_512_INPUT_REPRESENTATION_LENGTH + 1) % BLOCK_SIZE);
    finalPlainText += string(numberOfZeros, '0');
    finalPlainText += bitset<SHA_512_INPUT_REPRESENTATION_LENGTH>(plainTextSize).to_string();
    return finalPlainText;
}

uint64_t get_word(const string& string) {
    return bitset<WORD_LENGTH>(string).to_ullong();
}

vector<uint64_t> sha512(const string& user_input) {
    vector<uint64_t> buffers = {
            0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
            0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
    };

    vector<uint64_t> Round_Constants = {
            0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538,
            0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe,
            0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
            0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
            0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab,
            0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
            0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed,
            0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
            0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
            0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
            0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373,
            0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
            0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c,
            0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6,
            0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
            0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
    };

    string user_input_padded = sha512Padding(user_input);

    for (size_t i = 0; i < user_input_padded.length(); i += BLOCK_SIZE) {
        string currentBlock = user_input_padded.substr(i, BLOCK_SIZE);
        vector<uint64_t> w(ROUND_COUNT, 0);
        for (size_t j = 0; j < 16; ++j) {
            w[j] = get_word(currentBlock.substr(j * WORD_LENGTH, WORD_LENGTH));
        }

        for (size_t j = 16; j < 80; ++j) {
            uint64_t sigma0 = (rotr64(w[j - 15], 1)) ^ (rotr64(w[j - 15], 8)) ^ (w[j - 15] >> 7);
            uint64_t sigma1 = (rotr64(w[j - 2], 19)) ^ (rotr64(w[j - 2], 61)) ^ (w[j - 2] >> 6);
            w[j] = (w[j - 16] + sigma0 + w[j - 7] + sigma1) ;
        }

        uint64_t a, b, c, d, e, f, g, h;
        tie(a, b, c, d, e, f, g, h) = make_tuple(buffers[0], buffers[1], buffers[2], buffers[3], buffers[4], buffers[5], buffers[6], buffers[7]);

        for (size_t j = 0; j < ROUND_COUNT; ++j) {
            uint64_t sum0 = (rotr64(a, 28)) ^ (rotr64(a, 34)) ^ (rotr64(a, 39));
            uint64_t sum1 = (rotr64(e, 14)) ^ (rotr64(e, 18)) ^ (rotr64(e, 41));
            uint64_t ch = (e & f) ^ ((~e) & g);
            uint64_t maj = (a & b) ^ (a & c) ^ (b & c);

            uint64_t temp1 = (h + ch+ sum1 + w[j] + Round_Constants[j]) ;
            uint64_t temp2 = (sum0 + maj) ;

            h = g;
            g = f;
            f = e;
            e = (d + temp1) ;
            d = c;
            c = b;
            b = a;
            a = (temp1 + temp2) ;
        }

        buffers[0] = (buffers[0] + a) ;
        buffers[1] = (buffers[1] + b) ;
        buffers[2] = (buffers[2] + c) ;
        buffers[3] = (buffers[3] + d) ;
        buffers[4] = (buffers[4] + e) ;
        buffers[5] = (buffers[5] + f) ;
        buffers[6] = (buffers[6] + g) ;
        buffers[7] = (buffers[7] + h) ;
    }

    return buffers;
}

int main() {
    string inputText;
    cout << "Enter the string to Hash: ";
    getline(cin, inputText);
    vector<uint64_t> hashValue = sha512(inputText);
    cout << "Calculated Hash Value is: " << endl;
    for(uint64_t ch: hashValue){
        cout << hex << setfill('0') << setw(16) << ch;
    }
    cout << endl;
    return 0;
}
