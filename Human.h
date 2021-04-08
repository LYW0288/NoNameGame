#ifndef HUMAN_H_INCLUDED
#define HUMAN_H_INCLUDED

#include "Object.h"


class Human : public Object{
public:
    Human(int _x, int _y, bool _num) : Object(_x, _y, _num){
        font = al_load_font("./Title/misaki_gothic.ttf", 24, 0);
    }
    void Draw( int window_pos ) override {
        if(!broken)al_draw_bitmap(img, window_pos+x, y-height, 0);
        if(next>=0 && next<4) al_draw_bitmap(talk[next], window_pos+x-width+10, y-140-height, 0);
        else if(next==4) choose = true, next++;
        if(match && !broken){
            if(num)al_draw_text(font, al_map_rgb(255, 255, 255), x+window_pos-70+width/2, y+10, ALLEGRO_ALIGN_LEFT, "PRESS F");
            else al_draw_text(font, al_map_rgb(255, 255, 255), x+window_pos-70+width/2, y+10, ALLEGRO_ALIGN_LEFT, "ENTER");
        }
    }
    void IsMatch(Bear *P1){
        if(P1->num!=num) return;
        if( P1->getX()+BEAR_WIDTH<x+P1->window_pos-40 || P1->getX()>x+P1->window_pos+40+width || P1->getY()>y+40 || P1->getY()+BEAR_HEIGHT<y-height-40 ){
            if(match)P1->talk_on = false, match=false;
        }
        else
            P1->talk_on = true, match=true;


        if(P1->black && !broken && match){
            broken=true;
            P1->eat();
            return;
        }
        else if (P1->black && broken && match)
            return;

        if(choose) P1->choose=true, choose=false, strcpy(P1->restore, name), event=true;

        if(event && !P1->choose && P1->_eat) broken = true, event=false;
        else if(event && !P1->choose && !P1->_eat) P1->_eat=false, event=false;

        if(P1->plus_ && match) P1->plus_=false, next++;

    }
    void Event(){

    }

protected:
    ALLEGRO_BITMAP *talk[10];
    ALLEGRO_BITMAP *mov;
    bool choose = false;
    bool match = false;
    int next=-1;
    char name[10];
    int width, height;
    ALLEGRO_FONT *font = NULL;
};


#endif


