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
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    //rest(1000);
    //set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
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
    /*int frog_speed = 8;
    if (key[KEY_LEFT] && frog_x > 0) {
                frog_x -= frog_speed;}
    if (key[KEY_RIGHT] && frog_x < SCREEN_W - 32) {
                frog_x += frog_speed;}
    if (key[KEY_UP] && frog_y > 0) {
                frog_y -= frog_speed;}
    if (key[KEY_DOWN] && frog_y < SCREEN_H - 32) {
                frog_y += frog_speed;}*/ //deplacement grenouille

    return 0;
}END_OF_MAIN();
