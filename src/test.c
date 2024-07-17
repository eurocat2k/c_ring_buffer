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
    printf("Step 1: After pushed 5 characters. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    // pop off first 3 chars
    Circular_Buf_Pop(cbuf, 3, out);
    printf("Step 2: After popped off 3 characters. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    printf("\tpopped out: [ %.*s ]\n", 3, out);
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    // push another 5 octets
    in[0] = 'F';
    in[1] = 'G';
    in[2] = 'H';
    in[3] = 'I';
    in[4] = 'J';
    Circular_Buf_Push(cbuf, in, 5);
    printf("Step 3: After pushed another 5 characters. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    // pop off first 2 chars
    Circular_Buf_Pop(cbuf, 2, out);
    printf("Step 4: After popped off 2 characters. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    printf("\tpopped out: [ %.*s ]\n", 2, out);
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    // push another 5 characters
    in[0] = 'K';
    in[1] = 'L';
    in[2] = 'M';
    in[3] = 'N';
    in[4] = 'O';
    Circular_Buf_Push(cbuf, in, 5);
    printf("Step 5: After pushed another 5 characters. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    // push another 5 characters
    in[0] = 'P';
    in[1] = 'Q';
    in[2] = 'R';
    in[3] = 'S';
    Circular_Buf_Push(cbuf, in, 4);
    printf("Step 6: And Another 4 characters pushed into. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    // pop off 6 characters
    Circular_Buf_Pop(cbuf, 6, out);
    printf("Step 7: After popped out 6 characters. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    printf("\tpopped out: [ %.*s ]\n", MAX_INPUT, out);
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    // pop off 5 characters
    Circular_Buf_Pop(cbuf, 6, out);
    printf("Step 8: After popped out 6 characters. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    printf("\tpopped out: [ %.*s ]\n", 6, out);
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    // pop off remaining characters
    Circular_Buf_Pop(cbuf, Circular_Buf_GetDataSize(cbuf), out);
    printf("Step 9: After popped out the remaining characters. Size: %zu, Usage: %zu\n", Circular_Buf_GetCapacity(cbuf),
           Circular_Buf_GetDataSize(cbuf));
    printf("\tpopped out: [ %.*s ]\n", 2, out);
    // display content of the buffer
    Circular_Buf_Print(cbuf, false);
    //
    Circular_Buf_Free(cbuf);
    return 0;
}