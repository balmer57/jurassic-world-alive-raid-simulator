#include "logger.h"

#include <cstdio>

bool Logger::on = true;

int Logger::Log(const char fmt[], ...)
{
    va_list va;
    va_start(va, fmt);
    auto r = vprintf(fmt, va);
    va_end(va);
    return r;
}

