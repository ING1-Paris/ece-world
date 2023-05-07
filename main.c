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
    //bitmap[0] = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\bar jakpot.bmp", NULL);
    //bitmap[1] = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\bar jakpot.bmp", NULL);
    //bitmap[2] = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\bar jakpot.bmp", NULL);
    //BITMAP *background=load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\images rouleau.bmp", NULL);
    //bitmap2[0]=load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\image piece .bmp", NULL);
    //bitmap2[1]=load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\image piece .bmp", NULL);
    //bitmap2[2] = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\image piece .bmp", NULL);

    //bitmap3[0] = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\image piece .bmp", NULL);
    //bitmap3[1] = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\image piece .bmp", NULL);
    //bitmap3[2] = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\image piece .bmp", NULL);

    //BITMAP* manivelle = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\image manivelle.bmp", NULL);
    //BITMAP* manivelleretour = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\manivelle retour.bmp", NULL);
    return 0;
}END_OF_MAIN();