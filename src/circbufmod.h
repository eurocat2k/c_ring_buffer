// !! Under construction
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

#endif  /* __CIRCBUFMOD_H__ */
