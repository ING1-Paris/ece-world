#ifndef SPRITES_H
#define SPRITES_H

#include <allegro.h>

#include "../utils/consts.h"
#include "../utils/structs.h"

void load_idle_sprites(GameState *game);
void load_walk_sprites(GameState *game);
void load_background_sprite(GameState *game);
void load_background_overlay_sprite(GameState *game);
void load_ticket_sprite(GameState *game);

#endif