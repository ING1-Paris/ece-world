/*
!TODO: supprimer les variables globales sinon ça va mal aller 
!      (toutes les foutres dans une structure qu'on se trimballe partout)
TODO: Une séparation du snake.c en plusieurs sous fichiers .c
TODO: Spawn le snake a une position aléatoire
TODO: rendre le jeu jolie mdr
TODO: ajouter des effets sonores et une musique de fond
TODO: ajouter un décompte avec de "dépauser" le jeu
TODO: ajouter un "appuyer sur espace pour commencer" avant de commencer le jeu sinon c'est violent

TODO: dormir un peu
*/

#ifndef SNAKE_H
#define SNAKE_H

/* CONSTANTES */
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BLOCK_SIZE 25
#define FPS 10
#define MIN_DISTANCE_FROM_BORDER BLOCK_SIZE
#define SNAKE_INITIAL_LENGTH 4

/* FICHIER DE SAUVEGARDE */
#define SNAKE_SAVE_FILE "attractions/snake/snake.txt"

/* COULEURS */
#define SNAKE_HEAD_COLOR makecol(0, 0, 255)
#define SNAKE_COLOR makecol(0, 255, 0)  // Light green

/* STRUCTURES */
typedef struct Block {
    int x, y;
    struct Block *next;
} Block;

/* FONCTIONS */
void add_block(int x, int y);
void init_game();
void increment_score();
int get_high_score();
void draw_game();
void save_score();
void reset_game();
void game_over_screen();
void draw_fruit(int x, int y, int color);
void move_snake();
void handle_input();
void check_collisions();
void free_memory();

#endif
