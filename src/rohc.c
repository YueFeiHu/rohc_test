#include "rohc.h"
#include <stdio.h>
void *kmalloc(int size, int type)
{
    if (type != GFP_ATOMIC)
    {
        printf("wrong kmalloc type..\n");
        exit(0);
    }
    return malloc(size);
}

unsigned short ip_fast_csum(unsigned char *iph,
                            unsigned int ihl)
{
    unsigned int sum;

    __asm__ __volatile__(" \n\
            movl (%1), %0      \n\
            subl $4, %2		\n\
            jbe 2f		\n\
            addl 4(%1), %0	\n\
            adcl 8(%1), %0	\n\
            adcl 12(%1), %0	\n\
1:          adcl 16(%1), %0	\n\
            lea 4(%1), %1	\n\
            decl %2		\n\
            jne 1b		\n\
            adcl $0, %0		\n\
            movl %0, %2		\n\
            shrl $16, %0	\n\
            addw %w2, %w0	\n\
            adcl $0, %0		\n\
            notl %0		\n\
2:				\n\
            "
            /* Since the input registers which are loaded with iph and ipl
            are modified, we must also specify them as outputs, or gcc
            will assume they contain their original values. */
            : "=r"(sum), "=r"(iph), "=r"(ihl)
            : "1"(iph), "2"(ihl));
    return (sum);
}
#ifdef __linux__
int get_microseconds(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

int get_milliseconds(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
#elif WIN32 
int get_microseconds(void)
{
    return 0;
}

int get_milliseconds(void)
{
    return 0;
}
#endif

void print_packet(const char *packet, size_t packet_size)
{
    int i;
    unsigned char c;
    for (i = 0; i < packet_size; i++)
    {
        if (i != 0 && i % 10 == 0)
        {
            puts("\n");
        }
        c = packet[i];
        printf("0x%02x ", c);
    }
    puts("\n");
}