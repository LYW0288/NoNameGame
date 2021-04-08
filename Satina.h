#ifndef SATINA_H_INCLUDED
#define SATINA_H_INCLUDED

#include "Object.h"
#include "Human.h"


class Satina : public Human{
public:
    Satina(int _x, int _y, bool _num) : Human(_x, _y, _num){
        width=56;
        height=104;
        char buffer[50];
        strcpy(name, "Satina");
        img = al_load_bitmap("./Bear/Satina.png");
        mov = al_load_bitmap("./Title/TALK.png");
        for(int i=0; i<4; i++){
            sprintf(buffer, "./Talk/satina/TALK_%d.png", i);
            talk[i] = al_load_bitmap(buffer);
        }
    }
protected:
};


#endif



