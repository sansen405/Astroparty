#ifndef BULLET_H
#define BULLET_H

#include <stdint.h>
#include "Rocket.h" 
#include "../inc/ST7735.h"

class bullet {
private:
    int posX;
    int posY;
    int vX;
    int vY;
    int dimX;
    int dimY;
    int counter;

public:
    bullet(rocket r);
    void startMoving(rocket r);
    void setVelocity(int velocityX, int velocityY);
    bool draw();
};

#endif