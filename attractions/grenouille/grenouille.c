#include <allegro.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FROG_H 32
#define FROG_W 32
#define LOG_WIDTH 128
#define LOG_HEIGHT 64

#define LOG_SPEED 1
#define FROG_SPEED 2

#define RIVIERE_END_SAVE_FILE "attractions/grenouille/end.txt"
#define RIVIERE_BEST_SAVE_FILE "attractions/grenouille/best.txt"

int est_sur_rondin(int x_grenouille, int y_grenouille, int x_rondin, int y_rondin, int largeur_rondin, int hauteur_rondin) {
    int sur_rondin = 0;
    if (y_grenouille + 16 >= y_rondin && y_grenouille + 16 <= y_rondin + hauteur_rondin) {
        if (x_grenouille + 16 >= x_rondin && x_grenouille + 16 <= x_rondin + largeur_rondin) {
            sur_rondin = 1;
        }
    }
    return sur_rondin;
}

int main() {
    srand(time(NULL));
    allegro_init();
    install_keyboard();
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0) != 0) {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // Charger les sprites à partir de fichiers bitmap
    BITMAP *frog_bmp = load_bitmap("attractions/grenouille/assets/grenouilleoff.bmp", NULL);
    BITMAP *log_bmp = load_bitmap("attractions/grenouille/assets/bois.bmp", NULL);
    BITMAP *fond = load_bitmap("attractions/grenouille/assets/fondfrog.bmp", NULL);

    if (!frog_bmp || !log_bmp || !fond) {
        allegro_message("Impossible de charger les sprites.");
        return 1;
    }

    // Créer les sprites de grenouille et de rondins de bois
    int frog_x = SCREEN_W / 2;
    int frog_y = SCREEN_H - FROG_H;

    // Faire sauter la grenouille ,deplacement grenouille,Déclaration des variables
    int log_x[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int log_y[12] = {120, 180, 240, 300, 120, 180, 240, 300, 120, 180, 240, 300};
    int log_speed[12] = {LOG_SPEED, -LOG_SPEED, LOG_SPEED, -LOG_SPEED, LOG_SPEED, -LOG_SPEED, LOG_SPEED, -LOG_SPEED,
                         LOG_SPEED, -LOG_SPEED, LOG_SPEED, -LOG_SPEED};
    for (int i = 0; i < 4; i++) {
        log_x[i] = SCREEN_W / 3;
        log_x[i + 4] = 2 * SCREEN_W / 3;
        log_x[i + 8] = SCREEN_W;
        log_speed[i] = (rand() % 1) + 1;
        log_speed[i + 4] = log_speed[i];
        log_speed[i + 8] = log_speed[i];
    }

    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *buffer_menu = create_bitmap(SCREEN_W, SCREEN_H);

    clear_bitmap(buffer);
    clear_bitmap(buffer_menu);

    float max_score_ = -1;
    float score_ = -1;

    int num_played = 0;
    while (!key[KEY_ENTER]) {
        // rectfill(buffer_menu, 0, 0, SCREEN_W, SCREEN_W, makecol(0, 0, 255));
        rectfill(buffer_menu, SCREEN_W / 2 - 50, SCREEN_H / 2 - 25, SCREEN_W / 2 + 50, SCREEN_H / 2 + 25, makecol(255, 255, 255));
        textout_centre_ex(buffer_menu, font, "Play", SCREEN_W / 4, SCREEN_H / 4, makecol(0, 0, 0), -1);
        clear_to_color(buffer_menu, makecol(0, 255, 0));
        draw_sprite(buffer_menu, fond, 80, 50);  //,SCREEN_H/3-50,SCREEN_H/3-50,500,281
        vsync();
        blit(buffer_menu, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    clock_t start_time = clock();
    float elapsed_time = 0.0f;
    bool game_over = false;
    while (!key[KEY_ESC] && !game_over) {
        clear_to_color(buffer, makecol(0, 0, 0));
        elapsed_time = (float)(clock() - start_time) / CLOCKS_PER_SEC;
        rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H / 4, makecol(0, 255, 0));
        rectfill(buffer, 0, SCREEN_H - SCREEN_H / 4, SCREEN_W, SCREEN_H, makecol(0, 255, 0));
        rectfill(buffer, 0, SCREEN_H / 4, SCREEN_W, SCREEN_H - SCREEN_H / 4, makecol(0, 0, 255));

        for (int i = 0; i < 4; i++) {
            log_x[i] += log_speed[i];
            log_x[i + 4] += log_speed[i];
            log_x[i + 8] += log_speed[i];
            if (log_x[i] > SCREEN_W) {
                log_x[i] = 0 - LOG_WIDTH;
                log_speed[i] = (rand() % 4) + 1;
                log_speed[i + 4] = log_speed[i];
            }
            if (log_x[i + 4] > SCREEN_W) {
                log_x[i + 4] = 0 - LOG_WIDTH;
                log_speed[i + 4] = (rand() % 4) + 1;
                log_speed[i] = log_speed[i + 4];
            }
            if (log_x[i + 4] < 0 - LOG_WIDTH) {
                log_x[i + 4] = 0 - LOG_WIDTH;
                log_speed[i + 4] = (rand() % 4) + 1;
                log_speed[i] = log_speed[i + 4];
            }
            if (log_x[i] < 0 - LOG_WIDTH) {
                log_x[i] = SCREEN_W;
                log_speed[i] = -((rand() % 4) + 1);
                log_speed[i + 4] = log_speed[i];
            }
            if (log_x[i + 8] > SCREEN_W) {
                log_x[i + 8] = 0 - LOG_WIDTH;
                log_speed[i + 8] = (rand() % 4) + 1;
                log_speed[i] = log_speed[i + 8];
            }
            if (log_x[i + 8] < 0 - LOG_WIDTH) {
                log_x[i + 8] = 0 - LOG_WIDTH;
                log_speed[i + 8] = (rand() % 4) + 1;
                log_speed[i] = log_speed[i + 8];
            }
            log_speed[i + 4] = log_speed[i];
            log_speed[i + 8] = log_speed[i];
        }
        for (int i = 0; i < 12; i++) {
            masked_blit(log_bmp, buffer, 0, 0, log_x[i], log_y[i], LOG_WIDTH, LOG_HEIGHT);
        }

        int sur_rondin = 0;
        for (int i = 0; i < 12; i++) {
            if (est_sur_rondin(frog_x, frog_y, log_x[i], log_y[i], LOG_WIDTH, LOG_HEIGHT)) {
                sur_rondin = 1;
                frog_x += log_speed[i];
            }
        }

        if (sur_rondin) {
            if (key[KEY_LEFT] && frog_x > 0) {
                frog_x -= FROG_SPEED;
            } else if (key[KEY_RIGHT] && frog_x < SCREEN_W - 32) {
                frog_x += FROG_SPEED;
            } else if (key[KEY_UP] && frog_y > 0) {
                frog_y -= FROG_SPEED;
            } else if (key[KEY_DOWN] && frog_y < SCREEN_H - 32) {
                frog_y += FROG_SPEED;
            }
        } else {
            if (key[KEY_LEFT] && frog_x > 0) {
                frog_x -= FROG_SPEED;
            } else if (key[KEY_RIGHT] && frog_x < SCREEN_W - 32) {
                frog_x += FROG_SPEED;
            } else if (key[KEY_UP] && frog_y > 0) {
                frog_y -= FROG_SPEED;
            } else if (key[KEY_DOWN] && frog_y < SCREEN_H - 32) {
                frog_y += FROG_SPEED;
            }
        }
        if ((sur_rondin == 0 && frog_y + 16 > SCREEN_H / 4 + 16 && frog_y + 16 < SCREEN_H - SCREEN_H / 4) ||
            (sur_rondin == 1 && frog_x > SCREEN_W)) {
            // allegro_message("Perdu ! Votre temps est de 0 secondes");
            game_over = 1;
            score_ = -1;
        }
        if (sur_rondin == 0 && frog_y + FROG_H < SCREEN_H / 4 && frog_x < SCREEN_W && frog_x > 0) {
            // allegro_message("Bien joue ! votre temps est de %.2f secondes\n \tVous avez gagné un ticket ! ", elapsed_time);
            game_over = 1;
            score_ = elapsed_time;
        }
        textprintf_ex(buffer, font, 10, 10, makecol(0, 0, 0), -1, "Score : %.2f ", elapsed_time);
        textprintf_ex(buffer, font, SCREEN_W - 100, 10, makecol(0, 0, 0), -1, "Best : %.2f ", max_score_);

        // textprintf_ex(buffer, font, SCREEN_H - 20, 10, makecol(0, 0, 0), -1, "tentative numéro %d",);

        vsync();
        draw_sprite(buffer, frog_bmp, frog_x, frog_y);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(20);
        num_played++;

        FILE *filemax = fopen(RIVIERE_BEST_SAVE_FILE, "r");
        if (filemax == NULL) {
            allegro_message("Impossible d'ouvrir le fichier %s", RIVIERE_BEST_SAVE_FILE);
            exit(EXIT_FAILURE);
        }
        fscanf(filemax, "%f", &max_score_);
        fclose(filemax);

        if ((score_ != -1 && score_ < max_score_) || max_score_ == -1) {
            max_score_ = score_;
            FILE *filemax = fopen(RIVIERE_BEST_SAVE_FILE, "w");
            if (filemax == NULL) {
                allegro_message("Impossible d'ouvrir le fichier %s", RIVIERE_BEST_SAVE_FILE);
                exit(EXIT_FAILURE);
            }
            fprintf(filemax, "%.2f", max_score_);
            fclose(filemax);
        }
    }

    FILE *fileend = fopen(RIVIERE_END_SAVE_FILE, "w");
    if (fileend == NULL) {
        allegro_message("Impossible d'ouvrir le fichier %s", RIVIERE_END_SAVE_FILE);
        exit(EXIT_FAILURE);
    }
    fprintf(fileend, "%.2f", score_);
    fclose(fileend);
}
END_OF_MAIN()
