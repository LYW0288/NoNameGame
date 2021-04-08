#ifndef BRICK_H_INCLUDED
#define BRICK_H_INCLUDED

#include "Object.h"
#define WIDTH 40
#define HEIGHT 40


class Brick : public Object{
public:
    Brick(int _x, int _y, bool _num) : Object(_x, _y, _num){
        img = al_load_bitmap("./Object/Brick_broken.png");
    }
    void Draw( int window_pos ) override {
        al_draw_bitmap(img, window_pos*!mov+x, y, 0);
    }
    void IsMatch(Bear *P1){
        if( P1->getX()>=P1->window_pos*!mov+x+WIDTH || P1->getX()+BEAR_WIDTH<=P1->window_pos*!mov+x ){
            if(ON[P1->num]) P1->Match = false, ON[P1->num]=false;
            if( !(P1->getY() >y+HEIGHT || P1->getY() + BEAR_HEIGHT <= y) ){
                if(P1->getX()==P1->window_pos*!mov+x+WIDTH) P1->LR=-1, L_R[P1->num]=true;
                else if(P1->getX()+BEAR_WIDTH==P1->window_pos*!mov+x) P1->LR=1, L_R[P1->num]=true;
                else if(L_R[P1->num])P1->LR=0, L_R[P1->num]=false;
            }
            else if(L_R[P1->num])P1->LR=0, L_R[P1->num]=false;
        }
        else if( P1->getY()+ P1->getV()  >y+HEIGHT || P1->getY()+ P1->getV() + BEAR_HEIGHT < y){
            if(L_R[P1->num])P1->LR=0, L_R[P1->num]=false;
            if(ON[P1->num]) P1->Match = false, ON[P1->num]=false;
        }
        else if( P1->getY() + P1->getV() + BEAR_HEIGHT >= y && P1->getY() + P1->getV() + BEAR_HEIGHT < y+HEIGHT ){
            if(L_R[P1->num])P1->LR=0, L_R[P1->num]=false;
            P1->Match = true;
            ON[P1->num] = true;
            P1->SetYV( y-BEAR_HEIGHT );
            if(stay)stay--;
            else event = true;
        }
        else if( P1->getY() + P1->getV() <= y+HEIGHT && P1->getY() + P1->getV() > y ){
            if(L_R[P1->num])P1->LR=0, L_R[P1->num]=false;
            if(!event) P1->SetYV( y+HEIGHT );
            else P1->TODEAD();
        }
        if(!mov && y>=field_height && !num) x=P1->window_pos+x, mov=true;
    }
    void Event(){
        y+=4;
    }

protected:
    bool L_R[2] = {false};
    bool ON[2] = {false};
    bool mov = false;
    int stay = 10;
};


#endif

