#ifndef JOHAN_H_INCLUDED
#define JOHAN_H_INCLUDED

#include "Object.h"
#include "Human.h"


class Johan : public Human{
public:
    Johan(int _x, int _y, bool _num) : Human(_x, _y, _num){
        width=24;
        height=52;
        char buffer[50];
        strcpy(name, "Johan");
        img = al_load_bitmap("./Bear/John.png");
        mov = al_load_bitmap("./Title/TALK.png");
        for(int i=0; i<4; i++){
            sprintf(buffer, "./Talk/johan/TALK_%d.png", i);
            talk[i] = al_load_bitmap(buffer);
        }
    }
protected:
};


#endif



