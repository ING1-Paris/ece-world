#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <allegro.h>

#include "tools.h"

// Renvoie le temps actuel en millisecondes
double current_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000.0 + time.tv_usec / 1000.0;
}

// Calcul le nombre de frames par seconde
// Et l'affiche dans le HUD si le mode debug est activé
void draw_fps(GameState* game) {
    double current_timestamp = current_time();

    if (current_timestamp >= debug_fps_timer + 1000) {
        debug_fps = debug_frames_accum;
        debug_frames_accum = 0;
        debug_fps_timer = current_timestamp;
    }

    debug_frames_accum++;

    if (game->debug) {
        char fps_str[30];
        char frame_accum_str[30];
        char fps_timer_str[30];
        char player_speed_str[30];

        sprintf(fps_str, "FPS: %.0f", debug_fps);
        sprintf(frame_accum_str, "Frames: %.0f", debug_frames_accum);
        sprintf(fps_timer_str, "Timestamp: %.0f", debug_fps_timer);
        sprintf(player_speed_str, "Pl Speed: %d", game->player_speed);

        textout_ex(game->buffer, game->font, fps_str, 10, 20, makecol(255, 255, 255), -1);
        textout_ex(game->buffer, game->font, frame_accum_str, 10, 40, makecol(255, 255, 255), -1);
        textout_ex(game->buffer, game->font, player_speed_str, 10, 60, makecol(255, 255, 255), -1);
        textout_ex(game->buffer, game->font, fps_timer_str, 10, 80, makecol(255, 255, 255), -1);
    }
}

// Renvoie une couleur aléatoire
int random_color() {
    int red = rand() % 256;
    int green = rand() % 256;
    int blue = rand() % 256;

    return makecol(red, green, blue);
}

// Libère la mémoire et détruit les bitmaps
void clean_game(GameState* game) {
    // Libère la mémoire salope

    destroy_font(game->font);

    destroy_bitmap(game->buffer);
    for (int i = 0; i < ATTRACTIONS_AMOUNT - SECONDARY_AMOUNT; i++) {
        destroy_bitmap(game->attractions_bitmaps[i]);
    }
    for (int i = 0; i < PLAYERS_AMOUNT; i++) {
        destroy_bitmap(game->player_bitmaps[i]);
    }
}

// Pour quitter le jeu avec la croix dans la fenêtre
void close_button_handler() {
    close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)