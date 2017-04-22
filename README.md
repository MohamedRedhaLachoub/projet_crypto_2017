# Projet de cryptographie de licence 3 2017
## Projet d'implémentation des tests de primalités de Fermat et Miller-Rabin

`void square_and_multiply(mpz_t res, mpz_t a, mpz_t exp, mpz_t mod);`

La fonction square_and_multiply utilise les techniques d'exponentiation rapide avec un modulo à mod.

`int test_de_fermat(mpz_t n, int k);`

La fonction test_de_fermat prend en paramètres un entier de type mpz_t de la bibliothèque GMP et un entier k et exécute k fois le test de Fermat sur l'entier.
Renvoie 1 si l'entier est fortement pseudo-premier, si k est assez grand la chance que l'on se trompe en déclarant n premier est très très faible.
Et renvoie 0 si l'entier est composé.

`int miller_rabin(mpz_t n, int k);`

La fonction miller_rabin prend en paramètres un entier de type mpz_t de la bibliothèque GMP et un entier k et exécute k fois le test de Miller-Rabin sur l'entier.
Renvoie 1 si l'entier est premier, 0 sinon.

Commande d'utilisation
===================================
`gcc projet_crypto.c -o projet_crypto.out -lgmp`

Commande permettant de compiler le programme ou alors utiliser le Makefile avec la commande `make`.

`./projet_crypto [nombre à tester] [nombre de test à effectuer]`

