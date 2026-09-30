/*	Jeu de mastermind : programme de test de fonctions spécifiques
*/

#include "mastermind.h"

#include <stdio.h>	/* fonctions d'entrée /sortie */

/* _______________________________
	Declaration des fonctions	*/

/* ____ Palette de couleurs
*/
void couleur_palette(void);

/* ____ Définition automatique de la couleur d'une composante de la combinaison secrète
*/
void mastermind_secret_auto(mastermind* mm);

/* ____ Définition automatique de la couleur d'une composante de l'essai en cours
*/
void mastermind_essai_auto(mastermind* mm);


/* _______________________________
	Programme de test			*/
int main(void)
{
	mastermind mm;
	int cle;
	
	/* palette de couleur */
	couleur_palette();
	
	/* modification combinaison secrète par incrément couleur */
	printf("***** test combinaison secrète 1 2 3 4 par incrément couleur\n");	
	mastermind_initialiser(&mm);	
	mastermind_secret_auto(&mm);
	for(cle = 1 ; cle <= TAILLE_COMBI ; cle ++) {
		printf("\tcle %d couleur %u\n", cle, mastermind_get_secret(&mm, cle));
	}
	
	/* modification essai en cours par incrément couleur */
	printf("***** test essai en cours 1 2 3 4 par incrément couleur\n");	
	mastermind_valider_secret(&mm);
	mastermind_essai_auto(&mm);
	for(cle = 1 ; cle <= TAILLE_COMBI ; cle ++) {
		printf("\tcle %d couleur %u\n", cle, mastermind_get_essai_encours(&mm, cle));
	}

	/* ____ Programme terminé */
	return 0;
}

/* ____ Palette de couleurs
*/
void couleur_palette(void) {
	couleur c = COULEUR_INDETERMINEE - 1;
	int i;

	printf("***** test palette partant de COULEUR_INDETERMINEE - 1\n");	
	i = 0;
	do{
		printf("\tcouleur c = %d\n", (int)c);	
		c = couleur_suivante(c);
	} while(++i < NB_COULEURS+2);
	
	printf("***** test palette partant de COULEUR_MAX + 1\n");	
	c = COULEUR_MAX + 1;
	i = 0;
	do{
		printf("\tcouleur c = %d\n", (int)c);	
		c = couleur_suivante(c);
	} while(++i < 2);
}

/* ____ Définition automatique de la couleur d'une composante de la combinaison secrète
*/
void mastermind_secret_auto(mastermind* mm) {
	int cle, i;
	for(cle = 1 ; cle <= TAILLE_COMBI ; cle ++) {
		for(i = 1 ; i <= cle ; i ++) {
			mastermind_set_secret_auto(mm, cle);
		}
	}
}

/* ____ Définition automatique de la couleur d'une composante de l'essai en cours
*/
void mastermind_essai_auto(mastermind* mm) {
	int cle, i;
	for(cle = 1 ; cle <= TAILLE_COMBI ; cle ++) {
		for(i = 1 ; i <= cle ; i ++) {
			mastermind_set_essai_encours_auto(mm, cle);
		}
	}
}
