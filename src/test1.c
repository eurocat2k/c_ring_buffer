#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "circbuf.h"
#include "circbufmod.h"

#define MAX_INPUT 6

int main() {
    uint8_t in[MAX_INPUT] = {0};
    uint8_t out[MAX_INPUT] = {0};

    size_t nbytes = 0;

    cbuf_mod_handle_t cbuf = Circular_Buf_Modulo_Create(15);

    Circular_Buf_Modulo_Display(cbuf, true);

    // push 5 characters into the buffer
    in[0] = 'A';
    in[1] = 'B';
    in[2] = 'C';
    in[3] = 'D';
    in[4] = 'E';
    Circular_Buf_Modulo_Push(cbuf, in, 5);

    Circular_Buf_Modulo_Display(cbuf, true);

    // pop out 3
    Circular_Buf_Modular_Pop(cbuf, out, 3);

    fprintf(stdout, "\tPOPPED OUT DATA: %.*s\n", 3, out);

    Circular_Buf_Modulo_Display(cbuf, true);

    // push another 5 octets
    in[0] = 'F';
    in[1] = 'G';
    in[2] = 'H';
    in[3] = 'I';
    in[4] = 'J';
    Circular_Buf_Modulo_Push(cbuf, in, 5);

    Circular_Buf_Modulo_Display(cbuf, true);

    // pop out 2
    Circular_Buf_Modular_Pop(cbuf, out, 2);

    fprintf(stdout, "\tPOPPED OUT DATA: %.*s\n", 2, out);

    Circular_Buf_Modulo_Display(cbuf, true);

    // push another 5 characters
    in[0] = 'K';
    in[1] = 'L';
    in[2] = 'M';
    in[3] = 'N';
    in[4] = 'O';
    Circular_Buf_Modulo_Push(cbuf, in, 5);

    Circular_Buf_Modulo_Display(cbuf, true);

    // push another 5 characters
    in[0] = 'P';
    in[1] = 'Q';
    in[2] = 'R';
    in[3] = 'S';
    Circular_Buf_Modulo_Push(cbuf, in, 5);

    Circular_Buf_Modulo_Display(cbuf, true);

    // pop out 6
    Circular_Buf_Modular_Pop(cbuf, out, 6);

    fprintf(stdout, "\tPOPPED OUT DATA: %.*s\n", 6, out);

    Circular_Buf_Modulo_Display(cbuf, true);

    // pop out 6
    Circular_Buf_Modular_Pop(cbuf, out, 6);

    fprintf(stdout, "\tPOPPED OUT DATA: %.*s\n", 6, out);

    Circular_Buf_Modulo_Display(cbuf, true);

    // pop out remaining data

    nbytes = Circular_Buf_Modulo_DataSize(cbuf);

        Circular_Buf_Modular_Pop(cbuf, out, nbytes);

    fprintf(stdout, "\tPOPPED OUT DATA: %.*s\n", (int)nbytes, out);

    Circular_Buf_Modulo_Display(cbuf, true);

    // Free cbuf
    Circular_Buf_Modulo_Free(cbuf);

    return 0;
}