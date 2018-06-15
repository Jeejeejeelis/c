#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../src/stringman.h"


void randString(char *work, char *rev, int len)
{
    for (int i = 0; i < len; i++) {
        char c = rand() % ('z' - 'a') + 'a';
        work[i] = c;
        rev[len-1-i] = c;
    }
    work[len] = 0;
    rev[len] = 0;
}

START_TEST(test_turn_around) {
    char workStr[5][20] = { "testi", "sokos", "toimii", "0123456789abcdef", "" };
    char origStr[5][20];
    char revStr[5][20] = { "itset", "sokos", "iimiot", "fedcba9876543210", "" };
    randString(workStr[4], revStr[4], 10);
    memcpy(origStr, workStr, sizeof(origStr));
    for (int i = 0; i < 5; i++) {
        turn_around(workStr[i]);
        if (strlen(workStr[i]) > 19) {
            fail("[Task 6.1.a] Produced string is too long. You might have forgot trailing '\0'");
        }
        if (strcmp(workStr[i], revStr[i])) {
            fail("[Task 6.1.a] Reversing string '%s' should result '%s'. You produced: '%s'",
                    origStr[i], revStr[i], workStr[i]);
        }
    }
}
END_TEST

void randPal(char *work)
{
    for (int i = 0; i < 5; i++) {
        char c = rand() % ('z' - 'a') + 'a';
        work[i] = c;
        work[9-i] = c;
    }
    work[10] = 0;
}

START_TEST(test_is_reversed) {
    char workStr[5][20] = { "testi", "sokos", "soimii", "saippuakauppias", "" };
    int corRes[5] = { 0, 1, 0, 1, 1 };
    randPal(workStr[4]);
    for (int i = 0; i < 5; i++) {
        int res = is_reversed(workStr[i]);
        if (res != corRes[i]) {
            fail("[Task 6.1.a] Should return %d for string '%s'. You returned %d",
                    corRes[i], workStr[i], res);
        }
    }
}
END_TEST



START_TEST(test_reversed_words) {
    char workStr[3][200] = { "Small string to be reversed",
        "A palindrome is a word,\n"
        "phrase, number, or other sequence of\n"
        "symbols or elements.\n" };
    char origStr[3][200];
    char revStr[3][200] = { "llamS gnirts ot eb desrever",
        "A emordnilap si a drow,\n"
        "esarhp, rebmun, ro rehto ecneuqes fo\n"
        "slobmys ro stnemele.\n" };
    
    int count = 2;
    
    memcpy(origStr, workStr, sizeof(origStr));
    
    for (int i = 0; i < count; i++) {
        reversed_words(workStr[i]);
        if (strlen(workStr[i]) > 199) {
            fail("[Task 6.1.c] Produced string is too long. You might have forgot trailing '\0'");
        }
        if (strcmp(workStr[i], revStr[i])) {
            fail("[Task 6.1.c] Reversing string '%s' should result '%s'. You produced: '%s'",
                    origStr[i], revStr[i], workStr[i]);
        }
    }
}
END_TEST

void random_str(char *str, char *common) {
    char words[5][8];
    str[0] = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            words[i][j] = rand() % ('z' - 'a') + 'a';
        }
        words[i][6] = 0;
    }
    int com = rand() % 5;
    int loc = rand() % 5;
    for (int i = 0; i < 5; i++) {
        if (loc == i) {
            strcat(str, words[com]);
            strcat(str, " ");
        }
        strcat(str, words[i]);
        strcat(str, " ");
    }
    strcpy(common, words[com]);
}

START_TEST(test_most_common) {
    char test[3][50] = { "one two one three two four two",
    "aaa bbb bbb bbb bbb ccc ccc ccc", "" };
    char modres[3][8] = { "two", "bbb", "" };
    int retval[3] = {3, 4, 2};
    
    random_str(test[2], modres[2]);
    
    for (int i = 0; i < 3; i++) {
        char result[10];
        result[0] = 0;
        int ret = most_common(test[i], result, 10);
        if (ret != retval[i]) {
            fail("[Task 6.1.d] With string '%s' should return %d. You returned %d",
                    test[i], retval[i], ret);
        }
        if (strcmp(modres[i], result)) {
            fail("[Task 6.1.d] With string '%s' the most common string is '%s'. You returned '%s'",
                    test[i], modres[i], result);
        }
    }
}
END_TEST

int main(int argc, const char *argv[]) {
    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-6.1");

    tmc_register_test(s, test_turn_around, "6.1.a");
    tmc_register_test(s, test_is_reversed, "6.1.b");
    tmc_register_test(s, test_reversed_words, "6.1.c");
    tmc_register_test(s, test_most_common, "6.1.d");

    return tmc_run_tests(argc, argv, s);
}
