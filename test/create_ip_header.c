#include <stdio.h>
#include <stdlib.h>
struct iphdr
{
    unsigned char ihl : 4,
        version : 4;
    unsigned char tos;
    unsigned short tot_len;
    unsigned short id;
    unsigned short frag_off;
    unsigned char ttl;
    unsigned char protocol;
    unsigned short check;
    unsigned int saddr;
    unsigned int daddr;
    /*The options start here. */
};
int main()
{
    FILE *fp = fopen("../packet/ip_packet", "w");
    char buf1[] = {0x45, 0x00, 0x00, 0x40, 0x00, 0xb0, 0x40, 0x00, 0x3c, 0x06,
                   0x58, 0x74, 0xc0, 0xa8, 0x48, 0xd7, 0x0a, 0x0a, 0xc8, 0x0a,
                   0xcb, 0x18, 0x07, 0xe5, 0xaa, 0x74, 0xd7, 0x62, 0x00, 0x00,
                   0x00, 0x00, 0xb0, 0x02, 0xff, 0xff, 0xcf, 0x2d, 0x00, 0x00,
                   0x02, 0x04, 0x05, 0xb4, 0x01, 0x03, 0x03, 0x05, 0x01, 0x01,
                   0x08, 0x0a, 0x43, 0xa8, 0xf3, 0xbd, 0x00, 0x00, 0x00, 0x00,
                   0x04, 0x02, 0x00, 0x00};
    char buf2[] = {0x45, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x00, 0x01, 0x86,
                   0xa9, 0x3f, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                   0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x52, 0x4f, 0x48,
                   0x43, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21};
    
    fwrite(buf2, 1, sizeof(buf2), fp);
    struct iphdr *ips = (struct iphdr *)(buf2);
}