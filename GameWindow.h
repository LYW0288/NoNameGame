#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include "memory.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <list>
#include <time.h>
#include "global.h"
#include "Brick.h"
#include "Cloud.h"
#include "Cloud_fake.h"
#include "Thorn.h"
#include "Object.h"
#include "Bear.h"
#include "Hans.h"
#include "Human.h"
#include "Johan.h"
#include "Shata.h"
#include "Basha.h"
#include "Otto.h"
#include "Memory.h"
#include "Otis.h"
#include "Rodd.h"
#include "Mary.h"
#include "Farmer.h"
#include "Satina.h"
#include "SmoothPerson.h"

#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7
#define GAME_WIN 8

#define STATE_TITLE 0
#define STATE_START 1
#define STATE_STORY 2
#define STATE_SETTING 3


using namespace std;
// clock rate
const float FPS = 60;


class GameWindow
{
public:
    // constructor
    GameWindow();

    bool mouse_hover(int, int, int, int);
    void set_map(int stage, bool num);
    void DrawMap( int, int );

    Object *create_object(int, int, bool);
    // each process of scene
    void game_init();
    void game_reset();
    void game_play();
    void game_begin();

    int game_run();
    int game_update();

    void show_err_msg(int msg);
    void game_destroy();

    //state
    void set_state_title();
    void set_state_start();
    void set_state_story();
    void set_state_set();


    // draw running game map
    void draw_title_map();
    void draw_start_map();
    void draw_story_map();
    void draw_set_map();

    void state_change(int);

    // process of updated event
    int IsGoing(Bear *);

    int process_event();
    int process_title_event();
    int process_start_event();
    int process_story_event();
    int process_set_event();

public:
    bool initial = true;

private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *heart, *Bheart;
    ALLEGRO_BITMAP *brick;
    ALLEGRO_BITMAP *story;
    ALLEGRO_BITMAP *BE, *HE, *TE;
    ALLEGRO_BITMAP *gameover;
    ALLEGRO_BITMAP *Title;
    ALLEGRO_BITMAP *back_u, *back_d;
    ALLEGRO_BITMAP *back_up, *back_down;
    ALLEGRO_BITMAP *intro[11];

    ALLEGRO_DISPLAY* display = NULL;

    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *Medium_font = NULL;
    ALLEGRO_FONT *Large_font = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;

    ALLEGRO_SAMPLE_ID *ID = (ALLEGRO_SAMPLE_ID *)malloc(sizeof(ALLEGRO_SAMPLE_ID));
    //start
    ALLEGRO_SAMPLE *Sound = NULL;
    ALLEGRO_SAMPLE *Piano_song = NULL;
    ALLEGRO_SAMPLE *Title_song = NULL;


    int final_end=0;
    int state = STATE_TITLE;
    int mouse_x, mouse_y;
    int page=0;

    float volume = 1.0;

    Bear *P1, *P2;
    std::list<Object*> ObjectSet;
    std::list<Object*> ObjectSet_D;
    bool once = false;
    bool road[NumOfGrid] = {false};
    bool road_D[NumOfGrid] = {false};
    bool Obj[NumOfGrid] = {false};
    bool Obj_D[NumOfGrid] = {false};
    bool first=false;
    bool redraw = false;
};


#endif // MAINWINDOW_H_INCLUDED
