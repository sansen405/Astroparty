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
#include "Rocket.h"
#include "Bullet.h"

bullet::bullet(rocket r) {
        posX = r.getX();
        posY = r.getY();
        vX = 2*r.getVX();
        vY = 2*r.getVY();
        dimX = 5;
        dimY = 5;
        counter = 0;
    }
    // if button is pressed call rotate 


bool bullet::draw() {
    // Clear previous bullet
    bool onScreen = true;
    if(counter > 1){
        ST7735_FillRect(posX, posY - dimY + 1, dimX, dimY, ST7735_CYAN);

        if (posX + vX <= (127 - dimX) && posX + vX >= 0) {
            posX += vX;
        } else {
            onScreen = false;
        }

        if (posY + vY <= 159 && posY + vY >= (0 + dimY)) {
            posY += vY;
        } else {
            onScreen = false;
        }

        // Only draw if still on screen
        if (onScreen) {
            ST7735_FillRect(posX, posY - dimY + 1, dimX, dimY, ST7735_ORANGE);
        }
    }
    else{
        if (posX + vX <= (127 - dimX) && posX + vX >= 0) {
            posX += vX;
        } 
        if (posY + vY <= 159 && posY + vY >= (0 + dimY)) {
            posY += vY;
        }
    }
    counter++;
    return onScreen;
}



