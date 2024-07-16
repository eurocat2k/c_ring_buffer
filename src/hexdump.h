#ifndef __HEXDUMP_H__
#define __HEXDUMP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

void HexDump(void *src, size_t len);

#ifdef __cplusplus
}
#endif

#endif // __HEXDUMP_H__