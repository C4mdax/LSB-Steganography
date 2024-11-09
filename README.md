# HiddenInk

HiddenInk is a C based program that allows you to hide messages inside image archives and recover those text messages
for later use.

## Features
- A way to easily hide any text message inside an image archive without any visible changes in the archive
- When needed, a fast way to extract

## How do we hide this messages?

HiddenInk uses the LSB technique, that means Least Significant Bit technique, which basically means that we first calculate
the available pixels that composes the image were we're going to hide the message and then replace the least significant
bit of each channel that composes a single pixel of the image with the desired value to hide  


## Installation

### Prerequisites
To use this program you'll only need to install libpng, SDL1 and SDL2, libpng is an official PNG reference library
that supports great numbers of operations to a PNG archive that are used in this program and both SDLs are used for
similar purposes as well. To install, you simply write down on your terminal

```bash
sudo apt-get install libpng-dev libsdl1.2-dev libsdl2-dev
```

### Steps
In order to install the program, check in your terminal that you are in the directory were you want to install it and then
follow these steps

1. Clone the repository:
    ```bash
    git clone https://github.com/your_username/HiddenInk.git
    ```
2. Navigate to the project directory:
    ```bash
    cd HiddenInk/src
    ```
3. Compile the program
    ```bash
    gcc main.c utils.c image.c hider.c revealer.c -o HiddenInk `sdl2-config --cflags --libs` -lSDL2_image -lpng
    ```

## Using the program
Now after installing you're ready to go!

```bash
./HiddenInk -h ~/route/of/the/text ~/route/of/the/image ~/route/of/the/image/destiny
```

For extracting the hidden message, you can use execute

```bash
./HiddenInk -u ~/route/of/the/image/with/hidden/text ~/route/of/the/message/destiny
```

### Supported Image Archives
The program only supports PNG archive files

### Some considerations
One important aspect that you need to considerate before trying to hide a message is that the image has the adequate
size in order to hide the message because the amount of bits needed could exceed the amount of bits available from
the image. You can check if you have enough bits by multiplying 3 or 4 times (Depends if its RGB or RGBA) the amount of
pixels (Long X Short)
It's possible to extract a message from an image non processed from this program, but if the text was hidden with a
different process it's almost sure that the extraction will not be possible

## License Agreement
This work is licensed under Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0).

It is free for personal or commercial use with attribution required by mentioning the use of this work as follows:

> This site or product includes IP2Location™ ISO 3166-2 Subdivision Code which is available from [IP2Location](https://www.ip2location.com).

## Contributors
- **Luis Angel Moreno Delgado**
- **Edgar Salgado González**

## Contact
For any questions or suggestions, you can contact us at this mail **c4mdax@gmail.com**
