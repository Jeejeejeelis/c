#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include "../src/tcpheader.h"


void print_packet(char *buffer, unsigned char *bytes, unsigned int n)
{
    char b[16];
    buffer[0] = 0;
    for (unsigned int i = 0; i < n; i++) {
        sprintf(b, "%02x ", bytes[i]);
        strcat(buffer, b);
    }
}




START_TEST(test_parsePacket)
{
    unsigned char bytes[] = {
        0x12,0x34,0x45,0x67,0xaa,0xbb,0xcc,0xdd,
        0xee,0xff,0xaa,0xbb,0xb1,0x5c,0x08,0x00,
        0x12,0x34,0x00,0x00 };
    
    char buffer[80];
    print_packet(buffer, bytes, sizeof(bytes));
    
    int port = getSourcePort(bytes);
    fail_unless(getSourcePort(bytes) == 0x1234,
            "[Task 4.4.a] Incorrect getSourcePort(). You %d, reference: %d.\nHeader: %s.",
            port, 0x1234, buffer);
    
    port = getDestinationPort(bytes);
    fail_unless(getDestinationPort(bytes) == 0x4567,
            "[Task 4.4.a] Incorrect getDestinationPort(). You %d, reference: %d.\nHeader: %s.",
            port, 0x4567, buffer);
    
    port = getAckFlag(bytes);
    fail_unless(getAckFlag(bytes) == 1,
            "[Task 4.4.a] Incorrect getAckFlag(). You %d, reference: %d.\nHeader: %s.",
            port, 1, buffer);
    port = getDataOffset(bytes);
    fail_unless(getDataOffset(bytes) == 0xb,
            "[Task 4.4.a] Incorrect getDataOffset(). You %d, reference: %d.\nHeader: %s.",
            port, 0xb, buffer);
    
}
END_TEST


START_TEST(test_setPacket)
{
    unsigned char bytes[] = {
        0x0,0x0,0x0,0x0,0xaa,0xbb,0xcc,0xdd,
        0xee,0xff,0xaa,0xbb,0x01,0x6c,0x08,0x00,
        0x12,0x34,0x00,0x00 };
    
    setSourcePort(bytes, 0x1235);
    fail_unless(bytes[0] == 0x12 && bytes[1] == 0x35,
            "[Task 4.4.b] When setting source port to 0x%04x, byte 0 should be 0x%x (you: %x), byte 1 should be 0x%x (you: %x)",
            0x1234, 0x12, bytes[0], 0x35, bytes[1]);
    
    setDestinationPort(bytes, 0x4568);
    fail_unless(bytes[2] == 0x45 && bytes[3] == 0x68,
            "[Task 4.4.b] When setting destination port to 0x%04x, byte 2 should be 0x%x (you: %x), byte 3 should be 0x%x (you: %x)",
            0x4567, 0x45, bytes[2], 0x68, bytes[3]);
    
    setAckFlag(bytes, 1);
    fail_unless(bytes[13] == 0x7c,
            "[Task 4.4.b] When setting Ack flag to 1, byte 13 should change from 0x6c to 0x7c");

    setDataOffset(bytes, 6);
    fail_unless(bytes[12] == 0x61,
            "[Task 4.4.b] When setting data offset to 6, byte 12 should change from 0x01 to 0x61");
}
END_TEST


int main(int argc, const char *argv[])
{
    srand((unsigned) time(NULL));
    Suite *s = suite_create("Test-4.4");

    tmc_register_test(s, test_parsePacket, "4.4.a");
    tmc_register_test(s, test_setPacket, "4.4.b");
        
    return tmc_run_tests(argc, argv, s);
}
