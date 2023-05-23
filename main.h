#ifndef MAIN_H
#define MAIN_H

#include "utils/consts.h"
#include "utils/structs.h"
#include "utils/tools.h"
#include "functions/init.h"
#include "functions/display.h"
#include "functions/attractions.h"
#include "functions/checks.h"
#include "functions/keyboard.h"
#include "functions/players.h"

/* FONCTIONS */

void check_collisions(GameState* game);
void check_for_winner(GameState* game);

#endif