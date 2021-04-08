#ifndef OTIS_H_INCLUDED
#define OTIS_H_INCLUDED

#include "Object.h"
#include "Human.h"


class Otis : public Human{
public:
    Otis(int _x, int _y, bool _num) : Human(_x, _y, _num){
        width=44;
        height=76;
        char buffer[50];
        strcpy(name, "Otis");
        img = al_load_bitmap("./Bear/Otis.png");
        mov = al_load_bitmap("./Title/TALK.png");
        for(int i=0; i<4; i++){
            sprintf(buffer, "./Talk/otis/TALK_%d.png", i);
            talk[i] = al_load_bitmap(buffer);
        }
    }
protected:
};


#endif





