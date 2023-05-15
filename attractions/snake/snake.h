/*

TODO: Mettre les bitmaps pour la tête
TODO: Trouvez comment aggrandir le snake (32*32)
TODO: Chnanger les fonts du jeu
TODO: Ajouter des effets sonores (fruit, fruit *5, mort) et une musique de fond
TODO: ajouter un décompte avec de "dépauser" le jeu
TODO: ajouter un "appuyer sur espace pour commencer" avant de commencer le jeu sinon c'est violent
*/

#ifndef SNAKE_H
#define SNAKE_H

#include <allegro.h>
#include <stdbool.h>

/* CONSTANTES */
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BLOCK_SIZE 16
#define SPRITE_SIZE 16
#define INITIAL_FPS 20
#define MAX_FPS 30
#define SCORE_PER_FPS 5
#define MIN_DISTANCE_FROM_BORDER BLOCK_SIZE
#define SNAKE_INITIAL_LENGTH 10

/* DIRECTIONS */
#define SPRITE_TOP_LEFT 2      // 2
#define SPRITE_TOP_RIGHT 3     // 3
#define SPRITE_BOTTOM_LEFT 4   // 4
#define SPRITE_BOTTOM_RIGHT 5  // 5

#define SPRITE_LEFT_TOP SPRITE_TOP_LEFT
#define SPRITE_LEFT_BOTTOM SPRITE_BOTTOM_LEFT
#define SPRITE_RIGHT_TOP SPRITE_TOP_RIGHT
#define SPRITE_RIGHT_BOTTOM SPRITE_BOTTOM_RIGHT

/* FICHIER DE SAUVEGARDE */
#define SNAKE_SAVE_FILE "attractions/snake/snake.txt"

/* COULEURS */
#define SNAKE_HEAD_COLOR makecol(0, 0, 255)
#define SNAKE_COLOR makecol(0, 255, 0)  // Light green

/* STRUCTURES */
typedef struct Block {
    int x;
    int y;
    int sprite_id;
    struct Block *next;
    struct Block *prev;

} Block;

typedef struct GameState {
    BITMAP *buffer;
    Block *snake_head;

    // BITMAP *snake_head_sprite;
    BITMAP **snake_body_sprites;
    // BITMAP *fruit_sprite;

    int fruit_x;
    int fruit_y;

    int fps;
    int score;
    int direction;
    long start_time;
    double snake_speed;

    bool paused;
    bool game_over;
    bool game_exited;
} GameState;

/* FONCTIONS */
void add_block(GameState *game, int x, int y);
void init_game(GameState *game);
BITMAP **init_bitmap();
int get_high_score();
void draw_game(GameState *game);
void save_score(GameState *game);
void reset_game(GameState *game);
void game_over_screen(GameState *game);
void draw_fruit(GameState *game, int x, int y, int color);
void handle_input(GameState *game);
void check_collisions(GameState *game);
void free_memory(GameState *game);
void assign_sprite(Block *block);
int get_tail_orientation(Block *block);
int get_corner_orientation(Block *block);
void print_debug(char *message);
void move_snake(GameState *game);

#endif