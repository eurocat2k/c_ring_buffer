
#ifndef __HEXDUMP_H__
#define __HEXDUMP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void HexDump(const void *src, size_t len);
void HexDump2(const uint8_t *src, size_t len);

#ifdef __cplusplus
}
#endif

#endif // __HEXDUMP_H__
