#include "snake.h"

#include <allegro.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ajoute un bloc à la fin du snake
void add_block(GameState *game, int x, int y) {
    Block *new_block = (Block *)malloc(sizeof(Block));
    new_block->x = x;
    new_block->y = y;
    new_block->next = NULL;

    Block *last_block = game->snake_head;
    while (last_block->next != NULL) {
        last_block = last_block->next;
    }

    last_block->next = new_block;
    new_block->prev = last_block;
}

// Initialise le jeu, crée le snake initial et créer le fruit
void init_game(GameState *game) {
    game->buffer = create_bitmap(SCREEN_W, SCREEN_H);
    game->direction = 0;
    game->score = 0;
    game->fps = INITIAL_FPS;

    game->snake_head = (Block *)malloc(sizeof(Block));
    game->snake_head->x = (rand() % (SCREEN_WIDTH - 10 * MIN_DISTANCE_FROM_BORDER) + MIN_DISTANCE_FROM_BORDER) / BLOCK_SIZE * BLOCK_SIZE;
    game->snake_head->y = (rand() % (SCREEN_WIDTH - 10 * MIN_DISTANCE_FROM_BORDER) + MIN_DISTANCE_FROM_BORDER) / BLOCK_SIZE * BLOCK_SIZE;
    game->snake_head->next = NULL;

    for (int i = 1; i < SNAKE_INITIAL_LENGTH; i++) {
        add_block(game, game->snake_head->x - i * BLOCK_SIZE, game->snake_head->y);
    }

    game->fruit_x = (rand() % (SCREEN_WIDTH - 2 * MIN_DISTANCE_FROM_BORDER) + MIN_DISTANCE_FROM_BORDER) / BLOCK_SIZE * BLOCK_SIZE;
    game->fruit_y = (rand() % (SCREEN_HEIGHT - 2 * MIN_DISTANCE_FROM_BORDER) + MIN_DISTANCE_FROM_BORDER) / BLOCK_SIZE * BLOCK_SIZE;

    game->snake_body_sprites = init_bitmap();
}

BITMAP **init_bitmap() {
    BITMAP **snake_body_sprites = (BITMAP **)malloc(sizeof(BITMAP *) * 10);

    BITMAP *spritesheet = load_bitmap("snake_sprites.bmp", NULL);
    if (!spritesheet) {
        allegro_message("Erreur: le fichier snake_sprites.bmp est introuvable");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 10; i++) {
        snake_body_sprites[i] = create_sub_bitmap(spritesheet, i * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
    }

    return snake_body_sprites;
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
void draw_game(GameState *game) {
    clear_bitmap(game->buffer);
    draw_fruit(game, game->fruit_x, game->fruit_y, makecol(255, 0, 0));

    if (game->paused == false) {
        textout_centre_ex(game->buffer, font, "Appuyer sur P ou Echap pour mettre en pause", SCREEN_W / 2, SCREEN_H / 2, makecol(200, 200, 200), -1);
    }

    // Dessine le serpent
    Block *current_block = game->snake_head;
    while (current_block != NULL) {
        assign_sprite(current_block);
        if (current_block->sprite_id == 10) {
            rectfill(game->buffer, current_block->x, current_block->y, current_block->x + BLOCK_SIZE, current_block->y + BLOCK_SIZE, SNAKE_COLOR);
        } else {
            set_trans_blender(255, 0, 255, 0);
            drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
            draw_sprite(game->buffer, game->snake_body_sprites[current_block->sprite_id], current_block->x, current_block->y);
            drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
        }
        current_block = current_block->next;
    }

    if (game->paused == true) {
        // Assombrit l'arrière plan pour mettre en valeur l'état de pause
        set_trans_blender(0, 0, 0, 128);
        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
        rectfill(game->buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(0, 0, 0));
        drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);

        textout_centre_ex(game->buffer, font, "Le jeu est en pause, appuyer sur P ou Echap pour reprendre.", SCREEN_W / 2, SCREEN_H / 2, makecol(255, 255, 255), -1);
    }

    // Affiche le score actuel et le meilleurs score
    textprintf_ex(game->buffer, font, 0, 0, makecol(255, 255, 255), -1, "Score: %d", game->score);
    textprintf_ex(game->buffer, font, SCREEN_W - 100, 10, makecol(255, 255, 255), -1, "Best: %d", get_high_score());

    blit(game->buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

// Enregistre le score actuel si il est plus grand que le score enregistré
void save_score(GameState *game) {
    FILE *file = fopen(SNAKE_SAVE_FILE, "r");
    int high_score = 0;
    if (file) {
        fscanf(file, "%d", &high_score);
        fclose(file);
    }
    if (game->score > high_score) {
        file = fopen(SNAKE_SAVE_FILE, "w");
        if (file) {
            fprintf(file, "%d", game->score);
            fclose(file);
        }
    }
}

// Réinitialise le jeu et le relance
// Fonction appelée quand l'utilisateur redemarre le jeu
void reset_game(GameState *game) {
    // Supprime le serpent
    Block *current = game->snake_head;
    while (current != NULL) {
        Block *next = current->next;
        free(current);
        current = next;
    }

    game->score = 0;
    game->game_over = false;

    init_game(game);
}

// Affiche l'écran de fin de jeu
// Permet de redémarrer le jeu ou de quitter
void game_over_screen(GameState *game) {
    int choice = 0;  // 0 = Redémarrer, 1 = Quitter
    int done = 0;
    save_score(game);
    while (!done) {
        if (key[KEY_UP] || key[KEY_DOWN]) {
            choice = 1 - choice;
            rest(200);
        }
        if (key[KEY_SPACE]) {
            if (choice == 0) {
                // Redémarre le jeu
                reset_game(game);
                done = 1;
            } else {
                // Quitte le jeu
                game->game_exited = 1;
                done = 1;
            }
        }

        // Affiche les choix possibles
        clear_bitmap(game->buffer);
        textout_centre_ex(game->buffer, font, "Jeu terminé", SCREEN_W / 2, SCREEN_H / 2 - 50, makecol(255, 0, 0), -1);
        textout_centre_ex(game->buffer, font, "Redémarrer", SCREEN_W / 2, SCREEN_H / 2, choice == 0 ? makecol(255, 255, 255) : makecol(127, 127, 127), -1);
        textout_centre_ex(game->buffer, font, "Abandonner", SCREEN_W / 2, SCREEN_H / 2 + 50, choice == 1 ? makecol(255, 255, 255) : makecol(127, 127, 127), -1);
        blit(game->buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
}

// Dessine un fruit à la position (x, y)
// Mit en fonction pour que le fruit soit facilement modifiable
void draw_fruit(GameState *game, int x, int y, int color) {
    rectfill(game->buffer, x, y, x + BLOCK_SIZE, y + BLOCK_SIZE, color);
}

// Fait bouger le serpent dans la bonne direction
void move_snake(GameState *game) {
    int prev_x = game->snake_head->x;
    int prev_y = game->snake_head->y;

    // On change la position de la tête du serpent en fonction de la direction
    switch (game->direction) {
        case 0:  // Droite
            game->snake_head->x += BLOCK_SIZE;
            break;
        case 1:  // Haut
            game->snake_head->y -= BLOCK_SIZE;
            break;
        case 2:  // Gauche
            game->snake_head->x -= BLOCK_SIZE;
            break;
        case 3:  // Bas
            game->snake_head->y += BLOCK_SIZE;
            break;
    }

    // On change la position du reste des blocs du snake en les parcourant
    // Chaque bloc prend la position du bloc en amont
    Block *current_block = game->snake_head->next;
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
void handle_input(GameState *game) {
    if (key[KEY_UP] && game->direction != 3) {
        game->direction = 1;
    } else if (key[KEY_DOWN] && game->direction != 1) {
        game->direction = 3;
    } else if (key[KEY_LEFT] && game->direction != 0) {
        game->direction = 2;
    } else if (key[KEY_RIGHT] && game->direction != 2) {
        game->direction = 0;
    } else if (key[KEY_P] || key[KEY_ESC]) {
        game->paused = !(game->paused);
        draw_game(game);
        rest(100);
    }
}

// Vérifie les différentes collisions du snake avec les murs, lui-même et le fruit
void check_collisions(GameState *game) {
    // Vérfie si le serpent est sur le fruit
    if (game->snake_head->x == game->fruit_x && game->snake_head->y == game->fruit_y) {
        game->score++;  // Augmente le score car fruit mangé

        int new_block_x, new_block_y;
        Block *last_block = game->snake_head;
        while (last_block->next != NULL) {
            last_block = last_block->next;
        }

        // Determine le position du nouveau bloc en fonction de la direction du serpent
        switch (game->direction) {
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
        add_block(game, new_block_x, new_block_y);

        // Déplace le fruit à une nouvelle position aléatoire
        game->fruit_x = (rand() % (SCREEN_WIDTH - 2 * MIN_DISTANCE_FROM_BORDER) + MIN_DISTANCE_FROM_BORDER) / BLOCK_SIZE * BLOCK_SIZE;
        game->fruit_y = (rand() % (SCREEN_HEIGHT - 2 * MIN_DISTANCE_FROM_BORDER) + MIN_DISTANCE_FROM_BORDER) / BLOCK_SIZE * BLOCK_SIZE;
    }

    // Collision avec le corps du serpent
    Block *current_block = game->snake_head->next;
    while (current_block != NULL) {
        if (game->snake_head->x == current_block->x && game->snake_head->y == current_block->y) {
            game->game_over = true;
            break;
        }
        current_block = current_block->next;
    }

    // Collision avec les murs
    if (game->snake_head->x < 0 || game->snake_head->x >= SCREEN_WIDTH || game->snake_head->y < 0 || game->snake_head->y >= SCREEN_HEIGHT) {
        game->game_over = true;
    }
}

// On nettoie la mémoire en libérant tous les blocs du serpent
void free_memory(GameState *game) {
    Block *current_block = game->snake_head;
    while (current_block != NULL) {
        Block *next_block = current_block->next;
        free(current_block);
        current_block = next_block;
    }
    destroy_bitmap(game->buffer);
    destroy_bitmap(screen);
    for (int i = 0; i < 11; i++) {
        destroy_bitmap(game->snake_body_sprites[i]);
    }
}

void assign_sprite(Block *block) {
    int sprite_id;

    if (block->prev == NULL) {  // 10 - la tête
        sprite_id = 10;
    } else if (block->next == NULL) {  // 6 à 9 - la queue
        sprite_id = get_tail_orientation(block);
    } else if (block->prev->x == block->next->x) {  // 1 - le corps horizontal
        sprite_id = 0;
    } else if (block->prev->y == block->next->y) {  // 0 - le corps vertical
        sprite_id = 1;
    } else {  // 2 à 5 - le corps courbé
        sprite_id = get_corner_orientation(block);
        if (sprite_id == -1) {
            sprite_id = 10;
            allegro_message("Erreur lors de l'assignation du sprite");
        }
    }

    block->sprite_id = sprite_id;
}

int get_tail_orientation(Block *block) {
    if (block->prev->x != block->x) {
        if (block->prev->x > block->x) {
            return 9;
        } else {
            return 7;
        }
    } else {
        if (block->prev->y > block->y) {
            return 8;
        } else {
            return 6;
        }
    }
}

int get_corner_orientation(Block *block) {

    // Déterminer la direction du mouvement entre le bloc précédent et le bloc courant
    char *direction_prev;
    if (block->x > block->prev->x) {
        direction_prev = "right";
    } else if (block->x < block->prev->x) {
        direction_prev = "left";
    } else if (block->y > block->prev->y) {
        direction_prev = "up";
    } else {
        direction_prev = "down";
    }

    // Déterminer la direction du mouvement entre le bloc courant et le bloc suivant
    char *direction_next;
    if (block->x > block->next->x) {
        direction_next = "right";
    } else if (block->x < block->next->x) {
        direction_next = "left";
    } else if (block->y > block->next->y) {
        direction_next = "up";
    } else {
        direction_next = "down";
    }

    // Déduire l'orientation du coin à partir des directions du mouvement
    if (strcmp(direction_prev, "down") == 0 && strcmp(direction_next, "right") == 0) {
        return SPRITE_BOTTOM_LEFT;
    } else if (strcmp(direction_prev, "right") == 0 && strcmp(direction_next, "down") == 0) {
        return SPRITE_BOTTOM_LEFT;
    } else if (strcmp(direction_prev, "down") == 0 && strcmp(direction_next, "left") == 0) {
        return SPRITE_BOTTOM_RIGHT;
    } else if (strcmp(direction_prev, "left") == 0 && strcmp(direction_next, "down") == 0) {
        return SPRITE_BOTTOM_RIGHT;
    } else if (strcmp(direction_prev, "up") == 0 && strcmp(direction_next, "right") == 0) {
        return SPRITE_TOP_LEFT;
    } else if (strcmp(direction_prev, "right") == 0 && strcmp(direction_next, "up") == 0) {
        return SPRITE_TOP_LEFT;
    } else if (strcmp(direction_prev, "up") == 0 && strcmp(direction_next, "left") == 0) {
        return SPRITE_TOP_RIGHT;
    } else if (strcmp(direction_prev, "left") == 0 && strcmp(direction_next, "up") == 0) {
        return SPRITE_TOP_RIGHT;
    } else {
        // Ce n'est pas un coin
        return 10;
    }
}

void print_debug(char *message) {
    // write in debug.txt
    FILE *f = fopen("debug.txt", "a");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "%s\n", message);
    fclose(f);
}

int main() {
    // Initialisation du random et d'Allegro
    srand(time(NULL));
    allegro_init();
    install_keyboard();
    install_timer();
    set_color_depth(32);


    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);


    // On initialise le jeu
    GameState game;
    init_game(&game);

    // On lance la boucle principale du jeu
    while (game.game_exited == false) {
        game.start_time = clock();

        // On affiche l'écran de fin de jeu si le joueur a perdu
        if (game.game_over == true) {
            game_over_screen(&game);
        }

        // On obtient les entrées clavier
        handle_input(&game);

        // On déplace le serpent et on vérifie les collisions
        if (game.paused == false) {
            move_snake(&game);
            check_collisions(&game);
        }

        // On affiche le jeu
        draw_game(&game);

        game.fps = game.fps == MAX_FPS ? MAX_FPS : INITIAL_FPS + game.score / SCORE_PER_FPS;

        // On attend le temps restant pour avoir le bon nombre de FPS
        while ((clock() - game.start_time) < (CLOCKS_PER_SEC / game.fps)) {
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
    clear_bitmap(game.buffer);
    clear_bitmap(screen);
    allegro_exit();
    free_memory(&game);

    return 0;
}
END_OF_MAIN()
