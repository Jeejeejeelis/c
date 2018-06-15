#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "../src/crypt.h"



START_TEST(test_encrypt)
{
    char *files[] = { "nonexistent.txt", "empty.txt", "oneline.txt", "simple.bin", "testi.txt" };
    int refvals[] = { -1, 0, 41, 41, 213 };
    uint32_t keys[] = { 0x00000001, 0x63de2a3e, 0 };
    
    int numkeys = 2;
    
    char srcfile[32];
    for (int i = 0; i < numkeys; i++) {
        for (int j = 0; j < 5; j++) {
            int ret;
            int istest = 0;
            strcpy(srcfile, files[j]);
            if ((ret = encrypt("encrypt", srcfile, keys[i])) == -1) {
                sprintf(srcfile, "test/%s", files[j]);
                ret = encrypt("encrypt", srcfile, keys[i]);
                istest = 1;
            }
            fail_unless(ret == refvals[j], "[Task 5.2.a] encrypt(...) for file '%s' should return %d. You returned %d.",
                files[j], refvals[j], ret);
            if (ret == -1)
                continue;
            
            FILE *fstu = fopen("encrypt", "r");
            if (!fstu)
                fail("[Task 5.2.a] Could not open the file supposedly created by encrypt function");
            

            char reffile[32];
            if (istest)
                sprintf(reffile, "test/%s.e-%d.bin", files[j], i + 1);
            else
                sprintf(reffile, "%s.e-%d.bin", files[j], i + 1);
            FILE *fref = fopen(reffile, "r");
            if (!fref) {
                fclose(fstu);
                fail("[Task 5.2.a] Could not open encrypted reference file '%s'", reffile);
            }
            
            for (int k = 0; k < refvals[j]; k++) {
                int stu = fgetc(fstu);
                int ref = fgetc(fref);
                if (stu != ref) {
                    fclose(fstu); fclose(fref);
                    fail("[Task 5.2.a] encrypt for file '%s', key: 0x%08x -- Your file differs from reference at byte %d. You: 0x%02x, reference: 0x%02x",
                            files[j], keys[i], k + 1, stu, ref);
                }
            }
            fclose(fstu);
            fclose(fref);
        }
    }
}
END_TEST


START_TEST(test_decrypt)
{
    char *files[] = { "nonexistent.txt", "empty.txt", "oneline.txt", "simple.bin", "testi.txt" };
    int refvals[] = { -1, 0, 41, 41, 213 };
    //uint32_t keys[] = { 0x00000001, 0x63de2a3e, 0 };
    const uint32_t key = 0x63de2a3e;

    char srcfile[32];
    for (int j = 0; j < 5; j++) {
            int ret;
            int istest = 0;
            sprintf(srcfile, "%s.e-%d.bin", files[j], 2);
            if ((ret = decrypt("decrypt", srcfile, key)) == -1) {
                sprintf(srcfile, "test/%s.e-%d.bin", files[j], 2);
                ret = decrypt("decrypt", srcfile, key);
                istest = 1;
            }
            fail_unless(ret == refvals[j], "[Task 5.2.b] decrypt(...) for file '%s' should return %d. You returned %d.",
                files[j], refvals[j], ret);
            if (ret == -1)
                continue;
            
            FILE *fstu = fopen("decrypt", "r");
            if (!fstu)
                fail("[Task 5.2.b] Could not open the file supposedly created by encrypt function");

            char reffile[32];
            if (istest)
                sprintf(reffile, "test/%s", files[j]);
            else
                sprintf(reffile, "%s", files[j]);
            FILE *fref = fopen(reffile, "r");
            if (!fref) {
                fclose(fstu);
                fail("[Task 5.2.b] Could not open decrypted reference file '%s'", reffile);
            }
            
            for (int k = 0; k < refvals[j]; k++) {
                int stu = fgetc(fstu);
                int ref = fgetc(fref);
                if (stu != ref) {
                    fclose(fstu); fclose(fref);
                    fail("[Task 5.2.b] decrypt for file '%s', key: 0x%08x -- Your file differs from reference at byte %d. You: 0x%02x, reference: 0x%02x",
                            files[j], key, k + 1, stu, ref);
                }
            }
            fclose(fstu);
            fclose(fref);
        }
}
END_TEST


int main(int argc, const char *argv[]) {
    srand((unsigned)time(NULL));
    Suite *s = suite_create("Test-5.2");

    tmc_register_test(s, test_encrypt, "5.2.a");
    tmc_register_test(s, test_decrypt, "5.2.b");
    
    return tmc_run_tests(argc, argv, s);
}
