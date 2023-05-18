
#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define NUM_HORSES 8

#define HORSE_W 64
#define HORSE_H 64
#define FINISH_LINE 500
typedef struct cheval
{
    BITMAP* droite[3];
    int x, y;
    int direction;
    int frame;
    int en_deplacement;
    float vitesse;
    int index;
}t_cheval;

//BITMAP *horse_bitmaps[NUM_HORSES];
//int horse_positions[NUM_HORSES] = { 0 };
//int horse_speeds[NUM_HORSES] = { 0 };
//int finished_horses[NUM_HORSES] = { 0 };

void init_horses(t_cheval cheval[8]) {
    int i;
    char filename[32];

    for (i = 0; i < NUM_HORSES; i++) {
        sprintf(filename, "horse%d.bmp", i + 1);
        //horse_bitmaps[i] = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\cheval.bmp", NULL);
        cheval[i].x = 0;
        cheval[i].vitesse= rand() % 12 + 3;
        cheval[i].frame=0;
        cheval[i].direction=0;
        cheval[i].y=(SCREEN_H/8)*i;
        cheval[i].en_deplacement=1;
        //finished_horses[i] = 0;
    }
}
void separer_bitmap_personnage(t_cheval cheval[8], BITMAP* bitmap)
{
    int taille_w = 130;
    int taille_h = 90;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {

            cheval[i].droite[j] = create_sub_bitmap(bitmap, j * taille_w, 0* taille_h, taille_w, taille_h);

        }
    }
}
//void destroy_horses(t_cheval cheval[8]) {
//int i;

//for (i = 0; i < NUM_HORSES; i++) {
//destroy_bitmap(horse_bitmaps[i]);
//}
//}

void update_horse_positions(t_cheval cheval[8]) {
    int i;

    for (i = 0; i < NUM_HORSES; i++) {
        if (cheval[i].x<SCREEN_W) {
            cheval[i].x += cheval[i].vitesse;

            if (cheval[i].x+cheval[i].vitesse > SCREEN_W) {
                cheval[i].x=0;
                cheval[i].vitesse=0;
                //cheval[i].rang++;
            }
        }
    }
}

//void draw_horses(t_cheval cheval[8], BITMAP* buffer) {
//int i;

//for (i = 0; i < NUM_HORSES; i++) {
// draw_sprite(screen, horse_bitmaps[i], horse_positions[i], i * HORSE_H);
//}
//}
void dessiner_personnage(t_cheval cheval[8], BITMAP* buffer)
{
    BITMAP* frame;
    for (int i = 0; i < 8; i++) {
        frame = cheval[i].droite[cheval[i].frame];
        masked_blit(frame, buffer, 0, 0, cheval[i].x, cheval[i].y, frame->w, frame->h);
    }

}
void classerChevaux(t_cheval chevaux[8], int taille) {
    int i, j;

    // Parcours des chevaux et classement
    for (i = 0; i < taille - 1; i++) {
        for (j = i + 1; j < taille; j++) {
            if (chevaux[j].vitesse > chevaux[i].vitesse) {
                t_cheval temp = chevaux[i];
                chevaux[i] = chevaux[j];
                chevaux[j] = temp;
            }
        }
    }
}


int main() {
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
    srand(time(NULL));
    BITMAP *sprite= load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\4.bmp",NULL);
    //BITMAP *background= load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\image 2 piste.bmp",NULL);
    BITMAP *buffer2= create_bitmap(SCREEN_W,SCREEN_H);
    t_cheval cheval[8];
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    init_horses(cheval);
    cheval[0].index = 0;

    cheval[1].index = 1;

    cheval[2].index = 2;

    cheval[3].index = 3;

    cheval[4].index = 4;

    cheval[5].index = 5;

    cheval[6].index = 6;

    cheval[7].index = 7;
    classerChevaux(cheval, 8);
    printf("Classement des chevaux :\n");
    for (int i = 0; i < 8; i++) {
        printf("Cheval d'index %d a terminé à la place %d\n", cheval[i].index+1, i + 1);
    }
    printf("cheval numero 1 est :%d\n",cheval[0].index+1);

    separer_bitmap_personnage(cheval, sprite);

    int frame_counter = 0;

    while (!key[KEY_ESC]) {
        clear_bitmap(buffer);
        clear(screen);
        update_horse_positions(cheval);
        line(buffer, 0, SCREEN_H/8+15, SCREEN_W, SCREEN_H/8+15, makecol(255, 0, 0));
        line(buffer, 0, 2*SCREEN_H/8+15, SCREEN_W, 2*SCREEN_H/8+15, makecol(0, 255, 0));
        line(buffer, 0, 3*SCREEN_H/8+15, SCREEN_W, 3*SCREEN_H/8+15, makecol(0, 0, 255));
        line(buffer, 0, 4*SCREEN_H/8+15, SCREEN_W, 4*SCREEN_H/8+15, makecol(255, 255, 255));
        line(buffer, 0, 5*SCREEN_H/8+15, SCREEN_W, 5*SCREEN_H/8+15, makecol(255, 0, 0));
        line(buffer, 0, 6*SCREEN_H/8+15, SCREEN_W, 6*SCREEN_H/8+15, makecol(0, 255, 0));
        line(buffer, 0, 7*SCREEN_H/8+15, SCREEN_W, 7*SCREEN_H/8+15, makecol(0, 0, 255));

        //draw_horses();
        //stretch_blit(background, buffer, 0, 0, background->w, background->h, 0, 0, SCREEN_W, SCREEN_H);

        dessiner_personnage(cheval, buffer);
        //blit(buffer, buffer2, 0, 0, 0, 0, buffer->w, buffer->h);

        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
        frame_counter++;

        for (int i = 0; i < 8; i++) {
            if (frame_counter >= 2) {
                if (cheval[i].en_deplacement==1) {
                    cheval[i].frame = (cheval[i].frame + 1) % 3;
                } else {
                    cheval[i].frame = 0;
                }
                //frame_counter = 0;
            }
            rest(10);
        }
        frame_counter = 1;
        //rest(10)

    }

    //destroy_horses();
    allegro_exit();
    return 0;
}END_OF_MAIN()






