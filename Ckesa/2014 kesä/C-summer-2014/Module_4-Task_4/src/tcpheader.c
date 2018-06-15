#include <stdio.h>
#include "tcpheader.h"


int getSourcePort(const unsigned char *tcphdr)
{
    return (tcphdr[0] << 8) + tcphdr[1];
}

int getDestinationPort(const unsigned char *tcphdr)
{
    return (tcphdr[2] << 8) + tcphdr[3];
}

void setSourcePort(unsigned char *tcphdr, int port)
{
    tcphdr[0] = port >> 8;
    tcphdr[1] = port & 0xff;
}

void setDestinationPort(unsigned char *tcphdr, int port)
{
    tcphdr[2] = port >> 8;
    tcphdr[3] = port & 0xff;
}

int getAckFlag(const unsigned char *tcphdr)
{
    return (tcphdr[13] & 0x10) >> 4;
}

void setAckFlag(unsigned char *tcphdr, int flag)
{
    tcphdr[13] = (tcphdr[13] & 0xef) + (flag << 4);
}

int getDataOffset(const unsigned char *tcphdr)
{
    return tcphdr[12] >> 4;
}

void setDataOffset(unsigned char *tcphdr, int offset)
{
    tcphdr[12] = (tcphdr[12] & 0xf) + (offset << 4);
}
