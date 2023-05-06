#include <stdio.h>
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int est_sur_rondin(int x_grenouille, int y_grenouille, int x_rondin, int y_rondin, int largeur_rondin, int hauteur_rondin) {
    int sur_rondin = 0;
    if (y_grenouille == y_rondin) {
        if (x_grenouille >= x_rondin && x_grenouille <= x_rondin + largeur_rondin) {
            sur_rondin = 1;
        }
    }
    return sur_rondin;
}
void shuffleBitmaps(BITMAP **bitmaps, int count) {
    int i, j;
    BITMAP *temp;

    //srand(time(NULL)); // Initialisation de la graine aléatoire

    // Mélange du tableau
    for (i = count - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = bitmaps[i];
        bitmaps[i] = bitmaps[j];
        bitmaps[j] = temp;
    }
}
BITMAP *bitmap[3];
BITMAP *bitmap2[3];
BITMAP *bitmap3[3];
int main(void) {
    printf("bonjour !\n");
    printf("salut comment");
    return 0;
}END_OF_MAIN();
