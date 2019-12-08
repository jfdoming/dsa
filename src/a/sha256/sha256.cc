#include "sha256.h"

#include <sstream>
#include <iomanip>
#include <climits>
#include <cstring>

using namespace std;

// This implementation used http://www.iwar.org.uk/comsec/resources/cipher/sha256-384-512.pdf
// as a reference.

const size_t BLOCK_SIZE_IN_BITS = 512;
const size_t BLOCK_SIZE_IN_CHARS = BLOCK_SIZE_IN_BITS / CHAR_BIT;
const size_t BLOCK_LENGTH_SIZE_IN_BITS = 64;
const size_t PADDED_BLOCK_MAX_SIZE = BLOCK_SIZE_IN_BITS - BLOCK_LENGTH_SIZE_IN_BITS;
const size_t PADDED_BLOCK_MAX_SIZE_IN_CHARS = PADDED_BLOCK_MAX_SIZE / CHAR_BIT;
const size_t COMPRESS_COUNT = 64;
const size_t WORD_SIZE = 32;

const uint32_t K[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Thanks to https://www.i-programmer.info/programming/cc/12619-fundamental-c-shifts-and-rotates.html?start=1
// for the efficient right rotate implementation.
inline uint32_t ror(uint32_t v, unsigned char n) {
    return v >> n | v << (WORD_SIZE - n);
}

inline uint32_t Ch(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ ((~x) & z);
}

inline uint32_t Maj(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

inline uint32_t Sigma0(uint32_t x) {
    return ror(x, 2) ^ ror(x, 13) ^ ror(x, 22);
}

inline uint32_t Sigma1(uint32_t x) {
    return ror(x, 6) ^ ror(x, 11) ^ ror(x, 25);
}

inline uint32_t sigma0(uint32_t x) {
    return ror(x, 7) ^ ror(x, 18) ^ (x >> 3);
}

inline uint32_t sigma1(uint32_t x) {
    return ror(x, 17) ^ ror(x, 19) ^ (x >> 10);
}

void set_nth_bit(char *buffer, const uint64_t n) {
    const size_t index = n / CHAR_BIT;
    const unsigned char offset = n % CHAR_BIT;
    buffer[index] |= (1u << (CHAR_BIT - offset - 1));
}

void clear_nth_bit(char *buffer, const uint64_t n) {
    const size_t index = n / CHAR_BIT;
    const unsigned char offset = n % CHAR_BIT;
    buffer[index] &= ~(1u << (CHAR_BIT - offset - 1));
}

void write_length(char *buffer, const uint64_t length) {
    size_t iterations = BLOCK_LENGTH_SIZE_IN_BITS / CHAR_BIT;
    for (size_t i = 0; i < iterations; ++i) {
        buffer[i] = length >> (CHAR_BIT * (iterations - i - 1)) & ((1 << CHAR_BIT) - 1);
    }
}

void expanded(const char *block, uint32_t *W) {
    // Initialize the first few parts of W.
    size_t iterations = BLOCK_SIZE_IN_BITS / WORD_SIZE;
    size_t inner_iterations = WORD_SIZE / CHAR_BIT;
    for (size_t i = 0; i < iterations; ++i) {
        W[i] = 0u;
        for (size_t j = 0; j < inner_iterations; ++j) {
            W[i] <<= CHAR_BIT;
            W[i] |= (block[j + (i * inner_iterations)]) & ((1 << CHAR_BIT) - 1);
        }
    }

    // Initialize the rest of W.
    for (size_t i = iterations; i < COMPRESS_COUNT; ++i) {
        W[i] = sigma1(W[i - 2]) + W[i - 7] + sigma0(W[i - 15]) + W[i - 16];
    }
}

void sha256_compress(
        const char *block,
        uint32_t &h1, uint32_t &h2, uint32_t &h3, uint32_t &h4,
        uint32_t &h5, uint32_t &h6, uint32_t &h7, uint32_t &h8
) {
    uint32_t a = h1, b = h2, c = h3, d = h4,
             e = h5, f = h6, g = h7, h = h8;
    uint32_t t1, t2;

    uint32_t W[COMPRESS_COUNT];
    expanded(block, W);

    for (size_t i = 0; i < COMPRESS_COUNT; ++i) {
        t1 = h + Sigma1(e) + Ch(e, f, g) + K[i] + W[i];
        t2 = Sigma0(a) + Maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    // Update the IHVs; the uint32_t type guarantees arithmetic mod 2^32.
    h1 += a;
    h2 += b;
    h3 += c;
    h4 += d;
    h5 += e;
    h6 += f;
    h7 += g;
    h8 += h;
}

string sha256(const string &input) {
    return sha256(input.c_str(), input.length() * CHAR_BIT);
}

string sha256(const char *data, uint64_t bit_count) {
    uint32_t h1 = 0x6a09e667, h2 = 0xbb67ae85,
             h3 = 0x3c6ef372, h4 = 0xa54ff53a,
             h5 = 0x510e527f, h6 = 0x9b05688c,
             h7 = 0x1f83d9ab, h8 = 0x5be0cd19;

    uint64_t total_bit_count = bit_count + BLOCK_LENGTH_SIZE_IN_BITS;
    uint64_t n = (total_bit_count / BLOCK_SIZE_IN_BITS) + 1;
    uint64_t remaining_bits = bit_count;
    bool reached_end = false;

    for (uint64_t i = 0; i < n; ++i) {
        char padded_block[BLOCK_SIZE_IN_CHARS];

        strncpy(padded_block, data + (i * BLOCK_SIZE_IN_CHARS), BLOCK_SIZE_IN_CHARS);

        // strncpy does clear the unset bits; however, it's possible that
        // some extra bits would be in input such that the entirety of
        // padded_block is used. We need to make sure to clear these
        // extra bits.
        for (size_t j = remaining_bits; j < BLOCK_SIZE_IN_BITS; ++j) {
            clear_nth_bit(padded_block, j);
        }

        if (!reached_end && remaining_bits < BLOCK_SIZE_IN_BITS) {
            set_nth_bit(padded_block, remaining_bits);
            reached_end = true;
        }

        if (remaining_bits < PADDED_BLOCK_MAX_SIZE - 1) {
            write_length(padded_block + PADDED_BLOCK_MAX_SIZE_IN_CHARS, bit_count);
            sha256_compress(padded_block, h1, h2, h3, h4, h5, h6, h7, h8);
        } else {
            sha256_compress(padded_block, h1, h2, h3, h4, h5, h6, h7, h8);
        }

        remaining_bits = remaining_bits < BLOCK_SIZE_IN_BITS
            ? 0
            : remaining_bits - BLOCK_SIZE_IN_BITS;
    }

    // Output the result!
    ostringstream oss;
    size_t width = (WORD_SIZE / CHAR_BIT) * 2;
    oss << setfill('0') << hex;
    oss << setw(width) << h1;
    oss << setw(width) << h2;
    oss << setw(width) << h3;
    oss << setw(width) << h4;
    oss << setw(width) << h5;
    oss << setw(width) << h6;
    oss << setw(width) << h7;
    oss << setw(width) << h8;
    return oss.str();
}
