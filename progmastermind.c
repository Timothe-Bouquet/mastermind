#include "cmastermind.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  ctr_mastermind ctr_S;
  ctr_mastermind* ctr = &ctr_S;
  srand(time(NULL));
  gtk_init(NULL, NULL);
  ctr_construire(ctr);
  ctr_attacher(ctr);
  gtk_widget_show_all(GTK_WIDGET(vue_get_fenetre(ctr->vue)));
  gtk_main();
  return EXIT_SUCCESS;
}
