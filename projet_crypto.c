#include <gmp.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	printf("Bonjour\n");
	mpz_t n;
	mpz_init(n);
	printf("%d\n", n);
	mpz_clear(n);
}
