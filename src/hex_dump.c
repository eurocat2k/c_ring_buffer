#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdint.h>
#include <ctype.h>

void HexDump(const void *src, size_t nbytes) {
    uint8_t *data = (uint8_t *)src;
    size_t i, j, k;
    uint8_t ch;
    printf("%-8s  00 01 02 03 04 05 06 07  08 09 0a 0b 0c 0d 0e 0f  %-16s\n", "Address", "Ascii");
    printf("%8s  =======================  =======================  %16s\n",
           "========", "================");
    for (i = 0; i < nbytes; i++)
    {
        if ((i % 16) == 0) {
            printf("%08lx", i);
        }
        if ((i % 8) == 0) {
            printf(" ");
        }
        // ch = data[i];
        printf("%3.02x", data[i]);

        if (((i % 16) == 15) || (i == nbytes - 1)) {

            for (j = 0; j < 15 - (i % 16); j++) {
                printf("   ");
            }

            printf(" |");
            k = 15;
            for (j = (i - (i % 16)); j <= i; j++, k--) {
                if ((data[i] >= 0x21) && (data[i] <= 0x7e)) {
                    printf("%c", data[i]);
                } else {
                    printf("%c", '.');
                }
            }

            if (k > 0 && k < 15) {
                for (k += 1; k > 0; k--) {
                    printf(" ");
                }
            }

            printf("|\n");
        }
    }
    printf("%8s  =======================  =======================  %16s\n",
           "========", "================");
    return;
}

// int main(void) {
//     uint8_t buffer[27];
//     HexDump(buffer, 27);
//     return 0
