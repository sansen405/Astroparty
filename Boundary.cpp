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
#include "Boundary.h"

boundary::boundary(int x, int y, int len, int wid){
    this->x = x;
    this->y = y;
    this->len = len;
    this->wid = wid;
}

bool boundary::draw(){
    ST7735_FillRect(x, y, len, wid, ST7735_ORANGE);
    return true;
}