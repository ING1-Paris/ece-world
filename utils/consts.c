#include "consts.h"

/* ======================== *
 * POUR LE DEBUG UNIQUEMENT *
 *  À DES FINS D'AFFICHAGE  *
 *  AFFICHER APPUYER SUR 0  *
 * ======================== */
double debug_fps;
double debug_frames_accum;
double debug_fps_timer;
//======================== */

// Voir "consts.h" pour les informations sur les variables

const int PLAYER1_KEYS[MOUVEMENT_KEYS_AMOUNT] = {KEY_Z, KEY_S, KEY_Q, KEY_D};
const int PLAYER2_KEYS[MOUVEMENT_KEYS_AMOUNT] = {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
const int PLAYER3_KEYS[MOUVEMENT_KEYS_AMOUNT] = {KEY_I, KEY_K, KEY_J, KEY_L};
const int PLAYER4_KEYS[MOUVEMENT_KEYS_AMOUNT] = {KEY_T, KEY_G, KEY_F, KEY_H};

const int* PLAYERS_KEYS[MOUVEMENT_KEYS_AMOUNT] = {PLAYER1_KEYS, PLAYER2_KEYS, PLAYER3_KEYS, PLAYER4_KEYS};

const char* ATTRACTIONS_NAMES[ATTRACTIONS_AMOUNT] = {ATTRACTION0_NAME, ATTRACTION1_NAME, ATTRACTION2_NAME, ATTRACTION3_NAME, ATTRACTION4_NAME};

volatile int close_button_pressed = FALSE;

const int grad_colors[MAX_PLAYERS_AMOUNT * 2] = {16750894, 14292071, 15740866, 6329578, 15740866, 6329578, 6329578, 16750894};