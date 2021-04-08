#ifndef SMOOTHPERSON_H_INCLUDED
#define SMOOTHPERSON_H_INCLUDED

#include "Object.h"
#include "Human.h"


class SmoothPerson : public Human{
public:
    SmoothPerson(int _x, int _y, bool _num) : Human(_x, _y, _num){
        width=24;
        height=52;
        char buffer[50];
        strcpy(name, "SmoothPerson");
        img = al_load_bitmap("./Bear/SmoothPerson.png");
        mov = al_load_bitmap("./Title/TALK.png");
        for(int i=0; i<4; i++){
            sprintf(buffer, "./Talk/smoothperson/TALK_%d.png", i);
            talk[i] = al_load_bitmap(buffer);
        }
    }
protected:
};


#endif




