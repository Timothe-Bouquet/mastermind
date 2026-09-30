#include "vue.h"
#include <stdlib.h>
#include <stdio.h>

void creer_vue(vue_t vue)
{
// Création de la palette de couleur
        vue->palette[0].red = 1; 
        vue->palette[0].green = 0; 
        vue->palette[0].blue = 0;
        vue->palette[0].alpha = 1;
        vue->palette[1].red = 0; 
        vue->palette[1].green = 1; 
        vue->palette[1].blue = 0; 
        vue->palette[1].alpha = 1;
        vue->palette[2].red = 0; 
        vue->palette[2].green = 0; 
        vue->palette[2].blue = 1; 
        vue->palette[2].alpha = 1;
        vue->palette[3].red = 0.83; 
        vue->palette[3].green = 0.45; 
        vue->palette[3].blue = 0.83; 
        vue->palette[3].alpha = 1;
        vue->palette[4].red = 1; 
        vue->palette[4].green = 0.65; 
        vue->palette[4].blue = 0; 
        vue->palette[4].alpha = 1;
        vue->palette[5].red = 1; 
        vue->palette[5].green = 1; 
        vue->palette[5].blue = 0; 
        vue->palette[5].alpha = 1;
        vue->palette[6].red = 1; 
        vue->palette[6].green = 1; 
        vue->palette[6].blue = 1; 
        vue->palette[6].alpha = 1;
        vue->palette[7].red = 0; 
        vue->palette[7].green = 0; 
        vue->palette[7].blue = 0; 
        vue->palette[7].alpha = 1;
// Création des widgets
        vue->fenetre = (GtkWindow*)gtk_window_new(GTK_WINDOW_TOPLEVEL);
        vue->separation = (GtkHBox*)gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        vue->jeu = (GtkVBox*)gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        vue->msg = (GtkLabel*)gtk_label_new("");
        vue->combi = (GtkHBox*)gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        for(int i = 0; i<TAILLE_COMBI; i++){
            vue->choix[i] = (GtkVBox*)gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
              vue->couleur[i] = (GtkColorButton *)gtk_color_button_new();
              gtk_color_chooser_add_palette((GtkColorChooser*)vue->couleur[i], GTK_ORIENTATION_VERTICAL, 2, 8, vue->palette);
        }
        
        vue->boutons = (GtkHBox*)gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        vue->rejouer = (GtkButton*)gtk_button_new_with_label("Rejouer");
        gtk_widget_set_sensitive((GtkWidget*)vue->rejouer, FALSE);
        vue->valider = (GtkButton*)gtk_button_new_with_label("Valider");
        vue->historique = (GtkVBox*)gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        for(int i = 0; i<NB_ESSAIS; i++){
            vue->combinaison[i] = (GtkHBox*)gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
            for(int j = 0; j<TAILLE_COMBI; j++){
                vue->couleurs[i][j] = (GtkColorButton *)gtk_color_button_new();
                gtk_widget_set_sensitive((GtkWidget*)vue->couleurs[i][j], FALSE);
            }
            vue->res[i] = (GtkLabel*)gtk_label_new("");
        }
// Emboîtement des widgets
        gtk_container_add((GtkContainer*)vue->fenetre, (GtkWidget*)vue->separation);
        gtk_box_pack_start((GtkBox*)vue->separation, (GtkWidget*)vue->jeu, TRUE, TRUE, 2);
        gtk_box_pack_start((GtkBox*)vue->jeu, (GtkWidget*)vue->msg, TRUE, FALSE, 2);
        gtk_box_pack_start((GtkBox*)vue->jeu, (GtkWidget*)vue->combi, TRUE, TRUE, 2);
        for(int i = 0; i<TAILLE_COMBI; i++){
            gtk_box_pack_start((GtkBox*)vue->combi, (GtkWidget*)vue->choix[i], TRUE, TRUE, 2);
            gtk_box_pack_start((GtkBox*)vue->choix[i], (GtkWidget*)vue->couleur[i], TRUE, TRUE, 2);
        }
        gtk_box_pack_start((GtkBox*)vue->jeu, (GtkWidget*)vue->boutons, TRUE, TRUE, 5);
        gtk_box_pack_start((GtkBox*)vue->boutons, (GtkWidget*)vue->rejouer, TRUE, TRUE, 2);
        gtk_box_pack_start((GtkBox*)vue->boutons, (GtkWidget*)vue->valider, TRUE, TRUE, 2);
        gtk_box_pack_start((GtkBox*)vue->separation, (GtkWidget*)vue->historique, TRUE, TRUE, 5);
        for(int i = 0; i<NB_ESSAIS; i++){
            gtk_box_pack_start((GtkBox*)vue->historique, (GtkWidget*)vue->combinaison[i], TRUE, TRUE, 5);
            for(int j = 0; j<TAILLE_COMBI; j++){
                gtk_box_pack_start((GtkBox*)vue->combinaison[i], (GtkWidget*)vue->couleurs[i][j], TRUE, TRUE, 5);
            }
            gtk_box_pack_start((GtkBox*)vue->historique, (GtkWidget*)vue->res[i], TRUE, TRUE, 5);
        }
}

GtkWindow* vue_get_fenetre(vue_t vue){
        return vue->fenetre;
}

GtkLabel* vue_get_message(vue_t vue){
        return vue->msg;
}

GtkColorButton* vue_get_bouton_color(vue_t vue, int n){
        return vue->couleur[n];
}

couleur vue_get_color(vue_t vue, int n){
        GdkRGBA rgba;
        gtk_color_chooser_get_rgba((GtkColorChooser*)vue_get_bouton_color(vue, n), &rgba);
        if(rgba.red == 1 && rgba.green == 0 && rgba.blue == 0)
                return COULEUR_ROUGE;
        if(rgba.red == 0 && rgba.green == 1 && rgba.blue == 0)
                return COULEUR_VERT;
        if(rgba.red == 0 && rgba.green == 0 && rgba.blue == 1)
                return COULEUR_BLEU;
        if(rgba.red == 0.83 && rgba.green == 0.45 && rgba.blue == 0.83)
                return COULEUR_MAUVE;
        if(rgba.red == 1 && rgba.green == 0.65 && rgba.blue == 0)
                return COULEUR_ORANGE;
        if(rgba.red == 1 && rgba.green == 1 && rgba.blue == 0)
                return COULEUR_JAUNE;
        if(rgba.red == 1 && rgba.green == 1 && rgba.blue == 1)
                return COULEUR_BLANC;
        if(rgba.red == 0 && rgba.green == 0 && rgba.blue == 0)
                return COULEUR_NOIR;
        return COULEUR_INDETERMINEE;
}


GtkButton* vue_get_rejouer(vue_t vue){
        return vue->rejouer;
}

GtkButton* vue_get_valider(vue_t vue){
        return vue->valider;
}

GtkColorButton* vue_get_historique_bouton_color(vue_t vue, int n, int i){
        return vue->couleurs[i][n];
}

GtkLabel* vue_get_res(vue_t vue, int i){
        return vue->res[i];
}

void vue_toggle_sensibility(GtkWidget* widget){
        if(gtk_widget_get_sensitive(widget) == FALSE)
                gtk_widget_set_sensitive(widget, TRUE);
        else
                gtk_widget_set_sensitive(widget, FALSE);
}

void vue_set_couleur_bouton(GtkColorButton* bouton, couleur color){
        GdkRGBA rgba;
        printf("MAMAGUEVO 1\n");
        rgba.alpha = 1;
        switch(color){
                case COULEUR_INDETERMINEE:
                        printf("MAMAGUEVO 2\n");
                        rgba.red = 0.5;
                        rgba.green = 0.5;
                        rgba.blue = 0.5;
                        gtk_color_chooser_set_rgba((GtkColorChooser*)bouton, &rgba);
                        break;
                case COULEUR_ROUGE:
                        rgba.red = 1;
                        rgba.green = 0;
                        rgba.blue = 0;
                        gtk_color_chooser_set_rgba((GtkColorChooser*)bouton, &rgba);
                        break;
                case COULEUR_VERT:
                        rgba.red = 0;
                        rgba.green = 1;
                        rgba.blue = 0;
                        gtk_color_chooser_set_rgba((GtkColorChooser*)bouton, &rgba);
                        break;
                case COULEUR_BLEU:
                        rgba.red = 0;
                        rgba.green = 0;
                        rgba.blue = 1;
                        gtk_color_chooser_set_rgba((GtkColorChooser*)bouton, &rgba);
                        break;
                case COULEUR_MAUVE:
                        rgba.red = 0.83;
                        rgba.green = 0.45;
                        rgba.blue = 0.83;
                        gtk_color_chooser_set_rgba((GtkColorChooser*)bouton, &rgba);
                        break;
                case COULEUR_ORANGE:
                        rgba.red = 1;
                        rgba.green = 0.65;
                        rgba.blue = 0;
                        gtk_color_chooser_set_rgba((GtkColorChooser*)bouton, &rgba);
                        break;
                case COULEUR_JAUNE:
                        rgba.red = 1;
                        rgba.green = 1;
                        rgba.blue = 0;
                        gtk_color_chooser_set_rgba((GtkColorChooser*)bouton, &rgba);
                        break;
                case COULEUR_BLANC:
                        rgba.red = 1;
                        rgba.green = 1;
                        rgba.blue = 1;
                        gtk_color_chooser_set_rgba((GtkColorChooser*)bouton, &rgba);
                        break;
                case COULEUR_NOIR:
                        rgba.red = 0;
                        rgba.green = 0;
                        rgba.blue = 0;
                        gtk_color_chooser_set_rgba((GtkColorChooser*)bouton, &rgba);
                        break;
                
        }
}

void vue_set_texte_label(GtkLabel* label, char* texte){
        gtk_label_set_text(label, texte);
}
