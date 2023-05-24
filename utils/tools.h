#ifndef TOOLS_H
#define TOOLS_H

#include <allegro.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "consts.h"
#include "structs.h"

double current_time();
void draw_fps(GameState* game);
int get_random_color();
void clean_game(GameState* game);
void close_button_handler();
void free_idle_bitmaps(GameState* game);
void update_animation_frame(GameState* game);
void free_walk_bitmaps(GameState* game);
void draw_diagonal_gradient(BITMAP* bmp, int start_color, int end_color);
void draw_transition(BITMAP* bmp, BITMAP* grad1, BITMAP* grad2, int t);
void fadeout(BITMAP* last_screen);
void fadein(BITMAP* new_screen);

#endif