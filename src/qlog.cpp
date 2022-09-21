#include <iostream>
#include "teestream.hpp"
#include "qlog.hpp"

namespace qlog {

TeeStream global_logger(std::cout);

void set_prefix(const char* prefix) {
    qlog::global_logger.set_prefix(prefix);
}

} // namespace qlog
