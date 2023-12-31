/**
 * @brief Library to interface STM32fxx MCUs with 1602A LCD Peripheral.
 * @author Sunday Clement
 * @date Jun 19th 2023
 **/ 

#ifndef H_LCD
#define H_LCD

#include "stm32f4xx_hal.h"


#define RS_PIN GPIO_PIN_7
#define RS_PIN_PORT GPIOE
#define RW_PIN GPIO_PIN_8
#define RW_PIN_PORT GPIOE
#define ENABLE_SIG_PIN GPIO_PIN_9
#define ENABLE_SIG_PORT GPIOE
#define DB0_PIN GPIO_PIN_14
#define DB0_PORT GPIOE
#define DB1_PIN GPIO_PIN_15
#define DB1_PORT GPIOE
#define DB2_PIN GPIO_PIN_13
#define DB2_PORT GPIOB
#define DB3_PIN GPIO_PIN_14
#define DB3_PORT GPIOB
#define DB4_PIN GPIO_PIN_10
#define DB4_PORT GPIOE
#define DB5_PIN GPIO_PIN_11
#define DB5_PORT GPIOE
#define DB6_PIN GPIO_PIN_12
#define DB6_PORT GPIOE
#define DB7_PIN GPIO_PIN_13
#define DB7_PORT GPIOE

#define BITMODE_8BIT 1u
#define BITMODE_4BIT 0u

extern uint32_t screenMode;//make accessible in other files

void quickInitLCD();
void InitLCD(uint32_t);

void send_To_LCD4BIT(int);
void send_To_LCD8BIT(int);
void sendInstruction(int);
void sendData(int);

void printstr(char*);

void clearDisplay();
void returnCursor();
void cursorRight();
void cursorLeft();
void setCursor(uint32_t, uint32_t);
void displayShift();
void setDisplayParams(int,int,int);
void customChar();


void ToggleInputType();
void setInputType(GPIO_PinState);

void ToggleRWmode();
void setReadWriteMode(GPIO_PinState);

void ToggleES();
void setEnableSignal(GPIO_PinState);



#endif