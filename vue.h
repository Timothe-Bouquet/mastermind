#include "modele-mm/mastermind.h"
#include <gtk/gtk.h>

/*	__________________________
	Structure de donnees		*/
struct vue_s{
        GdkRGBA palette[8];
        GtkWindow* fenetre;
          GtkHBox* separation;
            GtkVBox* jeu;
              GtkLabel* msg;
              GtkHBox* combi;
                GtkVBox* choix[TAILLE_COMBI];
                  GtkColorButton* couleur[TAILLE_COMBI];
              GtkHBox* boutons;
                GtkButton* rejouer;
                GtkButton* valider;
            GtkVBox* historique;
              GtkHBox* combinaison[NB_ESSAIS];
                GtkColorButton* couleurs[NB_ESSAIS][TAILLE_COMBI];
              GtkLabel* res[NB_ESSAIS];
};

typedef struct vue_s* vue_t;

/* Crée la vue
  Pré-cond: gtk_init(NULL, NULL) a été appelé
  Post-cond: l'interface graphique est prête à être affiché
*/
void creer_vue(vue_t vue);

/* Récupère un pointeur vers la fenêtre du jeu
  Pré-cond: le pointeur existe
  Post-cond: renvoie un pointeur
*/
GtkWindow* vue_get_fenetre(vue_t vue);

/* Récupère un pointeur vers le label des messages du jeu
  Pré-cond : le pointeur existe
  Post-cond : renvoie un pointeur
*/
GtkLabel* vue_get_message(vue_t vue);

/* Récupère un pointeur vers le bouton de la nième couleur
  Pré-cond : le pointeur existe et 0<=n<=TAILLE_COMBI
  Post-cond : renvoie un pointeur
*/
GtkColorButton* vue_get_bouton_color(vue_t vue, int n);

/* Récupère la nième couleur de la combinaison en cours
  Pré-cond : la couleur existe et 0<=n<=TAILLE_COMBI
  Post-cond : renvoie une couleur
*/
couleur vue_get_color(vue_t vue, int n);

/* Récupère un pointeur vers la nième couleur de la ième combinaison dans l'historique
  Pré-cond: le pointeur existe et 0<=n<=TAILLE_COMBI et 0<=i<=NB_ESSAIS-1
  Post-cond: renvoie un pointeur
*/
GtkColorButton* vue_get_historique_bouton_color(vue_t vue, int n, int i);

/* Récupère un pointeur vers le bouton rejouer
  Pré-cond : le pointeur existe
  Post-cond : renvoie un pointeur
*/
GtkButton* vue_get_rejouer(vue_t vue);

/* Récupère un pointeur vers le bouton valider
  Pré-cond : le pointeur existe
  Post-cond : renvoie un pointeur
*/
GtkButton* vue_get_valider(vue_t vue);

/* Récupère un pointeur vers le label du résultat de la ième combinaison
  Pré-cond : le pointeur existe et 0<=i<=NB_ESSAIS-1
  Post-cond : renvoie un pointeur
*/
GtkLabel* vue_get_res(vue_t vue, int i);

/* Change la sensibilité d'un widget
  Pré-cond : widget =! NULL et widget* =! NULL
  Post-cond : si le widget était insensible, il l'est maintenant;
              si le widget était sensible, il ne l'est plus.
*/
void vue_toggle_sensibility(GtkWidget* widget);

/* Change la couleur d'un label
  Pré-cond : bouton =! NULL et bouton* =! NULL et COULEUR_MIN-1<=color<=COULEUR_MAX
  Post-cond : la couleur du label devient la couleur numéro color
*/
void vue_set_couleur_bouton(GtkColorButton* bouton, couleur color);

/* Change le texte d'un label
  Pré-cond : label =! NULL et label* =! NULL
  Post-cond : le texte du lavel devient texte
*/
void vue_set_texte_label(GtkLabel* label, char* texte);
