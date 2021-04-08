#ifndef SHATA_H_INCLUDED
#define SHATA_H_INCLUDED

#include "Object.h"
#include "Human.h"


class Shata : public Human{
public:
    Shata(int _x, int _y, bool _num) : Human(_x, _y, _num){
        width=40;
        height=68;
        char buffer[50];
        strcpy(name, "Shata");
        img = al_load_bitmap("./Bear/Shata.png");
        mov = al_load_bitmap("./Title/TALK.png");
        for(int i=0; i<4; i++){
            sprintf(buffer, "./Talk/shata/TALK_%d.png", i);
            talk[i] = al_load_bitmap(buffer);
        }
    }
protected:
};


#endif



