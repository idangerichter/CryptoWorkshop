#pragma once
#include <cstdint>

int64_t rdtsc()
{
    int64_t a, d;
    asm volatile("mfence");
    asm volatile("rdtsc" : "=a"(a), "=d"(d));
    a = (d << 32) | a;
    asm volatile("mfence");
    return a;
}

template<typename T>
int64_t probe_timing(T* adrs)
{
    volatile int64_t time;

    asm __volatile__("    mfence             \n"
                     "    lfence             \n"
                     "    rdtsc              \n"
                     "    lfence             \n"
                     "    movl %%eax, %%esi  \n"
                     "    movl (%1), %%eax   \n"
                     "    lfence             \n"
                     "    rdtsc              \n"
                     "    subl %%esi, %%eax  \n"
                     // "    clflush 0(%1)      \n"
                     : "=a"(time)
                     : "c"(adrs)
                     : "%esi", "%edx");
    return time;
}
template<typename T>
void maccess(T* p)
{
    asm volatile("movq (%0), %%rax\n" : : "c"(p) : "rax");
}

template<typename T>
void flush(T* p)
{
    asm volatile("clflush 0(%0)\n" : : "c"(p) : "rax");
}
