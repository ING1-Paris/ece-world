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
    BITMAP *background=load_bitmap("C:\\Users\\kylia\\CLionProjects\\test 4\\images rouleau.bmp", NULL);
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

