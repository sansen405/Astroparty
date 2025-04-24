#include "Bullet.h"
#include <stdint.h>
#ifndef ROCKET_H
#define ROCKET_H
class rocket {
private:
    int posX;
    int posY;
    int dimX;
    int dimY;
    int vX;
    int vY;
    int aX;
    int aY;
    int direction; // index for sprite rotation
    int imageIndex;
    uint16_t* image;

public:

    int getX();  // Declaration of getX
    int getY();  // Declaration of getY
    int getMiddleX(); 
    int getMiddleY();
    int getVX(); // Declaration of getVX
    int getVY(); // Declaration of getVY
    rocket(int x, int y, int imageIndex);
    void rotate();
    void rotateInverse();
    void startMoving(int velX, int velY);
    void boundCheck();
    void setVelocity(int velocityX, int velocityY);
    void draw();
};
// array's 
extern const unsigned short BlueRocket_15x24[];



#endif // ROCKET_H
