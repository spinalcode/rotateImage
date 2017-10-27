#include "Pokitto.h"
#include "gfx.h"

Pokitto::Core game;

#define TIMES 256
#define TIMES2 65536


int sine[361];
int cosine[361];


void setup(){
    game.begin();
    game.display.width = 110; // half size
    game.display.height = 88;
    game.setFrameRate(60);
    game.display.setColorDepth(4);
    game.display.load565Palette(sprite_pal);
    game.display.bgcolor = 0;
    game.display.invisiblecolor = -16;
}

int main(){
    setup();
    float angle=0;
    for(int t=0; t<=360; t++){
        sine[t]=sin(angle)*TIMES;
        cosine[t]=cos(angle)*TIMES;
        angle+=(0.0174533); // radians
    }

    int ang=0;
    while (game.isRunning()) {

        int SIN = sine[ang];
        int COS = cosine[ang];
        int ux,uy;

        for(int y=0; y<88; y++){
            for(int x=0; x<110; x++){

                int x1 = (x-55)*TIMES;
                int y1 = (y-44)*TIMES;

//                ux=(x-55) * COS - (y-44) * SIN;
//                uy=(x-55) * SIN + (y-44) * COS;
                ux = (x1 * COS - y1 * SIN) / TIMES2;
                uy = (x1 * SIN + y1 * COS) / TIMES2;

                if(ux>-55 && ux <55 && uy >-44 && uy <44){
                    char col = rawData[(ux+55)+112*(87-(uy+44))];
                    game.display.drawPixel(x,y,col);
                }
            }
        }

//        if(ang++>=359) ang=0;

        ang-=2;
        if(ang<=2) ang=359;
        game.display.update();
  }




    return 1;
}
