#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <allegro.h>
#include <sys/time.h>

#include "main.h"

// Renvoie le temps actuel en millisecondes
double current_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000.0 + time.tv_usec / 1000.0;
}

void draw_fps(GameState* game) {
    double current_timestamp = current_time();

    if (current_timestamp >= fps_timer + 1000) {
        fps = frames_accum;
        frames_accum = 0;
        fps_timer = current_timestamp;
    }

    frames_accum++;

    if (game->debug) {
        char fps_str[30];
        char frame_accum_str[30];
        char fps_timer_str[30];
        char player_speed_str[30];

        sprintf(fps_str, "FPS: %.0f", fps);
        sprintf(frame_accum_str, "Frames: %.0f", frames_accum);
        sprintf(fps_timer_str, "Timestamp: %.0f", fps_timer);
        sprintf(player_speed_str, "Pl Speed: %d", game->player_speed);

        textout_ex(game->buffer, font, fps_str, 10, 20, makecol(255, 255, 255), -1);
        textout_ex(game->buffer, font, frame_accum_str, 10, 40, makecol(255, 255, 255), -1);
        textout_ex(game->buffer, font, player_speed_str, 10, 60, makecol(255, 255, 255), -1);
        textout_ex(game->buffer, font, fps_timer_str, 10, 80, makecol(255, 255, 255), -1);
    }
}

int random_color() {
    int red = rand() % 256;
    int green = rand() % 256;
    int blue = rand() % 256;

    return makecol(red, green, blue);
}

// Fonction de rafraîchissement de l'écran
void display(GameState* game) {
    // Efface l'écran
    clear_bitmap(game->buffer);

    // Dessine les personnages
    for (int i = 0; i < PLAYER_AMOUNT; i++) {
        Player player = game->players[i];
        rectfill(game->buffer, player.x, player.y, player.x + PLAYER_WIDTH, player.y + PLAYER_HEIGHT, player.color);
    }

    // Dessine les attractions
    for (int a = 0; a < ATTRACTIONS_AMOUNT; a++) {
        int color = 0;
        if (game->attractions[a].player_on_amount == 0) {
            color = makecol(255, 0, 0);
        } else if (game->attractions[a].player_on_amount < PLAYER_AMOUNT) {
            color = makecol(255, 255, 0);
        } else if (game->attractions[a].player_on_amount == PLAYER_AMOUNT) {
            color = makecol(0, 255, 0);
        }

        rectfill(game->buffer, game->attractions[a].x, game->attractions[a].y, game->attractions[a].x + game->attractions[a].width, game->attractions[a].y + game->attractions[a].height, color);
        // Écrire le nombre de joueurs sur l'attraction et le nom de l'attraction
        char player_on_amount_str[30];
        sprintf(player_on_amount_str, "%d", game->attractions[a].player_on_amount);
        textout_ex(game->buffer, font, player_on_amount_str, game->attractions[a].x + game->attractions[a].width / 2 - 5, game->attractions[a].y + game->attractions[a].height / 2 - 5, makecol(0, 0, 0), -1);
        textout_ex(game->buffer, font, game->attractions[a].name, game->attractions[a].x + 5, game->attractions[a].y + 5, makecol(0, 0, 0), -1);
    }

    // Dessine l'interface et le HUD
    // tickets
    for (int p = 0; p < PLAYER_AMOUNT; p++) {
        char tickets_str[30];
        sprintf(tickets_str, "Joueur %d : %d", p + 1, game->players[p].tickets);
        textout_ex(game->buffer, font, tickets_str, SCREEN_WIDTH - 150, 10 + 20 * p, makecol(255, 255, 255), -1);
    }

    if (game->attraction_is_over) {
        char attraction_is_over_str[60];
        char winners_are[60];
        char score_str[60];
        sprintf(attraction_is_over_str, "L'attraction %s est terminée !", game->attractions[game->attraction_index].name);
        game->attraction_winner_2 == -1 ? sprintf(winners_are, "Le gagnant est le joueur %d !", game->attraction_winner + 1) : sprintf(winners_are, "Les gagnants sont les joueurs %d et %d !", game->attraction_winner + 1, game->attraction_winner_2 + 1);
        game->attraction_winner_2 == -1 ? sprintf(score_str, "Joueur %d : %f points", game->attraction_winner + 1, game->attraction_winner_score) : sprintf(score_str, "Joueur %d : %f points - Joueur %d : %f points", game->attraction_winner + 1, game->attraction_winner_score, game->attraction_winner_2 + 1, game->attraction_winner_2_score);
        textout_ex(game->buffer, font, attraction_is_over_str, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 40, makecol(255, 255, 255), -1);
        textout_ex(game->buffer, font, winners_are, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 20, makecol(255, 255, 255), -1);
        textout_ex(game->buffer, font, score_str, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, makecol(255, 255, 255), -1);
        textout_ex(game->buffer, font, "Appuyez sur espace pour continuer", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 20, makecol(255, 255, 255), -1);
    }

    // Affiche le contenu du buffer sur l'écran
    draw_fps(game);
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

// Fonction de gestion des collisions avec les attractions
void check_collisions(GameState* game) {
    for (int a = 0; a < ATTRACTIONS_AMOUNT; a++) {
        for (int p = 0; p < PLAYER_AMOUNT; p++) {
            game->attractions[a].triggered[p] = 0;
            if (game->players[p].x < game->attractions[a].x + game->attractions[a].width &&
                game->players[p].x + PLAYER_WIDTH > game->attractions[a].x &&
                game->players[p].y < game->attractions[a].y + game->attractions[a].height &&
                game->players[p].y + PLAYER_HEIGHT > game->attractions[a].y) {
                game->attractions[a].triggered[p] = 1;
            }
        }
    }
    for (int a = 0; a < ATTRACTIONS_AMOUNT; a++) {
        int player_on_attraction = 0;
        for (int p = 0; p < PLAYER_AMOUNT; p++) {
            if (game->attractions[a].triggered[p]) {
                player_on_attraction++;
            }
        }
        game->attractions[a].player_on_amount = player_on_attraction;
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
    game->attraction_is_running = false;
    game->attraction_is_over = false;
    game->attraction_index = -1;
    game->attraction_winner = -1;
    game->attraction_winner_2 = -1;
    game->attraction_winner_score = -1;
    game->attraction_winner_2_score = -1;

    // Initialisation des personnages
    for (int i = 0; i < PLAYER_AMOUNT; i++) {
        game->players[i].x = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;
        game->players[i].y = SCREEN_HEIGHT - PLAYER_HEIGHT - 10;
        game->players[i].color = random_color();
        game->players[i].tickets = 5;
    }

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
    for (int a = 0; a < ATTRACTIONS_AMOUNT; a++) {
        char attractions_directory_path_temp[50];
        strcpy(game->attractions[a].name, ATTRACTIONS_NAMES[a]);
        sprintf(attractions_directory_path_temp, "attractions/%s/", game->attractions[a].name);
        sprintf(game->attractions[a].executable_path, "%s%s.o", attractions_directory_path_temp, game->attractions[a].name);
        sprintf(game->attractions[a].end_path, "%s%s", attractions_directory_path_temp, "end.txt");
        sprintf(game->attractions[a].best_path, "%s%s", attractions_directory_path_temp, "best.txt");
    }

    for (int a = 0; a < ATTRACTIONS_AMOUNT; a++) {
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
}

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

void run_attractions(GameState* game) {
    for (int a = 0; a < ATTRACTIONS_AMOUNT; a++) {
        if (game->attractions[a].player_on_amount == PLAYER_AMOUNT) {
            float end[PLAYER_AMOUNT] = {-1};
            char command[110];

            game->attraction_is_running = true;

            // Cost of the attraction
            for (int p = 0; p < PLAYER_AMOUNT; p++) {
                game->players[p].tickets -= 1;
            }

            sprintf(command, "./%s", game->attractions[a].executable_path);
            allegro_message("Running %s\n", command);
            // Get the score
            system(command);
            end[0] = wait_attractions_end(game, a);
            if (end[0] != -1) {
                float best = 0;
                int best_player = 0;
                switch (a) {
                    case 0:  // Canard
                        for (int p = 1; p < PLAYER_AMOUNT; p++) {
                            system(command);
                            end[p] = wait_attractions_end(game, a);
                        }
                        for (int p = 0; p < PLAYER_AMOUNT; p++) {
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
                        for (int p = 1; p < PLAYER_AMOUNT; p++) {
                            system(command);
                            end[p] = wait_attractions_end(game, a);
                        }
                        for (int p = 0; p < PLAYER_AMOUNT; p++) {
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
                        for (int p = 1; p < PLAYER_AMOUNT; p++) {
                            system(command);
                            end[p] = wait_attractions_end(game, a);
                        }
                        for (int p = 0; p < PLAYER_AMOUNT; p++) {
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
                        for (int p = 1; p < PLAYER_AMOUNT; p++) {
                            system(command);
                            end[p] = wait_attractions_end(game, a);
                        }
                        for (int p = 0; p < PLAYER_AMOUNT; p++) {
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
                        break;
                }
                allegro_message("Attraction %d is over\n", a);
                allegro_message("Winner is %d\n", game->attraction_winner);
                allegro_message("Score is %f\n", game->attraction_winner_score);
                game->attraction_winner_2 == -1 ? allegro_message("Winner 2 is %d\n", game->attraction_winner_2) : 1 == 1;
                game->attraction_winner_2_score == -1 ? allegro_message("Score 2 is %f\n", game->attraction_winner_2_score) : 1 == 1;
            }

            for (int p = 0; p < PLAYER_AMOUNT; p++) {
                game->players[p].x = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;
                game->players[p].y = SCREEN_HEIGHT - PLAYER_HEIGHT - 10;
            }
            game->attraction_is_running = false;
        }
    }
}

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
            if (!game->PRESSED_MISC_KEYS[3]) {
                clear_keybuf();
                break;
            }
            game->PRESSED_MISC_KEYS[3] = true;
        } else {
            game->PRESSED_MISC_KEYS[3] = false;
        }
    }

    allegro_message("End of %s\nScore : %f", game->attractions[attraction_index].name, end);

    return end;
}

void clean_game(GameState* game) {
    // Libère la mémoire salope

    destroy_bitmap(game->buffer);
}

int main() {
    // Initialisation d'Allegro
    srand(time(NULL));
    allegro_init();
    fps_timer = current_time();
    if (install_sound(DIGI_NONE, MIDI_NONE, NULL) != 0) {
        allegro_message("Error initializing sound system: %s\n", allegro_error);
        exit(EXIT_FAILURE);
    }

    if (install_keyboard() != 0) {
        allegro_message("Error initializing keyboard input.\n");
        exit(EXIT_FAILURE);
    }

    if (install_timer() != 0) {
        allegro_message("Error initializing timer.\n");
        exit(EXIT_FAILURE);
    }

    // Configuration de la fenêtre du jeu
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    // Creatin du jeu
    GameState game;
    init_game(&game);

    // Boucle de jeu principale
    while (!game.over) {
        // Gère les entrées clavier
        handle_input(&game);

        // Vérifie les collisions avec les attractions
        check_collisions(&game);

        // Rafraîchit l'écran
        display(&game);

        // On lance les attractions
        run_attractions(&game);

        // Gère le framerate, pour éviter que le jeu ne tourne trop vite
        rest(10);
    }

    clean_game(&game);

    return 0;
}
END_OF_MAIN()
