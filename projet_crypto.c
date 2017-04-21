#include <gmp.h>
#include <stdio.h>
#include <string.h>
				
			
			
			
void square_and_multiply(mpz_t res, mpz_t a, mpz_t exp, mpz_t mod){
	//a^exp mod n
	mpz_t r; long long int i;
	char* binexp;

	mpz_init_set(r, a);//On met a dans r
	binexp = mpz_get_str(NULL, 2, exp); // Transformation de l'exposant au format binaire.
	//printf("binexp : %s\n", binexp);

	for(i=1 ; i<strlen(binexp); i++){
		//printf("i=%d et bine=%c/n",i,binexp[i]);// test pour afficher le tableau binaire
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
	/*mpz_t res2;
	mpz_init(res2);
	mpz_powm(res2, a, exp, mod);
	printf("fonction de la gmp : %s\n", mpz_get_str(NULL, 10, res2));*/
}

int test_de_fermat(mpz_t n,int k){
	
	int i;
	mpz_t restmp, a, limite, n1;
	
	mpz_inits(restmp, a, NULL); //Initialisation de restmp et a à 0. a est l'entier aléatoire dans a^n-1 mod n qui est compris en 1 et n-1
	
	mpz_init_set(n1, n); // On utilise n1 pour stocker n-1
	mpz_sub_ui(n1, n1, 1);
	
	mpz_init_set(limite, n); //On initialise la limite à n-2 pour pouvoir générer un nombre aléatoire 1 < a < n-1
	mpz_sub_ui(limite,limite,2);
	
	gmp_randstate_t state;
	gmp_randinit_default(state);
	
	//Cas spécial si n est égal à 2 car on a un problème quand on essaye de trouver un a car on essaie de le générer 1 < a < 1
	if(mpz_cmp_ui(n, 2) == 0){
		return 1;
	}
	
	for(i = 0 ; i < k; i++){
		mpz_urandomm(a, state, limite);//Genere l'entier a aleatoirement entre 0 < a < n-2
		mpz_add_ui(a, a, 1); //Genere l'entier a aleatoirement entre 1 < a < n-1
		square_and_multiply(restmp, a, n1, n); // Effectue a^n-1 mod n
		if(mpz_cmp_ui(restmp, 1) != 0){ // verifie si le resultat est different de 1
			return 0;
		}
	}
		
	mpz_clears(limite, restmp, a, n1, state, NULL);
	return 1;
}	

//miller rabin, tant que t%2 est 0, t/2, s+1. t = n-1, s est le nombre de division par 2 faites. <-- Initialisation du t ;)

int main(int argc, char* argv[]){

	/* //Affiche les arguments du programme
	int i = 0;
	printf("argc : %d\n", argc);
	for(i = 0; i<argc; i++){
		printf("argv[%d] : %s\n", i, argv[i]);
	}
	*/

	if(argc == 3){
		mpz_t n, res; int k, bool;
		k = atoi(argv[2]);

		mpz_init(res);
		mpz_init_set_str(n, argv[1], 10); //Permet ne se pas se limiter par le int maximum pour notre n

		gmp_printf("n : %Zd\n",n);
		printf("k : %d\n", k);
		
		bool = test_de_fermat(n,k);
		if(bool){
			printf("Test de Fermat = Premier\n");
		}else{
			printf("Test de Fermat = Composé\n");
		}
		
		mpz_clears(n, res, NULL);
		return 0;
	}
	else{
		printf("Vous n'avez pas entrer le bon nombre d'arguments lors du lancement du programme.\n");
		return 1;
	}
}
