#include <gmp.h>
#include <stdio.h>
#define ligne printf("\n");

int main(int argc, char* argv[]){
	
	/**/ //Affiche les arguments du programme
	int i = 0;
	printf("argc : %d", argc);ligne
	for(i = 0; i<argc; i++){
		printf("argv[%d] : %s", i, argv[i]);ligne
	}
	/**/
	
	if(argc == 3){
		
		int n1 = atoi(argv[1]);
		printf("n1 = %d", n1);ligne
		
		mpz_t n;
		
		
		mpz_init(n);
		//mpz_set_si(n, n1); //Ici, on se sert de la valeur du atoi() précédent pour chopper la valeur n
		mpz_set_str(n, argv[1], 10); //Permet ne se pas se limiter par le int maximum pour notre n
		printf("%p", n);ligne
		mpz_clear(n);
		
		return 0;
	}
	else{
		printf("Vous n'avez pas entrer le bon nombre d'arguments lors du lancement du programme.\n");
		return 1;
	}
	
}
