#ifndef PLAYERS_H
#define PLAYERS_H

#include "../utils/structs.h"
#include "../utils/consts.h"
#include "../utils/tools.h"

void players_creation_menu(GameState *game);
void display_string_in_box(BITMAP* buffer, char* str, int player_index, FONT* font, bool first_time);
#endif