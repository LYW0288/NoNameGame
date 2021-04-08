#ifndef BASHA_H_INCLUDED
#define BASHA_H_INCLUDED

#include "Object.h"
#include "Human.h"


class Basha : public Human{
public:
    Basha(int _x, int _y, bool _num) : Human(_x, _y, _num){
        width=40;
        height=68;
        char buffer[50];
        strcpy(name, "Basha");
        img = al_load_bitmap("./Bear/Basha.png");
        mov = al_load_bitmap("./Title/TALK.png");
        for(int i=0; i<4; i++){
            sprintf(buffer, "./Talk/basha/TALK_%d.png", i);
            talk[i] = al_load_bitmap(buffer);
        }
    }
protected:
};


#endif




