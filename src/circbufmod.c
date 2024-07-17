// !! Under construction
#include "circbufmod.h"
#include "hexdump.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <sys/endian.h>

#ifndef MAX_BUFFER_SIZE_64K
#define MAX_BUFFER_SIZE_64K 65536   // 64K
#endif

// Helper function to round up nearest power of two value up to
// MAX_BUFFER_SIZE_64K
int RoundToMSB(int n) {
    int i = 1;
    while (i <= n) {
        i <<= 1;
    }
    if (abs(n - i) < abs(n - (i >> 1))) {
        return i;
    } else {
        return (n > i>>1) ? i : i>>1;
    }
}

struct cbuf_mod_t {
    size_t dataSize;
    size_t sizeMask;
    size_t maxCapacity;
    size_t tail;
    size_t head;
    uint8_t *data;
};

cbuf_mod_handle_t Circular_Buf_Modulo_Create(size_t size) {
    cbuf_mod_handle_t _cbuf = NULL;
    if (size == 0) {
        fprintf(stderr, "Invalid size.");
        return _cbuf;
    }
    size_t _size = (size_t)RoundToMSB((int)size);
    if (_size > MAX_BUFFER_SIZE_64K) {
        fprintf(stderr, "Too big size.");
        return _cbuf;
    }
    // try to allocate
    size_t _totalSize = sizeof(struct cbuf_mod_t) + _size;
    _cbuf = (struct cbuf_mod_t *)malloc(_totalSize);
    if (NULL == _cbuf) {
        perror("Memory alloaction failed");
        return _cbuf;
    }
    Circular_Buf_Modulo_Reset(_cbuf);
    _cbuf->maxCapacity = _size;
    _cbuf->sizeMask = _size - 1;
    _cbuf->data = (void *)(_cbuf + sizeof(struct cbuf_mod_t));
    return _cbuf;
}

void Circular_Buf_Modulo_Reset(cbuf_mod_handle_t cBuf) {
    cBuf->head = 0;
    cBuf->tail = 0;
    cBuf->dataSize = 0;
}

void Circular_Buf_Modulo_Free(cbuf_mod_handle_t cbuf) {
    if (NULL != cbuf) {
        free(cbuf);
    }
}

void Circular_Buf_Modulo_Put(cbuf_mod_handle_t cbuf, uint8_t data) {
    if (Circular_Buf_Modulo_IsFull(cbuf)) {
        cbuf->tail = ((cbuf->head + 1) & cbuf->sizeMask);
    }
    // store data into the buffer at 'head' index
    // *(uint8_t *)(cbuf->data + cbuf->head) = data;
    cbuf->data[cbuf->head] = data;
    // update 'head' index
    cbuf->head = ((cbuf->head + 1) & cbuf->sizeMask);
    Circular_Buf_Modulo_DataSize(cbuf);
}

void Circular_Buf_Modulo_Push(cbuf_mod_handle_t cbuf, void *data,
                              size_t nbytes) {
    uint8_t octet = 0;
    if (nbytes) {
        for (size_t i = 0; i < nbytes; i += 1) {
            octet = *(uint8_t *)(data + i);
            Circular_Buf_Modulo_Put(cbuf, octet);
        }
    }
}

bool Circular_Buf_Modular_Get(cbuf_mod_handle_t cbuf, uint8_t *dptr) {
    if (Circular_Buf_Modulo_IsEmpty(cbuf)) {
        return false;
    }
    *dptr = *(uint8_t *)(cbuf->data + cbuf->tail);
    *(cbuf->data + cbuf->tail) = 0;
    cbuf->tail = ((cbuf->tail + 1) & cbuf->sizeMask);
    return true;
}

bool Circular_Buf_Modular_Pop(cbuf_mod_handle_t cbuf, void *dst,
                              size_t nbytes) {
    if (Circular_Buf_Modulo_IsEmpty(cbuf)) {
        return false;
    }
    uint8_t *data_ptr = (uint8_t *)dst;
    size_t cnt = 0;
    while ((cnt < nbytes) && Circular_Buf_Modular_Get(cbuf, data_ptr)) {
        cnt += 1;
        data_ptr++;
    }
    Circular_Buf_Modulo_DataSize(cbuf);
    if (cnt == nbytes) {
        return true;
    }
    fprintf(stderr, "WARNING: size mismatch detected.\n");
    return false;
}

bool Circular_Buf_Modulo_Peek(cbuf_mod_handle_t cbuf, void *dst,
                                 size_t index) {
    if (Circular_Buf_Modulo_IsEmpty(cbuf)) {
        return false;
    }
    if (index >= Circular_Buf_Modulo_DataSize(cbuf)) {
        return false;
    }
    size_t data_index = ((cbuf->tail + index) & cbuf->sizeMask);
    *(uint8_t *)dst = *(uint8_t *)(cbuf->data + data_index);
    return true;
}

bool Circular_Buf_Modulo_IsFull(cbuf_mod_handle_t cbuf) {
    return (((cbuf->head - cbuf->tail) & cbuf->sizeMask) == cbuf->sizeMask);
}

bool Circular_Buf_Modulo_IsEmpty(cbuf_mod_handle_t cbuf) {
    return cbuf->tail == cbuf->head;
}

size_t __Data_Size(cbuf_mod_handle_t cbuf) {
    cbuf->dataSize = ((cbuf->head - cbuf->tail) & cbuf->sizeMask);
    return cbuf->dataSize;
}



size_t Circular_Buf_Modulo_DataSize(cbuf_mod_handle_t cbuf) {
    return __Data_Size(cbuf);
}

void Circular_Buf_Modulo_Display(cbuf_mod_handle_t cbuf, bool dump) {
    fprintf(stdout, "CBUF INFO: [\n");
    fprintf(stdout, "\tTAIL OFFSET = %zu\n", cbuf->tail);
    fprintf(stdout, "\tHEAD OFFSET = %zu\n", cbuf->head);
    fprintf(stdout, "\tDATA SIZE   = %zu\n", cbuf->dataSize);
    fprintf(stdout, "\tSIZE MASK   = 0x%02lX\n", cbuf->sizeMask);
    if (cbuf->maxCapacity <= 32) {
        // do not care dump at all, simply display all attributes and the buffer
        // contents as well.
        if (dump) {
            HexDump(cbuf->data, cbuf->maxCapacity);
        } else {
            fprintf(stdout, "\tDATA:");
            for (int i = 0; i < (int)cbuf->maxCapacity; i += 1) {
                fprintf(stdout, "[%02x]", *(uint8_t *)(cbuf->data + i));
            }
            fprintf(stdout, "\n");
        }
    } else {
        if (dump) {
            HexDump(cbuf->data, cbuf->maxCapacity);
        }
    }
    fprintf(stdout, "]\n\n");
}