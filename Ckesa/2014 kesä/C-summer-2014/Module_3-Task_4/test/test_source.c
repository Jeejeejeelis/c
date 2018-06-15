#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/fraction.h"


START_TEST(test_set)
{
    for (int i = 0; i < 3; i++) {
        unsigned int num = rand() % 20, den = rand() % 20;
        Fraction *f = setFraction(num, den);
        fail_unless(f != NULL, "[Task 3.4.a] setFraction returned NULL.\n");
        
        unsigned int refnum = getNum(f);
        unsigned int refden = getDenom(f);
        if (refnum != num || refden != den) {
            freeFraction(f);
            fail("[Task 3.4.a] called setFraction(%d,%d), but getNum and getDenom returned %d/%d\n",
                    num, den, refnum, refden);
        }
        freeFraction(f);
    }
}
END_TEST


START_TEST(test_compare)
{
    unsigned int a = 20 + (rand() % 10); 
    Fraction *fa = setFraction(a, a+1);
    fail_unless(fa != NULL, "[Task 3.4.b] Implement setFraction first.\n");
    Fraction *fb = setFraction(a, a+2);
    
    fail_unless(compFraction(fa, fb) == 1, "[Task 3.4.b] Comparing %u/%u and %u/%u should return 1\n",
            a, a+1, a, a+2);
    fail_unless(compFraction(fb, fa) == -1, "[Task 3.4.b] Comparing %u/%u and %u/%u should return -1\n",
            a, a+2, a, a+1);
    
    Fraction *faa = setFraction(2*a, 2*(a+1));
    fail_unless(compFraction(fa, faa) == 0, "[Task 3.4.b] Comparing %u/%u and %u/%u should return 0\n",
            a, a+1, 2*a, 2*(a+1));
    freeFraction(fa);
    freeFraction(fb);
    freeFraction(faa);
}
END_TEST

void printFr(char *buf, const Fraction *val)
{
    sprintf(buf, "%d/%d", getNum(val), getDenom(val));
}

START_TEST(test_add)
{
    Fraction *fa = setFraction(2, 3);
    fail_unless(fa != NULL, "[Task 3.4.c] Implement setFraction first.\n");
    Fraction *fb = setFraction(3, 4);
    Fraction *fm = setFraction(17, 12);
    Fraction *fn = setFraction(75, 36);
    Fraction *fs = addFraction(fa, fb);
    
    fail_unless(fs != NULL, "[Task 3.4.c] addFraction returned NULL.\n");
    
    char bufS[16];
    char bufM[16];
    char bufN[16];
    printFr(bufS, fs);
    printFr(bufM, fm);
    fail_unless(!compFraction(fs, fm), "[Task 3.3.c] Sum of 2/3 and 3/4 should be %s. You returned %s.\n", bufM,bufS);
    freeFraction(fs);
    fs = addFraction(fm, fa);
    printFr(bufS, fs);
    printFr(bufN, fn);
    fail_unless(!compFraction(fs, fn), "[Task 3.3.c] Sum of %s and 2/3 should be %s. You returned %s.\n", bufM,bufN,bufS);
    freeFraction(fa);
    freeFraction(fb);
    freeFraction(fm);
    freeFraction(fn);
    freeFraction(fs);
}
END_TEST


START_TEST(test_reduce)
{
    char buf[32];
    Fraction *fa = setFraction(6, 12);
    fail_unless(fa != NULL, "[Task 3.4.d] Implement setFraction first.\n");   
    //Fraction *sa = setFraction(1, 2);
    reduceFraction(fa);
    printFr(buf, fa);

    if (getNum(fa) != 1 || getDenom(fa) != 2) {
        fail("[Task 3.4.d] Reducing 6/12 should result in 1/2. You had %s.\n",buf);
    }
    
    unsigned int mul1 = rand() % 5 + 1;
    unsigned int mul2 = rand() % 20 + 5;
    Fraction *fb = setFraction(mul1, mul2*mul1);
    reduceFraction(fb);
    printFr(buf, fb);
    //Fraction *sb = setFraction(1, mul2)
    if (getNum(fb) != 1 || getDenom(fb) != mul2) {
        fail("[Task 3.4.d] Reducing %d/%d should result in 1/%d. You had %s.\n",
                mul1, mul1*mul2, mul2, buf);
    }
    
    freeFraction(fa);
    freeFraction(fb);
}
END_TEST


int main(int argc, const char *argv[])
{
    srand((unsigned int)time(NULL));
    	Suite *s = suite_create("Test-3.4");

	tmc_register_test(s, test_set, "3.4.a");
	tmc_register_test(s, test_compare, "3.4.b");
	tmc_register_test(s, test_add, "3.4.c");
	tmc_register_test(s, test_reduce, "3.4.d");        
        
	return tmc_run_tests(argc, argv, s);
}
