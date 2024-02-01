#include "main.h"

int main() {
    // Initialisation de l'aléatoires
    srand(time(NULL));

    // Initialisation d'Allegro
    install_all_allegro();

    // Menu
    DEBUG_MODE > 0 ?: start_menu();

    // Creatin du jeu
    GameState game;
    init_game(&game);

    // Init Bitmap
    init_bitmap(&game);

    // Load sprites
    load_idle_sprites(&game);
    load_walk_sprites(&game);
    load_background_sprite(&game);
    load_background_overlay_sprite(&game);
    load_ticket_sprite(&game);
    game.debug_hud = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    clear_to_color(game.debug_hud, makecol(255, 0, 255));

    // Players creations menu
    players_creation_menu(&game);

    // Boucle de jeu principale
    while (!game.over) {
        // On incrémente le compteur d'animation

        update_animation_frame(&game);

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
        rest(5);
    }

    // On nettoie la mémoire
    clean_game(&game);

    return 0;
}
END_OF_MAIN()
