#include "keyboard.h"

// Fonction qui gère les entrées clavier
void handle_input(GameState* game) {
    // Récupère les entrées clavier
    clear_keybuf();
    for (int i = 0; i < PLAYERS_AMOUNT; i++) {
        Player player = game->players[i];

        /* DÉPLACEMENT DES JOUEURS */
        if (
            (key[PLAYERS_KEYS[i][0]] && player.y - game->player_speed >= 0) ||
            (key[PLAYERS_KEYS[i][1]] && player.y + PLAYER_HEIGHT + game->player_speed <= SCREEN_HEIGHT) ||
            (key[PLAYERS_KEYS[i][2]] && player.x - game->player_speed >= 0) ||
            (key[PLAYERS_KEYS[i][3]] && player.x + PLAYER_WIDTH + game->player_speed <= SCREEN_WIDTH)) {
            player.is_walking = true;

            // Sauvegarder les anciennes coordonnées en cas de collision
            int old_x = player.x;
            int old_y = player.y;

            if (key[PLAYERS_KEYS[i][0]] && player.y - game->player_speed >= 0) {
                player.y -= game->player_speed;
                player.direction = DIRECTION_UP;
            }
            if (key[PLAYERS_KEYS[i][1]] && player.y + PLAYER_HEIGHT + game->player_speed <= SCREEN_HEIGHT) {
                player.y += game->player_speed;
                player.direction = DIRECTION_DOWN;
            }
            if (key[PLAYERS_KEYS[i][2]] && player.x - game->player_speed >= 0) {
                player.x -= game->player_speed;
                player.direction = DIRECTION_LEFT;
            }
            if (key[PLAYERS_KEYS[i][3]] && player.x + PLAYER_WIDTH + game->player_speed <= SCREEN_WIDTH) {
                player.x += game->player_speed;
                player.direction = DIRECTION_RIGHT;
            }

            // Vérifier les collisions avec les autres joueurs
            for (int j = 0; j < PLAYERS_AMOUNT; j++) {
                if (i != j) {
                    Player other = game->players[j];
                    if (player.x < other.x + PLAYER_WIDTH - 64 && player.x + PLAYER_WIDTH - 64 > other.x &&
                        player.y < other.y + PLAYER_HEIGHT - 32 && player.y + PLAYER_HEIGHT - 32 > other.y) {
                        // Collision détectée, rétablir les anciennes coordonnées
                        player.x = old_x;
                        player.y = old_y;
                    }
                }
            }

        } else {
            player.is_walking = false;
        }

        game->players[i] = player;
    }

    /* GESTION DES TOUCHES DE RÉGLAGE DE LA VITESSE */
    if (key[KEY_ENTER]) {
        if (game->player_speed < 10 && !game->PRESSED_MISC_KEYS[0]) {
            game->player_speed++;
        }
        game->PRESSED_MISC_KEYS[0] = true;
    } else {
        game->PRESSED_MISC_KEYS[0] = false;
    }

    if (key[KEY_RSHIFT]) {
        if (game->player_speed > 1 && !game->PRESSED_MISC_KEYS[1]) {
            game->player_speed--;
        }
        game->PRESSED_MISC_KEYS[1] = true;
    } else {
        game->PRESSED_MISC_KEYS[1] = false;
    }

    if (key[KEY_0]) {
        if (game->player_speed > 1 && !game->PRESSED_MISC_KEYS[2]) {
            if (game->debug_mode == 2) {
                allegro_message("Debug mode desactivated");
                game->debug_mode = 0;
            } else {
                game->debug_mode++;
                allegro_message("Debug mode : %d", game->debug_mode);
            }
        }
        game->PRESSED_MISC_KEYS[2] = true;
    } else {
        game->PRESSED_MISC_KEYS[2] = false;
    }

    if (key[KEY_ESC]) {
        if (!game->attraction_is_running && !game->PRESSED_MISC_KEYS[3]) {
            game->over = true;
        }
        game->PRESSED_MISC_KEYS[3] = true;
    } else {
        game->PRESSED_MISC_KEYS[3] = false;
    }
    if (key[KEY_R]) {
        if (!game->attraction_is_running && !game->PRESSED_MISC_KEYS[4]) {
            load_idle_sprites(game);
            load_walk_sprites(game);
            load_background_sprite(game);
            load_background_overlay_sprite(game);
        }
        game->PRESSED_MISC_KEYS[4] = true;
    } else {
        game->PRESSED_MISC_KEYS[4] = false;
    }
}