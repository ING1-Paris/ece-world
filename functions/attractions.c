#include "attractions.h"

// Fonction qui lance les attractions
void run_attractions(GameState* game) {
    for (int a = 0; a < ATTRACTIONS_AMOUNT; a++) {
        if (game->debug_mode > 1) {
            char debug_str[100];
            sprintf(debug_str, "%d players on %s attraction", game->attractions[a].player_on_amount, game->attractions[a].name);
            textout_ex(game->debug_hud, game->font, debug_str, 10, 180 + 20 * a, makecol(255, 255, 255), -1);
        }

        if (game->attractions[a].player_on_amount == PLAYERS_AMOUNT) {
            char debug_str[100];
            sprintf(debug_str, "%s attration launched", game->attractions[a].name);
            textout_ex(game->debug_hud, game->font, debug_str, 10, 300 + 20 * a, makecol(255, 255, 255), -1);
            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                game->players[p].x = game->attractions[a].x;
                game->players[p].y = game->attractions[a].y;
            }
            display(game);
            if (game->attractions[a].is_exit == true) {
                game->over = true;
            } else if (game->attractions[a].is_stats == true) {
                game->stats_displayed = true;

            } else {
                float end[PLAYERS_AMOUNT] = {-1};
                char command[110];
                game->attraction_is_running = true;

                sprintf(command, "./%s", game->attractions[a].executable_path);
                if (game->debug_mode > 0) {
                    allegro_message("Running %s\n", command);
                }

                if (end[0] != -1 || false == false) {
                    float best = 0;
                    int best_player = 0;
                    int best_player_2 = -1;
                    switch (a) {
                        case 0:  // Canard
                            // Cost of the attraction
                            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                                game->players[p].tickets -= 1;
                            }
                            display(game);

                            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                                system(command);
                                end[p] = wait_attractions_end(game, a);
                                wait_for_next_player(game, p, end[p]);
                            }

                            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                                if (end[p] > best) {
                                    best = end[p];
                                    best_player = p;
                                } else if (end[p] == best) {
                                    best_player_2 = p;
                                }
                            }
                            if (best == 0) {
                                game->attraction_winner = -1;
                                game->attraction_winner_score = -1;
                                game->attraction_winner_2 = -1;
                                game->attraction_winner_2_score = -1;
                            } else if (best_player_2 == -1) {
                                game->attraction_winner = best_player;
                                game->attraction_winner_score = best;
                                game->attraction_winner_2 = -1;
                                game->attraction_winner_2_score = -1;
                                game->players[best_player].tickets += 1;
                            } else {
                                game->attraction_winner = best_player;
                                game->attraction_winner_score = best;
                                game->attraction_winner_2 = best_player_2;
                                game->attraction_winner_2_score = best;
                                game->players[best_player].tickets += 1;
                                game->players[best_player_2].tickets += 1;
                            }

                            game->attraction_index = a;
                            game->attraction_is_over = true;
                            break;

                            game->attraction_index = a;
                            game->attraction_is_over = true;
                            break;

                        case 1:  // Cheval
                            // Cost of the attraction
                            system(command);
                            end[0] = wait_attractions_end(game, a);
                            display(game);
                            for (int p = 0; p < 2; p++) {
                                game->players[p].tickets -= 1;
                            }

                            if (end[0] == 0) {
                                game->attraction_winner = -1;
                                game->attraction_winner_2 = -1;
                            } else if (end[0] == 1) {
                                game->attraction_winner = 0;
                                game->attraction_winner_2 = -1;

                                game->players[0].tickets += 1;
                            } else if (end[0] == 2) {
                                game->attraction_winner = 1;
                                game->attraction_winner_2 = -1;

                                game->players[1].tickets += 1;

                            } else if (end[0] == 3) {
                                game->attraction_winner = 0;
                                game->attraction_winner_2 = 1;

                                game->players[0].tickets += 1;
                                game->players[1].tickets += 1;
                            }
                            game->attraction_index = a;
                            game->attraction_is_over = true;
                            game->attraction_winner_score = -1;
                            game->attraction_winner_2_score = -1;
                            break;
                        case 2:  // Grenouille
                            // Cost of the attraction
                            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                                game->players[p].tickets -= 1;
                            }
                            display(game);

                            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                                system(command);
                                end[p] = 500 - wait_attractions_end(game, a) * 10;
                                if (end[p] == 500) {
                                    end[p] = 0;
                                }
                                wait_for_next_player(game, p, end[p]);
                            }
                            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                                if (end[p] > best) {
                                    best = end[p];
                                    best_player = p;
                                } else if (end[p] == best) {
                                    best_player_2 = p;
                                }
                            }

                            if (best == 0) {
                                game->attraction_winner = -1;
                                game->attraction_winner_score = -1;
                                game->attraction_winner_2 = -1;
                                game->attraction_winner_2_score = -1;
                            } else if (best_player_2 == -1) {
                                game->attraction_winner = best_player;
                                game->attraction_winner_score = best;
                                game->attraction_winner_2 = -1;
                                game->attraction_winner_2_score = -1;
                                game->players[best_player].tickets += 1;
                            } else {
                                game->attraction_winner = best_player;
                                game->attraction_winner_score = best;
                                game->attraction_winner_2 = best_player_2;
                                game->attraction_winner_2_score = best;
                                game->players[best_player].tickets += 1;
                                game->players[best_player_2].tickets += 1;
                            }

                            game->attraction_index = a;
                            game->attraction_is_over = true;
                            break;

                        case 3:  // Jackpot
                            // Cost of the attraction
                            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                                game->players[p].tickets -= 1;
                            }
                            display(game);

                            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                                system(command);
                                end[p] = wait_attractions_end(game, a);
                                wait_for_next_player(game, p, end[p]);
                            }

                            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                                if (end[p] > best) {
                                    best = end[p];
                                    best_player = p;
                                } else if (end[p] == best) {
                                    best_player_2 = p;
                                }
                            }

                            if (best == 0) {
                                game->attraction_winner = -1;
                                game->attraction_winner_score = -1;
                                game->attraction_winner_2 = -1;
                                game->attraction_winner_2_score = -1;
                            } else if (best_player_2 == -1) {
                                game->attraction_winner = best_player;
                                game->attraction_winner_score = best;
                                game->attraction_winner_2 = -1;
                                game->attraction_winner_2_score = -1;
                                game->players[best_player].tickets += 1;
                            } else {
                                game->attraction_winner = best_player;
                                game->attraction_winner_score = best;
                                game->attraction_winner_2 = best_player_2;
                                game->attraction_winner_2_score = best;
                                game->players[best_player].tickets += 1;
                                game->players[best_player_2].tickets += 1;
                            }

                            game->attraction_index = a;
                            game->attraction_is_over = true;
                            break;
                        case 4:  // Snake
                            // Cost of the attraction
                            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                                game->players[p].tickets -= 1;
                            }
                            display(game);

                            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                                system(command);
                                end[p] = wait_attractions_end(game, a);
                                wait_for_next_player(game, p, end[p]);
                            }
                            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                                // récuper le meilleurs jouer ou les 2 meilleurs si égalité
                                if (end[p] > best) {
                                    best = end[p];
                                    best_player = p;
                                } else if (end[p] == best) {
                                    best_player_2 = p;
                                }
                            }

                            if (best == 0) {
                                game->attraction_winner = -1;
                                game->attraction_winner_score = -1;
                                game->attraction_winner_2 = -1;
                                game->attraction_winner_2_score = -1;
                            } else if (best_player_2 == -1) {
                                game->attraction_winner = best_player;
                                game->attraction_winner_score = best;
                                game->attraction_winner_2 = -1;
                                game->attraction_winner_2_score = -1;
                                game->players[best_player].tickets += 1;
                            } else {
                                game->attraction_winner = best_player;
                                game->attraction_winner_score = best;
                                game->attraction_winner_2 = best_player_2;
                                game->attraction_winner_2_score = best;
                                game->players[best_player].tickets += 1;
                                game->players[best_player_2].tickets += 1;
                            }

                            game->attraction_index = a;
                            game->attraction_is_over = true;
                            game->attraction_index = a;
                            game->attraction_is_over = true;
                            break;
                    }
                    if (game->debug_mode > 0) {
                        allegro_message("Attraction %d is over\n", a);
                        allegro_message("Winner is %d\n", game->attraction_winner);
                        allegro_message("Score is %f\n", game->attraction_winner_score);
                        game->attraction_winner_2 == -1 ? allegro_message("Winner 2 is %d\n", game->attraction_winner_2) : 1 == 1;
                        game->attraction_winner_2_score == -1 ? allegro_message("Score 2 is %f\n", game->attraction_winner_2_score) : 1 == 1;
                    }
                }

                for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                    game->players[p].x = (SCREEN_WIDTH - PLAYERS_AMOUNT * PLAYER_WIDTH) / 2 + PLAYER_WIDTH * p;
                    game->players[p].y = SCREEN_HEIGHT - PLAYER_HEIGHT - 10;
                    game->players[p].direction = DIRECTION_DOWN;
                    game->players[p].is_walking = false;

                }
                game->attraction_is_running = false;
            }
        }
    }
}

// Attend la fin d'une attraction et renvoie le endfile
float wait_attractions_end(GameState* game, int attraction_index) {
    float end = -1;
    while (end == -1) {
        FILE* end_file = fopen(game->attractions[attraction_index].end_path, "r");
        if (end_file == NULL) {
            printf("Error opening %s\n", game->attractions[attraction_index].end_path);
            exit(1);
        }
        fscanf(end_file, "%f", &end);
        fclose(end_file);
        if (key[KEY_ESC]) {
            rest(300);
            break;
        }
    }
    if (game->debug_mode > 0) {
        allegro_message("End of %s\nScore : %f", game->attractions[attraction_index].name, end);
    }

    return end;
}

// Attend que le joueur appuie sur ESPACE pour commencer l'attraction
void wait_for_next_player(GameState* game, int player_index, float score) {
    char points_str[100];
    char next_str[100];
    sprintf(points_str, score >= 2 ? "Vous avez obtenu un score de %.f points" : "Vous avez obtenu un score de %.f point", score);
    if (player_index != PLAYERS_AMOUNT - 1) {
        sprintf(next_str, "Au tour de %s de jouer", game->players[player_index].name);
    }
    rectfill(screen, SCREEN_WIDTH * 0.35, SCREEN_HEIGHT * 0.42, SCREEN_WIDTH * 0.65, SCREEN_HEIGHT * 0.6, makecol(0, 0, 0));
    textout_centre_ex(screen, game->font, points_str, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 40, makecol(255, 255, 255), -1);
    textout_centre_ex(screen, game->font, next_str, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, makecol(255, 0, 0), -1);
    textout_centre_ex(screen, game->font, "Appuyer sur ESPACE pour commencer", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 40, makecol(156, 220, 100), -1);
    while (!key[KEY_SPACE]) {
        rest(10);
    }
    while (key[KEY_SPACE]) {
        rest(10);
    }
    clear_keybuf(); 
    display(game);
}