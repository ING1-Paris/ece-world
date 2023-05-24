#include "tools.h"

// Renvoie le temps actuel en millisecondes
double current_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000.0 + time.tv_usec / 1000.0;
}

// Calcul le nombre de frames par seconde
// Et l'affiche dans le HUD si le mode debug est activé
void draw_fps(GameState* game) {
    double current_timestamp = current_time();

    if (current_timestamp >= debug_timestamp + 1000) {
        debug_fps = debug_frames_accum;
        debug_frames_accum = 0;
        debug_timestamp = current_timestamp;
    }

    debug_frames_accum++;

    if (game->debug_mode > 0) {
        char fps_str[30];
        char frame_accum_str[30];
        char fps_timer_str[30];
        char player_speed_str[30];

        sprintf(fps_str, "FPS: %.0f", debug_fps);
        sprintf(frame_accum_str, "Frames counter: %.0f", debug_frames_accum);
        sprintf(player_speed_str, "Players Speed: %d", game->player_speed);
        sprintf(fps_timer_str, "Timestamp: %.f", debug_timestamp / 1000);

        textout_ex(game->buffer, game->font, fps_str, 10, 20, makecol(255, 255, 255), -1);
        textout_ex(game->buffer, game->font, frame_accum_str, 10, 40, makecol(255, 255, 255), -1);
        textout_ex(game->buffer, game->font, player_speed_str, 10, 60, makecol(255, 255, 255), -1);
        textout_ex(game->buffer, game->font, fps_timer_str, 10, 80, makecol(255, 255, 255), -1);
    }
}

// Renvoie une couleur aléatoire
int get_random_color() {
    // Verifie que la couleur n'est pas trop sombre
    // Sinon on en génère une autre
    int red = rand() % 255;
    int green = rand() % 255;
    int blue = rand() % 255;




    return makecol(red, green, blue);
}

// Libère la mémoire et détruit les bitmaps
void clean_game(GameState* game) {
    // Libère la mémoire salope

    destroy_font(game->font);

    destroy_bitmap(game->buffer);
    for (int i = 0; i < ATTRACTIONS_AMOUNT - SECONDARY_AMOUNT; i++) {
        destroy_bitmap(game->attractions_bitmaps[i]);
    }
    for (int i = 0; i < PLAYERS_AMOUNT; i++) {
        destroy_bitmap(game->player_bitmaps[i]);
    }
    free_idle_bitmaps(game);
    free_walk_bitmaps(game);
}

// Libère la mémoire et détruit les bitmaps du idle
void free_idle_bitmaps(GameState* game) {
    for (int i = 0; i < PLAYERS_AMOUNT; i++) {
        if (game->players[i].idle_bitmaps) {
            for (int j = 0; j < 4; j++) {
                if (game->players[i].idle_bitmaps[j]) {
                    for (int k = 0; k < 2; k++) {
                        if (game->players[i].idle_bitmaps[j][k]) {
                            destroy_bitmap(game->players[i].idle_bitmaps[j][k]);
                            game->players[i].idle_bitmaps[j][k] = NULL;
                        }
                    }
                    free(game->players[i].idle_bitmaps[j]);
                    game->players[i].idle_bitmaps[j] = NULL;
                }
            }
            free(game->players[i].idle_bitmaps);
            game->players[i].idle_bitmaps = NULL;
        }
    }
}

// Libère la mémoire et détruit les bitmaps du walk
void free_walk_bitmaps(GameState* game) {
    for (int i = 0; i < PLAYERS_AMOUNT; i++) {
        if (game->players[i].walk_bitmaps) {
            for (int j = 0; j < 4; j++) {
                if (game->players[i].walk_bitmaps[j]) {
                    for (int k = 0; k < 4; k++) {
                        if (game->players[i].walk_bitmaps[j][k]) {
                            destroy_bitmap(game->players[i].walk_bitmaps[j][k]);
                            game->players[i].walk_bitmaps[j][k] = NULL;
                        }
                    }
                    free(game->players[i].walk_bitmaps[j]);
                    game->players[i].walk_bitmaps[j] = NULL;
                }
            }
            free(game->players[i].walk_bitmaps);
            game->players[i].walk_bitmaps = NULL;
        }
    }
}

// Pour quitter le jeu avec la croix dans la fenêtre
void close_button_handler() {
    close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)

void update_animation_frame(GameState* game) {
    double current_time_a = current_time();
    if (current_time_a - game->last_frame_time > 200) {
        game->animation_frame = (game->animation_frame + 1) % 16;
        game->last_frame_time = current_time_a;
    }
}

// Dessine un dégradé diagonal dans la background.
// Je n'ai pas créee cette fonction, je l'ai trouvée sur internet.
// Je n'ai pas réussi à en retrouver le lien par contre
void draw_diagonal_gradient(BITMAP* bmp, int start_color, int end_color) {
    int width = bmp->w;
    int height = bmp->h;

    // Extract RGB components from start and end colors
    int start_r = getr(start_color), start_g = getg(start_color), start_b = getb(start_color);
    int end_r = getr(end_color), end_g = getg(end_color), end_b = getb(end_color);

    // Calculate color differences
    int r_diff = end_r - start_r;
    int g_diff = end_g - start_g;
    int b_diff = end_b - start_b;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Determining the ratio for color interpolation.
            float ratio = (float)(x + y) / (width + height - 2);

            // Interpolating the colors.
            int r = start_r + r_diff * ratio;
            int g = start_g + g_diff * ratio;
            int b = start_b + b_diff * ratio;

            // Getting the color.
            int color = makecol(r, g, b);

            // Setting the pixel.
            putpixel(bmp, x, y, color);
        }
    }
}

void draw_transition(BITMAP* bmp, BITMAP* grad1, BITMAP* grad2, int t) {
    int width = bmp->w;
    int height = bmp->h;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Get colors from grad1 and grad2.
            int color1 = getpixel(grad1, x, y);
            int color2 = getpixel(grad2, x, y);

            // Extract RGB components from color1 and color2.
            int r1 = getr(color1), g1 = getg(color1), b1 = getb(color1);
            int r2 = getr(color2), g2 = getg(color2), b2 = getb(color2);

            // Calculate interpolated RGB components.
            float prog = t / 100.0;

            int r = r1 + (r2 - r1) * prog;
            int g = g1 + (g2 - g1) * prog;
            int b = b1 + (b2 - b1) * prog;

            // Create new color.
            int color = makecol(r, g, b);

            // Set pixel in bmp.
            putpixel(bmp, x, y, color);
        }
    }
}

void fadeout(BITMAP* last_screen) {
    BITMAP* buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);

    for (int i = 0; i < 256; i++) {
        blit(last_screen, buffer, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        set_trans_blender(0, 0, 0, i);
        rectfill(buffer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, makecol(0, 0, 0));
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        rest(20);
    }
    drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);

    destroy_bitmap(buffer);
}

void fadein(BITMAP* new_screen) {
    BITMAP* buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);

    for (int i = 0; i < 256; i++) {
        blit(new_screen, buffer, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        set_trans_blender(0, 0, 0, 255 - i);
        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);

        rectfill(buffer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, makecol(0, 0, 0));
        drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        rest(10);
    }

    destroy_bitmap(buffer);
}