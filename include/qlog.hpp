#pragma once

#include <cstdlib>
#include "teestream.hpp"

namespace qlog {

extern TeeStream global_logger;

void set_prefix(const char* prefix);

template <typename ...T>
void log(T && ... args) {
    global_logger.print(std::forward<T>(args)..., '\n');
}

template <typename ...T>
void var(const char* text, T && ... args) {
    global_logger.print(text, " = ");
    global_logger._printcomma(std::forward<T>(args)...);
    global_logger._print('\n');
}

template <typename ...T>
void logtag(char const* tag, T && ... args) {
    char * v = std::getenv(tag);
    if (!v) { return; } // do nothing if environment variable not set
    if (strcmp(v, "1")) { return; } // and the value must be 1
    global_logger.print(std::forward<T>(args)..., '\n');
}

template <typename ...T>
void vartag(const char* tag, const char* text, T && ... args) {
    char * v = std::getenv(tag);
    if (!v) { return; } // do nothing if environment variable not set
    if (strcmp(v, "1")) { return; } // and the value must be 1
    global_logger.print(text, " = ");
    global_logger._printcomma(std::forward<T>(args)...);
    global_logger._print('\n');
}

} // namespace qlog

#define QLOG(...) (qlog::log(__VA_ARGS__))
#define QVAR(...) (qlog::var(#__VA_ARGS__, __VA_ARGS__))
#define QLOGTAG(t, ...) (qlog::logtag((t), __VA_ARGS__))
#define QVARTAG(t, ...) (qlog::vartag((t), (#__VA_ARGS__), __VA_ARGS__))
