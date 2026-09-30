#include "vue.h"

struct s_ctr_mastermind;

typedef struct s_ctr_bouton {
  int num;
  struct s_ctr_mastermind* parent;
} ctr_bouton;

typedef struct s_ctr_mastermind {
  mastermind* jeu;
  vue_t vue;
  ctr_bouton boutons[TAILLE_COMBI];
} ctr_mastermind;

/* initialisation:
	- initialise le champ jeu
	- initialise la vue
	- instancie les tableaux fleches_haut et fleches_bas
	Précondition: appel à gtk_init
*/
void ctr_construire(ctr_mastermind* ctr);

/* met à jour la vue selon l'état du modèle:
	- état de la partie
	- historique
	- boutons d'action
*/
void ctr_rafraichir_vue(ctr_mastermind* ctr);

/* définit le comportement de l'ig 
*/
void ctr_attacher(ctr_mastermind* ctr);

/*met à jour l'essai en cours dans le modèle quand une couleur est choisie dans la vue
  
*/
void ctr_set_bouton_color(ctr_bouton* cb);

/*suite au clic sur le bouton "valider", joue la combinaison en cours si elle est valide
*/
void ctr_jouer_combinaison(ctr_mastermind* ctr);

/*suite au clic sur le bouton "rejouer", réinitialise le modèle et la vue
*/
void ctr_rejouer(ctr_mastermind* ctr);
