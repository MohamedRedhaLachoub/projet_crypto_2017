#include <gmp.h>
#include <stdio.h>

int main(int argc, char* argv[]){

	/* //Affiche les arguments du programme
	int i = 0;
	printf("argc : %d\n", argc);
	for(i = 0; i<argc; i++){
		printf("argv[%d] : %s\n", i, argv[i]);
	}
	*/

	if(argc == 3){
		mpz_t n;
		int k = atoi(argv[2]);
		printf("k : %d\n", k);

		//mpz_init(n); //On initialise le n en même temps que lui donner la valeur plus bas.

		mpz_init_set_str(n, argv[1], 10); //Permet ne se pas se limiter par le int maximum pour notre n
		printf("%p\n", n);
		printf("n : %s\n", mpz_get_str(NULL, 10, n)); //Fait passer directement n en string et permet donc de ne pas perdre à l'affichage, ATTENTION le str passer en param est NULL possible fuite de mémoire puisque qu'elle est alloué par GMP

		mpz_clear(n);
		return 0;
	}
	else{
		printf("Vous n'avez pas entrer le bon nombre d'arguments lors du lancement du programme.\n");
		return 1;
	}

}
