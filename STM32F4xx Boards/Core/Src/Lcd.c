#include "../Inc/Lcd.h"

uint32_t screenMode = 0;

/**
 * @brief Initializes the LCD to 4bit mode/2 lines/and 5x8 font size
 *        also turns display on, and cursor on.
 * @retval none
*/
void quickInitLCD() {
    HAL_Delay(200);//power on init time
    //setEnableSig(GPIO_PIN_SET);//set enable signal
    setInputType(GPIO_PIN_RESET);//set to instruction mode
    setReadWriteMode(GPIO_PIN_RESET);//set to write

    sendInstruction( 0x30 );
    HAL_Delay(4);
    sendInstruction( 0x30 );
    HAL_Delay(4);
    sendInstruction( 0x30 );
    HAL_Delay(4);


    //now in 4bit mode
    sendInstruction( 0x20 );
    HAL_Delay(4);

    //disp settings
    sendInstruction( 0x28 );
    HAL_Delay(4);

    //disp on
    sendInstruction( 0x08 );
    HAL_Delay(4);

    //clear display
    sendInstruction( 0x01 );
    HAL_Delay(4);
    //entry mode
    sendInstruction( 0x06 );
    HAL_Delay(4);

    //Setting LCD to 4-bit mode
    //sendInstruction(0x28);

    //Display parameters of LCD
    sendInstruction(0x0F);

    return;
}

/**
 * @brief Initializes the LCD to either 4-bit mode or 8-bit mode /2 lines / and 5x8 font size
 *        also turns the display on, cursor and cursor blink on.
 * @param BITMODE  if BITMODE is set to 0 then the LCD is initialized in 4-bit mode
 *                 else if it is set to 1 then the LCD is initialized in 8-bit mode
 * @retval none
*/
void InitLCD(uint32_t BITMODE) {
    if( BITMODE > BITMODE_8BIT ) return;//only allows for 1 or 0 as function args

    screenMode = BITMODE; 

    HAL_Delay(400);//power on init time
    //setEnableSig(GPIO_PIN_SET);//set enable signal
    setInputType(GPIO_PIN_RESET);//set to instruction mode
    setReadWriteMode(GPIO_PIN_RESET);//set to write

    sendInstruction( 0x30 );
    HAL_Delay(4);
    sendInstruction( 0x30 );
    HAL_Delay(4);
    sendInstruction( 0x30 );
    HAL_Delay(4);

    if(screenMode == BITMODE_8BIT) {
        //disp settings
        sendInstruction( 0x38 );
        HAL_Delay(4);
    }
    else {
        //now in 4bit mode
        sendInstruction( 0x20 );
        HAL_Delay(4);
        //disp settings
        sendInstruction( 0x28 );
        HAL_Delay(4);
    }

    //disp on
    sendInstruction( 0x08 );
    HAL_Delay(4);

    //clear display
    sendInstruction( 0x01 );
    HAL_Delay(4);
    //entry mode
    sendInstruction( 0x06 );
    HAL_Delay(4);

    //Setting LCD to 4-bit mode
    //sendInstruction(0x28);

    //Display parameters of LCD
    sendInstruction(0x0F);

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
 * @brief Sends All 8 bits to each corresponding line on the databus
 * @param data the instruction/data being sent to the LCD, all 8
 *             bits are taken of inputted integer.
 * @retval none
*/
void send_To_LCD8BIT(int data) {
    int bits[8] = {0};

    for(int i = 0; i < 8; i++) {
        bits[i] = (data >> i) & 1;
    }
    
    
    HAL_GPIO_WritePin(DB7_PORT, DB7_PIN, bits[7]);
    HAL_GPIO_WritePin(DB6_PORT, DB6_PIN, bits[6]);
    HAL_GPIO_WritePin(DB5_PORT, DB5_PIN, bits[5]);
    HAL_GPIO_WritePin(DB4_PORT, DB4_PIN, bits[4]);
    HAL_GPIO_WritePin(DB3_PORT, DB3_PIN, bits[3]);
    HAL_GPIO_WritePin(DB2_PORT, DB2_PIN, bits[2]);
    HAL_GPIO_WritePin(DB1_PORT, DB1_PIN, bits[1]);
    HAL_GPIO_WritePin(DB0_PORT, DB0_PIN, bits[0]);

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

    if(screenMode == BITMODE_4BIT) {
        send_To_LCD4BIT(ins>>4);//upper 4 bits
        send_To_LCD4BIT(ins);//lower 4 bits
    }
    else {
        send_To_LCD8BIT(ins);
    }
    
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

    if(screenMode == BITMODE_4BIT) {
        send_To_LCD4BIT(data>>4);//upper 4 bits
        send_To_LCD4BIT(data);//lower 4 bits
    }
    else {
        send_To_LCD8BIT(data);
    }

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
 * @brief Returns the cursor to the top left of the LCD screen
 * @retval none
*/
void returnCursor() {
    sendInstruction(0x02);
    HAL_Delay(50);

    return;
}

/**
 * @brief makes the cursor Increment to the right, therefore printing right to left
 * @retval none
*/
void cursorRight() {
    sendInstruction(0x06);
    HAL_Delay(50);

    return;
}

/**
 * @brief makes the cursor Increment to the left, therefore printing left to right
 * @retval none
*/
void cursorLeft() {
    sendInstruction(0x04);
    HAL_Delay(50);

    return;
}

/**
 * @brief Sets the cursor position on the LCD screen
 * @param row the index of the row/line you want to select, from 0 to 1
 * @param column the index of the column you want to select, from 0 to 15
 * @retval none
*/
void setCursor(uint32_t row, uint32_t column) {
    returnCursor();//reset cursor position to assume cursor is at 0,0

    for(int j = 0; j < column + (40 * row); j++) {
        sendInstruction(0x14);
    }

    HAL_Delay(50);
    
    return;
}

/**
 * @brief Shifts/Scrolls the entire display left or right by one character depending of specification
 * @param Direction the direction to shift the display, left(0) or right(1 or non zero int).
 * @retval none
*/
void displayShift(uint32_t Direction) {
    if(Direction == 1u) {
        sendInstruction(0x1C);//scroll right
    }
    else {
        sendInstruction(0x18);//scroll left
    }

    return;
}

/**
 * @brief Configures the display parameter, Display, Cursor, and Cursor blink
 * 
 * @param Display Determines whether the display is on or off, with 1 or 0 respectively.
 * @param Cursor sets the cursor On == 1, Off == 0
 * @param Blink sets the cursor blink On == 1, Off == 0
 * 
 * @retval none
*/
void setDisplayParams(int Display, int Cursor, int Blink) {
    uint32_t disp = 0, curs = 0, blnk = 0;

    if(Display == 1) {
        disp = 0x0C;
    }
    if(Cursor == 1) {
        curs = 0x0A;
    }
    if(Blink == 1) {
        blnk = 0x09;
    }


    sendInstruction( 0x08 | disp | curs | blnk );

    return;
}

/**
 * @brief Shifts/Scrolls the entire display left or right by one character depending of specification
 * @param Direction the direction to shift the display, left(0) or right(1 or non zero int).
 * @retval none
*/
void customChar() {


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

