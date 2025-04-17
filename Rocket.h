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

public:

    int getX();  // Declaration of getX
    int getY();  // Declaration of getY
    int getVX(); // Declaration of getVX
    int getVY(); // Declaration of getVY
    rocket(int x, int y);
    void rotate();
    void startMoving(int velX, int velY);
    void setVelocity(int velocityX, int velocityY);
    void draw();

    
};

#endif // ROCKET_H
