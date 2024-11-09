#ifndef UTILS_H
#define UTILS_H

/** Methods to Utils file. */

/**
 * @brief Verifies that the file given as a parameter exists.
 * @param filename The file path/name.
 * @return The entire Boolean condition of existence.
 */
int file_exists(const char* filename);

/**
 * @brief Verify that the image given as a parameter has a valid PNG extension for the program.
 * @param image_filename The image file path/name.
 * @return The boolean integer validity condition. 
 */
int is_valid_image_format(const char* image_filename);

#endif
