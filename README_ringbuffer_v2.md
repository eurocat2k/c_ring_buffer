# RING BUFFER VERSION #2 *[(back)](README.md)*

### About test program of the version #2
0. Create a circular buffer object - with its buffer as well - on the heap (size: 16 octets).
1. Push 5 characters into the buffer: *'A'..'E'*. Display buffer's attributes and contents.
2. Pop off 3 characters and print buffer.
3. Push 5 characters into buffer and print.
4. Pop off 2 characters then print.
5-6. Push total 9 characters and print.
7-8. Pop off total 12 characters and print.
9. Pop off the remaining (2) characters and print.
10. Free up cbuffer object, and return from the program.

### Build and run 1st variant
```
cc -O2 -g test1.c circbufmod.c hexdump.c -o test1 && ./test1
```
### Expected output
```
CBUF INFO: [
        TAIL OFFSET = 0
        HEAD OFFSET = 0
        DATA SIZE   = 0
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00  ................                                                      
====== =======================   =======================  ================

]

Step 1: After pushed 5 characters.
CBUF INFO: [
        TAIL OFFSET = 0
        HEAD OFFSET = 5
        DATA SIZE   = 5
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 41 42 43 44 45 00 00 00   00 00 00 00 00 00 00 00  ABCDE...........                                                      
====== =======================   =======================  ================

]

        POPPED OUT DATA: ABC
Step 2: After popped 3 characters.
CBUF INFO: [
        TAIL OFFSET = 3
        HEAD OFFSET = 5
        DATA SIZE   = 2
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 00 00 00 44 45 00 00 00   00 00 00 00 00 00 00 00  ...DE...........                                                      
====== =======================   =======================  ================

]

Step 3: After pushed 5 characters.
CBUF INFO: [
        TAIL OFFSET = 3
        HEAD OFFSET = 10
        DATA SIZE   = 7
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 00 00 00 44 45 46 47 48   49 4A 00 00 00 00 00 00  ...DEFGHIJ......                                                      
====== =======================   =======================  ================

]

        POPPED OUT DATA: DE
Step 4: After popped 2 characters.
CBUF INFO: [
        TAIL OFFSET = 5
        HEAD OFFSET = 10
        DATA SIZE   = 5
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 00 00 00 00 00 46 47 48   49 4A 00 00 00 00 00 00  .....FGHIJ......                                                      
====== =======================   =======================  ================

]

Step 5: After pushed 5 characters.
CBUF INFO: [
        TAIL OFFSET = 5
        HEAD OFFSET = 15
        DATA SIZE   = 10
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 00 00 00 00 00 46 47 48   49 4A 4B 4C 4D 4E 4F 00  .....FGHIJKLMNO.                                                      
====== =======================   =======================  ================

]

Step 6: After pushed 4 characters.
CBUF INFO: [
        TAIL OFFSET = 5
        HEAD OFFSET = 3
        DATA SIZE   = 14
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 51 52 53 00 00 46 47 48   49 4A 4B 4C 4D 4E 4F 50  QRS..FGHIJKLMNOP                                                      
====== =======================   =======================  ================

]

        POPPED OUT DATA: FGHIJK
Step 7: After popped 6 characters.
CBUF INFO: [
        TAIL OFFSET = 11
        HEAD OFFSET = 3
        DATA SIZE   = 8
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 51 52 53 00 00 00 00 00   00 00 00 4C 4D 4E 4F 50  QRS........LMNOP                                                      
====== =======================   =======================  ================

]

        POPPED OUT DATA: LMNOPQ
Step 8: After popped 6 characters.
CBUF INFO: [
        TAIL OFFSET = 1
        HEAD OFFSET = 3
        DATA SIZE   = 2
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 00 52 53 00 00 00 00 00   00 00 00 00 00 00 00 00  .RS.............                                                      
====== =======================   =======================  ================

]

        POPPED OUT DATA: RS
Step 9: After popped 2 characters.
CBUF INFO: [
        TAIL OFFSET = 3
        HEAD OFFSET = 3
        DATA SIZE   = 0
        SIZE MASK   = 0x0F
====== =======================   =======================  ================
OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........
====== =======================   =======================  ================
000000 00 00 00 00 00 00 00 00   00 00 00 00 00 00 00 00  ................                                                      
====== =======================   =======================  ================

]

```

**circbufmod.h** *[(back)](README.md)*
```c
#ifndef __CIRCBUFMOD_H__
#define __CIRCBUFMOD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX
#define MAX(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a > _b ? _a : _b;                                                         \
  })
#endif

#ifndef MIN
#define MIN(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a < _b ? _a : _b;                                                         \
  })
#endif

typedef struct cbuf_mod_t cbuf_mod_t;
typedef cbuf_mod_t *cbuf_mod_handle_t;
/**
 * @brief Constructor, create circular buffer handler object with size parameter which has to
 *        be a 2^N value where N >= 3.
 * 
 * @param size modulo (2 ** N), where N >= 3
 * @return cbuf_mod_handle_t handler object
 */
cbuf_mod_handle_t Circular_Buf_Modulo_Create(size_t size);
/**
 * @brief Reset cbuf attributes
 * 
 * @param cBuf pointer to cbuf object
 */
void Circular_Buf_Modulo_Reset(cbuf_mod_handle_t cBuf);
/**
 * @brief Destructor of the cbuf object
 * 
 * @param cbuf 
 */
void Circular_Buf_Modulo_Free(cbuf_mod_handle_t cbuf);
/**
 * @brief Displays cbuf attribues
 *
 * @param cbuf pointer to cbuf object
 *
 * @param dump boolean, if true hexdumps the entire buffer contents, otherwise
 *             main attributes will be printed out.
 *
 */
void Circular_Buf_Modulo_Display(cbuf_mod_handle_t cbuf, bool dump);
/**
 * @brief Puts one octet into cbuf with head advanced
 * 
 * @param cbuf pointer to cbuf object
 * @param data octet to be stored into the buffer
 */
void Circular_Buf_Modulo_Put(cbuf_mod_handle_t cbuf, uint8_t data);
/**
 * @brief checks if cbuf is full or not
 * 
 * @param cbuf pointer to cbuf object
 * @return true if cbuffer is full
 * @return false otherwise
 */
bool Circular_Buf_Modulo_IsFull(cbuf_mod_handle_t cbuf);
/**
 * @brief checks if buffer is empty or not
 * 
 * @param cbuf pointer to cbuf object
 * @return true if empty
 * @return false otherwise
 */
bool Circular_Buf_Modulo_IsEmpty(cbuf_mod_handle_t cbuf);
/**
 * @brief returns/calculates cbuffer capacity - how many octets are in the
 *        buffer
 * 
 * @param cbuf pointer to cbuf object
 * @return size_t number of octets stored into the buffer
 */
size_t Circular_Buf_Modulo_DataSize(cbuf_mod_handle_t cbuf);
/**
 * @brief store an array of octets into the buffer
 * 
 * @param cbuf pointer to cbuf object
 * @param data pointer to the data array as a source
 * @param nbytes number of bytes to be stored into the buffer
 */
void Circular_Buf_Modulo_Push(cbuf_mod_handle_t cbuf, void *data,
                              size_t nbytes);
/**
 * @brief gets off one octet from buffer
 * 
 * @param cbuf pointer to cbuf object
 * @param dptr pointer destination buffer - pointer to an octet
 * @return true if get success
 * @return false otherwise
 */
bool Circular_Buf_Modular_Get(cbuf_mod_handle_t cbuf, uint8_t *dptr);
/**
 * @brief pops off array of octets from buffer
 * 
 * @param cbuf pointer to the cbuf object
 * @param dst pointer to the destination buffer - allocated by user
 * @param nbytes number of octets to bo popped off
 * @return true if success the operation
 * @return false otherwise
 */
bool Circular_Buf_Modular_Pop(cbuf_mod_handle_t cbuf, void *dst, size_t nbytes);
/**
 * @brief peeks one octet from the range of stored data - tail .. head inclusive
 *        indexes are concerned.
 * 
 * @param cbuf pointer to the cbuf object
 * @param dst destination buffer where the octet will be stored 
 * @param index the position index between head and tail - data size
 * @return true if success the operation
 * @return false otherwise
 */
bool Circular_Buf_Modulo_Peek(cbuf_mod_handle_t cbuf, void *dst,
                                 size_t index);

#ifdef __cplusplus
}
#endif

#endif // __CIRCBUFMOD_H__
```
**circbufmod.c** *[(back)](README.md)*
```c
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
```
*[(back)](README.md)*
