#include "cmastermind.h"

void ctr_construire(ctr_mastermind* ctr) {
  static mastermind jeu_S;
  mastermind* jeu = &jeu_S;
  static struct vue_s vue_S;
  vue_t vue = &vue_S;
  ctr_bouton boutons[TAILLE_COMBI];
  int i;
  mastermind_initialiser_avec_secret(jeu);
  creer_vue(vue);
  ctr->jeu = jeu;
  ctr->vue = vue;
  for (i = 0 ; i < TAILLE_COMBI ; i++) {
    boutons[i].num = i;
    boutons[i].parent = ctr;
    ctr->boutons[i] = boutons[i];
  }
}

void ctr_rafraichir_vue(ctr_mastermind* ctr) {
  int i;
  int j;
  char res[30] = "  correct(s), dont   placé(s)";
  for (i = 1 ; i < (ctr->jeu)->num_essai_encours ; i++) {
    for (j = 1 ; j <= TAILLE_COMBI ; j++) {
      vue_set_couleur_bouton(vue_get_historique_bouton_color(ctr->vue, j-1, i-1), mastermind_get_essai(ctr->jeu, i, j));
    }
    res[0] = '0' + mastermind_get_nb_couleurs_correctes(ctr->jeu, i);
    res[19] = '0' + mastermind_get_nb_couleurs_placees(ctr->jeu, i);
    vue_set_texte_label(vue_get_res(ctr->vue, i-1), res);
  }
  
  for (i = 0 ; i < TAILLE_COMBI ; i++) {
    if (mastermind_get_essai_encours(ctr->jeu, i+1) == COULEUR_INDETERMINEE) {
      printf("efface?\n");
      vue_set_couleur_bouton(vue_get_bouton_color(ctr->vue, i), COULEUR_INDETERMINEE);
    }
  }
  if (mastermind_get_etat(ctr->jeu) == ETAT_MM_GAGNE || mastermind_get_etat(ctr->jeu) == ETAT_MM_PERDU) {
    vue_toggle_sensibility(GTK_WIDGET(vue_get_valider(ctr->vue)));
    vue_toggle_sensibility(GTK_WIDGET(vue_get_rejouer(ctr->vue)));
    for (j = 0 ; j < TAILLE_COMBI ; j++) {
      vue_toggle_sensibility(GTK_WIDGET(vue_get_bouton_color(ctr->vue, i)));
    }
  }
}

void ctr_attacher(ctr_mastermind* ctr) {
  //choisir une couleur
  int i;
  for (i = 0 ; i < TAILLE_COMBI ; i++) {
    g_signal_connect_swapped(G_OBJECT(vue_get_bouton_color(ctr->vue, i)), "color-set", G_CALLBACK(ctr_set_bouton_color), &(ctr->boutons[i]));
  }
  
  //valider la combinaison
  g_signal_connect_swapped(G_OBJECT(vue_get_valider(ctr->vue)), "clicked", G_CALLBACK(ctr_jouer_combinaison), ctr);
  
  //bouton rejouer
  g_signal_connect_swapped(G_OBJECT(vue_get_rejouer(ctr->vue)), "clicked", G_CALLBACK(ctr_rejouer), ctr);
  
  //quitter
  g_signal_connect(G_OBJECT(vue_get_fenetre(ctr->vue)), "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void ctr_set_bouton_color(ctr_bouton* cb) {
  mastermind_set_essai_encours((cb->parent)->jeu, cb->num + 1, vue_get_color((cb->parent)->vue, cb->num));
  if (vue_get_color((cb->parent)->vue, cb->num) == COULEUR_INDETERMINEE)
    vue_set_texte_label(vue_get_message((cb->parent)->vue), "une couleur est invalide, choisissez parmi les couleurs autorisées");
}

void ctr_jouer_combinaison(ctr_mastermind* ctr) {
  mastermind_valider_essai_encours(ctr->jeu);
  ctr_rafraichir_vue(ctr);
}

void ctr_rejouer(ctr_mastermind* ctr) {
  int i;
  vue_toggle_sensibility(GTK_WIDGET(vue_get_valider(ctr->vue)));
  vue_toggle_sensibility(GTK_WIDGET(vue_get_rejouer(ctr->vue)));
  for (i = 0 ; i < TAILLE_COMBI ; i++) {
    vue_toggle_sensibility(GTK_WIDGET(vue_get_bouton_color(ctr->vue, i)));
  }
  mastermind_initialiser_avec_secret(ctr->jeu);
  ctr_rafraichir_vue(ctr);
}
