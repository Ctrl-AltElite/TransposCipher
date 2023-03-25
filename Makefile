CC := gcc

.PHONY : cipher cracker all

all: cipher cracker

cipher:
	$(CC) -o cipher src/transpositional_cipher.c
cracker:
	$(CC) -o cracker src/transpositional_cipher_cracker.c
