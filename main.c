#include <stdio.h>
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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