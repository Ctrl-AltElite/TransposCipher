#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "transpositional_cipher_0.h"

const char alphabets[4][128] = {
	"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c",
	"abcdefghijklmnopqrstuvwxyz",
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
};

const unsigned a = 25;
const unsigned i = 12;
unsigned m; // alp len

void PrintUsage(char *app) {
    printf("-- Usage --\n  %s <ciphertext> <alphabet id>\n", app);
    printf("-- Examples --\n");
    printf("  %s tpill 1\n", app);
    printf("\n-- Alphabets --\n");
    printf("\n  0: all ascii printable characters (mostly used only on computers)");
    printf("\n  1: all latin lowercase characters (third most used tc0 alphabet)");
    printf("\n  2: all latin characters (most common and default alphabet for tc0)");
    printf("\n  3: all latin characters and digits (second most common alphabet for tc0");
    printf("\n\n\n");
}

void delay(unsigned millis) {
    clock_t start = clock();
    while (clock() < start + millis) { }
}

void ClearFgets() {
    char name[16] = {0};
    while (!strchr(name, '\n')) {
        if (!fgets(name, (sizeof name), stdin)) {
            break;
        }
    }
}

int main(int argc, char **argv) {
    char *ciphertext = *(argv+1);
    char *alphabet_id = *(argv+2);
    int s = 0;
    if (ciphertext == NULL) {
        printf("Error: Ciphertext not specified.\n"); s = 1;
    } else if (alphabet_id == NULL) {
        printf("Error: Alphabet id not specified.\n"); s = 1;
    }

    if (s) {
        PrintUsage(*argv);
	    return 1;
    }
    int aid = atoi(alphabet_id);
    const char *alphabet = alphabets[aid];
    m = strlen(alphabet);
    unsigned key;
    for (key = 0; key < m; ++key) {
        char *trans = TranspositionAlphabet(key, i, a, alphabet, strlen(alphabet));
        char *plain = Cipher(trans, alphabet, m, ciphertext, strlen(ciphertext), 0);
        printf("key(%d): %s\n", key, plain);
        free(plain);
        free(trans);
        delay(1000);
    }
    return 0;
}
