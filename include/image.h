#ifndef IMAGE_H
#define IMAGE_H

/** Methods to Image file. */

/**
 * Calculates the size in bits of the given image.
 * For this, the width and height of the image must be
 * known, finally obtaining the size of the image.
 * The size of the image in bits will correspond to its
 * width times its height times 24 (since we know that each
 * pixel stores 24 bits because it has 3 channels).
 * @param image_filename The name of the image to determine its size.
 * @return The size of the image (in bits).
 */
unsigned long calculate_image_size_in_bits(const char* image_filename);

/**
 * Determine if an image has enough space to store text with the LSB steganography technique.
 * It only compares the bit size of the image with the bit size of the message.
 * @param image_filename The name of the image given to hide the message.
 * @param message_length_in_bits The size in bits of the message.
 */
int has_sufficient_space(const char* image_filename, int message_length_in_bits);

#endif
