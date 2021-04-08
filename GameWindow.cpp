#include "GameWindow.h"
#include <iostream>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)

#define BAD_END 1
#define HAPPY_END 2
#define TRUE_END 3
#define GAMEOVER 4

#define BRICK 1
#define CLOUD 2
#define THORN 3
#define CFAKE 4
#define JOHAN 10
#define SHATA 11
#define BASHA 12
#define OTTO 13
#define MEMORY 14
#define OTIS 15
#define RODD 16
#define MARY 17
#define FARMER 18
#define SATINA 19
#define SMOOTHPERSON 20
#define HANS 21


bool
GameWindow::mouse_hover(int startx, int starty, int width, int height)
{
    if(mouse_x >= startx && mouse_x <= startx + width)
        if(mouse_y >= starty && mouse_y <= starty + height)
            return true;

    return false;
}

Object*
GameWindow::create_object(int type, int pos, bool num)
{
    Object *o = NULL;
    switch(type){
        case BRICK:
            o = new Brick((pos/10)*40, (pos%10)*40, num);
            break;
        case CLOUD:
            o = new Cloud((pos/10)*40, (pos%10)*40, num);
            break;
        case THORN:
            o = new Thorn((pos/10)*40, (pos%10)*40, num);
            break;
        case JOHAN:
            o = new Johan((pos/10)*40, (pos%10)*40, num);
            break;
        case CFAKE:
            o = new Cfake((pos/10)*40, (pos%10)*40, num);
            break;
        case MEMORY:
            o = new Memory((pos/10)*40, (pos%10)*40, num);
            break;
        case OTTO:
            o = new Otto((pos/10)*40, (pos%10)*40, num);
            break;
        case OTIS:
            o = new Otis((pos/10)*40, (pos%10)*40, num);
            break;
        case FARMER:
            o = new Farmer((pos/10)*40, (pos%10)*40, num);
            break;
        case MARY:
            o = new Mary((pos/10)*40, (pos%10)*40, num);
            break;
        case SATINA:
            o = new Satina((pos/10)*40, (pos%10)*40, num);
            break;
        case BASHA:
            o = new Basha((pos/10)*40, (pos%10)*40, num);
            break;
        case SHATA:
            o = new Shata((pos/10)*40, (pos%10)*40, num);
            break;
        case RODD:
            o = new Rodd((pos/10)*40, (pos%10)*40, num);
            break;
        case SMOOTHPERSON:
            o = new SmoothPerson((pos/10)*40, (pos%10)*40, num);
            break;
        case HANS:
            o = new Hans((pos/10)*40, (pos%10)*40, num);
            break;
    }
    return o;
}

void
GameWindow::set_map(int stage, bool num){
    char buffer[50];
    int type;
    FILE *file;

    if(num)
        sprintf(buffer, "Map/DOWN_%d.txt", stage);
    else
        sprintf(buffer, "Map/Up_%d.txt", stage);

    file = fopen(buffer, "r");

    fscanf(file, "%s", buffer);
    type = atoi(buffer);

    if(num)this->ObjectSet_D.clear();
    else this->ObjectSet.clear();

    while(fscanf(file, "%s", buffer) != EOF && buffer[0]!='S') {
        if(num)road_D[atoi(buffer)] = true;
        else road[atoi(buffer)] = true;
    }
    while(fscanf(file, "%s", buffer)!=EOF && buffer[0]!='E'){
        type = atoi(buffer);
        while(fscanf(file, "%s", buffer) != EOF && buffer[0]!='S') {
            Object *o = create_object(type, atoi(buffer), num);
            if(o != NULL){
                if(num) ObjectSet_D.push_back(o);
                else ObjectSet.push_back(o);
            }
            if(type!=BRICK){
                if(num){
                    if(type==CLOUD) Obj_D[atoi(buffer)+10]=true;
                    Obj_D[atoi(buffer)]=true;
                }
                else {
                    if(type==CLOUD) Obj[atoi(buffer)+10]=true;
                    Obj[atoi(buffer)]=true;
                }
            }
        }
    }
    fclose(file);

    if(stage==5 && num==0)
        al_play_sample(Piano_song, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void
GameWindow::DrawMap(int position, int position_D){
    for(int i=0; i<NumOfGrid; i++)
        if(road[i])
            al_draw_bitmap(brick, position+(i/10)*40, (i%10)*40, 0);
    for(int i=0; i<NumOfGrid; i++)
        if(road_D[i])
            al_draw_bitmap(brick, position_D+(i/10)*40, window_height/2+(i%10)*40, 0);
}

void
GameWindow::game_init(){
    char buffer[50];

    back_down = al_load_bitmap("Map/BACK_D_0_5.png");
    back_up = al_load_bitmap("Map/BACK_D_1_5.png");
    icon = al_load_bitmap("./icon.png");
    heart = al_load_bitmap("./Map/love.png");
    Bheart = al_load_bitmap("./Map/loveB.png");
    brick = al_load_bitmap("./Object/Brick.png");
    story = al_load_bitmap("./Title/Story.png");
    Title = al_load_bitmap("./Title/Title.png");
    BE = al_load_bitmap("./Title/BE.png");
    TE = al_load_bitmap("./Title/TE.png");
    HE = al_load_bitmap("./Title/HE.png");
    gameover = al_load_bitmap("./Title/GAMEOVER.png");
    back_u = al_load_bitmap("./Map/BACK_U.png");
    back_d = al_load_bitmap("./Map/BACK_D.png");
    al_set_display_icon(display, icon);
    al_reserve_samples(3);
    for(int i = 0; i < 11; i++){
        sprintf(buffer, "./Intro/%d.png", i);
        intro[i] = al_load_bitmap(buffer);
    }
    Sound = al_load_sample("./Music/State0.wav");
    Title_song = al_load_sample("./Music/Title.wav");
    Piano_song = al_load_sample("./Music/Piano.wav");
    P1 = new Bear();
    for(int i = 0; i < 8; i++){
        sprintf(buffer, "./Bear/P1_%d.png", i+1);
        P1->setImg(buffer, i);
    }
    P2 = new Bear();
    for(int i = 0; i < 8; i++){
        sprintf(buffer, "./Bear/P2_%d.png", i+1);
        P2->setImg(buffer, i);
    }
}

void
GameWindow::game_play(){
    int msg;

    srand(time(NULL));

    msg = -1;
    /*
    *  We start the game by calling game_begin to start timer and play music
    * [TODO]:
    *     You may add some function to create starting scene before calling game_begin
    *     e.g: game_start_scene()
    */
    game_begin();

    /*
    *  while game is running, the result of game_run will be returned to msg.
    *  If msg is GAME_EXIT, then tower game will terminate.
    */
    while(msg != GAME_EXIT)
        msg = game_run();

    show_err_msg(msg);
}

void
GameWindow::show_err_msg(int msg){
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

GameWindow::GameWindow(){
    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    /*
    * Create two timers to control different parts of tower game:
    *    a. timer: control the animation of each object, stopped when game doesn't run.
    *    b. monster_pro: control the production of monster, stooped when there is no need to produce monster.
    */
    timer = al_create_timer(1.0 / FPS);

    if(timer == NULL)
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_font("./Title/misaki_gothic.ttf", 24, 0); // load small font
    Medium_font = al_load_ttf_font("./Title/misaki_gothic.ttf",48,0); //load medium font
    Large_font = al_load_ttf_font("./Title/misaki_gothic.ttf",72,0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    // Initializing resources that tower game needs.
    game_init();
}

void
GameWindow::game_begin(){
    if(state == STATE_TITLE) set_state_title();
    else if(state == STATE_START) set_state_start();
    else if(state == STATE_STORY) set_state_story();
    else if(state == STATE_SETTING) set_state_set();
    al_start_timer(timer);
}

void
GameWindow::set_state_title(){
    al_stop_sample(ID);
    al_play_sample(Title_song, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, ID);
    draw_title_map();
}

void
GameWindow::set_state_set(){
    draw_set_map();
}

void
GameWindow::set_state_start(){
    al_stop_sample(ID);
    al_play_sample(Sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, ID);
    draw_start_map();
}

void
GameWindow::set_state_story(){
    al_stop_sample(ID);
    al_play_sample(Sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, ID);
    draw_story_map();
}

int
GameWindow::game_run(){
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;
}


int
GameWindow::game_update(){

    if(P1->getHeart()<=0 && P2->getHeart()<=0){
        final_end=GAMEOVER;
        return GAME_CONTINUE;
    }
    else if(P1->End && P2->End){
        if(P1->black && P2->black)
            final_end=BAD_END;
        else if(P1->black || P2->black)
            final_end=TRUE_END;
        else if(!P1->black  &&  !P2->black)
            final_end=HAPPY_END;
        return GAME_CONTINUE;
    }
    else if(P1->End && P2->getHeart()<=0){
        if(P1->black)
            final_end=BAD_END;
        else
            final_end=HAPPY_END;
        return GAME_CONTINUE;

    }
    else if(P2->End && P1->getHeart()<=0){
        if(P2->black)
            final_end=BAD_END;
        else
            final_end=HAPPY_END;
        return GAME_CONTINUE;
    }


    std::list<Object*>::iterator it;
    if(P1->change && P1->getHeart()>0){
        P1->change=false;
        memset(road, 0, NumOfGrid);
        memset(Obj, 0, NumOfGrid);
        set_map(P1->stage, 0);
        P1->reSet_U();
    }
    if(P2->change && P2->getHeart()>0){
        P2->change=false;
        memset(road_D, 0, NumOfGrid);
        memset(Obj_D, 0, NumOfGrid);
        set_map(P2->stage, 1);
        P2->ResetPos();
    }
    if(P1->getHeart()>0){
        for(it=ObjectSet.begin(); it!=ObjectSet.end(); it++){
            (*it)->IsMatch(P1);
            (*it)->IsMatch(P2);
            if((*it)->event) (*it)->Event();
        }
    }
    if(P2->getHeart()>0){
        for(it=ObjectSet_D.begin(); it!=ObjectSet_D.end(); it++){
            (*it)->IsMatch(P1);
            (*it)->IsMatch(P2);
            if((*it)->event) (*it)->Event();
        }
    }
    if(P1->getHeart()>0) P1->Update( road, Obj );
    if(P2->getHeart()>0)P2->Update( road_D, Obj_D );


    return GAME_CONTINUE;
}

void
GameWindow::game_reset(){
    redraw = false;

    once = false;
    page=0;
    final_end=0;
    memset(road, 0, NumOfGrid);
    memset(Obj, 0, NumOfGrid);
    memset(road_D, 0, NumOfGrid);
    memset(Obj_D, 0, NumOfGrid);
    P1->resetAll();
    P2->resetAll();
    P2->ResetPos();
    set_map( P1->stage, 0 );
    set_map( P2->stage, 1 );
    // stop sample instance

    // stop timer
    al_stop_timer(timer);

}

void
GameWindow::game_destroy(){
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);

    al_destroy_timer(timer);
    al_destroy_bitmap(icon);
}

int
GameWindow::process_event(){
    if(state == STATE_TITLE) return process_title_event();
    if(state == STATE_START) return process_start_event();
    if(state == STATE_STORY) return process_story_event();
    if(state == STATE_SETTING) return process_set_event();
}

int
GameWindow::process_set_event(){
    int i;
    int instruction = GAME_CONTINUE;
    static bool first=false;

    al_wait_for_event(event_queue, &event);
    redraw = false;

    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer)
            redraw = true;
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                state_change(STATE_TITLE);
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
        if(event.mouse.button == 1) {
            page++;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
    }

    if(redraw) {
        // Re-draw map
        draw_set_map();
        redraw = false;
    }

    return instruction;
}

int
GameWindow::process_title_event(){
    int i;
    int instruction = GAME_CONTINUE;
    static bool first=false;

    al_wait_for_event(event_queue, &event);
    redraw = false;

    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer)
            redraw = true;
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                return GAME_EXIT;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
        if(event.mouse.button == 1) {
            if(mouse_hover(window_width/2-64, window_height/2+2, 128, 20)){
                if(!first) state_change(STATE_STORY), first=true;
                else state_change(STATE_START);
            }
            else if(mouse_hover(window_width/2-64, window_height/2+22, 128, 20))
                state_change(STATE_SETTING);
            else if(mouse_hover(window_width/2-64, window_height/2+42, 128, 20))
                return GAME_EXIT;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
    }

    if(redraw) {
        // Re-draw map
        draw_title_map();
        redraw = false;
    }

    return instruction;
}

int
GameWindow::process_start_event(){
    int i;
    int instruction = GAME_CONTINUE;

    al_wait_for_event(event_queue, &event);
    redraw = false;

    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer)
            redraw = true;
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if(final_end!=0 && final_end!=TRUE_END) state_change(STATE_TITLE);
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                state_change(STATE_TITLE);
                break;
            case ALLEGRO_KEY_ENTER:
                if(P1->talk_on) P1->talkPlus();
                if(P1->choose && P1->Yes && !P1->black) P1->eat();
                else if(P1->choose && !P1->Yes && !P1->black) P1->choose=false, P1->_eat=false;
                break;
            case ALLEGRO_KEY_F:
                if(P2->talk_on) P2->talkPlus();
                if(P2->choose && P2->Yes && !P2->black) P2->eat();
                else if(P2->choose && !P2->Yes && !P2->black) P2->choose=false, P2->_eat=false;
                break;
            case ALLEGRO_KEY_UP:
                if(P1->choose) P1->Yes = !P1->Yes;
                else P1->setUp(true, road);
                break;
            case ALLEGRO_KEY_DOWN:
                if(P1->choose) P1->Yes = !P1->Yes;
                break;
            case ALLEGRO_KEY_RIGHT:
                P1->setRight(true);
                break;
            case ALLEGRO_KEY_LEFT:
                P1->setLeft(true);
                break;
            case ALLEGRO_KEY_W:
                if(P2->choose) P2->Yes = !P2->Yes;
                else P2->setUp(true, road);
                break;
            case ALLEGRO_KEY_S:
                if(P2->choose) P2->Yes = !P2->Yes;
                break;
            case ALLEGRO_KEY_D:
                P2->setRight(true);
                break;
            case ALLEGRO_KEY_A:
                P2->setLeft(true);
                break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP) {
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                P1->setUp(false, road);
                break;
            case ALLEGRO_KEY_RIGHT:
                P1->setRight(false);
                break;
            case ALLEGRO_KEY_LEFT:
                P1->setLeft(false);
                break;
            case ALLEGRO_KEY_W:
                P2->setUp(false, road);
                break;
            case ALLEGRO_KEY_D:
                P2->setRight(false);
                break;
            case ALLEGRO_KEY_A:
                P2->setLeft(false);
                break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
        if(event.mouse.button == 1) {
            if(final_end!=0 && final_end!=TRUE_END) state_change(STATE_TITLE);
            if(mouse_hover(window_width/2-40, 40, 80, 80)){
                if(P1->choose && P1->Yes && !P1->black) P1->eat();
                else if(P1->choose && !P1->Yes && !P1->black) P1->choose=false, P1->_eat=false;
            }
            if(mouse_hover(window_width/2-40, 40+field_height, 80, 80)){
                if(P2->choose && P2->Yes && !P2->black) P2->eat();
                else if(P2->choose && !P2->Yes && !P2->black) P2->choose=false, P2->_eat=false;
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
        if(mouse_hover(window_width/2-40, 40, 80, 40)){
            P1->Yes = true;
        }
        else if(mouse_hover(window_width/2-40, 80, 80, 40)) P1->Yes = false;
        if(mouse_hover(window_width/2-40, 40+field_height, 80, 40)){
            P2->Yes = true;
        }
        else if(mouse_hover(window_width/2-40, 80+field_height, 80, 40)) P2->Yes = false;
    }

    if(redraw) {
        instruction = game_update();
        // Re-draw map
        draw_start_map();
        redraw = false;
    }

    return instruction;
}

int
GameWindow::process_story_event(){
    int i;
    int instruction = GAME_CONTINUE;

    al_wait_for_event(event_queue, &event);
    redraw = false;

    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer)
            redraw = true;
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                state_change(STATE_TITLE);
                break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
        if(event.mouse.button == 1) {
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
    }

    if(redraw) {
        // Re-draw map
        draw_story_map();
        redraw = false;
    }

    return instruction;
}

void
GameWindow::draw_title_map(){

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(Title, 0, 0, 0);
    if(mouse_hover(window_width/2-64, window_height/2+2, 128, 20))
        al_draw_rectangle(window_width/2-64, window_height/2+2, window_width/2+64, window_height/2+22, al_map_rgb(255, 255, 255), 3);
    if(mouse_hover(window_width/2-64, window_height/2+22, 128, 20))
        al_draw_rectangle(window_width/2-64, window_height/2+22, window_width/2+64, window_height/2+42, al_map_rgb(255, 255, 255), 3);
    if(mouse_hover(window_width/2-64, window_height/2+42, 128, 20))
        al_draw_rectangle(window_width/2-64, window_height/2+42, window_width/2+64, window_height/2+62, al_map_rgb(255, 255, 255), 3);
    al_draw_text(font, al_map_rgb(255,255,255), window_width/2, window_height/2, ALLEGRO_ALIGN_CENTER, "Game start");
    al_draw_text(font, al_map_rgb(255,255,255), window_width/2, window_height/2+20, ALLEGRO_ALIGN_CENTER, "Introduction");
    al_draw_text(font, al_map_rgb(255,255,255), window_width/2, window_height/2+40, ALLEGRO_ALIGN_CENTER, "EXIT");


    al_flip_display();
}

void
GameWindow::draw_set_map(){

    al_clear_to_color(al_map_rgb(0, 0, 0));
    if(page==11) page=0;
    al_draw_bitmap(intro[page], 0, 0, 0);

    al_flip_display();
}

void
GameWindow::draw_story_map(){
    static int y = 800;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(story, 0, y, 0);
    if(y == -1200) state = STATE_START;
    else y-=1;


    al_flip_display();
}

void
GameWindow::draw_start_map(){
    static int TEY=0;
    if(final_end!=0){
        al_clear_to_color(al_map_rgb(0, 0, 0));
        if(!once){
            once=true;
            al_stop_sample(ID);
            al_play_sample(Sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, ID);
        }

        if(final_end==GAMEOVER)
            al_draw_bitmap(gameover, 0, 0, 0);
        else if(final_end==BAD_END){
            al_draw_bitmap(BE, 0, 0, 0);
        }
        else if(final_end==HAPPY_END){
            al_draw_bitmap(HE, 0, 0, 0);
        }
        else if(final_end==TRUE_END){
            al_draw_bitmap(TE, 0, TEY+800, 0);

            if(P1->black)al_draw_textf(Large_font, al_map_rgb(255, 255, 255), 40, 2096+TEY+800-12, ALLEGRO_ALIGN_LEFT, "%s", P1->name);
            else if(P2->black)al_draw_textf(Large_font, al_map_rgb(255, 255, 255), 40, 2096+TEY+800-12, ALLEGRO_ALIGN_LEFT, "%s", P2->name);

            if(TEY==-3000) state_change(STATE_TITLE), TEY=0;
            else TEY--;
        }
        al_flip_display();
        return;
    }


    static int cal_1=0, cal_2=0;
    al_clear_to_color(al_map_rgb(255, 255, 255));

    if(P1->black)al_draw_bitmap(back_d, 0, 0, 0);
    else al_draw_bitmap(back_u, 0, 0, 0);


    if(P2->black) al_draw_bitmap(back_d, 0, field_height, 0);
    else al_draw_bitmap(back_u, 0, field_height, 0);

    if(P2->stage==6)al_draw_bitmap(back_up, P2->window_pos, field_height, 0);

    al_draw_filled_rectangle(0, window_height/2-2, window_width, window_height/2+2, al_map_rgb(0, 0, 0));

    DrawMap(P1->window_pos, P2->window_pos);
    for(std::list<Object*>::iterator it = ObjectSet.begin(); it != ObjectSet.end(); it++)
        (*it)->Draw(P1->window_pos);
    for(std::list<Object*>::iterator it = ObjectSet_D.begin(); it != ObjectSet_D.end(); it++)
        (*it)->Draw(P2->window_pos);

    P1->Draw();
    P2->Draw();
    if(P2->stage==6)al_draw_bitmap(back_down, P2->window_pos, field_height, 0);


    al_draw_textf(Medium_font, al_map_rgb(0, 0, 0), 0, 0, ALLEGRO_ALIGN_LEFT, "%s", P1->name);
    al_draw_textf(Medium_font, al_map_rgb(0, 0, 0), 0, field_height, ALLEGRO_ALIGN_LEFT, "%s", P2->name);
    for(int i=0; i<P1->getHeart(); i++){
        if(P1->black) al_draw_bitmap(Bheart, i*30, 40, 0);
        else al_draw_bitmap(heart, i*30, 40, 0);
    }
    for(int i=0; i<P2->getHeart(); i++){
        if(P2->black) al_draw_bitmap(Bheart, i*30, field_height+40, 0);
        else al_draw_bitmap(heart, i*30, field_height+40, 0);
    }

    if(P1->getHeart()<=0){
        al_draw_filled_rectangle(0, 0, 1000, 400, al_map_rgb(0, 0, 0));
        al_draw_text(Large_font, al_map_rgb(255, 255, 255), window_width/2, 100, ALLEGRO_ALIGN_CENTER, "GAME OVER");
    }
    if(P2->getHeart()<=0){
        al_draw_filled_rectangle(0, field_height, 1000, field_height+400, al_map_rgb(0, 0, 0));
        al_draw_text(Large_font, al_map_rgb(255, 255, 255), window_width/2, 100+field_height, ALLEGRO_ALIGN_CENTER, "GAME OVER");
    }


    if(P1->change)al_draw_filled_rectangle(0, 0, 1000, 400, al_map_rgb(0, 0, 0));
    if(P2->change) al_draw_filled_rectangle(0, field_height, 1000, field_height+400, al_map_rgb(0, 0, 0));

    if(P1->nowt){
        if(cal_1==40) cal_1=0, P1->nowt=false;
        else cal_1++, al_draw_filled_rectangle(0, 0, 1000, 400, al_map_rgb(255, 0, 0));
    }
    if(P2->nowt){
        if(cal_2==40) cal_2=0, P2->nowt=false;
        else cal_2++, al_draw_filled_rectangle(0, 0+field_height, 1000, 400+field_height, al_map_rgb(255, 0, 0));
    }
    if(P1->choose){
        al_draw_filled_rectangle(window_width/2-40, 40, window_width/2+40, 120, al_map_rgb(255, 255, 255));
        al_draw_filled_rectangle(window_width/2-40, 40+40*!P1->Yes, window_width/2+40, 80+40*!P1->Yes, al_map_rgb(0, 0, 0));
        al_draw_rectangle(window_width/2-40, 40, window_width/2+40, 120, al_map_rgb(0, 0, 0), 4);
        if(!P1->Yes){
            al_draw_text(font, al_map_rgb(0, 0, 0), window_width/2-35, 40, ALLEGRO_ALIGN_LEFT, "Yes");
            al_draw_text(font, al_map_rgb(255, 255, 255), window_width/2-35, 80, ALLEGRO_ALIGN_LEFT, "No");
        }
        else{
            al_draw_text(font, al_map_rgb(255, 255, 255), window_width/2-35, 40, ALLEGRO_ALIGN_LEFT, "Yes");
            al_draw_text(font, al_map_rgb(0, 0, 0), window_width/2-35, 80, ALLEGRO_ALIGN_LEFT, "No");
        }
    }

    if(P2->choose){
        al_draw_filled_rectangle(window_width/2-40, 40+field_height, window_width/2+40, 120+field_height, al_map_rgb(255, 255, 255));
        al_draw_filled_rectangle(window_width/2-40, 40+40*!P2->Yes+field_height, window_width/2+40, 80+40*!P2->Yes+field_height, al_map_rgb(0, 0, 0));
        al_draw_rectangle(window_width/2-40, 40+field_height, window_width/2+40, 120+field_height, al_map_rgb(0, 0, 0), 4);
        if(!P2->Yes){
            al_draw_text(font, al_map_rgb(0, 0, 0), window_width/2-35, 40+field_height, ALLEGRO_ALIGN_LEFT, "Yes");
            al_draw_text(font, al_map_rgb(255, 255, 255), window_width/2-35, 80+field_height, ALLEGRO_ALIGN_LEFT, "No");
        }
        else{
            al_draw_text(font, al_map_rgb(255, 255, 255), window_width/2-35, 40+field_height, ALLEGRO_ALIGN_LEFT, "Yes");
            al_draw_text(font, al_map_rgb(0, 0, 0), window_width/2-35, 80+field_height, ALLEGRO_ALIGN_LEFT, "No");
        }
    }

    al_flip_display();
}

void
GameWindow::state_change(int _state){
    game_reset();
    state = _state;
    game_begin();
}
