#include <stdio.h>
#include <allegro.h>
#include "math.h"
#define SCREEN_W 640
#define SCREEN_H 480
typedef struct {
    int x, y;
    int speed_x, speed_y;
    int is_alive;
} Duck;
int canardcollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    return !(x1 + w1 < x2 || x2 + w2 < x1 || y1 + h1 < y2 || y2 + h2 < y1);
}
int main() {
    // Initialisation d'Allegro
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_W, SCREEN_H, 0, 0);

    BITMAP *canard = load_bitmap("../canard.bmp", NULL);
    BITMAP *harpon = load_bitmap("../harpon.bmp", NULL);
    BITMAP *filet = load_bitmap("../filet.bmp",NULL);

    // Variables de jeu
    int score = 0;
    int ducks_caught = 0;
    int time_elapsed = 0;
    int fishing_rod_x = SCREEN_W / 2;
    int fishing_rod_y = SCREEN_H - 100;
    int canard_x[10];
    int canard_y[10];
    int vitesse_canard[10];
    clock_t start_time = clock();
    float elapsed_time = 0.0f;
    for(int i=0;i<10;i++){
        vitesse_canard[i]=(rand() %10)-5;
        canard_x[i]= rand() % SCREEN_W +vitesse_canard[i];
        canard_y[i] = rand() % (SCREEN_H - 100)+vitesse_canard[i];
    }
    BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *buffer_menu = create_bitmap(SCREEN_W, SCREEN_H);

    Duck ducks[10];

    
    for (int i = 0; i < 10; i++) {
        ducks[i].x = rand() % SCREEN_W;
        ducks[i].y = rand() % SCREEN_H;
        ducks[i].speed_x = rand() % 6 - 3;
        ducks[i].speed_y = rand() % 6 - 3;
        ducks[i].is_alive = 1;
    }
    int pos_x[10];
    int pos_y[10];
    for (int i = 0; i < 10; i++) {
        pos_x[i]=10+rand()%60;
        pos_y[i]=10+rand()%60;
    }
    while(!key[KEY_ENTER]) {

        int button_x = 100;
        int button_height = 50;
        int button_xs = (SCREEN_W - button_x) / 2;
        int button_y = (SCREEN_H - button_height) / 2;
        rectfill(buffer_menu, 0, 0, SCREEN_W, SCREEN_W, makecol(0, 0, 255));
        rectfill(buffer_menu, button_xs, button_y, button_xs + button_x, button_y + button_height, makecol(255, 255, 255));
        textout_centre_ex(buffer_menu, font, "Play", SCREEN_W / 2, SCREEN_H / 2, makecol(0, 0, 0), -1);
        
        vsync();
        blit(buffer_menu, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    while (!key[KEY_ESC] ) {
        elapsed_time = (float) (clock() - start_time) / CLOCKS_PER_SEC;
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
                }}}
        draw_sprite(buffer,filet,0,0);
        for (int i = 0; i < 10; i++) {
            ducks[i].x += ducks[i].speed_x;
            ducks[i].y += ducks[i].speed_y;
            if (ducks[i].x < 0 || ducks[i].x > SCREEN_W) {
                ducks[i].speed_x = -ducks[i].speed_x;
            }
            if (ducks[i].y < 0 || ducks[i].y > SCREEN_H) {
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

            if (ducks[i].is_alive==0) {
                draw_sprite(buffer,canard,pos_x[i],pos_y[i]);
            }
            if (ducks[i].is_alive) {
            draw_sprite(buffer, canard, ducks[i].x, ducks[i].y);
        }}
        if(elapsed_time>10.00 && score>4 && score < 11){
            allegro_message("Bien joue ! vous avez attrapé %d canards\n \tVous avez gagné un ticket ! ", score);
            allegro_exit();
        }
        if(elapsed_time>10.00 && score<4 && score>0 ){
            allegro_message("Vous n'avez attrapé aucun canard\n \tVous n'avez rien gagné ");
            allegro_exit();
        }
        textprintf_centre_ex(screen, font, SCREEN_W / 2, 10, makecol(255, 255, 255),-1, "Score: %d", score);
        draw_sprite(buffer, harpon, mouse_x-harpon->w, mouse_y);
        textprintf_ex(buffer, font, 10, 10, makecol(0, 0, 0), -1, "Temps ecoule : %.2f secondes", 10.00-elapsed_time);
        vsync();
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }

    // Libération des ressources graphiques
    destroy_bitmap(canard);
    destroy_bitmap(harpon);
    destroy_bitmap(buffer);

    allegro_exit();
    return 0;
}END_OF_MAIN()
 

