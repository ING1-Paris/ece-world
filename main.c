// TODO: Changer les BITMAPS des JOUEURS
// TODO: Ajouter des bmp pour les tickets
// TODO: Changer les bmps pour les attractions
// TODO: Ajouter un bmp pour le background
// TODO: Changer bmp exit et stats

// TODO: Faire le menu stats avec SAVE + READ

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <allegro.h>
#include <sys/time.h>

#include "main.h"


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

    // Menu
    start_menu(&game);

    // Players creations menu
    players_creation_menu(&game);


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

        if (close_button_pressed) {
            game.over = true;
        }

        // Gère le framerate, pour éviter que le jeu ne tourne trop vite
        rest(9);
    }

    // On nettoie la mémoire
    clean_game(&game);

    return 0;
}
END_OF_MAIN()
