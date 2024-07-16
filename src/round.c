#include <stdlib.h>

int RoundToMSB(int n) {
    int i = 1;
    while (i <= n) {
        i <<= 1;
    }
    if (abs(n - i) < abs(n - (i >> 1))) {
        return i;
    } else {
        return (n > (i >> 1)) ? i : (i >> 1);
    }
}
