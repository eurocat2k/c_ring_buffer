#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "circbuf.h"

#define MAX_INPUT   6
#define CBUFSIZE    16

int main(void) {
    uint8_t in[MAX_INPUT] = {0};
    uint8_t out[MAX_INPUT] = {0};
    uint8_t cbuffer[CBUFSIZE] = {0};

    cbuf_handle_t cbuf = Circular_Buf_Create(CBUFSIZE);
    // push 5 characters into the buffer
    in[0] = 'A';
    in[1] = 'B';
    in[2] = 'C';
    in[3] = 'D';
    in[4] = 'E';
    Circular_Buf_Push(cbuf, in, 5);
    // print buffer attributes
    printf("0. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    // pop off first 3 chars
    Circular_Buf_Pop(cbuf, 3, out);
    printf("1. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    printf("\tpopped out: %.*s\n", 3, out);
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    // push another 5 octets
    in[0] = 'F';
    in[1] = 'G';
    in[2] = 'H';
    in[3] = 'I';
    in[4] = 'J';
    Circular_Buf_Push(cbuf, in, 5);
    printf("1. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    // pop off first 2 chars
    Circular_Buf_Pop(cbuf, 2, out);
    printf("2. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    printf("\tpopped out: %.*s\n", 2, out);
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    // push another 5 characters
    in[0] = 'K';
    in[1] = 'L';
    in[2] = 'M';
    in[3] = 'N';
    in[4] = 'O';
    Circular_Buf_Push(cbuf, in, 5);
    printf("3. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    // push another 5 characters
    in[0] = 'P';
    in[1] = 'Q';
    in[2] = 'R';
    in[3] = 'S';
    Circular_Buf_Push(cbuf, in, 4);
    printf("4. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    // pop off 6 characters
    Circular_Buf_Pop(cbuf, 6, out);
    printf("5. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    printf("\tpopped out: %.*s\n", MAX_INPUT, out);
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    // pop off 5 characters
    Circular_Buf_Pop(cbuf, 6, out);
    printf("6. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    printf("\tpopped out: %.*s\n", 6, out);
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    // pop off remaining characters
    Circular_Buf_Pop(cbuf, Circular_Buf_GetDataSize(cbuf), out);
    printf("7. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    printf("\tpopped out: %.*s\n", 2, out);
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    //
    Circular_Buf_Free(cbuf);
    return 0;
}