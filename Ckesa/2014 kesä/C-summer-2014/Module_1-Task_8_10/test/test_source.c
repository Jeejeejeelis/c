#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../src/source.h"



// STUB here
START_TEST(test_ascii_chart) {
char stu[2048];
char mod[2048] = " 28 0x1c ?	 29 0x1d ?	 30 0x1e ?	 31 0x1f ?\n 32 0x20  	 33 0x21 !	 34 0x22 \"	 35 0x23 #\n 36 0x24 $	 37 0x25 %	 38 0x26 &";
int start = 28;
int num = 10;
freopen("mockoutput", "w", stdout);
ascii_chart(start, start + num);
read_stdout(stu, 2048);

char infostr[100] = "";
if (mycompare(stu, mod, infostr, 1)) {
fail("[Task 1.8] Called ascii_chart(%d, %d). Your output:\n%s\nReference output:\n%s\nReason: %s\n",
start, start + num, stu, mod, infostr);
}
}
END_TEST


// STUB goes here
START_TEST(test_secret_msg) {
char *mod[2] = {
"what's up?",
"This is another secret message"
};
for (int i = 0; i < 2; i++) {
char stu[2048];
freopen("mockoutput", "w", stdout);
secret_msg(i);
read_stdout(stu, 2048);

char infostr[100] = "";
if (mycompare(stu, mod[i], infostr, 1)) {
fail("[Task 1.9] Called secret_msg with string '%s'. Your output:\n%s\nReference output:\n%s\nReason: %s\n",
msgs[i], stu, mod[i], infostr);
}
}
}
END_TEST


void calc_helper(char *str)
{
    FILE *mock_input = freopen("mockinput", "w+", stdin);
    fputs(str, mock_input);
    fseek(mock_input, 0, SEEK_SET);
}

START_TEST(test_calculator)
{
    char buf[80];
    float a, b;
    a = (float)(rand() % 100 + 1) / 10;
    b = (float)(rand() % 100 + 1) / 10;    
    sprintf(buf, "%.1f - %.1f", a, b);
    calc_helper(buf);
    float stu = calculator();
    float mod = a - b;
    fail_unless(stu == mod, "[Task 1.10] With input \"%s\" calculator() returned %f. Should have returned %f.",
            buf, stu, mod);
    
    a = (float)(rand() % 100 + 1) / 10;
    b = (float)(rand() % 100 + 1) / 10;
    float c = (float)(rand() % 100 + 1) / 10;
    sprintf(buf, "%.1f + (%.1f * %.1f)", a, b, c);
    calc_helper(buf);
    stu = calculator();
    mod = a + (b * c);
    fail_unless(stu == mod, "[Task 1.10] With input \"%s\" calculator() returned %f. Should have returned %f.",
            buf, stu, mod);    
    
    a = (float)(rand() % 100 + 1) / 10;
    b = (float)(rand() % 100 + 1) / 10;
    c = (float)(rand() % 100 + 1) / 10;
    float d = (float)(rand() % 100 + 1) / 10;
    float e = (float)(rand() % 100 + 1) / 10;
    sprintf(buf, "(%.1f - (%.1f * %.1f)) / (%.1f + %.1f)", a, b, c, d, e);
    calc_helper(buf);
    stu = calculator();
    mod = (a - (b * c)) / (d + e);
    fail_unless(stu == mod, "[Task 1.10] With input \"%s\" calculator() returned %f. Should have returned %f.",
            buf, stu, mod);        
}
END_TEST


int main(int argc, const char *argv[]) {
    srand((unsigned) time(NULL));
    Suite *s = suite_create("Test-1.8-10");

    tmc_register_test(s, test_ascii_chart, "1.8");
    tmc_register_test(s, test_secret_msg, "1.9");
    tmc_register_test(s, test_calculator, "1.10");

    return tmc_run_tests(argc, argv, s);
}
