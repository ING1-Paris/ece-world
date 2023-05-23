#ifndef CONSTS_H
#define CONSTS_H

#include <allegro.h>

/* VARIABLE GLOBALE DE *DEBUG UNIQUEMENT* */
extern double fps;
extern double frames_accum;
extern double fps_timer;

// Dimensions de la fenêtre du jeu
#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 900

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50

#define ATTRACTION_WIDTH 100
#define ATTRACTION_HEIGHT 100

#define PLAYER_AMOUNT 2

#define ATTRACTIONS_AMOUNT 7
#define SECONDARY_AMOUNT 2

#define TICKETS_AMOUNT 5

/*TOUCHE DES JOUEURS*/
#define MOUVEMENT_KEYS_AMOUNT 4
#define MISC_KEYS_AMOUNT 5

extern const int PLAYER1_KEYS[MOUVEMENT_KEYS_AMOUNT];
extern const int PLAYER2_KEYS[MOUVEMENT_KEYS_AMOUNT];
extern const int PLAYER3_KEYS[MOUVEMENT_KEYS_AMOUNT];
extern const int PLAYER4_KEYS[MOUVEMENT_KEYS_AMOUNT];

extern const int* PLAYERS_KEYS[MOUVEMENT_KEYS_AMOUNT];

/* ATTRACTIONS NAME */
#define ATTRACTION0_NAME "canard"
#define ATTRACTION1_NAME "cheval"
#define ATTRACTION2_NAME "grenouille"
#define ATTRACTION3_NAME "jackpot"
#define ATTRACTION4_NAME "snake"

extern const char* ATTRACTIONS_NAMES[ATTRACTIONS_AMOUNT];

#endif