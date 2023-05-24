#ifndef CONSTS_H
#define CONSTS_H

#include <allegro.h>

#define DEBUG_MODE 1

/* VARIABLE GLOBALE DE *DEBUG UNIQUEMENT* */
extern double debug_fps;
extern double debug_frames_accum;
extern double debug_timestamp;

// Variable globale pour la fermeture de la fenêtre (par pitié c'est le seul moyen)
extern volatile int close_button_pressed;

// Paramètres fixe duq jeu
#define PLAYERS_AMOUNT 4
#define MAX_PLAYERS_AMOUNT 4
#define TICKETS_AMOUNT 5

// Dimensions de la fenêtre du jeu
#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 900

// Dimensions d'un sprite de joueur
#define PLAYER_WIDTH CHARACTERS_SPRITES_SIZE_STRETCHED
#define PLAYER_HEIGHT CHARACTERS_SPRITES_SIZE_STRETCHED

#define CHARACTERS_SPRITES_SIZE 32
#define CHARACTERS_SPRITES_SIZE_STRETCHED 128

// Directions
#define DIRECTION_DOWN 0
#define DIRECTION_UP 1
#define DIRECTION_RIGHT 2
#define DIRECTION_LEFT 3

#define IDLE_SPRITESHET_FILE "assets/sprites/idle"
#define WALK_SPRITESHET_FILE "assets/sprites/walk"
#define BACKGROUND_FILE "assets/background.bmp"
#define BACKGROUND_OVERLAY_FILE "assets/overlay.bmp"
#define TICKET_FILE "assets/ticket.bmp"

// Dimensions d'un sprite d'attraction
#define ATTRACTION_WIDTH 200
#define ATTRACTION_HEIGHT 200
#define ATTRACTION_SPRITES_WIDTH 100
#define ATTRACTION_SPRITES_HEIGHT 100

// Nombre d'attractions
#define ATTRACTIONS_AMOUNT 7
#define SECONDARY_AMOUNT 2

// Nombre maximum de caractères dans les noms des joueurs
#define NAME_MAX_LENGTH 20

// Touche des joueurs
#define MOUVEMENT_KEYS_AMOUNT 4
#define MISC_KEYS_AMOUNT 5
extern const int PLAYER1_KEYS[MOUVEMENT_KEYS_AMOUNT];
extern const int PLAYER2_KEYS[MOUVEMENT_KEYS_AMOUNT];
extern const int PLAYER3_KEYS[MOUVEMENT_KEYS_AMOUNT];
extern const int PLAYER4_KEYS[MOUVEMENT_KEYS_AMOUNT];
extern const int* PLAYERS_KEYS[MOUVEMENT_KEYS_AMOUNT];

// Nom des attractions
#define ATTRACTION0_NAME "canard"
#define ATTRACTION1_NAME "cheval"
#define ATTRACTION2_NAME "grenouille"
#define ATTRACTION3_NAME "jackpot"
#define ATTRACTION4_NAME "snake"
extern const char* ATTRACTIONS_NAMES[ATTRACTIONS_AMOUNT];

// Page de création des joueurs
#define TEXT_INPUT_BOX_WIDTH 500
#define TEXT_INPUT_BOX_HEIGHT 50
extern const int grad_colors[MAX_PLAYERS_AMOUNT * 2];

#endif