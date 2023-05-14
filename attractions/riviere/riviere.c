#include <allegro.h>
#include "time.h"
#include "stdbool.h"
#define SCREEN_W 640
#define SCREEN_H 480
#define LOG_SPEED 2
#define FROG_H 32
#define LOG_WIDTH 128
#define LOG_HEIGHT 64
/*typedef struct grenouille{
    int x;
    int y;
}grenouille;
typedef struct rondin{
    int x;
    int y;
    int direction;
}rondin;*/
int est_sur_rondin(int x_grenouille, int y_grenouille, int x_rondin, int y_rondin, int largeur_rondin, int hauteur_rondin) {
    int sur_rondin = 0;
    if (y_grenouille>= y_rondin && y_grenouille<=y_rondin+hauteur_rondin) {
        if (x_grenouille >= x_rondin && x_grenouille <= x_rondin + largeur_rondin) {
            sur_rondin = 1;
        }
    }
    return sur_rondin;
}

int main() {
    // Initialiser Allegro
    allegro_init();
    install_keyboard();
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_W, SCREEN_H, 0, 0);
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,SCREEN_W,SCREEN_H,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // Charger les sprites à partir de fichiers bitmap
    BITMAP *frog_bmp = load_bitmap("C:\\Users\\redah\\projetalgogrenouille\\grenouilleoff.bmp", NULL);
    BITMAP *log_bmp = load_bitmap("C:\\Users\\redah\\projetalgogrenouille\\bois.bmp", NULL);
    BITMAP *fond= load_bitmap("C:\\Users\\redah\\projetalgogrenouille\\fond.bmp",NULL);
    if (!frog_bmp || !log_bmp || !fond) {
        allegro_message("Impossible de charger les sprites.");
        return 1;
    }
// Déclaration des variables
    int frog_x = SCREEN_W / 2;
    int frog_y = SCREEN_H - FROG_H;
    int score = 0;        
    int log_x[12] = { 0, 0, 0, 0,0, 0, 0, 0,0,0,0,0};
    int log_y[12] = { 120, 180, 240, 300 ,120, 180, 240, 300,120, 180, 240, 300 ,120 };
    int log_speed[12] = { LOG_SPEED, -LOG_SPEED, LOG_SPEED, -LOG_SPEED ,LOG_SPEED, -LOG_SPEED, LOG_SPEED, -LOG_SPEED,LOG_SPEED, -LOG_SPEED, LOG_SPEED, -LOG_SPEED };
     //initialisation rondin
    for (int i = 0; i < 4; i++) {
        log_x[i] = SCREEN_W/3;
        log_x[i+4]= 2*SCREEN_W/3;
        log_x[i+8]=SCREEN_W;
        log_speed[i] = (rand() % 4) + 1;
        log_speed[i+4] =log_speed[i] ;
        log_speed[i+8] =log_speed[i];
}
    //création des buffer, initialisation du temps,de la vitesse de la grenouille et du score
    int frog_speed = 8;
    BITMAP *buffer= create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(buffer);
    clock_t start_time = clock(); // temps de début du jeu
    float elapsed_time = 0.0f; // temps écoulé
    float scorefinal[10];
    float max_score=0;
    float score=0;
    int num_played = 0;
// Boucle de jeu
        while (!key[KEY_ESC]) {
            clear_to_color(buffer, makecol(0, 0, 0));
            elapsed_time = (float)(clock() - start_time) / CLOCKS_PER_SEC;
            // Dessin du fond d'écran
            rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H / 4, makecol(0, 255, 0));
            rectfill(buffer, 0, SCREEN_H - SCREEN_H / 4, SCREEN_W, SCREEN_H, makecol(0, 255, 0));
            rectfill(buffer,0,SCREEN_H/4,SCREEN_W,SCREEN_H-SCREEN_H/4, makecol(0,0,255));

           
            textprintf_ex(screen, font, 10, 10, makecol(0, 0, 0), -1, "Temps : %d", score);
            vsync();
            acquire_screen();
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            release_screen();
        }
// faire fonction grenouille qui tombe à l'eau (perdu avec temps =0)
// faire fonction gagner si la grenouille arrive à destination avec le temps
// faire fonction afficher le score du joueur




}END_OF_MAIN()



