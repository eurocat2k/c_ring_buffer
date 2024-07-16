# C ring-buffer
Ring buffer written In C useful ADT for system programming. In my case various TCP clients use this facility to reconstruct segmented data packages.

## 1 Variant

**circbuf.h**
```C
#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <sys/endian.h>

typedef struct circular_buf_t circular_buf_t;
// Handle type, the way users interact with the API
typedef circular_buf_t *cbuf_handle_t;

// Create a new circular buffer handle
extern cbuf_handle_t Circular_Buf_Create(size_t size);

// Destruct circular_buf_t
extern void Circular_Buf_Free(cbuf_handle_t cBuf);

// Initialize system's default circular buffer handle
// extern cbuf_handle_t Circular_Buf_Init(cbuf_handle_t cBuf, void *buf, size_t
// size);

// Reset the circular_buf_t
extern void Circular_Buf_Reset(cbuf_handle_t cBuf);

// get the buffer capacity
extern size_t Circular_Buf_GetCapacity(cbuf_handle_t cBuf);

// get occupied data size of circular_buf_t
extern size_t Circular_Buf_GetDataSize(cbuf_handle_t cBuf);

// Push data to the tail of a circular buffer from 'src' with 'length' size in
// byte.
extern void Circular_Buf_Push(cbuf_handle_t cBuf, void *src, size_t length);

// Pop data from a circular buffer to 'dataOut'  with wished 'length' size in
// byte,return the actual data size in byte popped out,which is less or equal to
// the input 'length parameter.
extern size_t Circular_Buf_Pop(cbuf_handle_t cBuf, size_t length,
                               void *dataOut);

// Read data from a circular buffer to 'dataOut'  with wished 'length' size in
// byte,return the actual data size in byte popped out,which is less or equal to
// the input 'length parameter.
extern size_t Circular_Buf_Read(cbuf_handle_t cBuf, size_t length,
                                void *dataOut);

// for test purpose, print the circular buffer's data content by printf(...);
// the 'hex' parameters indicates that if the data should be printed in asscii
// string or hex data format.
extern void Circular_Buf_Print(cbuf_handle_t cBuf, bool hex);

#ifdef __cplusplus
}
#endif

#endif // __CIRCBUF_H__
```
**circbuf.c**
```C
#include "circbuf.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct circular_buf_t {
    size_t size;       // capacity bytes size
    size_t dataSize;   // occupied data size
    size_t tailOffset; // head offset, the oldest byte position offset
    size_t headOffset; // tail offset, the lastest byte position offset
    void *buffer;
};

// extern cbuf_handle_t Circular_Buf_Init(cbuf_handle_t cBuf, void *buf, size_t
// size) {
//     //
//     size_t totalSize = sizeof(struct circular_buf_t) + size;
//     void *p = malloc(totalSize);
//     cbuf_handle_t buffer = (cbuf_handle_t)p;
//     buffer->buffer = p + sizeof(struct circular_buf_t);
//     buffer->size = size;
//     Circular_Buf_Reset(buffer);
//     return buffer;
// }

extern cbuf_handle_t Circular_Buf_Create(size_t size) {
    size_t totalSize = sizeof(struct circular_buf_t) + size;
    void *p = malloc(totalSize);
    memset(p, 0, totalSize);
    cbuf_handle_t buffer = (cbuf_handle_t)p;
    buffer->buffer = p + sizeof(struct circular_buf_t);
    buffer->size = size;
    Circular_Buf_Reset(buffer);
    return buffer;
}

extern void Circular_Buf_Free(cbuf_handle_t cBuf) {
    Circular_Buf_Reset(cBuf);
    cBuf->size = 0;
    cBuf->dataSize = 0;
    cBuf->buffer = NULL;
    free(cBuf);
}

extern void Circular_Buf_Reset(cbuf_handle_t cBuf) {
    cBuf->headOffset = -1;
    cBuf->tailOffset = -1;
    cBuf->dataSize = 0;
}

extern size_t Circular_Buf_GetCapacity(cbuf_handle_t cBuf) {
    return cBuf->size;
}

extern size_t Circular_Buf_GetSize(cbuf_handle_t cBuf) { return cBuf->size; }

extern size_t Circular_Buf_GetDataSize(cbuf_handle_t cBuf) {
    return cBuf->dataSize;
}

extern void Circular_Buf_Push(cbuf_handle_t cBuf, void *src, size_t length) {
    if (length == 0) {
        return;
    }

    size_t writableLen = length;
    void *pSrc = src;

    if (writableLen > cBuf->size) { // in case of size overflow
        size_t overFlowLen = writableLen - cBuf->size;
        writableLen = cBuf->size;
        pSrc = src + overFlowLen;
    }

    bool resetHead = false;
    // in case the circle buffer won't be full after adding the data
    if (cBuf->tailOffset + writableLen < cBuf->size) {
        memcpy((void *)&cBuf->buffer[(cBuf->tailOffset + 1)], pSrc, writableLen);

        if ((cBuf->tailOffset < cBuf->headOffset) &&
            ((cBuf->tailOffset + writableLen) >= cBuf->headOffset)) {
            resetHead = true;
        }
        cBuf->tailOffset += writableLen;
    } else {    // in case the circle buffer will be overflow after adding the data
        size_t remainSize = cBuf->size - cBuf->tailOffset - 1; // the remain size
        memcpy((void *)&cBuf->buffer[cBuf->tailOffset + 1], pSrc, remainSize);

        size_t coverSize =
            writableLen -
            remainSize; // size of data to be covered from the beginning
        
        memcpy((void *)cBuf->buffer, pSrc + remainSize, coverSize);

        if (cBuf->tailOffset < cBuf->headOffset){
            resetHead = true;
        } else {
            if (coverSize > cBuf->headOffset) {
                resetHead = true;
            }
        }
        cBuf->tailOffset = coverSize - 1;
    }

    if (cBuf->headOffset == -1) {
        cBuf->headOffset = 0;
    }
    if (resetHead) {
        if (cBuf->tailOffset + 1 < cBuf->size) {
            cBuf->headOffset = cBuf->tailOffset + 1;
        } else {
            cBuf->headOffset = 0;
        }
        cBuf->dataSize = cBuf->size;
    } else {
        if (cBuf->tailOffset >= cBuf->headOffset) {
            cBuf->dataSize = cBuf->tailOffset - cBuf->headOffset + 1;
        } else {
            cBuf->dataSize =
                cBuf->size - (cBuf->headOffset - cBuf->tailOffset - 1);
        }
    }
}

size_t inter_circular_buf_read(cbuf_handle_t cBuf, size_t length, void *dataOut,
                               bool resetHead) {
    if (cBuf->dataSize == 0 || length == 0) {
        return 0;
    }

    size_t rdLen = length;

    if (cBuf->dataSize < rdLen) {
        rdLen = cBuf->dataSize;
    }

    if (cBuf->headOffset <= cBuf->tailOffset) {
        if (dataOut) {
            memcpy(dataOut, &cBuf->buffer[cBuf->headOffset], rdLen);
        }

        if (resetHead) {
            cBuf->headOffset += rdLen;
            if (cBuf->headOffset > cBuf->tailOffset) {
                cBuf->headOffset = -1;
                cBuf->tailOffset = -1;
            }
        }
    } else {
        if (cBuf->headOffset + rdLen <= cBuf->size) {
            if (dataOut) {
                memcpy(dataOut, &cBuf->buffer[cBuf->headOffset], rdLen);
            }
            if (resetHead) {
                cBuf->headOffset += rdLen;
                if (cBuf->headOffset == cBuf->size) {
                    cBuf->headOffset = 0;
                }
            }
        } else {
            size_t frg1Len = cBuf->size - cBuf->headOffset;
            if (dataOut) {
                memcpy(dataOut, &cBuf->buffer[cBuf->headOffset], frg1Len);
            }

            size_t frg2len = rdLen - frg1Len;
            if (dataOut) {
                memcpy(dataOut + frg1Len, cBuf->buffer, frg2len);
            }

            if (resetHead) {
                cBuf->headOffset = frg2len;
                if (cBuf->headOffset > cBuf->tailOffset) {
                    cBuf->headOffset = -1;
                    cBuf->tailOffset = -1;
                }
            }
        }
    }

    if (resetHead) {
        cBuf->dataSize -= rdLen;
    }

    return rdLen;
}

extern size_t Circular_Buf_Pop(cbuf_handle_t cBuf, size_t length,
                               void *dataOut) {
    return inter_circular_buf_read(cBuf, length, dataOut, true);
}

extern size_t Circular_Buf_Read(cbuf_handle_t cBuf, size_t length,
                                void *dataOut) {
    return inter_circular_buf_read(cBuf, length, dataOut, false);
}

// print circular buffer's content into str,
extern void Circular_Buf_Print(cbuf_handle_t cBuf, bool hex) {
    char *b = cBuf->buffer;
    size_t cSize = Circular_Buf_GetSize(cBuf);
    char *str = malloc(2 * cSize + 1);

    char c;

    for (size_t i = 0; i < cSize; i++) {
        if (Circular_Buf_GetDataSize(cBuf) == 0) {
            c = '_';
        } else if (cBuf->tailOffset < cBuf->headOffset) {
            if (i > cBuf->tailOffset && i < cBuf->headOffset) {
                c = '_';
            } else {
                c = b[i];
            }
        } else {
            if (i > cBuf->tailOffset || i < cBuf->headOffset) {
                c = '_';
            } else {
                c = b[i];
            }
        }
        if (hex) {
            if (c == '_' || c == '|') {
                sprintf(str + i * 2, "%c|", c);
            } else {
                sprintf(str + i * 2, "%02X|", c);
            }
        } else {

            sprintf(str + i * 2, "%c|", c);
        }
    }

    printf("Circular_Buffer: %s <size %zu dataSize:%zu>\n", str,
            Circular_Buf_GetSize(cBuf), Circular_Buf_GetDataSize(cBuf));

    free(str);
}
```

