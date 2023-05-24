#include "init.h"

// Charge les bitmaps du jeu
void init_bitmap(GameState* game) {
    // Chargement des bitmaps des attractions
    for (int i = 0; i < ATTRACTIONS_AMOUNT - SECONDARY_AMOUNT; i++) {
        char path[100];
        // allegro_message("%s", game->attractions[i].name);
        sprintf(path, "assets/sprites/old/%s.bmp", game->attractions[i].name);
        BITMAP* sprite = load_bitmap(path, NULL);
        BITMAP* temp = create_sub_bitmap(sprite, 0, 0, ATTRACTION_SPRITES_WIDTH, ATTRACTION_SPRITES_HEIGHT);
        game->attractions_bitmaps[i] = create_bitmap(ATTRACTION_WIDTH, ATTRACTION_HEIGHT);
        stretch_blit(temp, game->attractions_bitmaps[i], 0, 0, ATTRACTION_SPRITES_WIDTH, ATTRACTION_SPRITES_HEIGHT, 0, 0, ATTRACTION_WIDTH, ATTRACTION_HEIGHT);

        if (!game->attractions_bitmaps[i]) {
            printf("Impossible de charger le bitmap %s\n", path);
            exit(1);
        }

        destroy_bitmap(sprite);
        destroy_bitmap(temp);
    }


    // Chargement des fonts
    game->font = load_font("assets/font.pcx", NULL, NULL);
    if (!game->font) {
        allegro_message("Error loading font\n");
        exit(EXIT_FAILURE);
    }
}

// Initialise le jeu
void init_game(GameState* game) {
    // Création du buffer du jeu
    BITMAP* buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    game->buffer = buffer;

    // Initialisation des variables du jeu
    game->player_speed = 3;
    game->animation_frame = 0;
    game->last_frame_time = 0;
    game->debug_mode = DEBUG_MODE;
    game->over = false;
    game->winner_displayed = false;
    game->stats_displayed = false;
    game->attraction_is_over = false;

    game->winner = -1;
    game->attraction_is_running = false;
    game->attraction_is_over = false;
    game->attraction_index = -1;
    game->attraction_winner = -1;
    game->attraction_winner_2 = -1;
    game->attraction_winner_score = -1;
    game->attraction_winner_2_score = -1;

    // Initialisation des touches
    for (int i = 0; i < MISC_KEYS_AMOUNT; i++) {
        game->PRESSED_MISC_KEYS[i] = false;
    }

    // Initialisation des attractions
    int attraction_spacing_x = 150;
    int attraction_spacing_y = 150;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            // Ici, on ajoute un décalage supplémentaire basé sur l'espacement défini.
            game->attractions[i * 2 + j].y = SCREEN_HEIGHT / 2 - ATTRACTION_HEIGHT / 2 + (j - 1) * (ATTRACTION_HEIGHT + attraction_spacing_y) + (j == 1 ? attraction_spacing_y / 2 : 0);

            int attraction_in_row = j == 0 ? 3 : 2;

            // Et ici aussi pour l'axe "x".
            game->attractions[i * 2 + j].x = (SCREEN_WIDTH - attraction_in_row * (ATTRACTION_WIDTH + attraction_spacing_x)) / 2 + i * (ATTRACTION_WIDTH + (attraction_in_row == 3 ? attraction_spacing_x : attraction_spacing_x * 2));
        }
    }

    // Initialisation des chemins des attractions
    for (int a = 0; a < ATTRACTIONS_AMOUNT - SECONDARY_AMOUNT; a++) {
        char attractions_directory_path_temp[50];
        strcpy(game->attractions[a].name, ATTRACTIONS_NAMES[a]);
        sprintf(attractions_directory_path_temp, "games/%s/", game->attractions[a].name);
        sprintf(game->attractions[a].executable_path, "%s%s.o", attractions_directory_path_temp, game->attractions[a].name);
        sprintf(game->attractions[a].end_path, "%s%s", attractions_directory_path_temp, "end.txt");
        sprintf(game->attractions[a].best_path, "%s%s", attractions_directory_path_temp, "best.txt");
    }

    for (int a = 0; a < ATTRACTIONS_AMOUNT - SECONDARY_AMOUNT; a++) {
        game->attractions[a].width = ATTRACTION_WIDTH;
        game->attractions[a].height = ATTRACTION_HEIGHT;
        game->attractions[a].player_on_amount = 0;
        game->attractions[a].is_exit = false;
        game->attractions[a].is_stats = false;
        for (int p = 0; p < PLAYERS_AMOUNT; p++) {
            game->attractions[a].triggered[p] = 0;
        }

        // ininialize attraction's end file
        FILE* end_file = fopen(game->attractions[a].end_path, "w");
        if (end_file == NULL) {
            printf("Error opening %s\n", game->attractions[a].end_path);
            exit(1);
        }
        fprintf(end_file, "-1");
        fclose(end_file);
    }

    for (int s = ATTRACTIONS_AMOUNT - SECONDARY_AMOUNT; s < ATTRACTIONS_AMOUNT; s++) {
        game->attractions[s].width = ATTRACTION_WIDTH;
        game->attractions[s].height = ATTRACTION_HEIGHT;
        game->attractions[s].player_on_amount = 0;

        for (int p = 0; p < PLAYERS_AMOUNT; p++) {
            game->attractions[s].triggered[p] = 0;
        }
    }

    // Initialisation des attractions secondaires
    game->attractions[ATTRACTIONS_AMOUNT - 1].is_exit = true;
    game->attractions[ATTRACTIONS_AMOUNT - 1].x = SCREEN_WIDTH - ATTRACTION_WIDTH - 10;
    game->attractions[ATTRACTIONS_AMOUNT - 1].y = SCREEN_HEIGHT - ATTRACTION_HEIGHT - 10;
    strcpy(game->attractions[ATTRACTIONS_AMOUNT - 1].name, "exit");

    game->attractions[ATTRACTIONS_AMOUNT - 2].is_stats = true;
    game->attractions[ATTRACTIONS_AMOUNT - 2].x = 10;
    game->attractions[ATTRACTIONS_AMOUNT - 2].y = SCREEN_HEIGHT - ATTRACTION_HEIGHT - 10;
    strcpy(game->attractions[ATTRACTIONS_AMOUNT - 2].name, "stats");
}

// Installe toutes les modules d'Allegro nécessaires
// et gère d'autres paramètres de la fenêtre
void install_all_allegro() {
    allegro_init();

    debug_timestamp = current_time();
    if (install_sound(DIGI_NONE, MIDI_NONE, NULL) != 0) {
        allegro_message("Error initializing sound system: %s\n", allegro_error);
        exit(EXIT_FAILURE);
    }

    if (install_keyboard() != 0) {
        allegro_message("Error initializing keyboard: %s\n", allegro_error);

        exit(EXIT_FAILURE);
    }

    if (install_timer() != 0) {
        allegro_message("Error initializing timer: %s\n", allegro_error);
        exit(EXIT_FAILURE);
    }

    // Configuration de la fenêtre du jeu
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    // Affiche la souris (ne marche que préciséement une fois sur deux)
    enable_hardware_cursor();
    show_mouse(screen);

    // Change le titre de la fenêtre
    set_window_title("ECE World 2023");

    // On définit le gestionnaire du bouton de fermeture.
    LOCK_FUNCTION(close_button_handler);
    set_close_button_callback(close_button_handler);
}