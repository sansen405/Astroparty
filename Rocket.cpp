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
#include "images.h"
#include "Rocket.h"







rocket :: rocket(int x,int y,int imgInd) {
        posX = x;
        posY = y;
        vX = 0;
        vY = 0;
        aX = 0;
        aY = 0;
        if(imgInd == 1 || imgInd == 3 || imgInd == 5 || imgInd == 7){
            dimX = 21;
            dimY = 21;
        }
        if(imgInd == 0 || imgInd == 4){
            dimX = 16;
            dimY = 21;
        }
        else{
            dimY = 21;
            dimX = 16;
        }


        imageIndex = imgInd;
        image = rotationsBlue[imgInd];
        direction = 0;
    }


#define TIP_OFFSET 15  // how far from center to tip (adjust to fit rocket sprite)

int rocket::getX() {
    return posX + dimX/2;
}

int rocket::getY() {
    return posY - dimY/2;  // minus because screen Y grows downward
}


int rocket::getVX() {
    return vX; // center of the rocket horizontally
}

int rocket::getVY() {
    return vY; // just above the rocket (tip of the nose)
}

bool isNearlyWhite(unsigned short color) {
    // Extract RGB components from custom RGB565 format (BGR565)
    unsigned char blue  = (color >> 11) & 0x1F;  // bits 15–11
    unsigned char green = (color >> 5)  & 0x3F;  // bits 10–5
    unsigned char red   = color         & 0x1F;  // bits 4–0

    // Thresholds close to max values (31 for R/B, 63 for G)
    const unsigned char RED_THRESH = 29;
    const unsigned char GREEN_THRESH = 58;
    const unsigned char BLUE_THRESH = 29;

    return (red >= RED_THRESH) && (green >= GREEN_THRESH) && (blue >= BLUE_THRESH);
}




    // if button is pressed call rotate 
void rocket::rotate(){
    // Circular velocity steps (unit circle * 3 for speed)
    // int rotateX[16] = {
    //      0,  1,  2,  3,  3,  3,  2,  1,
    //      0, -1, -2, -3, -3, -3, -2, -1
    // };

    // int rotateY[16] = {
    //     -3, -3, -2, -1,  0,  1,  2,  3,
    //      3,  3,  2,  1,  0, -1, -2, -3
    // };
    int rotateX[16] = {
     0,  -1,  -2,  -2,  -2,  -2,  -2,  -1,
     0, 1, 2, 2, 2, 2, 2, 1
    };

    int rotateY[16] = {
        2, 2, 2, 1,  0,  -1,  -2,  -2,
        -2,  -2,  -2,  -1,  0, 1, 2, 2
    };

    for (int row = 0; row < 23; row++) {
        for (int col = 0; col < 23; col++) {
            ST7735_DrawPixel(posX + col, posY - row, Astrobackground[(posY - row) * 128 + (posX + col)]);
         }
    }

    imageIndex++;
    if(imageIndex == 4){
        imageIndex = 0;
    }
     Clock_Delay1ms(1000);

    image = rotationsBlue[imageIndex];
    if(imageIndex == 1 || imageIndex == 3 || imageIndex == 5 || imageIndex == 7){
       dimX = 21;
        dimY = 21;
    }   
    if(imageIndex == 0 || imageIndex == 4){
        dimX = 16;
        dimY = 21;
    }
    else{
        dimY = 21;
        dimX = 16;
    }


    // keeps track of rotation index
    //direction = (direction + 1) % 16; // rotate clockwise

    vX = rotateX[imageIndex*4];
    vY = rotateY[imageIndex*4];
}

// void rocket:: rotateInverse() {
// int rotateX[16] = {
//      0,  -1,  -2,  -2,  -2,  -2,  -2,  -1,
//      0, 1, 2, 2, 2, 2, 2, 1
// };

// int rotateY[16] = {
//     2, 2, 2, 1,  0,  -1,  -2,  -2,
//      -2,  -2,  -2,  -1,  0, 1, 2, 2
// };


//     // keeps track of rotation index
//     direction = (direction  + 1) % 16; // rotate clockwise

//     vX = -rotateX[direction];
//     vY = -rotateY[direction];
// }  
void rocket::rotateInverse() {
    int rotateX[16] = {
        0,  -1,  -2,  -2,  -2,  -2,  -2,  -1,
        0, 1, 2, 2, 2, 2, 2, 1
    };

    int rotateY[16] = {
        2, 2, 2, 1,  0,  -1,  -2,  -2,
       -2,  -2,  -2,  -1,  0, 1, 2, 2
    };

    direction = (direction +1) % 16;

    vX = -rotateX[direction];
    vY = -rotateY[direction];
}



void rocket:: startMoving (int velX, int velY) {
        vY = velY;
        vX = velX;
    }
    // setting
void rocket:: setVelocity(int velocityX, int velocityY) {
        this->vX = velocityX;
        this->vY = velocityY;
    }

bool rocket::hitByBullet(bullet bull){
    int bullX = bull
}



void rocket:: draw() {
        // ST7735_FillRect(posX, posY, dimX, dimY, ST7735_CYAN);// makes so it doesnt drag
        // Clear previous sprite from screen using correct Y-offset
// ST7735_FillRect(posX, posY - dimY + 1, dimX, dimY, ST7735_CYAN);

    // sets position and keeps it within bounds
        if(posX+vX<=(127-15) && posX+vX>=0) {
            posX+=vX;
         }
        if (posY+vY <=159 && posY+vY>=(0+24)) {
            posY+=vY;
         }


//        ST7735_DrawTransperantBitmap(posX, posY, BlueRocket_15x24, 15, 24, 0xFFFF);
//       ST7735_DrawBitmap(posX, posY,BlueRocket_15x24, 15, 24);
         int spriteColorIndex = 0;
         for (int row = 0; row < dimY; row++) {
             for (int col = 0; col < dimX; col++) {
                 int currPixelColor = image[spriteColorIndex];
                 spriteColorIndex++;

                 if (currPixelColor > 0xD1000) {

                     ST7735_DrawPixel(posX + col, posY - row, Astrobackground[(posY - row) * 128 + (posX + col)]); // gets right index of background to show
                 }
             else {
                 ST7735_DrawPixel(posX + col, posY - row, currPixelColor);
             }
         }
     }
}