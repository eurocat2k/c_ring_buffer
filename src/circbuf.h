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