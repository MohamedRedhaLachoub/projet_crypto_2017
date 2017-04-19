#include <gmp.h>
#include <stdio.h>
#define ligne printf("\n");

int main(int argc, char* argv[]){
	
	/**/ //Affiche les arguments du programme
	int i = 0;
	printf("argc : %d", argc); ligne
	for(i = 0; i<argc; i++){
		printf("argc[%d] : %s\n", i, argv[i]);
	}
	/**/
	
	if(argc == 3){
		mpz_t n;
		mpz_init(n);
		printf("%d\n", n);
		mpz_clear(n);
		
		return 0;
	}
	else{
		printf("Vous n'avez pas entrer le bon nombre d'arguments lors du lancement du programme.\n");
		return 1;
	}
	
}
