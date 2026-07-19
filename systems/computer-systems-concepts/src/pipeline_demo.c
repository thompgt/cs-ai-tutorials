/* pipeline_demo.c
 *
 * A tiny C program used to walk through the compilation pipeline:
 * preprocessing (-E), compilation to assembly (-S), assembling to an
 * object file (-c), and linking to a final executable.
 */
#include <stdio.h>

/* A macro: the preprocessor will textually substitute SQUARE(x) with
 * ((x) * (x)) wherever it is used, before the compiler proper ever runs. */
#define SQUARE(x) ((x) * (x))

int add(int a, int b) {
    return a + b;
}

int main(void) {
    int x = 5;
    int y = SQUARE(x);      /* becomes ((x) * (x)) after preprocessing */
    int z = add(x, y);
    printf("x=%d y=%d z=%d\n", x, y, z);
    return 0;
}
