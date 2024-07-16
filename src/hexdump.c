#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/endian.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#ifndef ASCII_BUF_SIZE
#define ASCII_BUF_SIZE  16
#endif // ASCII_BUF_SIZE

void HexDump(void *src, size_t len) {
    bool odd = true;
    char ch;
    size_t offset = 0, size = len, left = size;
    uint8_t *data = (uint8_t *)src, asciibuf[ASCII_BUF_SIZE + 1] = {0};
    int lencnt = 0, index = 0;

    // header
    //               00000 4C 6F 72 65 6D 20 49 70   73 75 6D 20 69 73 20 73  Lorem Ipsum is s
    fprintf(stdout, "====== =======================   =======================  ================\n");
    fprintf(stdout, "OFFSET 00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F  ASCII...........\n");
    fprintf(stdout, "====== =======================   =======================  ================\n");
    fprintf(stdout, "%06X", (unsigned)offset);

    // outer loop
    for (size_t i = 0; i < size; i += 1, left -= 1) {
        ch = *(data + i);
        asciibuf[index++] = ch;
        fprintf(stdout, "%3.02X", ch);
        lencnt += 1;
        if (((i + 1) % 8) == 0) {
            if (odd) {
                fprintf(stdout, "  ");
                odd = false;
            } else {
                index = 0;
                offset += 16;
                fprintf(stdout, "  ");
                for (int k = 0; k < 16; k += 1) {
                    if (isalnum(asciibuf[k]) ||
                        ispunct(asciibuf[k]) ||
                        isspace(asciibuf[k])) {
                        fprintf(stdout, "%c", asciibuf[k]);
                    } else {
                        fprintf(stdout, ".");
                    }
                }
                fprintf(stdout, "\n%06X", (unsigned)offset);
                odd = true;
                lencnt = 0;
            }
        }
        //
    }

    // PRINT OUT REMAINIG CHARACTERS FROM BUFFER AND FILL UP THE ASCII TAB
    int rem = ASCII_BUF_SIZE - lencnt;

    for (int i = rem; i > 0; i -= 1) {
        if (rem == 8) {
            fprintf(stdout, "   ");
        } else {
            if (i % 8 == 0) {
                fprintf(stdout, "     ");
            } else {
                fprintf(stdout, "   ");
            }
        }
    }

    fprintf(stdout, "  ");

    for (int k = 0; k < lencnt; k += 1) {
        if (isalnum(asciibuf[k]) || ispunct(asciibuf[k]) ||
            isspace(asciibuf[k])) {
            fprintf(stdout, "%c", asciibuf[k]);
        } else {
            fprintf(stdout, ".");
        }
    }

    fprintf(stdout, "\n====== =======================   =======================  ================\n\n");
}