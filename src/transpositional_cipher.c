#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "transpositional_cipher_0.h"

// const char alphabet[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c";
// /\   all printable characters
// -----------------------------
// \/ latin lowercase characters
// const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
const char alphabets[4][128] = {
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c",
    "abcdefghijklmnopqrstuvwxyz",
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
};

const unsigned a = 25;
const unsigned i = 12;

void ClearFgets() {
    char name[16] = {0};
    while (!strchr(name, '\n')) {
        if (!fgets(name, (sizeof name), stdin)) {
            break;
        }
    }
}

int main(int argc, char **argv) {
    unsigned alp = 2;
    if (argc >= 2) {
        if (strcmp(*(argv+1), "-h") == 0) {
            printf("-- Usage --\n  %s <alphabet id>\n", *argv);
            printf("-- Examples --\n");
            printf("  %s 1\n", *argv);
            printf("\n-- Alphabets --\n");
            printf("\n  0: all ascii printable characters (mostly used only on computers)");
            printf("\n  1: all latin lowercase characters (third most used tc0 alphabet)");
            printf("\n  2: all latin characters (most common and default alphabet for tc0)");
            printf("\n  3: all latin characters and digits (second most common alphabet for tc0");
            printf("\n\n\n");
            return 0;
        } else {
            alp = atoi(*(argv+1));
        }
    }

    printf("Picked up alphabet #%d\n", alp);

    const char *alphabet = alphabets[alp];
    const unsigned m = strlen(alphabet);

    char key_buff[16] = {0};
    printf("Enter the key: ");
    assert(fgets(key_buff, 16, stdin) != NULL);

    const int key = atoi(key_buff) % m;

    char *trans = TranspositionAlphabet(key, i, a, alphabet, strlen(alphabet));
    
    char user[256] = {0};
    char choice[4] = {0};
    printf("Mode (e - encrypt; d - decrypt):\n");
    assert(fgets(choice, 2, stdin) != NULL);
    ClearFgets();
    if (choice[0] == 'e') {
        printf("Enter text to encrypt: ");
        assert(fgets(user, 256, stdin) != NULL);
        printf("Result: %s\n", Cipher(alphabet, trans, m, user, strlen(user), 0));
    } else {
        printf("Enter text to decrypt: ");
        assert(fgets(user, 256, stdin) != NULL);
        printf("Result: %s\n", Cipher(trans, alphabet, m, user, strlen(user), 0));
    }

    return 0;
}
