/* calling_convention.c
 *
 * A small function with five integer arguments and several locals, used
 * to inspect a real stack frame's prologue/epilogue in the compiled
 * assembly. Five arguments matters: on Windows x64 the first four
 * integer/pointer args pass in registers (rcx, rdx, r8, r9) and the fifth
 * must be passed on the stack, so this function's assembly shows both
 * register-passed and stack-passed arguments.
 */
#include <stdio.h>

long long compute(long long a, long long b, long long c, long long d, long long e) {
    long long local1 = a + b;
    long long local2 = c * d;
    long long local3 = local1 - local2 + e;
    return local3 * 2;
}

int main(void) {
    long long result = compute(10, 20, 3, 4, 5);
    printf("result=%lld\n", result);
    return 0;
}
