#ifndef MAIN_H
#define MAIN_H

/* VARIABLE GLOBALE DE *DEBUG UNIQUEMENT* */
double fps = 0;
double frames_accum = 0;
double fps_timer;

// Dimensions de la fenêtre du jeu
#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 900

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50

#define ATTRACTION_WIDTH 100
#define ATTRACTION_HEIGHT 100

#define PLAYER_AMOUNT 2
#define ATTRACTIONS_AMOUNT 7
#define SECONDARY_AMOUNT 2

#define TICKETS_AMOUNT 7

/*TOUCHE DES JOUEURS*/
#define MOUVEMENT_KEYS_AMOUNT 4
#define MISC_KEYS_AMOUNT 5

const int PLAYER1_KEYS[MOUVEMENT_KEYS_AMOUNT] = {KEY_Z, KEY_S, KEY_Q, KEY_D};
const int PLAYER2_KEYS[MOUVEMENT_KEYS_AMOUNT] = {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
const int PLAYER3_KEYS[MOUVEMENT_KEYS_AMOUNT] = {KEY_I, KEY_K, KEY_J, KEY_L};
const int PLAYER4_KEYS[MOUVEMENT_KEYS_AMOUNT] = {KEY_T, KEY_G, KEY_F, KEY_H};

const int* PLAYERS_KEYS[MOUVEMENT_KEYS_AMOUNT] = {PLAYER1_KEYS, PLAYER2_KEYS, PLAYER3_KEYS, PLAYER4_KEYS};

/* ATTRACTIONS PATH */
#define ATTRACTION0_NAME "canard"
#define ATTRACTION1_NAME "cheval"
#define ATTRACTION2_NAME "grenouille"
#define ATTRACTION3_NAME "jackpot"
#define ATTRACTION4_NAME "snake"

const char* ATTRACTIONS_NAMES[ATTRACTIONS_AMOUNT] = {ATTRACTION0_NAME, ATTRACTION1_NAME, ATTRACTION2_NAME, ATTRACTION3_NAME, ATTRACTION4_NAME};

// Structure de données pour les personnages
typedef struct t_player {
    int x;
    int y;
    int color;
    int tickets;
} Player;

// Structure de données pour les attractions spéciaux
typedef struct t_attraction {
    int x;
    int y;
    int width;
    int height;
    int player_on_amount;

    bool triggered[PLAYER_AMOUNT];
    bool is_exit;
    bool is_stats;

    char name[20];

    char executable_path[100];
    char end_path[100];
    char best_path[100];
} Attraction;

typedef struct t_gameState {
    int player_speed;
    int fps;
    int winner;

    bool PRESSED_MISC_KEYS[MISC_KEYS_AMOUNT];
    bool debug;
    bool over;
    bool attraction_is_running;
    bool stats_displayed;
    bool winner_displayed;
    bool attraction_is_over;

    int attraction_index;
    int attraction_winner;
    int attraction_winner_2;
    float attraction_winner_score;
    float attraction_winner_2_score;

    FONT* font;
    BITMAP* buffer;
    BITMAP* attractions_bitmaps[ATTRACTIONS_AMOUNT - SECONDARY_AMOUNT];
    BITMAP* player_bitmaps [PLAYER_AMOUNT];
    Player players[PLAYER_AMOUNT];
    Attraction attractions[ATTRACTIONS_AMOUNT];
} GameState;

/* FONCTIONS */
double current_time();
void draw_fps(GameState* game);
void init_bitmap(GameState* game);
int random_color();
void display(GameState* game);
void check_collisions(GameState* game);
void init_game(GameState* game);
void handle_input(GameState* game);
void run_attractions(GameState* game);
float wait_attractions_end(GameState* game, int attraction_index);
void clean_game(GameState* game);
void check_for_winner(GameState* game);

#endif