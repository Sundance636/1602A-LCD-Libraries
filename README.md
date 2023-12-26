# 1602A-LCD-Libraries
Library with simple functions written to interface 1602A LCDs with compatible Microcontroller Units.

## Getting Started

Either download then extract the folder corresponding to your Microcontroller Unit in use or clone the repository  and move the files into your project workspace folder, and the library will be available once you include the Lcd header file.

Cloning the repository:
```
git clone https://github.com/Sundance636/1602A-LCD-Libraries.git
```

### Prerequisites

Using STM32 based boards:
+ STM32CubeIDE
+ stlink

Using ESP8622:
+ [PlatformIO](https://platformio.org/)

## Installing

### Linux

Using your package manager of choice install the required STM32 packages
#### Arch Linux

```
yay -S stlink && yay -S stm32cubeide
```
<p></p>

**Installing PlatormIO Extentsion on Visual Studio Code:**

With Visual Studio Code open, press (CTRL+SHIFT+X) to open the extentions tab and search for and install "PlatformIO IDE ".

## Examples
STM32 'Hello World'

ESP8266 'Hello World'

## Resources

For 1602A LCD:
<p> <a href="https://www.openhacks.com/uploadsproductos/eone-1602a1.pdf"> Specification For LCD Module </a> </p>
<p> <a href="https://web.alfredstate.edu/faculty/weimandn/lcd/lcd_initialization/lcd_initialization_index.html"> Screen Initialization Process </a></p>
