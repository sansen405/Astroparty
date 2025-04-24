// Lab9HMain.cpp
// Runs on MSPM0G3507
// Lab 9 ECE319H
// Your name
// Last Modified: 12/26/2024

#include <cstddef>
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
#include "bullet.h"
#include "images.h"
#include "sounds.h"

void clearShip(rocket* r);
//#include "UART.h"
// ships as global declerations
  rocket* ship2; // player 2
  rocket* ship1;
  bullet* bulletP1 = nullptr;
  bullet* bulletP2 = nullptr;

  int flag = 0;
extern "C" void __disable_irq(void);
extern "C" void __enable_irq(void);
extern "C" void TIMG12_IRQHandler(void);
// ****note to ECE319K students****
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

uint32_t M=1;
uint32_t Random32(void){
  M = 1664525*M+1013904223;
  return M;
}
uint32_t Random(uint32_t n){
  return (Random32()>>16)%n;
}

SlidePot Sensor(1500,0); // copy calibration from Lab 7

// games  engine runs at 30Hz
void TIMG12_IRQHandler(void){uint32_t pos,msg;
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
// game engine goes here
    // 1) sample slide pot
    // 2) read input switches
    // read input from switches ()
    flag = 1;
      int turn = GPIOB->DIN31_0 & 0x1; // gets value to turn
    // 3) move sprites
      if (turn) {
        ship1->rotateInverse();
      }

      // logic for UART 


      ship2->rotateInverse();

      // logic for ship2 shoot


      int shoot = GPIOB->DIN31_0 & 0x2;
      if (shoot) {
        if (bulletP1 == nullptr) {
            bulletP1 = new bullet(*ship1); // Copy rocket state
        }
      }
    // 4) start sounds
    // 5) set semaphore
    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}
uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

typedef enum {English, Spanish, Portuguese, French} Language_t;
Language_t myLanguage=English;
typedef enum {HELLO, GOODBYE, LANGUAGE} phrase_t;
const char Hello_English[] ="Hello";
const char Hello_Spanish[] ="\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] ="All\x83";
const char Goodbye_English[]="Goodbye";
const char Goodbye_Spanish[]="Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[]="English";
const char Language_Spanish[]="Espa\xA4ol";
const char Language_Portuguese[]="Portugu\x88s";
const char Language_French[]="Fran\x87" "ais";
const char *Phrases[3][4]={
  {Hello_English,Hello_Spanish,Hello_Portuguese,Hello_French},
  {Goodbye_English,Goodbye_Spanish,Goodbye_Portuguese,Goodbye_French},
  {Language_English,Language_Spanish,Language_Portuguese,Language_French}
};
// use main1 to observe special characters
int main1(void){ // main1
    char l;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
  ST7735_FillScreen(0x0000);            // set screen to black
  for(int myPhrase=0; myPhrase<= 2; myPhrase++){
    for(int myL=0; myL<= 3; myL++){
         ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
         ST7735_OutString((char *)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000);       // set screen to black
  l = 128;
  while(1){
    Clock_Delay1ms(2000);
    for(int j=0; j < 3; j++){
      for(int i=0;i<16;i++){
        ST7735_SetCursor(7*j+0,i);
        ST7735_OutUDec(l);
        ST7735_OutChar(' ');
        ST7735_OutChar(' ');
        ST7735_SetCursor(7*j+4,i);
        ST7735_OutChar(l);
        l++;
      }
    }
  }
}
// use main2 to observe graphics
int main2(void){ // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_DrawBitmap(0,159,BlueRocket_15x24,15,24);


  // for(uint32_t t=500;t>0;t=t-5){
  //   SmallFont_OutVertical(t,104,6); // top left
  //   Clock_Delay1ms(50);              // delay 50 msec
  // }
  // ST7735_FillScreen(0x0000);   // set screen to black
  // ST7735_SetCursor(1, 1);
  // ST7735_OutString((char *)"GAME OVER");
  // ST7735_SetCursor(1, 2);
  // ST7735_OutString((char *)"Nice try,");
  // ST7735_SetCursor(1, 3);
  // ST7735_OutString((char *)"Earthling!");
  // ST7735_SetCursor(2, 4);
  // ST7735_OutUDec(1234);
  while(1){
  }
}

// use main3 to test switches and LEDs
int main3(void){ // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  while(1){
    // write code to test switches and LEDs

  }
}
// use main4 to test sound outputs
int main(void){ uint32_t last=0,now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(ADC0,6,0); // ADC1 channel 6 is PB20, TExaS scope
  __enable_irq();
  while(1){
    Sound_Shoot();
    // modify this to test all your sounds
  }
}
// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
int main5(void) { // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
  ST7735_FillScreen(ST7735_BLACK);
  Sensor.Init(); // PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(0, 0, &TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
  TimerG12_IntArm(80000000 / 30, 0); // 30 Hz game engine
  __enable_irq();

  int score1 = 0;
  int score2 = 0;

  // START OF GAME - 3 ROUNDS
  for (int i = 0; i < 3; i++) {
    ST7735_DrawBitmap(0, 159, Astrobackground, 128, 160);

    // Reinitialize ships
    ship1 = new rocket(0, 159, 0);
    ship2 = new rocket(127 - 16, 22, 0); // player 2
    ship1->startMoving(2, 2);

    flag = 0; // reset flag before round
    if (bulletP1 != nullptr) {
      delete bulletP1;
      bulletP1 = nullptr;
    }

    if (bulletP2 != nullptr) {
      delete bulletP2;
      bulletP2 = nullptr;
    }

    bool roundOver = false;

    while (!roundOver) {
      if (flag) {
        flag = 0;


//ship 2 hit by ship 1 bullet
        if (bulletP1 != nullptr && ship2 != nullptr) {
          if (bulletP1->hitShip(ship2)) {

            // for (int row = 0; row < 21; row++) {
            //   for (int col = 0; col < 21; col++) {
            //       ST7735_DrawPixel(ship2->getX() + col, ship2->getY() - row,
            //       Astrobackground[(ship2->getY() - row) * 128 + (ship2->getX() + col)]);
            //   }
            // } 
            clearShip(ship1);
            ship1->draw();

            delete ship2;
            ship2 = nullptr;

            delete bulletP1;
            bulletP1 = nullptr;

            score1++;
            roundOver = true;
            break;
          }
        }


//ship 1 hit by ship 2 bullet
        else if (bulletP2 != nullptr && ship1 != nullptr) {
          if (bulletP2->hitShip(ship1)) {
            // for (int row = 0; row < 21; row++) {
            //   for (int col = 0; col < 21; col++) {
            //       ST7735_DrawPixel(ship1->getX() + col, ship1->getY() - row,
            //       Astrobackground[(ship1->getY() - row) * 128 + (ship1->getX() + col)]);
            //   }
            // } 
            clearShip(ship1);
            ship2->draw();

            delete ship1;
            ship1 = nullptr;

            delete bulletP2;
            bulletP2 = nullptr;

            score1++;
            roundOver = true;
            break;
          }
        }

//draw ships in new location after movement
        if (ship2 != nullptr) {
          ship2->draw();
        }
        if (ship1 != nullptr) {
          ship1->draw();
        }


//bullet on edge or boundary
        if (bulletP1 != nullptr) {
          if (!bulletP1->draw()) {
            delete bulletP1;
            bulletP1 = nullptr;
          }
        }

        if (bulletP2 != nullptr) {
          if (!bulletP2->draw()) {
            delete bulletP2;
            bulletP2 = nullptr;
          }
        }
      }
    }

//Delay and cleanup before next round
    Clock_Delay1ms(2000);
    ST7735_FillScreen(ST7735_BLACK);
  }
}

void clearShip(rocket* r){
    for (int row = 0; row < 21; row++) {
      for (int col = 0; col < 21; col++) {
          ST7735_DrawPixel(ship2->getX() + col, ship2->getY() - row,
          Astrobackground[(ship2->getY() - row) * 128 + (ship2->getX() + col)]);          
      }
    } 
}




