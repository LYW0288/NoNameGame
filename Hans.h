#ifndef HANS_H_INCLUDED
#define HANS_H_INCLUDED

#include "Object.h"
#include "Human.h"


class Hans : public Human{
public:
    Hans(int _x, int _y, bool _num) : Human(_x, _y, _num){
        char buffer[50];
        strcpy(name, "Hans");
        img = al_load_bitmap("./Bear/Hans.png");
        mov = al_load_bitmap("./Title/TALK.png");
        for(int i=0; i<4; i++){
            sprintf(buffer, "./Talk/hans/TALK_%d.png", i);
            talk[i] = al_load_bitmap(buffer);
        }
        width=44;
        height=56;
    }
protected:
};


#endif


