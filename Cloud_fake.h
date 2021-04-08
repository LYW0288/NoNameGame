#ifndef CFAKE_H_INCLUDED
#define CFAKE_H_INCLUDED

#include "Object.h"
#define WIDTH 80
#define HEIGHT 40


class Cfake : public Object{
public:
    Cfake(int _x, int _y, bool _num) : Object(_x, _y, _num){
        b[0] = al_load_bitmap("./Object/Cloud.png");
        b[1] = al_load_bitmap("./Object/Cloud_broken.png");
        b[2] = al_load_bitmap("./Object/Cloud_broken_2.png");
    }
    void Draw( int window_pos ) override{
        if(now!=3)al_draw_bitmap(b[now], window_pos+x, y, 0);
    }
    void IsMatch(Bear *P1){
        if(event) {
            if(L_R[P1->num])P1->LR=0, L_R[P1->num]=false;
            if(ON[P1->num]) P1->Match = false, ON[P1->num]=false;
        }
        else{
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
                if(stay) event=true;
                else stay--;
            }
            else if( P1->getY() + P1->getV() <= y+HEIGHT && P1->getY() + P1->getV() > y ){
                P1->SetV( -P1->getV()/2 );
                P1->setU();
                if(L_R[P1->num])P1->LR=0, L_R[P1->num]=false;
            }
        }
    }
    void Event(){
        if(step==40 && now<3) now++;
        if(step==40) step=0;
        else step++;
    }

protected:
    int stay=5;
    int step = 0;
    int now = 0;
    ALLEGRO_BITMAP *b[3];
    bool L_R[2] = {false};
    bool ON[2] = {false};
};


#endif



