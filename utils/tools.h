#ifndef TOOLS_H
#define TOOLS_H

#include "structs.h"

double current_time();
void draw_fps(GameState* game);
int random_color();
void clean_game(GameState* game);
void close_button_handler();

#endif