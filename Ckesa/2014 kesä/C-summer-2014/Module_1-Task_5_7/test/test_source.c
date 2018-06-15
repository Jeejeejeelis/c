#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../src/source.h"



// STUB here
START_TEST(test_drawbox) {
char stu[2048];
char *mod = "####\n####\n####\n####\n####\n";
int xs = 4;
int ys = 5;
freopen("mockoutput", "w", stdout);
draw_box(xs, ys);
read_stdout(stu, 2048);

char infostr[100] = "";
if (mycompare(stu, mod, infostr)) {
fail("[Task 1.5] Called draw_box(%d, %d). Your output:\n%s\nReference output:\n%s\nReason: %s\n",
xs, ys, stu, mod, infostr);
}
}
END_TEST



// STUB goes here
START_TEST(test_draw_triangle) {
char stu[2048];
char *mod = "....#\n...##\n..###\n.####\n#####\n";
int size = 5;
freopen("mockoutput", "w", stdout);
draw_triangle(size);
read_stdout(stu, 2048);

char infostr[100] = "";
if (mycompare(stu, mod, infostr)) {
fail("[Task 1.6] Called draw_triangle(%d). Your output:\n%s\nReference output:\n%s\nReason: %s\n",
size, stu, mod, infostr);
}
}
END_TEST


START_TEST(test_draw_ball) {
char stu[2048];
char *mod = "...*...\n.*****.\n.*****.\n*******\n.*****.\n.*****.\n...*...\n";
int size = 3;
freopen("mockoutput", "w", stdout);
draw_ball(size);
read_stdout(stu, 2048);

char infostr[100] = "";
if (mycompare(stu, mod, infostr)) {
fail("[Task 1.7] Called draw_ball(%d). Your output:\n%s\nReference output:\n%s\nReason: %s\n",
size, stu, mod, infostr);
}
}
END_TEST

int main(int argc, const char *argv[]) {
    srand((unsigned) time(NULL));
    Suite *s = suite_create("Test-1.5-7");

    tmc_register_test(s, test_drawbox, "1.5");
    tmc_register_test(s, test_draw_triangle, "1.6");
    tmc_register_test(s, test_draw_ball, "1.7");

    return tmc_run_tests(argc, argv, s);
}
