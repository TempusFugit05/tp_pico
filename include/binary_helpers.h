#ifndef BINARY_HELPERS_H
#define BINARY_HELPERS_H

#define EXTRACT_BIT(number, bit) ((((uint32_t)1 << bit) & number) >> bit)
#define SET_BIT(number, bit, set) ((number & ~((uint32_t)1 << bit)) | (uint32_t)set << bit)

#endif // BINARY_HELPERS_H