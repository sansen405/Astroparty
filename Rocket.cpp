#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/SlidePot.h"
#include "../inc/DAC5.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "images/images.h"

class Rocket{
    private:
        int dimX;
        int dimY;
        int posX;
        int posY;
        int vX;
        int vY;
        int direction;

    public:
        rocket(int posX, int posY){
            posX = posX;
            posY = posY;
            dimX = 15;
            dimY = 24;
            vX = 0;
            vY = 0;
            dir = 0; //represents index in rocket costumes array for rotate
        }

        void setVelocity(int vX, int vY){
            this->vX = vX;
            this->vY = vY;
        }

        void rotate(){
            //iterate through array of rocket costumes for rotation
            //change velocity in x and y
        }

        int getVelocityX_FromDir(int dir){

        }

        int getVelocityY_FromDir(int dir){
            
        }
}



