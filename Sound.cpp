#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "Sound.h"
#include "sounds.h"
#include "sounds/sounds.h"
#include "../inc/DAC5.h"
#include "../inc/Timer.h"

const uint8_t *soundPt = 0;
uint32_t soundCount = 0;
uint32_t period = 0;

void SysTick_IntArm(uint32_t period, uint32_t priority) {
    SysTick->CTRL = 0x00;
    SysTick->LOAD = period - 1;
    SysTick->VAL = 0;
    SCB->SHP[1] = (SCB->SHP[1] & (~0xC0000000)) | (priority << 30);
    SysTick->CTRL = 0x07;
}

// initialize a 11kHz SysTick, however no sound should be started
// initialize any global variables
// Initialize the 5 bit DAC
void Sound_Init(void) {
    DAC5_Init();
    soundPt = 0;
    soundCount = 0;
    period = 80000000 / 11000;
    SysTick->CTRL = 0;
}

extern "C" void SysTick_Handler(void);

void SysTick_Handler(void) {
    if (soundCount > 0) {
        DAC5_Out(*soundPt);
        soundPt++;
        soundCount--;
    } else {
        SysTick->CTRL = 0;
        soundPt = 0;
    }
}

//******* Sound_Start ************
// This function does not output to the DAC. 
// Rather, it sets a pointer and counter, and then enables the SysTick interrupt.
// It starts the sound, and the SysTick ISR does the output
// feel free to change the parameters
// Sound should play once and stop
// Input: pt is a pointer to an array of DAC outputs
//        count is the length of the array
// Output: none
// special cases: as you wish to implement
void Sound_Start(const uint8_t *pt, uint32_t count) {
    if (pt == 0 || count == 0) return;
    soundPt = pt;
    soundCount = count;
    SysTick_IntArm(period, 0);
}

void Sound_Shoot(void) {
    Sound_Start(Shoot, sizeof(Shoot));
}

void Sound_Win(void) {
    // Sound_Start(marioKartWinSound, sizeof(marioKartWinSound));
}
