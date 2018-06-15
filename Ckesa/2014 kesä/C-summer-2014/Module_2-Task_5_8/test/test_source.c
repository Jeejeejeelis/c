#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../src/source.h"



void pr_array(char *buf, int *arr, int n)
{
    char b[40];
    sprintf(buf, "{");
    while (n--) {
        sprintf(b, "%d", *arr++);
        if (n)
            strcat(b, ", ");
        strcat(buf, b);
    }
    strcat(buf, "}");
}

START_TEST(test_sort)
{
	int ar1[] = {65, 234, 676, 3, 98, 35, 297, 34, 12};
	int ar1_sorted[] = {3, 12, 34, 35, 65, 98, 234, 297, 676};
	int ar2[] = {5, 93, 4, 54, 2, 876, 11, 123};
	int ar2_sorted[] = {2, 4, 5, 11, 54, 93, 123, 876};
	int ok = 1, i;
        char obuf1[100], obuf2[100];

	sort(ar1, 9);
	sort(ar2, 8);

	for (i = 0; i < 9; i++) {
		if (ar1[i] != ar1_sorted[i]) {
			ok = 0;
			break;
		}
	}
        if (!ok) {
            pr_array(obuf1, ar1, 9);
            pr_array(obuf2, ar1_sorted, 9);
            fail("[Task 2.5] Array {65, 234, 676, 3, 98, 35, 297, 34, 12} not ordered correctly.\nYour array: %s.\nShould be: %s\n", obuf1, obuf2);
        }
	for (i = 0; i < 8; i++) {
		if (ar2[i] != ar2_sorted[i]) {
			ok = 0;
			break;
		}
	}
        if (!ok) {
            pr_array(obuf1, ar2, 8);
            pr_array(obuf2, ar2_sorted, 8);
            fail("[Task 2.5] Array {5, 93, 4, 54, 2, 876, 11, 123} not ordered correctly.\nYour array: %s.\nShould be: %s\n", obuf1, obuf2);
        }
        
}
END_TEST

START_TEST(test_count_alpha)
{
    char str[20];
    for (int i = 0; i < 3; i++) {
        int count = 0;
        unsigned int len = rand() % 10 + 4;
        for (unsigned int j = 0; j < len; j++) {
            int c = rand() % 90 + 32;
            if (isalpha(c))
                count++;
            str[j] = c;
        }
        str[len] = 0;
        int stu = count_alpha(str);
        fail_unless(stu == count, "[Task 2.6] There are %d alpha characters in string '%s'. You returned: %d",
                count, str, stu);
    }
}
END_TEST


START_TEST(test_count_substr)
{
    char *str[] = { "one two one twotwo three", "abcdefghijk", "ttatamtammtammitammi", "a b a b b b c d" };
    char *sub[] = { "two", "kkk", "tammi", "b" };
    int ans[] = { 3, 0, 2, 4 };
    
    for (int i = 0; i < 4; i++) {
        int stu = count_substr(str[i], sub[i]);
        fail_unless(stu == ans[i],
                "[Task 2.7] count_substr(\"%s\", \"%s\") should have returned %d. You returned %d.",
                str[i], sub[i], ans[i], stu);
    }
}
END_TEST

START_TEST(test_remove_substr)
{
    char *str[] = { "one two one twotwo three", "abcdefghijk", "ttatamtammtammitammi", "a b a b b b c d" };
    char *sub[] = { "two", "kkk", "tammi", "b" };
    char *ans[] = { "one  one  three", "abcdefghijk", "ttatamtamm", "a  a    c d" };
    
    for (int i = 0; i < 4; i++) {
        char work[30];
        memset(work, 0, 30);
        strcpy(work, str[i]);
        remove_substr(work, sub[i]);
        if (strcmp(work, ans[i])) {
            fail("[Task 2.8] remove_substr(\"%s\", \"%s\") should change the string to \"%s\". Your string: \"%s\".",
                    str[i], sub[i], ans[i], work);
        }
    }
}
END_TEST


int main(int argc, const char *argv[])
{
    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-2.5-8");

    tmc_register_test(s, test_sort, "2.5");
    tmc_register_test(s, test_count_alpha, "2.6");
    tmc_register_test(s, test_count_substr, "2.7");
    tmc_register_test(s, test_remove_substr, "2.8");
    
    return tmc_run_tests(argc, argv, s);
}
