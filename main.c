#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <allegro.h>
#include <sys/time.h>

#include "main.h"

/* ======================= * 
* POUR LE DEBUG UNIQUEMENT *
*  À DES FINS D'AFFICHAGE  *
*  AFFICHER AVEC TOUCHE 0  *
* ======================== */
double fps;             // *
double frames_accum;    // *
double fps_timer;       // *
//======================== */z


const int PLAYER1_KEYS[MOUVEMENT_KEYS_AMOUNT] = {KEY_Z, KEY_S, KEY_Q, KEY_D};
const int PLAYER2_KEYS[MOUVEMENT_KEYS_AMOUNT] = {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
const int PLAYER3_KEYS[MOUVEMENT_KEYS_AMOUNT] = {KEY_I, KEY_K, KEY_J, KEY_L};
const int PLAYER4_KEYS[MOUVEMENT_KEYS_AMOUNT] = {KEY_T, KEY_G, KEY_F, KEY_H};

const int* PLAYERS_KEYS[MOUVEMENT_KEYS_AMOUNT] = {PLAYER1_KEYS, PLAYER2_KEYS, PLAYER3_KEYS, PLAYER4_KEYS};

const char* ATTRACTIONS_NAMES[ATTRACTIONS_AMOUNT] = {ATTRACTION0_NAME, ATTRACTION1_NAME, ATTRACTION2_NAME, ATTRACTION3_NAME, ATTRACTION4_NAME};


int main() {
    // Initialisation de l'aléatoires
    srand(time(NULL));

    // Initialisation d'Allegro
    install_all_allegro();

    // Creatin du jeu
    GameState game;
    init_game(&game);

    // Init Bitmap
    init_bitmap(&game);

    // Players creations menu
    players_creation_menu(&game);
    show_mouse(screen);
    // Boucle de jeu principale
    while (!game.over) {
        // Gère les entrées clavier
        handle_input(&game);

        // Vérifie les collisions avec les attractions
        check_collisions(&game);

        // On lance les attractions
        run_attractions(&game);

        // On vérifie si il y a un gagnant
        check_for_winner(&game);

        // Rafraîchit l'écran
        display(&game);

        // Gère le framerate, pour éviter que le jeu ne tourne trop vite
        rest(9);
    }

    clean_game(&game);

    return 0;
}
END_OF_MAIN()
