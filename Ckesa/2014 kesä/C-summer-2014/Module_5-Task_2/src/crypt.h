#ifndef AALTO_CRYPT_H
#define	AALTO_CRYPT_H

int encrypt(const char *dstfile, const char *srcfile, uint32_t key);
int decrypt(const char *dstfile, const char *srcfile, uint32_t key);

#endif	/* AALTO_ANYDATA_H */
