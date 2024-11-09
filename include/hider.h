#ifndef HIDER_H
#define HIDER_H

/** Methods to Hider file. */

/**
 * @brief Hides the text contained in the text file within a given PNG image, and saves the PNG image with the hidden message.
 * @param text_filename The name of the file that contains the text to hide.
 * @param image_filename The name of the image file.
 * @param image_destiny_name The name of the resulting image file with the hidden data.
 */
void hide_text_in_image(const char* text_filename, const char* image_filename, const char* image_destiny_name);

/**
 * @brief Gets the length of the message to hide in its binary form (the number of bits).
 * @param filename The name of the file that contains the text to hide.
 * @return unsigned long The number of bits in the binary form of the message.
 */
unsigned long get_message_length_in_bits(const char* filename);

#endif
