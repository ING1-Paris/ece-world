#include "checks.h"

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
            game->attractions[a].player_on_amount = player_on_attraction;
        }
    }
}

void check_for_winner(GameState* game) {
    // Check if there is a player with 0 tickets and if there is, return the player with the most tickets
    int winner = -1;
    int best = -1;

    bool loser_in_game = false;

    for (int i = 0; i < PLAYER_AMOUNT; i++) {
        if (game->players[i].tickets == 0) {
            loser_in_game = true;
        }
    }

    if (loser_in_game) {
        for (int i = 0; i < PLAYER_AMOUNT; i++) {
            if (game->players[i].tickets == 0) {
                for (int j = 0; j < PLAYER_AMOUNT; j++) {
                    if (game->players[j].tickets > best) {
                        best = game->players[j].tickets;
                        winner = j;
                    }
                }
            }
        }
        game->winner_displayed = true;
        game->winner = winner;
    }
}