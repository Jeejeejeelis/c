#ifndef AALTO_FILEPROC_H
#define	AALTO_FILEPROC_H

int process_file(const char *dstfile, const char *srcfile,
        int (*proc)(char *, void *, unsigned int),
        void *param, unsigned int unitsize);
int xorcrypt(char *buf, void *key, unsigned int size);

#endif
