#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define NUM_HORSES 8
typedef struct cheval {
    BITMAP *droite[3];
    int x, y;
    int direction;
    int frame;
    int en_deplacement;
    float vitesse;
    int index;
} t_cheval;

void init_horses(t_cheval cheval[8]) {
    int i;

    for (i = 0; i < NUM_HORSES; i++) {
        cheval[i].x = 1;
        cheval[i].vitesse = rand() % 15 + 3;
        cheval[i].frame = 0;
        cheval[i].direction = 0;
        cheval[i].y = (SCREEN_H / 8) * i;
        cheval[i].en_deplacement = 1;
    }
}
void separer_bitmap_personnage(t_cheval cheval[8], BITMAP *bitmap) {
    int taille_w = 130;
    int taille_h = 90;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            cheval[i].droite[j] = create_sub_bitmap(bitmap, j * taille_w, 0 * taille_h, taille_w, taille_h);
        }
    }
}

void update_horse_positions(t_cheval cheval[8]) {
    int i;

    for (i = 0; i < NUM_HORSES; i++) {
        if (cheval[i].x < SCREEN_W) {
            cheval[i].x += cheval[i].vitesse;

            if (cheval[i].x + cheval[i].vitesse > SCREEN_W) {
                cheval[i].x = 0;
                cheval[i].vitesse = 0;
            }
        }
    }
}

void dessiner_personnage(t_cheval cheval[8], BITMAP *buffer) {
    BITMAP *frame;
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

    int nombre;
    int nombre2;
    do {
        textprintf_ex(screen, font, 00, 230, makecol(255, 255, 255), -1, "Le joueur 1 choisit un nombre entre 1 et 8 avec les touches correspondantes mais pas celles du pad  :");
    } while (!key[KEY_1] && !key[KEY_2] && !key[KEY_3] && !key[KEY_4] && !key[KEY_5] && !key[KEY_6] && !key[KEY_7] && !key[KEY_8]);
    if (key[KEY_1]) {
        nombre = 1;
    } else if (key[KEY_2]) {
        nombre = 2;
    } else if (key[KEY_3]) {
        nombre = 3;
    } else if (key[KEY_4]) {
        nombre = 4;
    } else if (key[KEY_5]) {
        nombre = 5;
    } else if (key[KEY_6]) {
        nombre = 6;
    } else if (key[KEY_7]) {
        nombre = 7;
    } else {
        nombre = 8;
    }
    clear(screen);
    do {
        textprintf_ex(screen, font, 0, 200, makecol(255, 255, 255), -1, "          Le joueur 2 choisit une lettre entre A et H dans l'ordre alphabetique correspondant :");
        textprintf_ex(screen, font, 0, 230, makecol(255, 255, 255), -1, "        en effet la A correspond a un 1 et le H a un  8 le A etant bugge c'est un S");
    } while (!key[KEY_A] && !key[KEY_B] && !key[KEY_C] && !key[KEY_D] && !key[KEY_E] && !key[KEY_F] && !key[KEY_G] && !key[KEY_H]);
    if (key[KEY_A]) {
        nombre2 = 1;
    } else if (key[KEY_B]) {
        nombre2 = 2;
    } else if (key[KEY_C]) {
        nombre2 = 3;
    } else if (key[KEY_D]) {
        nombre2 = 4;

    } else if (key[KEY_E]) {
        nombre2 = 5;
    } else if (key[KEY_F]) {
        nombre2 = 6;
    } else if (key[KEY_G]) {
        nombre2 = 7;
    } else {
        nombre2 = 8;
    }

    srand(time(NULL));
    BITMAP *sprite = load_bitmap("attractions/cheval/4.bmp", NULL);
    BITMAP *double_buffer = create_bitmap(SCREEN_W, SCREEN_H);
    t_cheval cheval[8];
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *buffer3 = create_bitmap(SCREEN_W, SCREEN_H);
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

    separer_bitmap_personnage(cheval, sprite);

    int frame_counter = 0;
    int test = 0;
    rest(3000);
    clear(screen);

    while (!key[KEY_ESC]) {
        if (cheval[0].x != 0 && cheval[1].x != 0 && cheval[2].x != 0 && cheval[3].x != 0 && cheval[4].x != 0 && cheval[6].x != 0 && cheval[7].x != 0) {
            clear_bitmap(buffer);
            update_horse_positions(cheval);
            line(buffer, 0, SCREEN_H / 8 + 15, SCREEN_W, SCREEN_H / 8 + 15, makecol(255, 0, 0));
            line(buffer, 0, 2 * SCREEN_H / 8 + 15, SCREEN_W, 2 * SCREEN_H / 8 + 15, makecol(0, 255, 0));
            line(buffer, 0, 3 * SCREEN_H / 8 + 15, SCREEN_W, 3 * SCREEN_H / 8 + 15, makecol(0, 0, 255));
            line(buffer, 0, 4 * SCREEN_H / 8 + 15, SCREEN_W, 4 * SCREEN_H / 8 + 15, makecol(255, 255, 255));
            line(buffer, 0, 5 * SCREEN_H / 8 + 15, SCREEN_W, 5 * SCREEN_H / 8 + 15, makecol(255, 0, 0));
            line(buffer, 0, 6 * SCREEN_H / 8 + 15, SCREEN_W, 6 * SCREEN_H / 8 + 15, makecol(0, 255, 0));
            line(buffer, 0, 7 * SCREEN_H / 8 + 15, SCREEN_W, 7 * SCREEN_H / 8 + 15, makecol(0, 0, 255));

            dessiner_personnage(cheval, buffer);

            blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
            frame_counter++;

            for (int i = 0; i < 8; i++) {
                if (frame_counter >= 2) {
                    if (cheval[i].en_deplacement == 1) {
                        cheval[i].frame = (cheval[i].frame + 1) % 3;
                    } else {
                        cheval[i].frame = 0;
                    }
                }
                rest(10);
            }
            frame_counter = 1;
        }

        else if (cheval[0].x == 0 && cheval[1].x == 0 && cheval[2].x == 0 && cheval[3].x == 0 && cheval[4].x == 0 && cheval[6].x == 0 && cheval[7].x == 0) {
            clear_bitmap(buffer);

            for (int i = 0; i < 8; i++) {
                rectfill(double_buffer, 0, 10, SCREEN_W, 10 + text_height(font), makecol(0, 0, 0));
                textprintf_ex(double_buffer, font, 200, 10, makecol(255, 255, 255), -1, "Le Classement de la course est le suivant  :");
                textprintf_ex(double_buffer, font, 300, 30 + i * 15, makecol(255, 255, 255), -1, "Cheval %d : Rang %d", cheval[i].index + 1, i + 1);
            }

            FILE *f = fopen("attractions/cheval/end.txt", "w");
            if (f == NULL) {
                allegro_message("Error opening end.txt\n");
                exit(1);
            }

            if (nombre == cheval[0].index + 1) {
                textprintf_ex(double_buffer, font, 300, 200, makecol(255, 255, 255), -1, "Le joueur 1 a gagne la partie");
                blit(double_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                fprintf(f, "1");
            } else if (nombre2 == cheval[0].index + 1) {
                textprintf_ex(double_buffer, font, 300, 200, makecol(255, 255, 255), -1, "Le joueur 2 a gagne la partie");
                blit(double_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                fprintf(f, "2");
            } else if (nombre2 == nombre == cheval[0].index + 1) {
                textprintf_ex(double_buffer, font, 300, 200, makecol(255, 255, 255), -1, "Le joueur 1 et 2  ont  gagne la partie");
                blit(double_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                fprintf(f, "3");

            } else {
                textprintf_ex(double_buffer, font, 300, 200, makecol(255, 255, 255), -1, "La partie est perdue pour les 2 joueurs ");
                blit(double_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                fprintf(f, "0");
            }
            fclose(f);
        } else {
            clear_bitmap(buffer);
            update_horse_positions(cheval);
            line(buffer, 0, SCREEN_H / 8 + 15, SCREEN_W, SCREEN_H / 8 + 15, makecol(255, 0, 0));
            line(buffer, 0, 2 * SCREEN_H / 8 + 15, SCREEN_W, 2 * SCREEN_H / 8 + 15, makecol(0, 255, 0));
            line(buffer, 0, 3 * SCREEN_H / 8 + 15, SCREEN_W, 3 * SCREEN_H / 8 + 15, makecol(0, 0, 255));
            line(buffer, 0, 4 * SCREEN_H / 8 + 15, SCREEN_W, 4 * SCREEN_H / 8 + 15, makecol(255, 255, 255));
            line(buffer, 0, 5 * SCREEN_H / 8 + 15, SCREEN_W, 5 * SCREEN_H / 8 + 15, makecol(255, 0, 0));
            line(buffer, 0, 6 * SCREEN_H / 8 + 15, SCREEN_W, 6 * SCREEN_H / 8 + 15, makecol(0, 255, 0));
            line(buffer, 0, 7 * SCREEN_H / 8 + 15, SCREEN_W, 7 * SCREEN_H / 8 + 15, makecol(0, 0, 255));

            dessiner_personnage(cheval, buffer);

            blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
            frame_counter++;

            for (int i = 0; i < 8; i++) {
                if (frame_counter >= 2) {
                    if (cheval[i].en_deplacement == 1) {
                        cheval[i].frame = (cheval[i].frame + 1) % 3;
                    } else {
                        cheval[i].frame = 0;
                    }
                    // frame_counter = 0;
                }
                rest(10);
            }
            frame_counter = 1;
        }
    }
    allegro_exit();
    return 0;
}
END_OF_MAIN()
