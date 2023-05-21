#include <stdio.h>
#include <allegro.h>
#include <sys/time.h>
#include "math.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct {
    int x, y;
    int speed_x, speed_y;
    int is_alive;
} Duck;

int canardcollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    return !(x1 + w1 < x2 || x2 + w2 < x1 || y1 + h1 < y2 || y2 + h2 < y1);
}

double get_elapsed_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
}

int main() {
    // Initialisation d'Allegro
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    BITMAP *canard = load_bitmap("attractions/canard/assets/canard.bmp", NULL);
    BITMAP *harpon = load_bitmap("attractions/canard/assets/harpon.bmp", NULL);
    BITMAP *filet = load_bitmap("attractions/canard/assets/filet.bmp", NULL);

    if (!canard) {
        printf("Erreur lors du chargement de l'image du canard\n");

        return 1;
    }
    if (!harpon) {
        printf("Erreur lors du chargement de l'image du harpon\n");

        return 1;
    }
    if (!filet) {
        printf("Erreur lors du chargement de l'image du filet\n");

        return 1;
    }
    // Variables de jeu
    int score = 0;
    double start_time = get_elapsed_time();
    double elapsed_time = 0;

    BITMAP *buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP *buffer_menu = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);

    Duck ducks[10];

    for (int i = 0; i < 10; i++) {
        ducks[i].x = rand() % SCREEN_WIDTH;
        ducks[i].y = rand() % SCREEN_HEIGHT;
        ducks[i].speed_x = rand() % 6 - 3;
        ducks[i].speed_y = rand() % 6 - 3;
        ducks[i].is_alive = 1;
    }
    int pos_x[10];
    int pos_y[10];
    for (int i = 0; i < 10; i++) {
        pos_x[i] = 10 + rand() % 60;
        pos_y[i] = 10 + rand() % 60;
    }
    while (!key[KEY_ENTER]) {
        int button_x = 100;
        int button_height = 50;
        int button_xs = (SCREEN_WIDTH - button_x) / 2;
        int button_y = (SCREEN_HEIGHT - button_height) / 2;
        rectfill(buffer_menu, 0, 0, SCREEN_WIDTH, SCREEN_WIDTH, makecol(0, 0, 255));
        rectfill(buffer_menu, button_xs, button_y, button_xs + button_x, button_y + button_height, makecol(255, 255, 255));
        textout_centre_ex(buffer_menu, font, "Play", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, makecol(0, 0, 0), -1);

        vsync();
        blit(buffer_menu, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    while (!key[KEY_ESC]) {
        double elapsed_time = get_elapsed_time() - start_time;
        clear_to_color(buffer, makecol(0, 0, 255));
        if (mouse_b & 1) {
            for (int i = 0; i < 10; i++) {
                if (ducks[i].is_alive) {
                    int distance_x = ducks[i].x - mouse_x;
                    int distance_y = ducks[i].y - mouse_y;
                    int distance = sqrt(distance_x * distance_x + distance_y * distance_y);
                    if (distance < 40) {
                        ducks[i].is_alive = 0;
                        score++;
                    }
                }
            }
        }
        draw_sprite(buffer, filet, 0, 0);
        for (int i = 0; i < 10; i++) {
            ducks[i].x += ducks[i].speed_x;
            ducks[i].y += ducks[i].speed_y;
            if (ducks[i].x < 0 || ducks[i].x > SCREEN_WIDTH) {
                ducks[i].speed_x = -ducks[i].speed_x;
            }
            if (ducks[i].y < 0 || ducks[i].y > SCREEN_HEIGHT) {
                ducks[i].speed_y = -ducks[i].speed_y;
            }
            for (int j = 0; j < 10; j++) {
                if (i != j && canardcollision(ducks[i].x, ducks[i].y, 40, 40, ducks[j].x, ducks[j].y, 40, 40)) {
                    ducks[i].speed_x = -ducks[i].speed_x;
                    ducks[i].speed_y = -ducks[i].speed_y;
                    ducks[j].speed_x = -ducks[j].speed_x;
                    ducks[j].speed_y = -ducks[j].speed_y;
                }
            }
        }

        for (int i = 0; i < 10; i++) {
            if (ducks[i].is_alive == 0) {
                draw_sprite(buffer, canard, pos_x[i], pos_y[i]);
            }
            if (ducks[i].is_alive) {
                draw_sprite(buffer, canard, ducks[i].x, ducks[i].y);
            }
        }

        if (elapsed_time > 10.00 && score > 4 && score < 11) {
            FILE *fichier = fopen("attractions/canard/end.txt", "w");
            if (fichier == NULL) {
                allegro_message("Erreur lors de l'ouverture du fichier\n");
                exit(EXIT_FAILURE);
            }
            allegro_message("Bien joue ! vous avez attrapé %d canards\n \tVous avez gagné un ticket ! ", score);
            fprintf(fichier, "%d", score);
            allegro_exit();
            fclose(fichier);
        }
        else if (elapsed_time > 10.00) {
            FILE *fichier = fopen("attractions/canard/end.txt", "w");
            if (fichier == NULL) {
                allegro_message("Erreur lors de l'ouverture du fichier\n");
                exit(EXIT_FAILURE);
            }
            allegro_message("Vous n'avez attrapé aucun canard\n \tVous n'avez rien gagné ");
            fprintf(fichier, "0");
            allegro_exit();
            fclose(fichier);
        }

        allegro_message("Elapsted time : %f", elapsed_time);

        textprintf_centre_ex(buffer, font, SCREEN_WIDTH / 2, 10, makecol(255, 255, 255), -1, "Score: %d", score);
        draw_sprite(buffer, harpon, mouse_x - harpon->w, mouse_y);
        textprintf_ex(buffer, font, 10, 10, makecol(0, 0, 0), -1, "Temps ecoule : %.2f secondes", 10.00 - elapsed_time);
        vsync();
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    // Libération des ressources graphiques
    destroy_bitmap(canard);
    destroy_bitmap(harpon);
    destroy_bitmap(buffer);

    allegro_exit();
    return 0;
}
END_OF_MAIN()
