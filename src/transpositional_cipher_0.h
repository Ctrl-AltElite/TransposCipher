#ifndef TC0
#define TC0

#include <stdlib.h>
#include "xorshift.h"

void swap(char *a, char *b) {
    char t = *a;
    *a = *b;
    *b = t;
}

char *TranspositionAlphabet(unsigned k, unsigned inc, unsigned a, const char *alphabet, size_t lenght) {
    char *trans = (char *)malloc(lenght);
    memcpy(trans, alphabet, lenght);

    int i;
    struct xorshift32_state j;
    j.a = (a * k + inc) % lenght;
    for (i = 0; i < lenght; ++i) {
        swap(trans+i, trans+(j.a%lenght));
        xorshift32(&j);
    }
    return trans;
}

int GetIndex(const char *array, size_t lenght, const char c) {
    int i;
    for (i = 0; i < lenght; ++i) {
        if (*(array+i) == c) {
            return i;
        }
    }
    return -1;
}

char *Cipher(const char *alp1, const char *alp2, size_t alp_len, const char *msg, size_t msg_len, int v) {
    char *c = (char *)malloc(msg_len);
    char a2c = 0;
    int mi;
    for (mi = 0; mi < msg_len; ++mi) {
        int a1i = GetIndex(alp1, alp_len, *(msg + mi));
        if (a1i == -1) {
            if (v >=1) {
                printf("\'%c\' will stay as is. (not in alphabet)\n", *(msg + mi));
	    }
            a2c = *(msg + mi);
        } else {
            a2c = *(alp2 + a1i);
        }
        *(c+mi) = a2c;
    }
    return c; 
}

#endif
