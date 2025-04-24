// UART.h
// Header file for UART2 initialization
// Configures UART2 for 2375 baud rate, receive interrupt only

#ifndef ASTROUART_H_
#define ASTROUART_H_

#include <ti/devices/msp/msp.h>
#include <stdint.h>
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
#include "images.h"

// Function Prototypes
void ASTROUART_Init(void);

void ASTROUART_Out(uint8_t data);
void DONOTHING1();
void DONOTHING2();
void DONOTHING3();
void DONOTHING4();
uint8_t INPUT_ASTROUART(void);

#endif // ASTROUART_H_
