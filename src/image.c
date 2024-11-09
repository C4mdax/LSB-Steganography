#include "../include/image.h"
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * @file image.c
 * @brief File that contains the image processing methods for the program
 */

/**
 * @brief Calculates the size in bits of the given image.
 * @param image_filename The image file path/name.
 * @return unsigned long The size in bits of the image.
 */
unsigned long calculate_image_size_in_bits(const char* image_filename) {
    SDL_Surface *image = IMG_Load(image_filename);
    if (!image) {
        fprintf(stderr, "Error loading image: %s\n", IMG_GetError());
        return 0;
    }
    /* Getting the number of channels: 1 for grayscale, 3 for RGB, 4 for RGBA */
    int channels = image->format->BytesPerPixel;
    unsigned long size_in_bits = (image->w * image->h) * channels * 8;
    SDL_FreeSurface(image);
    return size_in_bits;
}

/**
 * @brief Check if the image is the right size to hide the message.
 * @param image_filename The image file path/name.
 * @param message_length_in_bits The size of the message in bits
 * @return The boolean integer validity condition. 
 */
int has_sufficient_space(const char* image_filename, int message_length_in_bits) {
    unsigned long image_size_in_bits = calculate_image_size_in_bits(image_filename);
    return image_size_in_bits >= message_length_in_bits; 
}
