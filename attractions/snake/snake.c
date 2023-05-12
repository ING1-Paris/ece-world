#include "snake.h"

#include <allegro.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* 🥶 VARIABLES GLOBALES 🥶 */

BITMAP *buffer;
Block *snake_head = NULL;

int fruit_x = 0;
int fruit_y = 0;

int score = 0;
int direction = 0;
int start_time = 0;

bool paused = false;
bool game_over = false;
bool game_exited = false;

// Ajoute un bloc à la fin du snake
void add_block(int x, int y) {
    Block *new_block = (Block *)malloc(sizeof(Block));
    new_block->x = x;
    new_block->y = y;
    new_block->next = NULL;

    Block *last_block = snake_head;
    while (last_block->next != NULL) {
        last_block = last_block->next;
    }

    last_block->next = new_block;
}

// Initialise le jeu, crée le snake initial et créer le fruit
void init_game() {
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    direction = 0;
    score = 0;

    snake_head = (Block *)malloc(sizeof(Block));
    snake_head->x = SCREEN_WIDTH / 2;
    snake_head->y = SCREEN_HEIGHT / 2;
    snake_head->next = NULL;

    for (int i = 1; i < SNAKE_INITIAL_LENGTH; i++) {
        add_block(snake_head->x - i * BLOCK_SIZE, snake_head->y);
    }

    fruit_x = (rand() % (SCREEN_WIDTH - 2 * MIN_DISTANCE_FROM_BORDER) + MIN_DISTANCE_FROM_BORDER) / BLOCK_SIZE * BLOCK_SIZE;
    fruit_y = (rand() % (SCREEN_HEIGHT - 2 * MIN_DISTANCE_FROM_BORDER) + MIN_DISTANCE_FROM_BORDER) / BLOCK_SIZE * BLOCK_SIZE;
}

//  **FONCTION D'INTERRUPTION**
// L'augementation du score est dans une fonction pour pouvoir l'utiliser via une interruption
void increment_score() {
    score++;
}

// Obtiens le meilleurs score dans le fichier de sauvegarde
int get_high_score() {
    FILE *file = fopen(SNAKE_SAVE_FILE, "r");
    int high_score = 0;
    if (file) {
        fscanf(file, "%d", &high_score);
        fclose(file);
    }
    return high_score;
}

// Dessine le jeu selon l'état actuel du serpent, du fruit et du score
void draw_game() {
    clear_bitmap(buffer);
    draw_fruit(fruit_x, fruit_y, makecol(255, 0, 0));

    if (paused == false) {
        textout_centre_ex(buffer, font, "Appuyer sur P ou Echap pour mettre en pause", SCREEN_W / 2, SCREEN_H / 2, makecol(200, 200, 200), -1);
    }

    // Dessine la tête du serpent
    Block *current_block = snake_head;
    rectfill(buffer, current_block->x, current_block->y, current_block->x + BLOCK_SIZE, current_block->y + BLOCK_SIZE, SNAKE_HEAD_COLOR);

    // Dessine le reste du serpent
    current_block = current_block->next;
    while (current_block != NULL) {
        rectfill(buffer, current_block->x, current_block->y, current_block->x + BLOCK_SIZE, current_block->y + BLOCK_SIZE, SNAKE_COLOR);
        current_block = current_block->next;
    }

    if (paused == true) {
        // Assombrit l'arrière plan pour mettre en valeur l'état de pause
        set_trans_blender(0, 0, 0, 128);
        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
        rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(0, 0, 0));
        drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);

        textout_centre_ex(buffer, font, "Le jeu est en pause, appuyer sur P ou Echap pour reprendre.", SCREEN_W / 2, SCREEN_H / 2, makecol(255, 255, 255), -1);
    }

    // Affiche le score actuel et le meilleurs score
    textprintf_ex(buffer, font, 0, 0, makecol(255, 255, 255), -1, "Score: %d", score);
    textprintf_ex(buffer, font, SCREEN_W - 100, 10, makecol(255, 255, 255), -1, "Best: %d", get_high_score());

    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

// Enregistre le score actuel si il est plus grand que le score enregistré
void save_score() {
    FILE *file = fopen(SNAKE_SAVE_FILE, "r");
    int high_score = 0;
    if (file) {
        fscanf(file, "%d", &high_score);
        fclose(file);
    }
    if (score > high_score) {
        file = fopen(SNAKE_SAVE_FILE, "w");
        if (file) {
            fprintf(file, "%d", score);
            fclose(file);
        }
    }
}

// Réinitialise le jeu et le relance
// Fonction appelée quand l'utilisateur redemarre le jeu
void reset_game() {
    // Supprime le serpent
    Block *current = snake_head;
    while (current != NULL) {
        Block *next = current->next;
        free(current);
        current = next;
    }

    score = 0;
    game_over = false;

    init_game();
}

// Affiche l'écran de fin de jeu
// Permet de redémarrer le jeu ou de quitter
void game_over_screen() {
    int choice = 0;  // 0 = Redémarrer, 1 = Quitter
    int done = 0;
    save_score();
    while (!done) {
        if (key[KEY_UP] || key[KEY_DOWN]) {
            choice = 1 - choice;
            rest(200);
        }
        if (key[KEY_SPACE]) {
            if (choice == 0) {
                // Redémarre le jeu
                reset_game();
                done = 1;
            } else {
                // Quitte le jeu
                game_exited = 1;
                done = 1;
            }
        }

        // Affiche les choix possibles
        clear_bitmap(buffer);
        textout_centre_ex(buffer, font, "Jeu terminé", SCREEN_W / 2, SCREEN_H / 2 - 50, makecol(255, 0, 0), -1);
        textout_centre_ex(buffer, font, "Redémarrer", SCREEN_W / 2, SCREEN_H / 2, choice == 0 ? makecol(255, 255, 255) : makecol(127, 127, 127), -1);
        textout_centre_ex(buffer, font, "Abandonner", SCREEN_W / 2, SCREEN_H / 2 + 50, choice == 1 ? makecol(255, 255, 255) : makecol(127, 127, 127), -1);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
}

// Dessine un fruit à la position (x, y)
// Mit en fonction pour que le fruit soit facilement modifiable
void draw_fruit(int x, int y, int color) {
    rectfill(buffer, x, y, x + BLOCK_SIZE, y + BLOCK_SIZE, color);
}

// Fait bouger le serpent dans la bonne direction
void move_snake() {
    int prev_x = snake_head->x;
    int prev_y = snake_head->y;

    // On change la position de la tête du serpent en fonction de la direction
    switch (direction) {
        case 0:  // Droite
            snake_head->x += BLOCK_SIZE;
            break;
        case 1:  // Haut
            snake_head->y -= BLOCK_SIZE;
            break;
        case 2:  // Gauche
            snake_head->x -= BLOCK_SIZE;
            break;
        case 3:  // Bas
            snake_head->y += BLOCK_SIZE;
            break;
    }

    // On change la position du reste des blocs du snake en les parcourant
    // Chaque bloc prend la position du bloc en amont
    Block *current_block = snake_head->next;
    while (current_block != NULL) {
        int temp_x = current_block->x;
        int temp_y = current_block->y;
        current_block->x = prev_x;
        current_block->y = prev_y;
        prev_x = temp_x;
        prev_y = temp_y;
        current_block = current_block->next;
    }
}

// Gère les entrées clavier
// Mit en fonction pour par ruiner le main
void handle_input() {
    if (key[KEY_UP] && direction != 3) {
        direction = 1;
    } else if (key[KEY_DOWN] && direction != 1) {
        direction = 3;
    } else if (key[KEY_LEFT] && direction != 0) {
        direction = 2;
    } else if (key[KEY_RIGHT] && direction != 2) {
        direction = 0;
    } else if (key[KEY_P] || key[KEY_ESC]) {
        paused = !paused;
        rest(100);
    }
}

// Vérifie les différentes collisions du snake avec les murs, lui-même et le fruit
void check_collisions() {
    // Vérfie si le serpent est sur le fruit
    if (snake_head->x == fruit_x && snake_head->y == fruit_y) {
        increment_score();  // Augmente le score car fruit mangé

        int new_block_x, new_block_y;
        Block *last_block = snake_head;
        while (last_block->next != NULL) {
            last_block = last_block->next;
        }

        // Determine le position du nouveau bloc en fonction de la direction du serpent
        switch (direction) {
            case 0:  // Droite
                new_block_x = last_block->x - BLOCK_SIZE;
                new_block_y = last_block->y;
                break;
            case 1:  // Haut
                new_block_x = last_block->x;
                new_block_y = last_block->y + BLOCK_SIZE;
                break;
            case 2:  // Gauche
                new_block_x = last_block->x + BLOCK_SIZE;
                new_block_y = last_block->y;
                break;
            case 3:  // Bas
                new_block_x = last_block->x;
                new_block_y = last_block->y - BLOCK_SIZE;
                break;
        }

        // Ajoute le nouveau bloc au serpent
        add_block(new_block_x, new_block_y);

        // Déplace le fruit à une nouvelle position aléatoire
        fruit_x = (rand() % (SCREEN_WIDTH - 2 * MIN_DISTANCE_FROM_BORDER) + MIN_DISTANCE_FROM_BORDER) / BLOCK_SIZE * BLOCK_SIZE;
        fruit_y = (rand() % (SCREEN_HEIGHT - 2 * MIN_DISTANCE_FROM_BORDER) + MIN_DISTANCE_FROM_BORDER) / BLOCK_SIZE * BLOCK_SIZE;
    }

    // Collision avec le corps du serpent
    Block *current_block = snake_head->next;
    while (current_block != NULL) {
        if (snake_head->x == current_block->x && snake_head->y == current_block->y) {
            game_over = true;
            break;
        }
        current_block = current_block->next;
    }

    // Collision avec les murs
    if (snake_head->x < 0 || snake_head->x >= SCREEN_WIDTH || snake_head->y < 0 || snake_head->y >= SCREEN_HEIGHT) {
        game_over = true;
    }
}

// On nettoie la mémoire en libérant tous les blocs du serpent
void free_memory() {
    Block *current_block = snake_head;
    while (current_block != NULL) {
        Block *next_block = current_block->next;
        free(current_block);
        current_block = next_block;
    }
    clear_bitmap(buffer);
    clear_bitmap(screen);
}

int main() {
    // Initialisation du random et d'Allegro
    srand(time(NULL));
    allegro_init();
    install_keyboard();
    install_timer();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    // Vu que le score et que la fonction qui l'incrémente sont aussi en asynchrone
    // On les verrouillent pour pas qu'il y ait de pb de concurence
    LOCK_VARIABLE(score);
    LOCK_FUNCTION(increment_score);

    // On mets un timer pour incrémenter le score toutes les 10 secondes
    install_int_ex(increment_score, SECS_TO_TIMER(10));

    // On initialise le jeu
    init_game();

    // On lance la boucle principale du jeu
    while (game_exited == false) {
        start_time = clock();

        // On affiche l'écran de fin de jeu si le joueur a perdu
        if (game_over == true) {
            game_over_screen();
        }

        // On obtient les entrées clavier
        handle_input();

        // On déplace le serpent et on vérifie les collisions
        if (paused == false) {
            move_snake();
            check_collisions();
        }

        // On affiche le jeu
        draw_game();

        // On attend le temps restant pour avoir le bon nombre de FPS
        while ((clock() - start_time) < (CLOCKS_PER_SEC / FPS)) {
            // Détends toi, on a le temps
            // Souffle un peu, patiente
            // Tout va bien se passer
            // Il faut juste que tu me fasses confiances
            // Je sais ce que je fais et je sais où je vais
            // T'as vu la bête de phrase ?
            // Aller ciao la zone j'y retourne
        }
    }

    // On nettoie la mémoire et on quitte le jeu
    clear_bitmap(buffer);
    clear_bitmap(screen);
    allegro_exit();
    free_memory();

    return 0;
}
END_OF_MAIN()
