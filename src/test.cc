#include "test.h"

void _log_prefix(std::ostringstream &oss, const char *file, int line) {
    oss << "\t" << "at " << file << ":" << line << ": ";
}
