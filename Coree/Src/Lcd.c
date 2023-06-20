#include "Lcd.h"

/**
 * @brief Initializes the LCD to 4bit mode/2 lines/and 5x8 font size
 *        also turns display on, and cursor on.
 * @retval none
*/
void initLCD() {
    HAL_Delay(200);//power on init time
    //setEnableSig(GPIO_PIN_SET);//set enable signal
    setInputType(GPIO_PIN_RESET);//set to instruction mode
    setReadWriteMode(GPIO_PIN_RESET);//set to write

    //setting 4 bit mode
    HAL_GPIO_WritePin(DB7_PORT, DB7_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DB6_PORT, DB6_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DB5_PORT, DB5_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DB4_PORT, DB4_PIN, GPIO_PIN_RESET);

    setEnableSignal(GPIO_PIN_SET);
    setEnableSignal(GPIO_PIN_RESET);
 
    HAL_GPIO_WritePin(DB7_PORT, DB7_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DB6_PORT, DB6_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DB5_PORT, DB5_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DB4_PORT, DB4_PIN, GPIO_PIN_RESET);

    setEnableSignal(GPIO_PIN_SET);
    setEnableSignal(GPIO_PIN_RESET);


    //display parameters
    HAL_GPIO_WritePin(DB7_PORT, DB7_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DB6_PORT, DB6_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DB5_PORT, DB5_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DB4_PORT, DB4_PIN, GPIO_PIN_RESET);
    
    setEnableSignal(GPIO_PIN_SET);
    setEnableSignal(GPIO_PIN_RESET);

    HAL_Delay(30);    //lower
    HAL_GPIO_WritePin(DB7_PORT, DB7_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DB6_PORT, DB6_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DB5_PORT, DB5_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DB4_PORT, DB4_PIN, GPIO_PIN_SET);
    
    setEnableSignal(GPIO_PIN_SET);    
    setEnableSignal(GPIO_PIN_RESET);

    return;
}

/**
 * @brief Sends 4bits to each corresponding line on the databus
 * @param data the instruction/data being sent to the LCD, the 4
 *        least significant bits are taken of inputted integer.
 * @retval none
*/
void send_To_LCD4BIT(int data) {
    int bits[4] = {0};

    for(int i = 0; i < 4; i++) {
        bits[i] = (data >> i) & 1;
    }

    HAL_GPIO_WritePin(DB7_PORT, DB7_PIN, bits[3]);
    HAL_GPIO_WritePin(DB6_PORT, DB6_PIN, bits[2]);
    HAL_GPIO_WritePin(DB5_PORT, DB5_PIN, bits[1]);
    HAL_GPIO_WritePin(DB4_PORT, DB4_PIN, bits[0]);

    setEnableSignal(GPIO_PIN_SET);
    setEnableSignal(GPIO_PIN_RESET);

    return;
}

/**
 * @brief This function sends a specified instruction to the LCD
 *        in 4 bit, sending the upper half byte then the lower half byte.
 * @param ins the intstruction being sent to LCD.
 * @retval none
*/
void sendInstruction(int ins) {
    setInputType(GPIO_PIN_RESET);//set to instruction mode

    send_To_LCD4BIT(ins>>4);//upper 4 bits
    send_To_LCD4BIT(ins);//lower 4 bits

    return;
}

/**
 * @brief This function sends data to the LCD in 4 bit
 *        chunks, upper bit then lower bit.
 * @param data The data being sent to LCD
 * @retval none
*/
void sendData(int data) {
    setInputType(GPIO_PIN_SET);//set to data mode

    send_To_LCD4BIT(data>>4);//upper 4 bits
    send_To_LCD4BIT(data);//lower 4 bits

    return;
}

/**
 * @brief Prints the null terminated string given 
 *        as an argument to the screen.
 * @param string The string to be printed to the screen
 * @retval none
*/
void printstr(char* string) {
    int i = 0;
    while(string[i] !='\0') {
        sendData( (int)string[i] );
        HAL_Delay(20);
        i++;
    }
    return;
}

/**
 * @brief Clears the display of the lcd
 *        and returns the cursor to top left of screen
 * @retval none
*/
void clearDisplay() {
    sendInstruction(0X01);//instruction to clear display
    HAL_Delay(50);
    return;
}

/**
 * @brief Switches register select between
 *        Data Input and Instruction Input
 *        1 = Data , 0 = Instructions
 * @retval none
*/
void ToggleInputType() {
    HAL_GPIO_TogglePin(RS_PIN_PORT, RS_PIN);
    return;
}

/**
 * @brief Manually set the Register select
 *        (Use macros: "GPIO_PIN_SET" and "GPIO_PIN_RESET")
 * @param PIN_STATE the state the pin is at (on / off).
 * @retval none
*/
void setInputType(GPIO_PinState PIN_STATE) {
    HAL_GPIO_WritePin(RS_PIN_PORT, RS_PIN, PIN_STATE);
    return;
}

/**
 * @brief Switches between Read and Write
 *        mode from databus
 *        1 = Read , 0 = Write
 * @retval none
*/
void ToggleRWmode() {
    HAL_GPIO_TogglePin(RW_PIN_PORT, RW_PIN);
    return;
}

/**
 * @brief Manually set Read/Write mode
 *        (Use macros: "GPIO_PIN_SET" and "GPIO_PIN_RESET")
 * @param PIN_STATE the state of the pin (on / off)
 * @retval none
*/
void setReadWriteMode(GPIO_PinState PIN_STATE) {
    HAL_GPIO_WritePin(RW_PIN_PORT, RW_PIN, PIN_STATE);
    return;
}

/**
 * @brief Toggles Enable signal Pin
 * @retval none
*/
void ToggleES() {
    HAL_GPIO_TogglePin(ENABLE_SIG_PORT, ENABLE_SIG_PIN);
    return;
}

/**
 * @brief Manually set Enable Signal Pin
 *        (Use macros: "GPIO_PIN_SET" and "GPIO_PIN_RESET")
 * @param PIN_STATE the state to set the pin (on / off)
 * @retval none
*/
void setEnableSignal(GPIO_PinState PIN_STATE) {
    HAL_GPIO_WritePin(ENABLE_SIG_PORT, ENABLE_SIG_PIN, PIN_STATE);
    return;
}
