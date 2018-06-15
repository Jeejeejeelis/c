#include <check.h>
#include <assert.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../src/fileproc.h"

int makeupper(char *buf, void *null, unsigned int size)
{
    (void) null;
    while (size--) {
        *buf = toupper(*buf);
        buf++;
    }
    return 1;
}

int makelower(char *buf, void *null, unsigned int size)
{
    (void) null;
    while (size--) {
        *buf = tolower(*buf);
        buf++;
    }
    return 1;
}


START_TEST(test_process_file)
{
    char *files[] = { "test-1", "test-2" };
    int refret[] = { 94, 108 };
    
    char srcfile[32];
    int istest = 0;
    int (*func)(char *, void *, unsigned int);
    char funcid;
     
    for (int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            if (j == 0) {
                func = makeupper;
                funcid = 'U';
            } else {
                func = makelower;
                funcid = 'L';
            }
        strcpy(srcfile, files[i]);
        int ret;
        if ((ret = process_file("result", srcfile, func, NULL, 4)) == -1) {
                sprintf(srcfile, "test/%s", files[i]);
                ret = process_file("result", srcfile, func, NULL, 4);
                istest = 1;
        }
        if (ret != refret[i]) {
            fail("[Task 5.6.a] process_file(file: '%s') returned invalid return value. You: %d, expected: %d",
                    files[i], ret, refret[i]);
        }
        FILE *fstu = fopen("result", "r");
        if (!fstu)
                fail("[Task 5.6.a] Could not open the file supposedly created by process_file function");
            
        char reffile[32];
        if (istest)
                sprintf(reffile, "test/test-%d-%c", i+1, funcid);
        else
                sprintf(reffile, "test-%d-%c", i+1, funcid);
        FILE *fref = fopen(reffile, "r");
        if (!fref) {
                fclose(fstu);
                fail("[Task 5.6.a] Could not open reference file '%s'",
                        reffile);
        }
            for (int k = 0; k < refret[i]; k++) {
                int stu = fgetc(fstu);
                int ref = fgetc(fref);
                if (stu != ref) {
                    fclose(fstu); fclose(fref);
                    fail("[Task 5.6.a] Your file differs from reference '%s'",
                            reffile);
                }
            }
            fclose(fstu);
            fclose(fref);
        }
    }    
}
END_TEST


START_TEST(test_xorcrypt)
{
    char *file = "test-1";
    char srcfile[32];
    int istest = 0;
    const int refret = 94;
    unsigned char key[] = { 0xaa, 0xba, 0x69, 0x12, 0x52, 0xff, 0x76, 0x34 };
    
       strcpy(srcfile, file);
        int ret;
        if ((ret = process_file("result", srcfile, xorcrypt, key, 8)) == -1) {
                sprintf(srcfile, "test/%s", file);
                ret = process_file("result", srcfile, xorcrypt, key, 8);
                istest = 1;
        }
        if (ret != refret) {
            fail("[Task 5.6.b] process_file(file: '%s') returned invalid return value. You: %d, expected: %d",
                    file, ret, refret);
        }
        
        FILE *fstu = fopen("result", "r");
        if (!fstu)
                fail("[Task 5.6.b] Could not open the file supposedly created by process_file function");
            
        char reffile[32];
        if (istest)
                sprintf(reffile, "test/test-%d-%c", 1, 'X');
        else
                sprintf(reffile, "test-%d-%c", 1, 'X');
        FILE *fref = fopen(reffile, "r");
        if (!fref) {
                fclose(fstu);
                fail("[Task 5.6.b] Could not open reference file '%s'",
                        reffile);
        }
            for (int k = 0; k < refret; k++) {
                int stu = fgetc(fstu);
                int ref = fgetc(fref);
                if (stu != ref) {
                    fclose(fstu); fclose(fref);
                    fail("[Task 5.6.b] Your file differs from reference '%s'",
                            reffile);
                }
            }
            fclose(fstu);
            fclose(fref);        
}
END_TEST


int main(int argc, const char *argv[])
{
     srand((unsigned)time(NULL));
     Suite *s = suite_create("Test-5.6");

     tmc_register_test(s, test_process_file, "5.6.a");
     tmc_register_test(s, test_xorcrypt, "5.6.b");     
     //tmc_register_test(s, test_make_array, "5.5.b");
     //tmc_register_test(s, test_array_idx, "5.5.c");    
     
     return tmc_run_tests(argc, argv, s);
}
