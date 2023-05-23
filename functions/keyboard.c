#include "keyboard.h"

void handle_input(GameState* game) {
    // Récupère les entrées clavier
    clear_keybuf();
    for (int i = 0; i < PLAYER_AMOUNT; i++) {
        Player player = game->players[i];

        /* DÉPLACEMENT DES JOUEURS */
        if (key[PLAYERS_KEYS[i][0]] && player.y - game->player_speed >= 0) {
            player.y -= game->player_speed;
        }
        if (key[PLAYERS_KEYS[i][1]] && player.y + PLAYER_HEIGHT + game->player_speed <= SCREEN_HEIGHT) {
            player.y += game->player_speed;
        }
        if (key[PLAYERS_KEYS[i][2]] && player.x - game->player_speed >= 0) {
            player.x -= game->player_speed;
        }
        if (key[PLAYERS_KEYS[i][3]] && player.x + PLAYER_WIDTH + game->player_speed <= SCREEN_WIDTH) {
            player.x += game->player_speed;
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
            game->debug = !game->debug;
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
}