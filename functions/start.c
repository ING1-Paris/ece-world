#include "start.h"

// Menu de demarrage
void start_menu() {
    // Chargement des fonts
    FONT* font = load_font("assets/font.pcx", NULL, NULL);
    if (!font) {
        allegro_message("Error loading font\n");
        exit(EXIT_FAILURE);
    }

    BITMAP* buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP* grad1 = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP* grad2 = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP* grad3 = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP* grad_out = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP* temp = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP* text_bitmap = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP* text_bitmap_2 = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP* text_bitmap_3 = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP* title_bitmap = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);


    int t = 0;

    int color1 = get_random_color();
    int color2 = get_random_color();
    int color3 = get_random_color();

    draw_diagonal_gradient(grad1, color1, color2);
    draw_diagonal_gradient(grad2, color2, color3);

    clear_to_color(text_bitmap, makecol(255, 0, 255));
    clear_to_color(text_bitmap_2, makecol(255, 0, 255));
    clear_to_color(text_bitmap_3, makecol(255, 0, 255));

    textout_centre_ex(text_bitmap_2, font, "ECE WORLD 2023", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, makecol(255, 255, 255), -1);
    textout_centre_ex(text_bitmap, font, "Appuyez sur ESPACE pour commencer", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, makecol(255, 255, 255), -1);
    textout_centre_ex(text_bitmap_3, font, "Demarrage en cours", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, makecol(255, 255, 255), -1);

    int stretch_factor = 2;
    int stretch_factor_2 = 10;

    BITMAP* stretched_bitmap = create_bitmap(text_bitmap->w * stretch_factor, text_bitmap->h * stretch_factor);
    BITMAP* stretched_bitmap_2 = create_bitmap(text_bitmap_2->w * stretch_factor_2, text_bitmap_2->h * stretch_factor_2);
    BITMAP* stretched_bitmap_3 = create_bitmap(text_bitmap_3->w * stretch_factor, text_bitmap_3->h * stretch_factor);

    clear_to_color(stretched_bitmap, makecol(255, 0, 255));
    clear_to_color(stretched_bitmap_2, makecol(255, 0, 255));
    clear_to_color(stretched_bitmap_3, makecol(255, 0, 255));

    masked_stretch_blit(text_bitmap, stretched_bitmap, 0, 0, text_bitmap->w, text_bitmap->h, 0, 0, stretched_bitmap->w, stretched_bitmap->h);
    masked_stretch_blit(text_bitmap_2, stretched_bitmap_2, 0, 0, text_bitmap_2->w, text_bitmap_2->h, 0, 0, stretched_bitmap_2->w, stretched_bitmap_2->h);
    masked_stretch_blit(text_bitmap_3, stretched_bitmap_3, 0, 0, text_bitmap_3->w, text_bitmap_3->h, 0, 0, stretched_bitmap_3->w, stretched_bitmap_3->h);

    clear_to_color(title_bitmap, makecol(255, 0, 255));

    int x = SCREEN_WIDTH / 2 - stretched_bitmap->w / 2;
    int y = SCREEN_HEIGHT / 2 - stretched_bitmap->h / 2 + 300;
    draw_sprite(title_bitmap, stretched_bitmap, x, y);

    int x2 = SCREEN_WIDTH / 2 - stretched_bitmap_2->w / 2;
    int y2 = SCREEN_HEIGHT / 2 - stretched_bitmap_2->h / 2 - 100;  // pour garder la même distance que précédemment
    draw_sprite(title_bitmap, stretched_bitmap_2, x2, y2);


    destroy_bitmap(text_bitmap);
    destroy_bitmap(text_bitmap_2);
    destroy_bitmap(text_bitmap_3);
    destroy_bitmap(stretched_bitmap);

    clear_keybuf();

    while (!key[KEY_SPACE]) {
        if (key[KEY_ESC]) {
            exit(EXIT_SUCCESS);
        }

        draw_transition(grad_out, grad1, grad2, t);
        blit(grad_out, buffer, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        masked_blit(title_bitmap, buffer,  0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        t += 1;
        if (t > 100) {
            t = 0;
            color1 = color2;
            color2 = color3;
            color3 = get_random_color();

            temp = grad1;
            grad1 = grad2;
            grad2 = grad3;
            grad3 = temp;

            draw_diagonal_gradient(grad3, color2, color3);
        }
    }



    while (key[KEY_SPACE]) {
        rest(10);
    }

    clear_to_color(title_bitmap, makecol(255, 0, 255));

    draw_sprite(title_bitmap, stretched_bitmap_3, x, y);

    draw_sprite(title_bitmap, stretched_bitmap_2, x2, y2);

    clear_bitmap(buffer);
    blit(grad_out, buffer, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    masked_blit(title_bitmap, buffer, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    fadeout(buffer);

    clear(screen);

    // textout_centre_ex(screen, font, "Demarrage en cours", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, makecol(255, 255, 255), 0);

    destroy_bitmap(grad1);
    destroy_bitmap(grad2);
    destroy_bitmap(grad3);
    destroy_bitmap(grad_out);
    destroy_bitmap(buffer);
    destroy_bitmap(stretched_bitmap_2);
    destroy_bitmap(stretched_bitmap_3);
    destroy_bitmap(title_bitmap);
}