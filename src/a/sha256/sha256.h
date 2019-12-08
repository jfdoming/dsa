#ifndef SHA_256_H
#define SHA_256_H

#include <string>

std::string sha256(const std::string &input);
std::string sha256(const std::string &input, long long bit_count);

#endif
