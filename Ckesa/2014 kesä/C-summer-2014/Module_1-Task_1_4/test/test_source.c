#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../src/source.h"


START_TEST(test_three_lines)
{
    freopen("mockoutput", "w", stdout);
    three_lines();
    fclose(stdout);
    FILE *fp = fopen("mockoutput", "r");
    char str [100] = { 0 };
    fread(str, 99, 1, fp);
    char infostr[100] = "";
    char *rightstr = "June\nJuly\nAugust\n";
    int ret = mycompare(str, rightstr, infostr);
    fail_unless(!ret, "[Task 1.1] Your output:\n%s\nReference output:\n%s\nReason: %s\n",
            str, rightstr, infostr);
    fclose(fp);
}
END_TEST

START_TEST(test_distOrigo)
{
    double res = distOrigo(2.5, 5);
    double ref = sqrt((2.5 * 2.5) + (5 * 5));
    fail_unless(res == ref, "[Task 1.2] distOrigo(2.5, 5) returned %f. Should have returned: %f",
            res, ref);
    
    res = distOrigo(0.1, 0.1);
    ref = sqrt((0.1 * 0.1) + (0.1 * 0.1));
    fail_unless(res == ref, "[Task 1.2] distOrigo(2.5, 5) returned %f. Should have returned: %f",
            res, ref);
}
END_TEST

START_TEST(test_simple_sum)
{
     FILE *mock_input = freopen("mockinput", "w+", stdin);
     fputs("6 8", mock_input);
     fseek(mock_input, 0, SEEK_SET);
     freopen("mockoutput", "w", stdout);
     simple_sum();
     fflush(stdout);
     FILE *fp = fopen("mockoutput", "r");
     char str [100];
     memset(str, 0, sizeof(str));
     fgets(str, 100, fp);
     char *ref = "6 + 8 = 14\n";
     char infostr[100] = "";
     int ret = mycompare(str, ref, infostr);
     fail_unless(!ret, "[Task 1.3] When giving input \"6 8\", your output:\n%s\nReference output:\n%s\nReason: %s\n",
            str, ref, infostr);
     fclose(fp);

     mock_input = freopen("mockinput", "w+", stdin);
     fputs("10200 20031", mock_input);
     fseek(mock_input, 0, SEEK_SET);
     freopen("mockoutput", "w", stdout);
     simple_sum();
     fflush(stdout);
     fp = fopen("mockoutput", "r");
     memset(str, 0, sizeof(str));
     fgets(str, 100, fp);
     ref = "10200 + 20031 = 30231\n";
     infostr[0] = 0;
     ret = mycompare(str, ref, infostr);
     fail_unless(!ret, "[Task 1.3] When giving input \"10200 20031\", your output:\n%s\nReference output:\n%s\nReason: %s\n",
            str, ref, infostr);
     fclose(fp);
}
END_TEST


START_TEST(test_simple_math)
{
#if defined(__CYGWIN__)
fail("Local tests not working on Cygwin. Send code to server for checking.\n");
#endif
FILE *mock_input = freopen("mockinput", "w+", stdin);
fputs("11 * 3", mock_input);
fseek(mock_input, 0, SEEK_SET);
float ret = simple_math();
if (ret != 33) {
fail("[Task 1.4] When giving input 11 * 3, function should return 33.");
}

mock_input = freopen("mockinput", "w+", stdin);
fputs("6 a 8", mock_input);
fseek(mock_input, 0, SEEK_SET);
ret = simple_math();
if (ret == ret) {
fail("[Task 1.4] When giving input 6 a 8, function should return 'nan'");
}
}
END_TEST




int main(int argc, const char *argv[])
{
    srand((unsigned)time(NULL));
	Suite *s = suite_create("Test-1.1-4");

	tmc_register_test(s, test_three_lines, "1.1");
        tmc_register_test(s, test_distOrigo, "1.2");
        tmc_register_test(s, test_simple_sum, "1.3");
        tmc_register_test(s, test_simple_math, "1.4");
        
	return tmc_run_tests(argc, argv, s);
}
