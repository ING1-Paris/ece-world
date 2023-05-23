#include "display.h"

// Fonction de rafraîchissement de l'écran
void display(GameState* game) {
    // Efface l'écran
    clear_to_color(game->buffer, makecol(0, 128, 0));

    if (game->winner_displayed == true) {
        set_trans_blender(0, 0, 0, 128);
        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
        rectfill(game->buffer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, makecol(0, 0, 0));
        drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
        char winner_str[50];
        sprintf(winner_str, "Le joueur %s a gagne !", game->players[game->winner].name);
        // Ecrire un PARTIE TERMINEE
        textout_centre_ex(game->buffer, game->font, "PARTIE TERMINEE", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20, makecol(255, 255, 255), -1);
        textout_centre_ex(game->buffer, game->font, winner_str, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, makecol(255, 255, 255), -1);
        textout_centre_ex(game->buffer, game->font, "Appuyez sur ECHAP pour quitter", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20, makecol(255, 255, 255), -1);
        blit(game->buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        while (!key[KEY_ESC]) {
        }
        exit(0);
    }

    // Dessine les personnages
    for (int i = 0; i < PLAYER_AMOUNT; i++) {
        Player player = game->players[i];
        // rectfill(game->buffer, player.x, player.y, player.x + PLAYER_WIDTH, player.y + PLAYER_HEIGHT, player.color);
        draw_sprite(game->buffer, game->player_bitmaps[i], player.x, player.y);
    }

    // Dessine les attractions
    for (int a = 0; a < ATTRACTIONS_AMOUNT; a++) {
        int color = 0;
        if (game->attractions[a].is_exit == true) {
            if (game->attractions[a].player_on_amount == 0) {
                color = makecol(0, 0, 0);
            } else if (game->attractions[a].player_on_amount < PLAYER_AMOUNT) {
                color = makecol(255, 77, 0);
            } else if (game->attractions[a].player_on_amount == PLAYER_AMOUNT) {
                color = makecol(255, 0, 0);
            }
        } else if (game->attractions[a].is_stats == true) {
            if (game->attractions[a].player_on_amount == 0) {
                color = makecol(0, 0, 255);
            } else if (game->attractions[a].player_on_amount < PLAYER_AMOUNT) {
                color = makecol(0, 128, 255);
            } else if (game->attractions[a].player_on_amount == PLAYER_AMOUNT) {
                color = makecol(200, 0, 255);
            }
        } else if (game->attractions[a].player_on_amount == 0) {
            color = makecol(255, 0, 0);
        } else if (game->attractions[a].player_on_amount < PLAYER_AMOUNT) {
            color = makecol(255, 255, 0);
        } else if (game->attractions[a].player_on_amount == PLAYER_AMOUNT) {
            color = makecol(0, 255, 0);
        }

        if (game->attractions[a].is_exit == false && game->attractions[a].is_stats == false) {
            draw_sprite(game->buffer, game->attractions_bitmaps[a], game->attractions[a].x, game->attractions[a].y);
        } else {
            rectfill(game->buffer, game->attractions[a].x, game->attractions[a].y, game->attractions[a].x + game->attractions[a].width, game->attractions[a].y + game->attractions[a].height, color);
        }

        //  Écrire le nombre de joueurs sur l'attraction et le nom de l'attraction
        if (game->attractions[a].player_on_amount == 0) {
        } else if (game->attractions[a].player_on_amount < PLAYER_AMOUNT) {
            char player_on_amount_str[30];
            sprintf(player_on_amount_str, "%d", game->attractions[a].player_on_amount);
            // Faire un fond noir derrière l'attraction
            set_trans_blender(0, 0, 0, 128);
            drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
            rectfill(game->buffer, game->attractions[a].x - 5, game->attractions[a].y - 5, game->attractions[a].x + ATTRACTION_WIDTH + 5, game->attractions[a].y + ATTRACTION_HEIGHT + 5, makecol(0, 0, 0));
            drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
            
            textout_centre_ex(game->buffer, font, player_on_amount_str, game->attractions[a].x + game->attractions[a].width / 2, game->attractions[a].y + game->attractions[a].height / 2 - 5, makecol(255, 255, 255), -1);
        } else if (game->attractions[a].player_on_amount == PLAYER_AMOUNT) {
            textout_centre_ex(game->buffer, game->font, "EN COURS", game->attractions[a].x + game->attractions[a].width / 2, game->attractions[a].y + game->attractions[a].height / 2 - 5, makecol(255, 255, 255), -1);
        }
        textout_ex(game->buffer, game->font, game->attractions[a].name, game->attractions[a].x + 5, game->attractions[a].y + 5, game->attractions[a].is_exit == true || game->attractions[a].is_stats == true ? makecol(255, 255, 255) : makecol(0, 0, 0), -1);
    }

    // Dessine l'interface et le HUD
    for (int p = 0; p < PLAYER_AMOUNT; p++) {
        char tickets_str[50];
        sprintf(tickets_str, game->players[p].tickets > 1 ? "%s : %d tickets" : "%s : %d ticket", game->players[p].name, game->players[p].tickets);
        textout_right_ex(game->buffer, game->font, tickets_str, SCREEN_WIDTH - 5, 5 + p * 20, makecol(0, 0, 0), -1);
    }

    if (game->attraction_is_over) {
        char attraction_is_over_str[60];
        char winners_are[60];
        char score_str[60];

        // make a little square behind the text
        set_trans_blender(0, 0, 0, 192);
        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
        rectfill(game->buffer, SCREEN_WIDTH * 0.4, SCREEN_HEIGHT * 0.4, SCREEN_WIDTH * 0.6, SCREEN_HEIGHT * 0.6, makecol(0, 0, 0));
        drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);

        sprintf(attraction_is_over_str, "L'attraction %s est terminee !", game->attractions[game->attraction_index].name);
        game->attraction_winner_2 == -1 ? sprintf(winners_are, "Le gagnant est le joueur %d !", game->attraction_winner + 1) : sprintf(winners_are, "Les gagnants sont les joueurs %d et %d !", game->attraction_winner + 1, game->attraction_winner_2 + 1);
        game->attraction_winner_2 == -1 ? sprintf(score_str, "Joueur %d : %.1f points", game->attraction_winner + 1, game->attraction_winner_score) : sprintf(score_str, "Joueur %d : %.1f points - Joueur %d : %.1f points", game->attraction_winner + 1, game->attraction_winner_score, game->attraction_winner_2 + 1, game->attraction_winner_2_score);
        textout_centre_ex(game->buffer, game->font, attraction_is_over_str, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 60, makecol(255, 255, 255), -1);
        textout_centre_ex(game->buffer, game->font, winners_are, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 30, makecol(255, 255, 255), -1);
        textout_centre_ex(game->buffer, game->font, score_str, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, makecol(255, 255, 255), -1);
        textout_centre_ex(game->buffer, game->font, "Appuyez sur espace pour continuer", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 30, makecol(255, 255, 255), -1);
    }

    if (game->attraction_is_running == true) {
        set_trans_blender(0, 0, 0, 128);
        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
        rectfill(game->buffer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, makecol(0, 0, 0));
        drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
    }

    // COMPTAGE DES FPS ICI
    draw_fps(game);
    // COMPTAGE DES FPS ICI

    // Affiche le contenu du buffer sur l'écran
    blit(game->buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    while (game->attraction_is_over) {
        if (key[KEY_SPACE]) {
            if (!game->PRESSED_MISC_KEYS[4]) {
                game->attraction_is_over = false;
            }
            game->PRESSED_MISC_KEYS[4] = true;
        } else {
            game->PRESSED_MISC_KEYS[4] = false;
        }
    }
}