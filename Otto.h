#ifndef OTTO_H_INCLUDED
#define OTTO_H_INCLUDED

#include "Object.h"
#include "Human.h"


class Otto : public Human{
public:
    Otto(int _x, int _y, bool _num) : Human(_x, _y, _num){
        width=52;
        height=52;
        char buffer[50];
        strcpy(name, "Otto");
        img = al_load_bitmap("./Bear/Otto.png");
        mov = al_load_bitmap("./Title/TALK.png");
        for(int i=0; i<4; i++){
            sprintf(buffer, "./Talk/otto/TALK_%d.png", i);
            talk[i] = al_load_bitmap(buffer);
        }
    }
protected:
};


#endif



