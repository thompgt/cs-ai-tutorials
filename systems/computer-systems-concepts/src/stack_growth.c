/* stack_growth.c
 *
 * Recurses to a chosen depth, printing the address of a local (stack
 * allocated) buffer at chosen checkpoints, to make stack growth and
 * per-call frame size directly observable instead of just asserted.
 */
#include <stdio.h>
#include <stdlib.h>

void recurse(int depth, int max_depth, int report_every) {
    /* volatile + used so the compiler cannot optimize this local away */
    volatile char local_buffer[256];
    local_buffer[0] = (char)depth;

    if (depth % report_every == 0 || depth == max_depth) {
        printf("depth=%d addr=%p\n", depth, (void *)&local_buffer[0]);
    }
    if (depth >= max_depth) {
        return;
    }
    recurse(depth + 1, max_depth, report_every);
}

int main(int argc, char **argv) {
    int max_depth = argc > 1 ? atoi(argv[1]) : 2000;
    int report_every = argc > 2 ? atoi(argv[2]) : 100;
    recurse(0, max_depth, report_every);
    return 0;
}
