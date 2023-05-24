#include "sprites.h"

void load_idle_sprites(GameState *game) {
    for (int i = 0; i < PLAYERS_AMOUNT; i++) {
        // Allocate memory for all directions and frames
        game->players[i].idle_bitmaps = (BITMAP ***)malloc(sizeof(BITMAP **) * 4);
        for (int j = 0; j < 4; j++) {
            game->players[i].idle_bitmaps[j] = (BITMAP **)malloc(sizeof(BITMAP *) * 2);
        }
        char filename[100];
        sprintf(filename, "%s%d.bmp", IDLE_SPRITESHET_FILE, i);
        BITMAP *spritesheet = load_bitmap(filename, NULL);
        if (!spritesheet) {
            printf("Cannot load spritesheet %s\n", filename);
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 2; k++) {
                BITMAP *temp = create_sub_bitmap(spritesheet, k * CHARACTERS_SPRITES_SIZE, j * CHARACTERS_SPRITES_SIZE, CHARACTERS_SPRITES_SIZE, CHARACTERS_SPRITES_SIZE);
                if (game->debug_mode > 0) {
                    allegro_message("Loading idles sprites for player %d, direction %d, frame %d\n", i, j, k);
                }
                // You must create and assign the bitmap to the correct location before you can stretch blit onto it
                game->players[i].idle_bitmaps[j][k] = create_bitmap(CHARACTERS_SPRITES_SIZE_STRETCHED, CHARACTERS_SPRITES_SIZE_STRETCHED);
                if (!game->players[i].idle_bitmaps[j][k]) {
                    printf("Cannot create bitmap for player %d, direction %d, frame %d\n", i, j, k);
                    exit(EXIT_FAILURE);
                }
                // Use the bitmap from the game state not from a temporary array
                stretch_blit(temp, game->players[i].idle_bitmaps[j][k], 0, 0, CHARACTERS_SPRITES_SIZE, CHARACTERS_SPRITES_SIZE, 0, 0, CHARACTERS_SPRITES_SIZE_STRETCHED, CHARACTERS_SPRITES_SIZE_STRETCHED);
                destroy_bitmap(temp);  // Free the temporary sub-bitmap
            }
        }
        destroy_bitmap(spritesheet);  // Don't forget to free the spritesheet bitmap when done
    }
}

void load_walk_sprites(GameState *game) {
    for (int i = 0; i < PLAYERS_AMOUNT; i++) {
        // Allocate memory for all directions and frames
        game->players[i].walk_bitmaps = (BITMAP ***)malloc(sizeof(BITMAP **) * 4);
        for (int j = 0; j < 4; j++) {
            game->players[i].walk_bitmaps[j] = (BITMAP **)malloc(sizeof(BITMAP *) * 4);
        }
        char filename[100];
        sprintf(filename, "%s%d.bmp", WALK_SPRITESHET_FILE, i);
        BITMAP *spritesheet = load_bitmap(filename, NULL);
        if (!spritesheet) {
            printf("Cannot load spritesheet %s\n", filename);
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                BITMAP *temp = create_sub_bitmap(spritesheet, k * CHARACTERS_SPRITES_SIZE, j * CHARACTERS_SPRITES_SIZE, CHARACTERS_SPRITES_SIZE, CHARACTERS_SPRITES_SIZE);
                if (game->debug_mode > 0) {
                    allegro_message("Loading walk sprites for player %d, direction %d, frame %d\n", i, j, k);
                }
                // You must create and assign the bitmap to the correct location before you can stretch blit onto it
                game->players[i].walk_bitmaps[j][k] = create_bitmap(CHARACTERS_SPRITES_SIZE_STRETCHED, CHARACTERS_SPRITES_SIZE_STRETCHED);
                if (!game->players[i].walk_bitmaps[j][k]) {
                    printf("Cannot create bitmap for player %d, direction %d, frame %d\n", i, j, k);
                    exit(EXIT_FAILURE);
                }
                // Use the bitmap from the game state not from a temporary array
                stretch_blit(temp, game->players[i].walk_bitmaps[j][k], 0, 0, CHARACTERS_SPRITES_SIZE, CHARACTERS_SPRITES_SIZE, 0, 0, CHARACTERS_SPRITES_SIZE_STRETCHED, CHARACTERS_SPRITES_SIZE_STRETCHED);
                destroy_bitmap(temp);  // Free the temporary sub-bitmap
            }
        }
        destroy_bitmap(spritesheet);  // Don't forget to free the spritesheet bitmap when done
    }
}

void load_background_sprite(GameState *game) {
    game->background = load_bitmap(BACKGROUND_FILE, NULL);
    if (!game->background) {
        allegro_message("Cannot load background %s\n", BACKGROUND_FILE);
        exit(EXIT_FAILURE);
    }
}

void load_background_overlay_sprite(GameState *game) {
    game->background_overlay = load_bitmap(BACKGROUND_OVERLAY_FILE, NULL);
    if (!game->background_overlay) {
        allegro_message("Cannot load background overlay %s\n", BACKGROUND_OVERLAY_FILE);
        exit(EXIT_FAILURE);
    }
}

void load_ticket_sprite(GameState *game) {
    game->ticket = load_bitmap(TICKET_FILE, NULL);
    if (!game->ticket) {
        allegro_message("Cannot load ticket %s\n", TICKET_FILE);
        exit(EXIT_FAILURE);
    }
}