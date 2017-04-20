#include <gmp.h>
#include <stdio.h>

void square_and_multiply(mpz_t res, mpz_t a, mpz_t exp, mpz_t n){
	//a^exp mod n
	mpz_t r; int i;
	mpz_init_set(r, a);
	//TODO: Trouver le moyen de chopper exp en binaire ;) une idée mpz_get_str(NULL, 2, exp);
	
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
		square_and_multiply(res, NULL, NULL, NULL);
		printf("result : %s\n", mpz_get_str(NULL, 10, res));
		
		mpz_clear(n);
		return 0;
	}
	else{
		printf("Vous n'avez pas entrer le bon nombre d'arguments lors du lancement du programme.\n");
		return 1;
	}

}
