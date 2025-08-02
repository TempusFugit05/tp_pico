#ifndef TP_DEBUG_H
#define TP_DEBUG_H

#include <pico/time.h>
#include <cstdio>

namespace tp
{

    void tp_assert(const bool assertion, const char* const expression, const char* const file, const unsigned int line);
    void tp_assert(const bool assertion, const char* const expression, const char* const file, const unsigned int line, const char* const message, ...);

    #define TP_ASSERT(expression) tp::tp_assert(expression, #expression, __FILE__, __LINE__)
    #define TP_ASSERT_MSG(expression, message, ...) tp::tp_assert(expression, #expression, __FILE__, __LINE__, message, ## __VA_ARGS__)

} // namespace tp

#endif // TP_DEBUG_H