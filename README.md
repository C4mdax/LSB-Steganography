# HiddenInk

HiddenInk is a C-based program that allows you to hide messages inside image files and recover those text messages later.

## Features
- Easily hide any text message inside a PNG image without visible changes in the image.
- Quickly extract hidden messages when needed.

## How does it work?

HiddenInk uses the Least Significant Bit (LSB) technique. This technique involves calculating the available pixels in the image where the message will be hidden and then replacing the least significant bit of each color channel of a pixel with bits of the hidden message.

## Installation

### Prerequisites
To use this program, install the following libraries:
- **libpng**: A reference library for PNG files, essential for handling PNG images.
- **SDL1** and **SDL2**: Used for graphics-related operations on images.

#### Installation Commands by Distribution

- **Debian/Ubuntu**:
    ```bash
    sudo apt-get install libsdl2-dev libsdl2-image-dev libpng-dev
    ```

- **Arch Linux**:
    ```bash
    sudo pacman -S sdl2 sdl2_image libpng
    ```

- **Gentoo**:
    ```bash
    sudo emerge media-libs/libsdl2 media-libs/sdl2-image media-libs/libpng
    ```

### Steps to Install
1. Clone the repository:
    ```bash
    git clone https://github.com/C4mdax/HiddenInk.git
    ```
2. Navigate to the project directory:
    ```bash
    cd HiddenInk/src
    ```
3. Compile the program:
    ```bash
    gcc main.c utils.c image.c hider.c revealer.c -o HiddenInk `sdl2-config --cflags --libs` -lSDL2_image -lpng
    ```

## Using HiddenInk
Once installed, you can start using HiddenInk as follows:

- **To hide a message**:
    ```bash
    ./HiddenInk -h <path/to/text> <path/to/image> <path/or/name/to/output/image>
    ```

- **To extract a hidden message**:
    ```bash
    ./HiddenInk -u <path/to/image/with/hidden/message> <path/or/name/to/output/message>
    ```

### Supported Image Format
HiddenInk currently supports PNG image files only.

### Important Considerations
Before hiding a message, ensure that the image has sufficient capacity to store it. The amount of space required depends on the number of pixels and color channels (3 for RGB or 4 for RGBA). The required bits can be calculated by multiplying the number of pixels by 3 or 4, depending on the image type.

Attempting to extract a message from an image modified by a different tool may result in errors.

## License
This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0) license. You are free to use this software for personal or commercial purposes with proper attribution.

> This project includes IP2Location™ ISO 3166-2 Subdivision Code from [IP2Location](https://www.ip2location.com).

## Contributors
- **Luis Angel Moreno Delgado**
- **Edgar Salgado González**

## Contact
For questions or suggestions, contact us at **c4mdax@gmail.com**
