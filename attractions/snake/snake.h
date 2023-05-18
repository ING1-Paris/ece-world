#ifndef SNAKE_H
#define SNAKE_H

/* CONSTANTES */
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 608
#define BLOCK_SIZE 32
#define SPRITE_SIZE 16
#define STRETCHED_SPRITE_SIZE 32
#define INITIAL_FPS 10
#define MAX_FPS 5 + INITIAL_FPS
#define SCORE_PER_FPS 5
#define MIN_FRUIT_DISTANCE_FROM_BORDER 2 * BLOCK_SIZE
#define MIN_SNAKE_SPAWN_DISTANCE_FROM_BORDER 10 * BLOCK_SIZE
#define SNAKE_INITIAL_LENGTH 10

/* DIRECTIONS DANS LE PLAN*/
#define DIRECTION_RIGHT 0
#define DIRECTION_DOWN 1
#define DIRECTION_LEFT 2
#define DIRECTION_UP P

/* DIRECTIONS DES SPRITES*/
#define SPRITE_TOP_LEFT 2      // 2
#define SPRITE_TOP_RIGHT 3     // 3
#define SPRITE_BOTTOM_LEFT 4   // 4
#define SPRITE_BOTTOM_RIGHT 5  // 5

#define SPRITE_LEFT_TOP SPRITE_TOP_LEFT
#define SPRITE_LEFT_BOTTOM SPRITE_BOTTOM_LEFT
#define SPRITE_RIGHT_TOP SPRITE_TOP_RIGHT
#define SPRITE_RIGHT_BOTTOM SPRITE_BOTTOM_RIGHT

/* FICHIERS */
#define SNAKE_END_SAVE_FILE "attractions/snake/end.txt"
#define SNAKE_BEST_SAVE_FILE "attractions/snake/best.txt"
#define SNAKE_FONT_FILE "attractions/snake/assets/font.pcx"
#define SNAKE_BITMAP_FILE "attractions/snake/assets/sprites.bmp"

/* SONS */
#define SNAKE_START_SOUND_FILE "attractions/snake/assets/sounds/start.wav"                    // 0
#define SNAKE_EATING_SOUND_FILE "attractions/snake/assets/sounds/eating.wav"                  // 1
#define SNAKE_SPEED_INCREASE_SOUND_FILE "attractions/snake/assets/sounds/speed_increase.wav"  // 2
#define SNAKE_HIGH_SCORE_SOUND_FILE "attractions/snake/assets/sounds/high_score.wav"          // 3
#define SNAKE_GAME_OVER_SOUND_FILE "attractions/snake/assets/sounds/game_over.wav"            // 4

#define SOUND_AMOUNT 5

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
    Block *snake_head;

    FONT *snake_font;

    SAMPLE **sounds;

    BITMAP *buffer;
    BITMAP *floor_sprite;

    BITMAP ***snake_head_sprites;
    BITMAP **snake_body_sprites;
    BITMAP **fruit_sprites;
    BITMAP **floor_tiles_sprite;

    int frame_counter;  // Compteur pour savoir quand changer d'image
    bool fruit_eaten;   // Si le fruit a été mangé

    int fruit_x;
    int fruit_y;
    int fruit_color;

    int fps;
    int score;
    int direction;
    long start_time;

    bool new_high_score;
    bool paused;
    bool over;
    bool exited;
    bool started;
} GameState;

/* FONCTIONS */
void add_block(GameState *game, int x, int y);
void init_game(GameState *game);
BITMAP **init_bitmap_snake_body(BITMAP *spritesheet);
BITMAP ***init_bitmap_snake_head(BITMAP *spritesheet);
BITMAP **init_bitmap_fruit(BITMAP *spritesheet);
BITMAP **init_bitmap_floor(BITMAP *spritesheet);
BITMAP *generate_floor_sprite(GameState *game);

int get_high_score();
void draw_game(GameState *game);
void save_score(GameState *game);
void reset_game(GameState *game);
void game_over_screen(GameState *game);
void draw_fruit(GameState *game, int x, int y);
void handle_input(GameState *game);
void check_collisions(GameState *game);
void free_memory(GameState *game);
void assign_sprite(Block *block);
int get_tail_orientation(Block *block);
int get_corner_orientation(Block *block);
void print_debug(char *message);
void move_snake(GameState *game);
SAMPLE **init_sounds();
void play_sound(GameState *game, int sound_id);

#endif