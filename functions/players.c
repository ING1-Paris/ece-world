#include "players.h"

// Menu de création des joueurs
void players_creation_menu(GameState* game) {
    // Initialisation des personnages
    clear_keybuf();
    for (int i = 0; i < PLAYERS_AMOUNT; i++) {
        game->players[i].x = (SCREEN_WIDTH - PLAYERS_AMOUNT * PLAYER_WIDTH) / 2 + PLAYER_WIDTH * i;
        game->players[i].y = SCREEN_HEIGHT - PLAYER_HEIGHT - 60;
        game->players[i].tickets = TICKETS_AMOUNT;
        game->players[i].direction = DIRECTION_DOWN;
        game->players[i].is_walking = false;
        int pos = 0;
        bool done = game->debug_mode > 0 ? true : false;
        char str[NAME_MAX_LENGTH + 1] = {0};
        game->debug_mode > 0 ? sprintf(str, "Player %d", i + 1) : 0;
        game->debug_mode > 0 ? strcpy(game->players[i].name, str) : 0;
        bool fist_time = true;
        while (!done) {
            if (keypressed()) {
                int newkey = readkey();
                char ascii = newkey & 0xff;   // Partie ASCII de la touche.
                char scancode = newkey >> 8;  // Partie scancode de la touche.

                if (ascii >= 32 && ascii <= 126) {  // Si c'est un caractère imprimable.
                    if (pos < NAME_MAX_LENGTH) {    // Si on n'a pas encore atteint la limite.
                        str[pos] = ascii;           // Ajouter le caractère à la chaîne.
                        pos++;                      // Avancer la position.
                    }
                } else if (scancode == KEY_BACKSPACE) {  // Si c'est la touche de retour arrière.
                    if (pos > 0) {                       // Si on peut effacer un caractère.
                        pos--;                           // Reculer la position.
                        str[pos] = 0;                    // Effacer le caractère.
                    }
                }
            }

            if (key[KEY_ENTER] && str[0] != 0) {
                done = true;
                // Afficher Enregistrement en cours
                textout_centre_ex(screen, game->font, "Enregistrement en cours...", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, makecol(255, 255, 255), -1);
                clear_keybuf();
                rest(500);
            }
            if (key[KEY_ESC]) {
                return;
            }

            display_string_in_box(game->buffer, str, i, game->font, fist_time);
            fist_time = false;
        }
        strcpy(game->players[i].name, str);
        if (game->debug_mode > 0) {
            allegro_message("Nom player %d: %s", i + 1, game->players[i].name);
        }
    }
}

// Affiche la chaîne de caractères dans la boîte de texte.
void display_string_in_box(BITMAP* buffer, char* str, int player_index, FONT* font2, bool first_time) {
    BITMAP* bg = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    draw_diagonal_gradient(bg, grad_colors[player_index * 2], grad_colors[player_index * 2 + 1]);

    // Dessine le fond.
    blit(bg, buffer, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Ecrir "Joueur X, entrez votre nom :"
    char player_str[30];
    sprintf(player_str, "Joueur %d, entrez votre nom :", player_index + 1);
    textout_centre_ex(buffer, font2, player_str, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, makecol(255, 255, 255), -1);

    // Dessine une boîte de texte au milieu de l'écran.
    int box_x = (SCREEN_WIDTH - TEXT_INPUT_BOX_WIDTH) / 2;
    int box_y = (SCREEN_HEIGHT - TEXT_INPUT_BOX_HEIGHT) / 2;
    rectfill(buffer, box_x, box_y, box_x + TEXT_INPUT_BOX_WIDTH, box_y + TEXT_INPUT_BOX_HEIGHT, makecol(255, 255, 255));

    // Crée une bitmap avec le texte.
    BITMAP* text_bitmap = create_bitmap_ex(32, text_length(font, str), text_height(font));  // Création de la bitmap avec une profondeur de couleur de 32 bits.
    clear_to_color(text_bitmap, makecol(255, 0, 255));                                      // Couleur magenta pour le fond.
    textout_ex(text_bitmap, font, str, 0, 0, makecol(0, 0, 0), makecol(255, 0, 255));       // Texte noir, fond magenta.

    // Crée une bitmap étirée.
    int stretch_factor = 3;  // Changez cela pour changer la taille du texte.
    BITMAP* stretched_bitmap = create_bitmap(text_bitmap->w * stretch_factor, text_bitmap->h * stretch_factor);

    // Étire le texte.
    stretch_blit(text_bitmap, stretched_bitmap, 0, 0, text_bitmap->w, text_bitmap->h, 0, 0, stretched_bitmap->w, stretched_bitmap->h);

    // Affiche le texte étiré centré dans la boîte.
    int text_x = box_x + (TEXT_INPUT_BOX_WIDTH - stretched_bitmap->w) / 2;
    int text_y = box_y + (TEXT_INPUT_BOX_HEIGHT - stretched_bitmap->h) / 2;
    draw_sprite(buffer, stretched_bitmap, text_x, text_y);
    if (first_time == true) {
        fadein(buffer);
    } else {
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);  // Affiche le buffer sur l'écran.
    }
    // Libère la mémoire.
    destroy_bitmap(text_bitmap);
    destroy_bitmap(stretched_bitmap);
    destroy_bitmap(bg);
}
