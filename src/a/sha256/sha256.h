#ifndef SHA_256_H
#define SHA_256_H

#include <string>
#include <cstdint>

std::string sha256(const std::string &input);
std::string sha256(const char *data, uint64_t bit_count);

#endif
