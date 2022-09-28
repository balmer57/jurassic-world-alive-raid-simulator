#ifndef __STRPRINTF__H__
#define __STRPRINTF__H__

#include <string>

std::string strprintf(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

#endif // __STRPRINTF__H__
