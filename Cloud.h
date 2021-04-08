#ifndef CLOUD_H_INCLUDED
#define CLOUD_H_INCLUDED

#include "Object.h"
#define WIDTH 80
#define HEIGHT 40


class Cloud : public Object{
public:
    Cloud(int _x, int _y, bool _num) : Object(_x, _y, _num){
        img = al_load_bitmap("./Object/Cloud.png");
    }
    void IsMatch(Bear *P1){
        if( P1->getX()>=P1->window_pos+x+WIDTH || P1->getX()+BEAR_WIDTH<=P1->window_pos+x ){
            if(ON[P1->num]) P1->Match = false, ON[P1->num]=false;
            if( !(P1->getY() >y+HEIGHT || P1->getY() + BEAR_HEIGHT <= y) ){
                if(P1->getX()==P1->window_pos+x+WIDTH) P1->LR=-1, L_R[P1->num]=true;
                else if(P1->getX()+BEAR_WIDTH==P1->window_pos+x) P1->LR=1, L_R[P1->num]=true;
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
            if(P1->getY() + P1->getV() + BEAR_HEIGHT < y+HEIGHT/4){
                P1->Match = true;
                ON[P1->num] = true;
            }
            else if(ON[P1->num]) P1->Match = false, ON[P1->num]=false;
            P1->SetV( -P1->getV()/2 );
        }
        else if( P1->getY() + P1->getV() <= y+HEIGHT && P1->getY() + P1->getV() > y ){
            P1->SetV( -P1->getV()/2 );
            P1->setU();
            if(L_R[P1->num])P1->LR=0, L_R[P1->num]=false;
        }
    }
    void Event(){}

protected:
    bool L_R[2] = {false};
    bool ON[2] = {false};
};


#endif


