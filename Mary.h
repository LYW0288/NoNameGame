#ifndef MARY_H_INCLUDED
#define MARY_H_INCLUDED

#include "Object.h"
#include "Human.h"


class Mary : public Human{
public:
    void Draw( int window_pos ) override {
        al_draw_bitmap(Sheep, window_pos+x, y-height, 0);
        if(!broken) al_draw_bitmap(img, window_pos+x, y-height, 0);
        if(next>0 && next<4) al_draw_bitmap(talk[next], window_pos+x-WIDTH, y-140-height, 0);
        else if(next==4) choose = true, next++;
        if(match && !broken){
            if(num)al_draw_text(font, al_map_rgb(255, 255, 255), x+window_pos-70+width/2, y+10, ALLEGRO_ALIGN_LEFT, "PRESS F");
            else al_draw_text(font, al_map_rgb(255, 255, 255), x+window_pos-70+width/2, y+10, ALLEGRO_ALIGN_LEFT, "ENTER");
        }
    }
    Mary(int _x, int _y, bool _num) : Human(_x, _y, _num){
        width=76;
        height=48;
        char buffer[50];
        strcpy(name, "Mary");
        img = al_load_bitmap("./Bear/Mary.png");
        mov = al_load_bitmap("./Title/TALK.png");
        Sheep = al_load_bitmap("./Bear/Sheep.png");
        for(int i=0; i<4; i++){
            sprintf(buffer, "./Talk/mary/TALK_%d.png", i);
            talk[i] = al_load_bitmap(buffer);
        }
    }
protected:
    ALLEGRO_BITMAP *Sheep;
};


#endif





