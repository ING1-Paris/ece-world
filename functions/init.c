#include "init.h"

void init_bitmap(GameState* game) {
    for (int i = 0; i < ATTRACTIONS_AMOUNT - SECONDARY_AMOUNT; i++) {
        char path[100];
        // allegro_message("%s", game->attractions[i].name);
        sprintf(path, "assets/sprites/%s.bmp", game->attractions[i].name);
        game->attractions_bitmaps[i] = load_bitmap(path, NULL);
        if (!game->attractions_bitmaps[i]) {
            printf("Impossible de charger le bitmap %s\n", path);
            exit(1);
        }
    }
    for (int i = 0; i < PLAYER_AMOUNT; i++) {
        char path[100];
        sprintf(path, "assets/sprites/player%d.bmp", i + 1);
        game->player_bitmaps[i] = load_bitmap(path, NULL);
        if (!game->player_bitmaps[i]) {
            printf("Impossible de charger le bitmap %s\n", path);
            exit(1);
        }
    }

    // Chargement des fonts
    game->font = load_font("assets/font.pcx", NULL, NULL);
    if (!game->font) {
        allegro_message("Error loading font\n");
        exit(EXIT_FAILURE);
    }
}

void init_game(GameState* game) {
    // Création du buffer pour le rafraîchissement de l'écran
    BITMAP* buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    game->buffer = buffer;

    // Initialisation des variables du jeu
    game->player_speed = 5;
    game->debug = false;
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
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            game->attractions[i * 2 + j].x = SCREEN_WIDTH / 2 - ATTRACTION_WIDTH / 2 + (i - 1) * (ATTRACTION_WIDTH + 50);
            game->attractions[i * 2 + j].y = SCREEN_HEIGHT / 2 - ATTRACTION_HEIGHT / 2 + (j - 1) * (ATTRACTION_HEIGHT + 50);
        }
    }

    /* INITIALIZE PATH */
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
        for (int p = 0; p < PLAYER_AMOUNT; p++) {
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
        for (int p = 0; p < PLAYER_AMOUNT; p++) {
            game->attractions[s].triggered[p] = 0;
        }
    }

    game->attractions[ATTRACTIONS_AMOUNT - 1].is_exit = true;
    game->attractions[ATTRACTIONS_AMOUNT - 2].is_stats = true;

    game->attractions[ATTRACTIONS_AMOUNT - 1].x = SCREEN_WIDTH - ATTRACTION_WIDTH - 10;
    game->attractions[ATTRACTIONS_AMOUNT - 1].y = SCREEN_HEIGHT - ATTRACTION_HEIGHT - 10;

    game->attractions[ATTRACTIONS_AMOUNT - 2].x = 10;
    game->attractions[ATTRACTIONS_AMOUNT - 2].y = SCREEN_HEIGHT - ATTRACTION_HEIGHT - 10;

    strcpy(game->attractions[ATTRACTIONS_AMOUNT - 1].name, "exit");
    strcpy(game->attractions[ATTRACTIONS_AMOUNT - 2].name, "stats");
}

void install_all_allegro() {
    allegro_init();

    fps_timer = current_time();
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



}