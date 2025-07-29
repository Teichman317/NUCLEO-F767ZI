#ifndef ST7701S_INIT_H
#define ST7701S_INIT_H

#include <stdint.h>

// Core display init entry point
void Display_Init_ST7701S(void);

// Optional low-level interface hooks (override as needed)
void WriteCommand(uint8_t cmd);
void WriteData(uint8_t data);
void Delay_ms(uint32_t ms); // Wrap HAL_Delay or similar

#endif // ST7701S_INIT_H
