#include "logger.h"

#include <cstdio>

int Logger::level = LOG_LEVEL_DEBUG;

int Logger::Log(const char fmt[], ...)
{
    va_list va;
    va_start(va, fmt);
    auto r = vprintf(fmt, va);
    va_end(va);
    return r;
}

