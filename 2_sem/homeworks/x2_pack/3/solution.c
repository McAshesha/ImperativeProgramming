#include <stdio.h>
#include <assert.h>

int main() {
#if defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER)
    printf("Compiler: GCC\n");
#elif defined(__clang__)
    printf("Compiler: clang\n");
#elif defined(__TINYC__)
    printf("Compiler: TCC\n");
#else
    return 1;
#endif

#if defined(__x86_64__) || defined(__x86_64) || defined(__amd64__) || defined(__amd64)
    printf("Bitness: 64\n");
#elif defined(__i386__) || defined(__i386)
    printf("Bitness: 32\n");
#else
    return 1;
#endif

#ifdef NDEBUG
    printf("Asserts: disabled\n");
#else
    printf("Asserts: enabled\n");
#endif

    return 0;
}