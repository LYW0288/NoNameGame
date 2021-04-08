#include "Bear.h"

void
Bear::Draw(){
    if(dead) al_draw_bitmap(img[3+4*direction], x, y, 0);
    else if( step<=10 )al_draw_bitmap(img[0+4*direction], x, y, 0);
    else if( step<=20 )al_draw_bitmap(img[1+4*direction], x, y, 0);
    else if( step<=30 )al_draw_bitmap(img[0+4*direction], x, y, 0);
    else if( step<=40 )al_draw_bitmap(img[2+4*direction], x, y, 0);
    al_draw_bitmap(after[direction], x, y, 0);
    if( !(left && right) && (left || right) ){
        if(left) direction = false;
        else direction = true;
        if(step==40) step=0;
        else step++;
    }
    else step = 0;
}

void
Bear::setUp( bool i, bool*road ){
    up = i;
}

void
Bear::Search( bool* road, bool* L, bool* R, bool* U ){
    int _v = (v>=40)?39:v;

    int pos_l = ((-window_pos+x)/40)*10+(-num*field_height+y+BEAR_HEIGHT+_v)/40;
    int pos_m = ((-window_pos+x+BEAR_WIDTH/2)/40)*10+(-num*field_height+y+BEAR_HEIGHT+_v)/40;
    int pos_r = ((-window_pos+x+BEAR_WIDTH-1)/40)*10+(-num*field_height+y+BEAR_HEIGHT+_v)/40;

    int pos_up_l = ((-window_pos+x)/40)*10+(-num*field_height+y+v)/40;
    int pos_up_m = ((-window_pos+x+BEAR_WIDTH/2)/40)*10+(-num*field_height+y+v)/40;
    int pos_up_r = ((-window_pos+x+BEAR_WIDTH-1)/40)*10+(-num*field_height+y+v)/40;

    int pos_run_lu = ((-window_pos+x-speed)/40)*10+(-num*field_height+y)/40;
    int pos_run_ld = ((-window_pos+x-speed)/40)*10+(-num*field_height+y+BEAR_HEIGHT-1)/40;
    int pos_run_ru = ((-window_pos+x+BEAR_WIDTH+speed)/40)*10+(-num*field_height+y)/40;
    int pos_run_rd = ((-window_pos+x+BEAR_WIDTH+speed)/40)*10+(-num*field_height+y+BEAR_HEIGHT-1)/40;

    if( (road[pos_l] || road[pos_m] || road[pos_r]) && pos_m%10!=0 && !(*U)) v=0, y=(pos_l%10)*40-BEAR_HEIGHT+num*field_height;
    else v++;
    if(!up) *U = up;
    else{
        int pos_l_U = ((-window_pos+x)/40)*10+(-num*field_height+y+BEAR_HEIGHT)/40;
        int pos_m_U = ((-window_pos+x+BEAR_WIDTH/2)/40)*10+(-num*field_height+y+BEAR_HEIGHT)/40;
        int pos_r_U = ((-window_pos+x+BEAR_WIDTH-1)/40)*10+(-num*field_height+y+BEAR_HEIGHT)/40;
        if(road[pos_l_U] || road[pos_m_U] || road[pos_r_U] || Match) *U = up;
    }


    if(y+v-num*field_height+BEAR_HEIGHT>=field_height){
        v=0, heart--, dead=true;
        return;
    }
    if(x==0 || road[pos_run_ld] || road[pos_run_lu] || pos_run_rd<0 || LR==-1) *L = false;
    if(x+BEAR_WIDTH==window_width || road[pos_run_ru] || road[pos_run_rd] || pos_run_rd>=NumOfGrid || LR==1) *R = false;

    if( y+v-num*field_height<0 ) *U = false, v=0, y=num*field_height;
    else if( road[pos_up_l] || road[pos_up_m] || road[pos_up_r]) *U = false, v=0, y=(pos_up_l%10)*40+40 +num*field_height;
    else if(*U && v>jump_speed) v-=4;
    else if(*U && v<=jump_speed) *U = false;
}

void
Bear::reborn(bool *road, bool *Obj){
    if(num){
        int D_pos = ((getPos()+10)/10)*10;
        for(int i=2, j=0; ; i++){
            if(road[D_pos+i-j*10]) {
                if(Obj[D_pos+i-j*10-1] || road[D_pos+i-j*10-1] || road[D_pos+i-j*10-2] ) j--;
                else{
                    al_play_sample(death, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    if(((D_pos+i-j*10)/10)*40+window_pos>800 && ((D_pos+i-j*10)/10)*40-800<1000 ) window_pos += 800-(((D_pos+i-j*10)/10)*40+window_pos);
                    x=window_pos+((D_pos+i-j*10)/10)*40, y= field_height + ((D_pos+i-j*10)%10)*40-BEAR_HEIGHT;
                    up=false;
                    break;
                }
            }
            if(i==9) j--, i=1;
        }
    }
    else{
        int U_pos = ((getPos()-10)/10)*10;
        for(int i=2, j=0; ; i++){
            if(road[U_pos+i-j*10]) {
                if(Obj[U_pos+i-j*10-1] || road[U_pos+i-j*10-1] || road[U_pos+i-j*10-2] ) j++;
                else{
                    al_play_sample(death, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    if(((U_pos+i-j*10)/10)*40+window_pos<200 && ((U_pos+i-j*10)/10)*40-200>0) window_pos += 200-(((U_pos+i-j*10)/10)*40+window_pos);
                    x=window_pos+((U_pos+i-j*10)/10)*40, y=((U_pos+i-j*10)%10)*40-BEAR_HEIGHT;
                    up=false;
                    break;
                }
            }
            if(i==9) j++, i=1;
        }
    }
}

void
Bear::eat(){
    if(!black){
        char buffer[50];
        strcpy(name, restore);
        sprintf(buffer, "./Bear/%s_L.png", name);
        after[0] = al_load_bitmap(buffer);
        sprintf(buffer, "./Bear/%s_R.png", name);
        after[1] = al_load_bitmap(buffer);
    }
    if(time==3) black=true;
    else time++;
    heart++;
    choose = false;
    _eat=true;
    nowt=true;
    al_play_sample(chew, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void
Bear::resetAll(){

    window_pos = 0;
    LR = 0;
    time=1;
    dead=false;
    Match = false;
    num = 0;
    strcpy(name, "Monster");
    black = false;
    talk_on = false;
    plus_ = false;
    choose = false, Yes=true;
    change=false;
    _eat=false;
    nowt=false;
    stage = 1;
    left = false;
    right = false;
    up = false;
    U = false;
    direction = true;
    End = 0;
    start=false;
    v = 0;
    x = -40;
    y = 360-BEAR_HEIGHT;
    after[0] = al_load_bitmap("./Bear/NULL.png");
    after[1] = al_load_bitmap("./Bear/NULL.png");
    speed = 4;
    heart = 10;
    jump_speed = -20;
    jumpping = 0;
    step =0;
}

void
Bear::talkPlus(){
    plus_=true;
}


void
Bear::Update( bool* road, bool* Obj ){
    if(window_pos==-1400 && x>880 && !num && y==360-BEAR_HEIGHT && stage==6){

        if(x<1000) x++, right=true;
        else{
            right=false, left=false, End=1;
        }
    }
    else if(window_pos==-1400 && x>880 && !num && y==360-BEAR_HEIGHT && stage!=6){
        if(x<1000) x++, right=true;
        else  right=false, stage++, change=true, left=false;
    }
    else if(window_pos==0 && x<120 && num && y==240-BEAR_HEIGHT+field_height && stage==6){

        if(x+BEAR_WIDTH>0) x--, left=true;
        else{
            left=false, right=false, End=1;
        }
    }
    else if(window_pos==0 && x<120 && num && y==360-BEAR_HEIGHT+field_height && stage!=6){
        if(x+BEAR_WIDTH>0) x--, left=true;
        else left=false, stage++, change=true, right=false;
    }
    else if(!start && num){
        if(x>960)
            x--, left=true;
        else if(x==960)
            left=false, start=true;
    }
    else if(!start && !num){
        if(x+BEAR_WIDTH<40)
            x++, right=true;
        else if(BEAR_WIDTH+x==40)
            right=false, start=true;
    }
    else if(dead){
        if(jumpping<20) y-=8, jumpping++;
        else if(jumpping<40) jumpping++;
        else jumpping=0, dead=false, reborn(road, Obj);
    }
    else{
        bool L=left, R=right;
        Search( road, &L, &R, &U );
        if(choose) L=false, R=false, U=false;
        y += v;
        if(x==800 && window_pos != -field_width+window_width && R) window_pos-=speed;
        else if(R) x+=speed;
        if(x==200 && window_pos != 0 && L) window_pos+=speed;
        else if(L) x-=speed;
    }
}
