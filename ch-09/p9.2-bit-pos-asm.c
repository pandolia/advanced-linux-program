/* p9.2-bit-pos-asm.c
 * Find Bit Position Using a loop */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    long max = atoi(argv[1]);
    int number;
    long i;
    unsigned position;
    volatile unsigned long long result;

    /* Repeat the operation for a large number of values. */
    for (number = 1; number <= max; ++number) {
        /* Compute the position of the most significant set bit
         * using the bsrl assembly instruction. */
        asm("bsrl %1, %0" : "=r" (position) : "r" (number));

        /* The position of the most significant set bit is the
         * number of shifts we needed after the first one. */
        result = position;
    }

    return 0;
}
