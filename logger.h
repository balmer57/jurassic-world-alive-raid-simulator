#ifndef __LOGGER__H__
#define __LOGGER__H__

#include <cstdarg>

class Logger
{
public:
    static bool on;
    static int Log(const char fmt[], ...) __attribute__((format(printf, 1, 2)));
};

#define LOG(...) (Logger::on ? Logger::Log(__VA_ARGS__) : 0)

#endif // __LOGGER__H__
