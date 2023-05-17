#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct player {
    int playerticket;


}player;

// Constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int BUFFER_SIZE = 2;
const int BITMAP_WIDTH = 350;
const int BITMAP_HEIGHT = 350;
const int SCROLL_SPEED = 2;
const int BORDER_WIDTH = 10;

// Bitmaps
BITMAP *bitmap[3];
BITMAP *bitmap2[3];
BITMAP *bitmap3[3];


// Double buffer
BITMAP *buffer[2];
int buffer_index = 0;

// Scroll offset
int scroll_offset = 0;
int scroll_offset2 = 0;
int scroll_offset3 = 0;
void shuffleBitmaps(BITMAP **bitmaps, int count) {
    int i, j;
    BITMAP *temp;

    //srand(time(NULL)); // Initialisation de la graine aléatoire

    // Mélange du tableau
    for (i = count - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = bitmaps[i];
        bitmaps[i] = bitmaps[j];
        bitmaps[j] = temp;
    }
}

int main() {
    // Initialize Allegro
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    //rest(1000);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    player player;

    // Load bitmaps
    bitmap[0] = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\bar jakpot.bmp", NULL);
    bitmap[1] = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\image piece .bmp", NULL);
    bitmap[2] = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\image 7.bmp", NULL);
  
    bitmap2[0]=load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\bar jakpot.bmp", NULL);
    bitmap2[1]=load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\image piece .bmp", NULL);
    bitmap2[2] = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\image 7.bmp", NULL);

    bitmap3[0] = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\image 7.bmp", NULL);
    bitmap3[1] = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\bar jakpot.bmp", NULL);
    bitmap3[2] = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\image piece .bmp", NULL);

    BITMAP* manivelle = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\image manivelle.bmp", NULL);
    BITMAP* manivelleretour = load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\manivelle retour.bmp", NULL);

    // Create double buffer
    buffer[0] = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    buffer[1] = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BITMAP* screen_bitmap = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    int clic_gauche_precedent=0;
    //blit(manivelleretour,screen_bitmap,0,0,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    int i, j;

    srand(time(NULL)); // Initialisation de la graine aléatoire
    BITMAP *temp;
    BITMAP *temp2;
    BITMAP *temp3;
    shuffleBitmaps(bitmap, 3);
    shuffleBitmaps(bitmap2, 3);
    shuffleBitmaps(bitmap3, 3);

    // Mélange du tableau
    //for (i = 2; i > 0; i--) {
        //j = rand() % (i + 1);
        //temp = bitmap[i];
        //bitmap[i] = bitmap[j];
        //bitmap[j] = temp;
    //}
    //for (i = 2; i > 0; i--) {
        //j = rand() % (i + 1);
        //temp2 = bitmap2[i];
        //bitmap2[i] = bitmap2[j];
        //bitmap2[j] = temp2;
    //}
    //for (i = 2; i > 0; i--) {
        //j = rand() % (i + 1);
        //temp3 = bitmap3[i];
        //bitmap3[i] = bitmap3[j];
        //bitmap3[j] = temp3;
    //}

    // Main loop
    int bitmap_index = 0;
    int bitmap_index2 = 0;
    int bitmap_index3 = 0;
    draw_sprite(screen,bitmap[0],0,130);
    draw_sprite(screen,bitmap2[0],355,130);
    draw_sprite(screen,bitmap3[0],710,130);
    rectfill(screen, 0, 0, SCREEN_WIDTH, 140, makecol(0, 0, 0)); // top
    rectfill(screen, 0, SCREEN_HEIGHT - 90, SCREEN_WIDTH, SCREEN_HEIGHT, makecol(0, 0, 0)); // bottom
    rectfill(screen, 0, 0, 10, SCREEN_HEIGHT, makecol(0, 0, 0)); // left
    rectfill(screen, SCREEN_WIDTH - 25, 0, SCREEN_WIDTH, SCREEN_HEIGHT, makecol(0, 0, 0));// right
    //draw_sprite(screen,bitmap[0],0,130);
    //draw_sprite(screen,bitmap2[0],355,130);
    //draw_sprite(screen,bitmap3[0],710,130);

    draw_sprite(screen, manivelle, 1060, 193);
    int k=0;
    player.playerticket=5;
    while (!key[KEY_ESC]) {
        // Le bouton gauche de la souris est enfoncé;
        //k=k+0.001;
        if(((mouse_b & 1&&mouse_x>106 && mouse_x < 1060+manivelle->w && mouse_y >= 300&& mouse_y < 300+manivelle->h)||(clic_gauche_precedent==1))&&k<=754) {
                //clear_to_color(screen_bitmap, makecol(0,0,0));

                clic_gauche_precedent=1;
                //int k=0;
                k=k+1;printf("%d\n",k);
                if (k==755){
                printf("je l'ai trouve las sjnjchdvcdnvkdjvkjkvjfjvfvl");
                player.playerticket-=1;
                int color1 = getpixel(screen, 175, SCREEN_HEIGHT-manivelleretour->h);
                int color2=getpixel(screen, 530, SCREEN_HEIGHT-manivelleretour->h);
                int color3=getpixel(screen, 885, SCREEN_HEIGHT-manivelleretour->h);
                if ((color1==color2)&&(color1==color3)&&(color2==color3)){
                    printf("la partie est gagne");
                    printf("%d   %d   %d",color1,color2,color3);
                    //piece=16637518  7=15343395
                    if (color1==16637518){
                        player.playerticket=player.playerticket+2;
                    }
                    if (color1==15343395){
                        player.playerticket=player.playerticket-1;
                    }
                    printf(" le nombre de tich=ket du joueur est de %d",player.playerticket);
                }
                else{
                    printf("partie perdue");
                }
            }


        if(k<500){
            scroll_offset =scroll_offset +SCROLL_SPEED+25;
            scroll_offset2 =scroll_offset2 +SCROLL_SPEED+20;
            scroll_offset3 =scroll_offset3 +SCROLL_SPEED+15;

        }
        else if (k>500 &&k <750){
            scroll_offset =scroll_offset +SCROLL_SPEED+5;
            scroll_offset2 =scroll_offset2 +SCROLL_SPEED+11;
            scroll_offset3 =scroll_offset3 +SCROLL_SPEED+19;
        }
        else if (k>750 && k<1000){
            scroll_offset =scroll_offset +SCROLL_SPEED+6;
            scroll_offset2 =scroll_offset2 +SCROLL_SPEED+5;
            scroll_offset3 =scroll_offset3 +SCROLL_SPEED+5;
        }
        else{
            scroll_offset =scroll_offset +SCROLL_SPEED;
            scroll_offset2 =scroll_offset2 +SCROLL_SPEED;
            scroll_offset3 =scroll_offset3 +SCROLL_SPEED;
        }




        // If the first bitmap goes out of screen, reset scroll offset and bitmap index
        if (scroll_offset >= BITMAP_HEIGHT) {
            scroll_offset = 0;
            bitmap_index = (bitmap_index + 1) % 3;
        }
        if (scroll_offset2 >= BITMAP_HEIGHT) {
                scroll_offset2 = 0;
                bitmap_index2 = (bitmap_index2 + 1) % 3;
        }
        if (scroll_offset3>= BITMAP_HEIGHT) {
                scroll_offset3 = 0;
                bitmap_index3 = (bitmap_index3 + 1) % 3;
        }

        // Draw bitmaps to buffer
        clear_bitmap(buffer[buffer_index]);

        // Draw bitmaps one after the other in a loop


        int y = -scroll_offset;
        int y2 = -scroll_offset2;
        int y3 = -scroll_offset3;

        for (int i = 0; i < 4; i++) {
            draw_sprite(buffer[buffer_index], bitmap[(bitmap_index + i) % 3], 0, y);
            draw_sprite(buffer[buffer_index], bitmap2[(bitmap_index2 + i) % 3], 355, y2);
            draw_sprite(buffer[buffer_index], bitmap3[(bitmap_index3 + i) % 3], 710, y3);
            y += BITMAP_HEIGHT;
            y2 += BITMAP_HEIGHT;
            y3 += BITMAP_HEIGHT;
        }
        rectfill(buffer[buffer_index], 0, 0, SCREEN_WIDTH, 140, makecol(0, 0, 0)); // top
        rectfill(buffer[buffer_index], 0, SCREEN_HEIGHT - 90, SCREEN_WIDTH, SCREEN_HEIGHT, makecol(0, 0, 0)); // bottom
        rectfill(buffer[buffer_index], 0, 0, 10, SCREEN_HEIGHT, makecol(0, 0, 0)); // left
        rectfill(buffer[buffer_index], SCREEN_WIDTH - 25, 0, SCREEN_WIDTH, SCREEN_HEIGHT, makecol(0, 0, 0));// right
        draw_sprite(buffer[buffer_index],manivelleretour,1060,300);


        // Flip buffer to screen
        //acquire_screen();
        blit(buffer[buffer_index], screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        //release_screen();

        // Switch buffer
        buffer_index = (buffer_index + 1) % BUFFER_SIZE;

        rest(1);
            }
        else{
            if (k!=0){
                if (key[KEY_R]){
                    clear_to_color(screen, makecol(0,0,0));
                    draw_sprite(screen,bitmap[0],0,130);

                }
                }
        }

    }
    //draw_sprite(screen,manivelle,0,0);
    //rest(2000);

    destroy_bitmap(buffer[0]);
    destroy_bitmap(buffer[1]);
    destroy_bitmap(bitmap[0]);
    destroy_bitmap(bitmap[1]);
    destroy_bitmap(bitmap[2]);
    destroy_bitmap(bitmap2[0]);
    destroy_bitmap(bitmap2[1]);
    destroy_bitmap(bitmap2[2]);
    destroy_bitmap(bitmap3[0]);
    destroy_bitmap(bitmap3[1]);
    destroy_bitmap(bitmap3[2]);
    return 0;
}
END_OF_MAIN();
