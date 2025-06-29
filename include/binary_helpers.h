#ifndef BINARY_HELPERS_H
#define BINARY_HELPERS_H

#define EXTRACT_BIT(number, bit) ((((uint32_t)1 << bit) & number) >> bit)
#define OVERRIDE_BIT(number, bit, set) ((number & ~((uint32_t)1 << bit)) | set << bit)
#define SET_BIT(number, bit) (number | ((uint32_t)1 << bit))
#define GET_BIT(number, bit) (number & ((uint32_t)1 << bit))
#define CLEAR_LEFT(number, to_clear) ((number << to_clear) >> to_clear)
#define CLEAR_RIGHT(number, to_clear) ((number >> to_clear) << to_clear)

#endif // BINARY_HELPERS_H