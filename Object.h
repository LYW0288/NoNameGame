#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "global.h"
#include "Bear.h"

class Object {
public:
    Object(int _x, int _y, bool _num){
        x = _x;
        y = _y+_num*field_height;
        num = _num;
    }
    ~Object() {}

    // pure function for drawing object
    virtual void Draw( int window_pos ){
        al_draw_bitmap(img, window_pos+x, y, 0);
    }
    virtual void IsMatch(Bear*) = 0;
    virtual void Event() = 0;

    int getPos() { return (x/40)*10+(y/40); }
    int getX() { return x; }
    int getY() { return y; }
    bool event =false;
    bool Out(){
        if(y<window_height) return true;
        else return false;
    }


protected:
    int x;
    int y;
    bool num = 0;
    bool broken = 0;
    ALLEGRO_BITMAP *img;
};

#endif // OBJECT_H_INCLUDED

