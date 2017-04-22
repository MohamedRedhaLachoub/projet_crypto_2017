#include <gmp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>			
			
void square_and_multiply(mpz_t res, mpz_t a, mpz_t exp, mpz_t mod){
	//a^exp mod n
	mpz_t r; long long int i;
	char* binexp;

	mpz_init_set(r, a);//On met a dans r
	binexp = mpz_get_str(NULL, 2, exp); // Transformation de l'exposant au format binaire.
	//printf("binexp : %s\n", binexp); //Affichage de l'exposant au format binaire pour tests.

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
	gmp_randinit_default(state);//Initialisation du rand
	
	//Cas spécial si n est égal à 2 car on a un problème quand on essaye de trouver un a car on essaie de le générer 1 < a < 1
	if(mpz_cmp_ui(n, 2) == 0){
		mpz_clears(limite, restmp, a, n1, state, NULL);
		return 1;
	}
	
	if(mpz_cmp_ui(n, 1) == 0){
		mpz_clears(limite, restmp, a, n1, state, NULL);
		return 0;
	}
	
	for(i = 0 ; i < k; i++){
		mpz_urandomm(a, state, limite);//Genere l'entier a aleatoirement entre 0 < a < n-2
		mpz_add_ui(a, a, 1); //Genere l'entier a aleatoirement entre 1 < a < n-1
		square_and_multiply(restmp, a, n1, n); // Effectue a^n-1 mod n
		if(mpz_cmp_ui(restmp, 1) != 0){ // verifie si le resultat est different de 1
			mpz_clears(limite, restmp, a, n1, state, NULL);
			return 0;
		}
	}
		
	mpz_clears(limite, restmp, a, n1, state, NULL);
	return 1;
}	


int miller_rabin(mpz_t n, int k){
	mpz_t n1, n2, t, a, y, two;
	int s = 0, i, j, cond;
	
	mpz_inits(a, y, NULL);
	mpz_init_set(n1, n);
	mpz_init_set(n2, n);
	mpz_init_set_ui(two, 2);//On stocke 2 dans un mpz_t pour pouvoir l'utiliser dans l'appel de square_and_multiply lors de la boucle principale
	mpz_sub_ui(n1, n1, 1);	
	mpz_sub_ui(n2, n1, 1);
	
	gmp_randstate_t state;
	gmp_randinit_default(state);
	
	//Cas spécial si n est égal à 2 car on a un problème quand on essaye de trouver un a car on essaie de le générer 1 < a < 1
	if(mpz_cmp_ui(n, 2) == 0){
		mpz_clears(n1, n2, a, y, two, state, NULL);
		return 1;
	}
	
	if(mpz_cmp_ui(n, 1) == 0){
		mpz_clears(n1, n2, a, y, two, state, NULL);
		return 0;
	}
	
	mpz_init_set(t, n1); //On commence avec t = n-1 qui sera pair de base sauf si n est pair.
	while(mpz_even_p(t)){ //Tant que t est pair
		mpz_div_ui(t, t, 2); //On divise t par 2
		s++; // Et on compte le nombre de fois où on divise t
	}
	
	//gmp_printf("t : %Zd, s : %d\n", t, s);
	
	for(i = 0; i<k; i++){
		mpz_urandomm(a, state, n2);//Genere l'entier a aleatoirement entre 0 < a < n
		mpz_add_ui(a, a, 1);
		square_and_multiply(y, a, t, n);
		cond=0; //Condition pour s'assurer que la boucle j ne renvoie pas composé si on tombe sur y == -1 mod n
		if(mpz_cmp_ui(y, 1) != 0 && mpz_cmp(y, n1) != 0){
			cond=1;
			for(j = 1; j<s; j++){
				square_and_multiply(y, y, two, n);
				if(mpz_cmp_ui(y, 1) == 0){
					mpz_clears(n1, n2, a, y, two, t, state, NULL);
					return 0;
				}
				if(mpz_cmp(y, n1) == 0){
					j = s; //On sort du for j
					cond=0; // on evite le return 0 pour retourner a la boucle principale
					break;
				}
			}
		}
		if(cond == 1)
		{
			mpz_clears(n1, n2, a, y, two, t, state, NULL);
			return 0;
		}
	}
	mpz_clears(n1, n2, a, y, two, t, state, NULL);
	return 1;
	
	//gmp_printf("t : %Zd, ", t);
	//printf("s = %d\n", s);
	mpz_clears(n1, n2, a, y, two, t, state, NULL);
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
		mpz_t n; int k, bool; //n est l'entier à tester, k le nombre de fois où les algos doivent tester le nombre et bool sert à stocker le résultat envoyer par les algorithmes.
		k = atoi(argv[2]); //On récupère k des entrées de l'utilisateur

		mpz_init_set_str(n, argv[1], 10); //Permet ne se pas se limiter par le int maximum pour notre n

		//gmp_printf("n : %Zd\n",n);
		//printf("k : %d\n", k);
		
		bool = test_de_fermat(n,k);
		if(bool){
			printf("Test de Fermat = Premier\n");
		}else{
			printf("Test de Fermat = Composé\n");
		}
		
		bool = miller_rabin(n, k);
		if(bool){
			printf("Test de Miller-Rabin = Premier\n");
		}
		else{
			printf("Test de Miller-Rabin = Composé\n");
		}
		
		mpz_clears(n, NULL);
		return 0;
	}
	else{
		printf("Vous n'avez pas entrer le bon nombre d'arguments lors du lancement du programme.\n");
		return -1;
	}
}
