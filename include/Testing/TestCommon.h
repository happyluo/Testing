#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <Testing/Config.h>
#include <Util/ColorStream.h>

using namespace Util;

TESTING_BEGIN

inline void testFailed(const char* expresion, const char* file, unsigned int line)
{
    colorostream out(std::cout);
    out.tostd() << fgred << "failed!" << std::endl;
    out.tostd() << file << ": " << line << ": assertion `" << expresion << "' failed!" << std::endl;
    abort();
}

#define test(expresion) ((expresion) ? ((void)0) : TESTING testFailed(#expresion, __FILE__, __LINE__))

TESTING_END

#endif
