all: projet_crypto.out

run: projet_crypto.out
	./projet_crypto.out

projet_crypto.out: projet_crypto.c
	gcc projet_crypto.c -o projet_crypto.out -lgmp

clean:
	rm projet_crypto.out
	
