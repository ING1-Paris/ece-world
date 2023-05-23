#include "start.h"

// Menu de demarrage
void start_menu(GameState* game) {
    textout_centre_ex(screen, game->font, "Appuyer sur ESPACE pour commencer", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, makecol(255, 255, 255), -1);
    while (!key[KEY_SPACE]) {
        rest(1);
    }
    clear_bitmap(screen);
    textout_centre_ex(screen, game->font, "Demarrage en cours", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, makecol(255, 255, 255), -1);
    rest(100); //1500
    clear_bitmap(screen);
}