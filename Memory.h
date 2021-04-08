#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include "Object.h"
#include "Human.h"


class Memory : public Human{
public:
    void Draw( int window_pos ) override {
        al_draw_bitmap(Piano, window_pos+x, y-height, 0);
        if(!broken) al_draw_bitmap(img, window_pos+x, y-height, 0);
        if(next>0 && next<4) al_draw_bitmap(talk[next], window_pos+x, y-140-height, 0);
        else if(next==4) choose = true, next++;
        if(match && !broken){
            if(num)al_draw_text(font, al_map_rgb(255, 255, 255), x+window_pos-70+width/2, y+10, ALLEGRO_ALIGN_LEFT, "PRESS F");
            else al_draw_text(font, al_map_rgb(255, 255, 255), x+window_pos-70+width/2, y+10, ALLEGRO_ALIGN_LEFT, "ENTER");
        }
    }
    Memory(int _x, int _y, bool _num) : Human(_x, _y, _num){
        width=80;
        height=64;
        char buffer[50];
        strcpy(name, "Memory");
        img = al_load_bitmap("./Bear/Memory.png");
        mov = al_load_bitmap("./Title/TALK.png");
        Piano = al_load_bitmap("./Bear/Piano.png");
        for(int i=0; i<4; i++){
            sprintf(buffer, "./Talk/memory/TALK_%d.png", i);
            talk[i] = al_load_bitmap(buffer);
        }
    }
protected:
    ALLEGRO_BITMAP *Piano;
};


#endif




