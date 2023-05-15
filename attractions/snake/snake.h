/*

TODO: Mettre des Bitmap sur le jeu
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
#define BLOCK_SIZE 25
#define INITIAL_FPS 10
#define MAX_FPS 20
#define SCORE_PER_FPS 5
#define MIN_DISTANCE_FROM_BORDER BLOCK_SIZE
#define SNAKE_INITIAL_LENGTH 4

/* FICHIER DE SAUVEGARDE */
#define SNAKE_SAVE_FILE "attractions/snake/snake.txt"

/* COULEURS */
#define SNAKE_HEAD_COLOR makecol(0, 0, 255)
#define SNAKE_COLOR makecol(0, 255, 0)  // Light green

/* STRUCTURES */
typedef struct Block {
    int x;
    int y;
    struct Block *next;
} Block;

typedef struct GameState {
    BITMAP *buffer;
    Block *snake_head;

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
BITMAP** init_bitmap();
int get_high_score();
void draw_game(GameState *game);
void save_score(GameState *game);
void reset_game(GameState *game);
void game_over_screen(GameState *game);
void draw_fruit(GameState *game, int x, int y, int color);
void move_snake(GameState *game);
void handle_input(GameState *game);
void check_collisions(GameState *game);
void free_memory(GameState *game);
void assign_sprite(Block *block);
int get_tail_orientation(Block *block);
int get_corner_orientation(Block *block);
void print_debug(char *message);
void move_snake(GameState *game);
void debug_init(char* message);

#endif
