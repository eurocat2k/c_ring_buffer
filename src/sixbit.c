#include <stdio.h>
#include <stdint.h>

/**
SixBit ASCII (used by AIS)[5]
    0	1   2   3	4	5	6	7	8	9   A   B   C	D   E   F
0x  @   A	B	C   D	E	F	G	H	I	J	K	L	M   N	O
1x	P	Q	R	S	T	U	V	W   X	Y	Z	[	\	]	^	_
2x	SP 	!   "	#	$	%	&	'	(	)	*	+   ,	-	.	/
3x	0	1	2	3	4	5   6	7	8	9	:	;	<	=	>	?
 */
static const uint8_t chartab[] =
    "#ABCDEFGHIJKLMNOPQRSTUVWXYZ##### ###############0123456789######";
static const size_t chartab_size = sizeof(chartab) / sizeof(chartab[0]);
/**
 * @brief returns the index of character in the chartab array
 * @param ch the character to be indexed
 * @return index if found, -1 otherwise
 */
int indexOf(int ch) {
    int i = 0;
    for (; i < chartab_size; i += 1) {
        if (ch == chartab[i]) {
            break;
        }
    }
    if (chartab[i] == '#') {
        return -1;
    }
    return i;
}
/**
 * @brief demonstrates ICAO 6-bit encoding, decoding strings
 */
int main(void) {
    uint8_t id[8] = {'M', 'A', 'H', '6', '1', '0', ' ', ' '};
    uint8_t decoded[8] = {0};
    uint8_t encoded[6] = {0};
    //
    printf("chartab_size = %zu\n", chartab_size);
    // encoding
    for (int i = 0, j = 0; i < 8; i += 4, j += 3) {
        encoded[j]     = ((indexOf(id[i]) << 2) | (indexOf(id[i + 1]) & 0x30) >> 4);
        encoded[j + 1] = ((indexOf(id[i + 1]) & 0x0f) << 4 | (indexOf(id[i + 2]) & 0x3f) >> 2);
        encoded[j + 2] = ((indexOf(id[i + 2]) & 0x03) << 6 | indexOf(id[i + 3]));
    }
    printf("encoded:");
    for (int i = 0; i < 6; i += 1) {
        printf("%3.02x", encoded[i]);
    }
    printf("\n");
    // decoding
    for (int i = 0, j = 0; i < 6; i += 3, j += 4) {
      decoded[j] = chartab[encoded[i] >> 2];
      decoded[j + 1] = chartab[(encoded[i] & 0x3) << 4 | (encoded[i + 1] & 0xf0) >> 4];
      decoded[j + 2] = chartab[(encoded[i + 1] & 0x0f) << 2 | (encoded[i + 2] & 0xC0) >> 6];
      decoded[j + 3] = chartab[(encoded[i + 2] & 0x3f)];
    }
    printf("decoded:");
    for (int i = 0; i < 8; i += 1) {
      printf("%3.02x", decoded[i]);
    }
    printf("\n");
    printf("decoded id: %.*s\n", 8, decoded);
    //
    return 0;
}
