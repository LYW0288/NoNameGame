#ifndef BEAR_H_INCLUDED
#define BEAR_H_INCLUDED

#define BEAR_HEIGHT 52
#define BEAR_WIDTH 28

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "global.h"

class Bear {
public:
    Bear() {
        strcpy(name, "Monster");
        chew = al_load_sample("./Music/chew.wav");
        death = al_load_sample("./Music/death.wav");
        after[0] = al_load_bitmap("./Bear/NULL.png");
        after[1] = al_load_bitmap("./Bear/NULL.png");
        }
    ~Bear() {}

    // pure function for drawing object
    void Draw();
    void setImg(char *buffer, int i){ img[i] = al_load_bitmap(buffer); }
    void setRight( bool i ) { right = i; }
    void setLeft( bool i ) { left = i; }
    void setUp( bool, bool* );
    void SetV( int i ){ v = i; };
    void setU() { U=false; }
    void SetYV(int _y){ v=0, y=_y, U=false; }
    void Update( bool*, bool* );
    void Search( bool*, bool*, bool*, bool* );
    void reborn(bool*, bool*);
    void ResetPos(){ x=1000, y=field_height+360-BEAR_HEIGHT, window_pos = -field_width+window_width, num = 1, direction=false, start=false; }
    void reSet_U(){ x=-40, y=360-BEAR_HEIGHT, window_pos = 0, start=false; }
    void resetAll();
    void TODEAD(){ if(!dead) dead=true, heart--; }
    void talkPlus();
    void eat();

    int getPos() { return ((-window_pos+x+num*BEAR_WIDTH)/40)*10+((y - num*field_height) /40); }
    int getY(){ return y; }
    int getX(){ return x; }
    int getV(){ return v; }
    int getSpeed(){ return speed; }
    int getHeart() { return heart; }
    int window_pos = 0;
    int LR = 0;
    bool dead=false;
    bool Match = false;
    bool num = 0;
    char name[50];
    char restore[50];

    bool talk_on = false;
    bool plus_ = false;
    bool choose = false, Yes=true;
    bool change=false;
    bool _eat=false;
    bool nowt=false;
    bool black = false;
    bool End=0;
    int stage = 1;
    ALLEGRO_BITMAP *after[2]={NULL};

protected:
    bool left = false;
    bool right = false;
    bool up = false;
    bool U = false;
    bool direction = true;
    bool start=false;
    int v = 0;
    int x = -40;
    int y = 360-BEAR_HEIGHT;
    int speed = 4;
    int heart = 10;
    int jump_speed = -20;
    int jumpping = 0;
    int step =0;
    int time=1;
    ALLEGRO_SAMPLE *chew = NULL;
    ALLEGRO_SAMPLE *death = NULL;

    ALLEGRO_BITMAP *img[8];
};

#endif


