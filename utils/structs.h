#ifndef STRUCTS_H
#define STRUCTS_H

#include <allegro.h>
#include <stdbool.h>
#include <stdio.h>

#include "consts.h"

// Structure de données pour les personnages
typedef struct t_player {
    char name[20];
    int direction;
    int x;
    int y;
    int tickets;

    bool is_walking;

    BITMAP*** idle_bitmaps;  // Liste de bitmaps (4 directions, 2 frames)
    BITMAP*** walk_bitmaps;  // Liste de bitmaps (4 directions, 4 frames)

} Player;

// Structure de données pour les attractions spéciaux
typedef struct t_attraction {
    int x;
    int y;
    int width;
    int height;
    int player_on_amount;

    bool triggered[PLAYERS_AMOUNT];
    bool is_exit;
    bool is_stats;

    char name[20];

    char executable_path[100];
    char end_path[100];
    char best_path[100];
} Attraction;

typedef struct t_gameState {
    int player_speed;
    int winner;
    int animation_frame;
    double last_frame_time;

    bool PRESSED_MISC_KEYS[MISC_KEYS_AMOUNT];
    int debug_mode;
    bool over;
    bool attraction_is_running;
    bool stats_displayed;
    bool winner_displayed;
    bool attraction_is_over;

    int attraction_index;
    int attraction_winner;
    int attraction_winner_2;
    float attraction_winner_score;
    float attraction_winner_2_score;

    FONT* font;
    BITMAP* buffer;
    BITMAP* background;
    BITMAP* background_overlay;
    BITMAP* debug_hud;
    BITMAP* ticket;
    BITMAP* attractions_bitmaps[ATTRACTIONS_AMOUNT - SECONDARY_AMOUNT];
    BITMAP* player_bitmaps[PLAYERS_AMOUNT];
    Player players[PLAYERS_AMOUNT];
    Attraction attractions[ATTRACTIONS_AMOUNT];
} GameState;

#endif