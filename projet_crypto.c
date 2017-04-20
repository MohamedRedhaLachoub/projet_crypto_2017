#include <gmp.h>
#include <stdio.h>
#include <string.h>

void square_and_multiply(mpz_t res, mpz_t a, mpz_t exp, mpz_t mod){
	//a^exp mod n
	mpz_t r; int i;
	char* binexp;

	mpz_init_set(r, a);//On met a dans r
	binexp = mpz_get_str(NULL, 2, exp); // Transformation de l'exposant au format binaire.
	printf("binexp : %s\n", binexp);

	for(i=1 ; i<=strlen(binexp)-1; i++){
		printf("i=%d et bine=%c",i,binexp[i]); 
		mpz_mul(r, r, r);
		mpz_mod(r, r, mod);
		if(binexp[i] == '1'){
			mpz_mul(r, r, a);
			mpz_mod(r, r, mod);
		}
	}

	mpz_set(res, r);
	mpz_clear(r);

	//Affichage test
	mpz_t res2;
	mpz_init(res2);
	mpz_powm(res2, a, exp, mod);
	printf("fonction de la gmp : %s\n", mpz_get_str(NULL, 10, res2));
}

int main(int argc, char* argv[]){

	/* //Affiche les arguments du programme
	int i = 0;
	printf("argc : %d\n", argc);
	for(i = 0; i<argc; i++){
		printf("argv[%d] : %s\n", i, argv[i]);
	}
	*/

	if(argc == 3){
		mpz_t n, res; int i,k;
		k = atoi(argv[2]);


		//mpz_init(n); //On initialise le n en même temps que lui donner la valeur plus bas.
		mpz_init(res);
		mpz_init_set_str(n, argv[1], 10); //Permet ne se pas se limiter par le int maximum pour notre n


		printf("%p\n", n);
		printf("n : %s\n", mpz_get_str(NULL, 10, n)); //Fait passer directement n en string et permet donc de ne pas perdre à l'affichage, ATTENTION le str passer en param est NULL possible fuite de mémoire puisque qu'elle est alloué par GMP
		printf("k : %d\n", k);

		//mpz_powm_ui(res, n, k, mod); //On n'a pas le droit d'utiliser cette fonction, il faut utiliser square and multiply.

		mpz_t exp, mod;
		mpz_init_set_ui(exp, k);
		mpz_init_set_ui(mod, 11);

		square_and_multiply(res, n, exp, mod);
		printf("result : %s\n", mpz_get_str(NULL, 10, res));

		mpz_clear(n);
		return 0;
	}
	else{
		printf("Vous n'avez pas entrer le bon nombre d'arguments lors du lancement du programme.\n");
		return 1;
	}

}
