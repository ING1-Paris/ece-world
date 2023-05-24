#ifndef ATTRACTIONS_H
#define ATTRACTIONS_H

#include "../utils/structs.h"
#include "../utils/consts.h"
#include "display.h"

void run_attractions(GameState* game);
float wait_attractions_end(GameState* game, int attraction_index);
void wait_for_next_player(GameState* game, int player_index, float score);

#endif