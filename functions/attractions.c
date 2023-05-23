#include "attractions.h"

// Fonction qui lance les attractions
void run_attractions(GameState* game) {
    for (int a = 0; a < ATTRACTIONS_AMOUNT; a++) {
        if (game->attractions[a].player_on_amount == PLAYERS_AMOUNT) {
            if (game->attractions[a].is_exit == true) {
                game->over = true;
            } else if (game->attractions[a].is_stats == true) {
                game->stats_displayed = true;
            } else {
                float end[PLAYERS_AMOUNT] = {-1};
                char command[110];
                game->attraction_is_running = true;

                // Cost of the attraction
                for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                    game->players[p].tickets -= 1;
                }

                sprintf(command, "./%s", game->attractions[a].executable_path);
                if (game->debug == true) {
                    allegro_message("Running %s\n", command);
                }
                // Get the score
                display(game);
                system(command);
                end[0] = wait_attractions_end(game, a);
                if (end[0] != -1) {
                    float best = 0;
                    int best_player = 0;
                    switch (a) {
                        case 0:  // Canard
                            for (int p = 1; p < PLAYERS_AMOUNT; p++) {
                                wait_for_next_player(game, p);
                                system(command);
                                end[p] = wait_attractions_end(game, a);
                            }
                            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                                if (end[p] > best) {
                                    best = end[p];
                                    best_player = p;
                                } else if (end[p] == best) {
                                    game->attraction_winner_2 = p;
                                    game->attraction_winner_2_score = end[p];
                                }
                            }
                            game->players[best_player].tickets += 1;

                            game->attraction_index = a;
                            game->attraction_is_over = true;
                            game->attraction_winner = best_player;
                            game->attraction_winner_score = best;
                            game->attraction_winner_2 = -1;
                            game->attraction_winner_2_score = -1;
                            break;

                        case 1:  // Cheval
                            if (end[0] == 0) {
                                game->attraction_winner = -1;
                            } else if (end[0] == 1) {
                                game->attraction_winner = 0;
                            } else if (end[0] == 2) {
                                game->attraction_winner = 1;
                            } else if (end[0] == 3) {
                                game->attraction_winner = 0;
                                game->attraction_winner_2 = 1;
                            }
                            if (game->attraction_winner != -1) {
                                game->players[game->attraction_winner].tickets += 1;
                            }
                            if (game->attraction_winner_2 != -1) {
                                game->players[game->attraction_winner_2].tickets += 1;
                            }
                            game->attraction_index = a;
                            game->attraction_is_over = true;
                            game->attraction_winner_2 = -1;
                            game->attraction_winner_2_score = -1;
                            break;
                        case 2:  // Grenouille
                            for (int p = 1; p < PLAYERS_AMOUNT; p++) {
                                wait_for_next_player(game, p);
                                system(command);
                                end[p] = wait_attractions_end(game, a);
                            }
                            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                                if (end[p] < best) {
                                    best = end[p];
                                    best_player = p;
                                }
                            }
                            game->players[best_player].tickets += 1;

                            game->attraction_index = a;
                            game->attraction_is_over = true;
                            game->attraction_winner = best_player;
                            game->attraction_winner_score = best;
                            game->attraction_winner_2 = -1;
                            game->attraction_winner_2_score = -1;
                            break;

                        case 3:  // Jackpot
                            for (int p = 1; p < PLAYERS_AMOUNT; p++) {
                                wait_for_next_player(game, p);
                                system(command);
                                end[p] = wait_attractions_end(game, a);
                            }
                            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                                if (end[p] > best) {
                                    best = end[p];
                                    best_player = p;
                                }
                            }
                            game->players[best_player].tickets += best;

                            game->attraction_index = a;
                            game->attraction_is_over = true;
                            game->attraction_winner = best_player;
                            game->attraction_winner_score = best;
                            game->attraction_winner_2 = -1;
                            game->attraction_winner_2_score = -1;
                            break;
                        case 4:  // Snake
                            for (int p = 1; p < PLAYERS_AMOUNT; p++) {
                                wait_for_next_player(game, p);
                                system(command);
                                end[p] = wait_attractions_end(game, a);
                            }
                            for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                                if (end[p] > best) {
                                    best = end[p];
                                    best_player = p;
                                } else if (end[p] == best) {
                                    game->attraction_winner_2 = p;
                                    game->attraction_winner_2_score = end[p];
                                }
                            }
                            game->players[best_player].tickets += 1;

                            game->attraction_index = a;
                            game->attraction_is_over = true;
                            game->attraction_winner = best_player;
                            game->attraction_winner_score = best;
                            game->attraction_winner_2 = -1;
                            game->attraction_winner_2_score = -1;
                            break;
                    }
                    if (game->debug == true) {
                        allegro_message("Attraction %d is over\n", a);
                        allegro_message("Winner is %d\n", game->attraction_winner);
                        allegro_message("Score is %f\n", game->attraction_winner_score);
                        game->attraction_winner_2 == -1 ? allegro_message("Winner 2 is %d\n", game->attraction_winner_2) : 1 == 1;
                        game->attraction_winner_2_score == -1 ? allegro_message("Score 2 is %f\n", game->attraction_winner_2_score) : 1 == 1;
                    }
                }

                for (int p = 0; p < PLAYERS_AMOUNT; p++) {
                    game->players[p].x = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;
                    game->players[p].y = SCREEN_HEIGHT - PLAYER_HEIGHT - 10;
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
    if (game->debug == true) {
        allegro_message("End of %s\nScore : %f", game->attractions[attraction_index].name, end);
    }

    return end;
}

// Attend que le joueur appuie sur ESPACE pour commencer l'attraction
void wait_for_next_player(GameState* game, int player_index) {
    char next_str[100];
    sprintf(next_str, "Au tour de %s de jouer", game->players[player_index].name);
    rectfill(screen, SCREEN_WIDTH * 0.4, SCREEN_HEIGHT * 0.45, SCREEN_WIDTH * 0.6, SCREEN_HEIGHT * 0.57, makecol(0, 0, 0));
    textout_centre_ex(screen, game->font, next_str, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20, makecol(255, 255, 255), -1);
    textout_centre_ex(screen, game->font, "Appuie sur ESPACE pour commencer", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20, makecol(255, 255, 255), -1);
    while (!key[KEY_SPACE]) {
        rest(10);
    }
    clear_keybuf();
    display(game);
}