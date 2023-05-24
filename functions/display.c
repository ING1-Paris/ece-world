#include "display.h"

// Fonction de rafraîchissement de l'écran
void display(GameState* game) {
    // Efface l'écran
    // clear(game->buffer);

    // Dessine le fond
    blit(game->background, game->buffer, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Dessine les personnages
    for (int i = 0; i < PLAYERS_AMOUNT; i++) {
        Player player = game->players[i];
        if (player.is_walking == true) {
            if (game->debug_mode > 1) {
                char debug_str[50];
                sprintf(debug_str, "Draw walk player %d direction %d frame %d", i, player.direction, (game->animation_frame + 3 * i) % 4);
                textout_ex(game->debug_hud, game->font, debug_str, 10, 100 + i * 20, makecol(255, 255, 255), -1);
            }
            draw_sprite(game->buffer, player.walk_bitmaps[player.direction][(game->animation_frame + 3 * i) % 4], player.x, player.y);
        } else {
            if (game->debug_mode > 1) {
                char debug_str[50];
                sprintf(debug_str, "Draw idle player %d direction %d frame %d", i, player.direction, (game->animation_frame + 1 * i) % 2);
                textout_ex(game->debug_hud, game->font, debug_str, 10, 100 + i * 20, makecol(255, 255, 255), -1);
            }
            draw_sprite(game->buffer, player.idle_bitmaps[player.direction][(game->animation_frame + 1 * i) % 2], player.x, player.y);
        }
    }

    // Dessine les attractions
    for (int a = 0; a < ATTRACTIONS_AMOUNT; a++) {
        int color = 0;
        if (game->attractions[a].is_exit == true) {
            if (game->attractions[a].player_on_amount == 0) {
                color = makecol(0, 0, 0);
            } else if (game->attractions[a].player_on_amount < PLAYERS_AMOUNT) {
                color = makecol(255, 77, 0);
            } else if (game->attractions[a].player_on_amount == PLAYERS_AMOUNT) {
                color = makecol(255, 0, 0);
            }
        } else if (game->attractions[a].is_stats == true) {
            if (game->attractions[a].player_on_amount == 0) {
                color = makecol(0, 0, 255);
            } else if (game->attractions[a].player_on_amount < PLAYERS_AMOUNT) {
                color = makecol(0, 128, 255);
            } else if (game->attractions[a].player_on_amount == PLAYERS_AMOUNT) {
                color = makecol(200, 0, 255);
            }
        }

        if (game->attractions[a].is_exit == false && game->attractions[a].is_stats == false) {
            draw_sprite(game->buffer, game->attractions_bitmaps[a], game->attractions[a].x, game->attractions[a].y);
        } else {
            rectfill(game->buffer, game->attractions[a].x, game->attractions[a].y, game->attractions[a].x + game->attractions[a].width, game->attractions[a].y + game->attractions[a].height, color);
        }

        //  Écrire le nombre de joueurs sur l'attraction et le nom de l'attraction
        if (game->attractions[a].player_on_amount == 0) {
        } else if (game->attractions[a].player_on_amount < PLAYERS_AMOUNT) {
            char player_on_amount_str[30];
            int player_needed = PLAYERS_AMOUNT - game->attractions[a].player_on_amount;
            sprintf(player_on_amount_str, "En attente de %d", player_needed);
            // Faire un fond noir derrière l'attraction
            set_trans_blender(0, 0, 0, 128);
            drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
            rectfill(game->buffer, game->attractions[a].x - 5, game->attractions[a].y - 5, game->attractions[a].x + ATTRACTION_WIDTH + 5, game->attractions[a].y + ATTRACTION_HEIGHT + 5, makecol(0, 0, 0));
            drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);

            textout_centre_ex(game->buffer, game->font, player_on_amount_str, game->attractions[a].x + game->attractions[a].width / 2, game->attractions[a].y + game->attractions[a].height / 2 - 15, makecol(255, 255, 255), -1);
            if (game->attractions[a].is_exit == true) {
                textout_centre_ex(game->buffer, game->font, player_needed > 1 ? "joueurs pour quitter" : "joueur pour quitter", game->attractions[a].x + game->attractions[a].width / 2, game->attractions[a].y + game->attractions[a].height / 2 + 15, makecol(255, 255, 255), -1);
            } else if (game->attractions[a].is_stats == true) {
                textout_centre_ex(game->buffer, game->font, player_needed > 1 ? "joueurs pour ouvrir" : "joueur pour ouvrir", game->attractions[a].x + game->attractions[a].width / 2, game->attractions[a].y + game->attractions[a].height / 2 + 15, makecol(255, 255, 255), -1);
            } else {
                textout_centre_ex(game->buffer, game->font, player_needed > 1 ? "joueurs pour demarrer" : "joueur pour demarrer", game->attractions[a].x + game->attractions[a].width / 2, game->attractions[a].y + game->attractions[a].height / 2 + 15, makecol(255, 255, 255), -1);
            }
        } else if (game->attractions[a].player_on_amount == PLAYERS_AMOUNT) {
            set_trans_blender(0, 0, 0, 128);
            drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
            rectfill(game->buffer, game->attractions[a].x - 5, game->attractions[a].y - 5, game->attractions[a].x + ATTRACTION_WIDTH + 5, game->attractions[a].y + ATTRACTION_HEIGHT + 5, makecol(0, 0, 255));
            drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
            textout_centre_ex(game->buffer, game->font, "EN COURS", game->attractions[a].x + game->attractions[a].width / 2, game->attractions[a].y + game->attractions[a].height / 2 - 5, makecol(255, 255, 255), -1);
            textout_centre_ex(game->buffer, game->font, "Une attraction est en cours, appuyer sur ECHAP pour la quitter", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, makecol(255, 255, 255), -1);
        }
    }

    // Dessine une étiquette sous le nom de l'attraction
    masked_blit(game->background_overlay, game->buffer, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    for (int a = 0; a < ATTRACTIONS_AMOUNT; a++) {
        textout_ex(game->buffer, game->font, game->attractions[a].name, game->attractions[a].x + 5, game->attractions[a].y + 5, game->attractions[a].is_exit == true || game->attractions[a].is_stats == true ? makecol(255, 255, 255) : makecol(0, 0, 0), -1);
    }

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

    // Dessine l'interface et le HUD
    for (int p = 0; p < PLAYERS_AMOUNT; p++) {
        char tickets_str[50];
        sprintf(tickets_str, "%s :  %d", game->players[p].name, game->players[p].tickets);
        textout_right_ex(game->buffer, game->font, tickets_str, SCREEN_WIDTH - 50, 20 + p * 30, makecol(255, 255, 255), -1);
        draw_sprite(game->buffer, game->ticket, SCREEN_WIDTH - 25 - 10, 24 + p * 30);
    }

    if (game->attraction_is_over) {
        char attraction_is_over_str[100];
        char winners_are[100];
        char winners[50];
        char score_str[100];

        // Petit carré derrère le texte
        set_trans_blender(0, 0, 0, 192);
        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
        rectfill(game->buffer, SCREEN_WIDTH * 0.35, SCREEN_HEIGHT * 0.41, SCREEN_WIDTH * 0.65, SCREEN_HEIGHT * 0.61, makecol(0, 0, 0));

        drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);

        sprintf(attraction_is_over_str, "L'attraction %s est terminee !", game->attractions[game->attraction_index].name);

        if (game->attraction_winner_2 == -1 && game->attraction_winner == -1) {
            sprintf(winners_are, "Tous les joueurs ont perdu !");
        } else if (game->attraction_winner_2 == -1) {
            sprintf(winners_are, "Le gagnant est le joueur");
            sprintf(winners, "%s", game->players[game->attraction_winner].name);
        } else {
            sprintf(winners_are, "Les gagnants sont les joueurs");
            sprintf(winners, "%s et %s", game->players[game->attraction_winner].name, game->players[game->attraction_winner_2].name);
        }

        if (game->attraction_winner_2_score == -1 && game->attraction_winner_score == -1) {
            sprintf(score_str, " ");
        } else if (game->attraction_winner_2_score == -1) {
            sprintf(score_str, game->attraction_winner_2_score >= 2 ? "%.f points" : "%.f point", game->attraction_winner_score);
        } else {
            if (game->attraction_winner_score < 2 && game->attraction_winner_2_score < 2) {
                sprintf(score_str, "%s : %.f point - %s : %.f point", game->players[game->attraction_winner].name, game->attraction_winner_score, game->players[game->attraction_winner_2].name, game->attraction_winner_2_score);
            }
            if (game->attraction_winner_score >= 2) {
                sprintf(score_str, game->attraction_winner_2_score >= 2 ? "%s : %.f points - %s : %.f points" : "%s : %.f points - %s : %.f point", game->players[game->attraction_winner].name, game->attraction_winner_score, game->players[game->attraction_winner_2].name, game->attraction_winner_2_score);
            } else if (game->attraction_winner_2_score >= 2) {
                sprintf(score_str, game->attraction_winner_score >= 2 ? "%s : %.f points - %s : %.f points" : "%s : %.f point - %s : %.f points", game->players[game->attraction_winner].name, game->attraction_winner_score, game->players[game->attraction_winner_2].name, game->attraction_winner_2_score);
            } else {
                sprintf(score_str, "%s : %.f point - %s : %.f point", game->players[game->attraction_winner].name, game->attraction_winner_score, game->players[game->attraction_winner_2].name, game->attraction_winner_2_score);
                allegro_message("ça devrait pas aller ici");
            }
        }
        textout_centre_ex(game->buffer, game->font, attraction_is_over_str, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 60, makecol(255, 255, 255), -1);
        textout_centre_ex(game->buffer, game->font, winners_are, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 30, makecol(255, 255, 255), -1);
        textout_centre_ex(game->buffer, game->font, winners, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, makecol(255, 0, 0), -1);
        textout_centre_ex(game->buffer, game->font, score_str, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 30, makecol(255, 255, 255), -1);
        textout_centre_ex(game->buffer, game->font, "Appuyez sur espace pour continuer", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 60, makecol(156, 220, 100), -1);
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
    masked_blit(game->debug_hud, game->buffer, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    blit(game->buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Efface le contenu du buffer de debug
    clear_to_color(game->debug_hud, makecol(255, 0, 255));

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