#ifndef INIT_H
#define INIT_H

#include <allegro.h>
#include <stdbool.h>

#include "../utils/structs.h"
#include "../utils/consts.h"
#include "../utils/tools.h"

void init_bitmap(GameState* game);
void init_game(GameState* game);
void install_all_allegro();

#endif