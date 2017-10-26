#include "Pokitto.h"
#include "gfx.h"

Pokitto::Core game;

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
    while (game.isRunning()) {

        double SIN = sin(-angle);
        double COS = cos(-angle);
        signed char ux,uy;

        for(int y=0; y<88; y++){
            for(int x=0; x<110; x++){

                ux=(x-55) * COS - (y-44) * SIN;
                uy=(x-55) * SIN + (y-44) * COS;
                if(ux>-55 && ux <55 && uy >-44 && uy <44){
                    char col = rawData[(ux+55)+112*(87-(uy+44))];
                    game.display.drawPixel(x,y,col);
                }
            }
        }

        angle+=(0.0174533*2.5);
        if(angle>6.2657347)angle=0;
        game.display.update();
  }
    return 1;
}
