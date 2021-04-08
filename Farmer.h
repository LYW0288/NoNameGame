#ifndef FARMER_H_INCLUDED
#define FARMER_H_INCLUDED

#include "Object.h"
#include "Human.h"


class Farmer : public Human{
public:
    Farmer(int _x, int _y, bool _num) : Human(_x, _y, _num){
        width=24;
        height=52;
        char buffer[50];
        strcpy(name, "Farmer");
        img = al_load_bitmap("./Bear/Farmer.png");
        mov = al_load_bitmap("./Title/TALK.png");
        for(int i=0; i<4; i++){
            sprintf(buffer, "./Talk/farmer/TALK_%d.png", i);
            talk[i] = al_load_bitmap(buffer);
        }
    }
protected:
};


#endif






