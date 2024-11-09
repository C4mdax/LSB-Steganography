#ifndef REVEALER_H
#define REVEALER_H

/** Methods to Revealer file. */

/**
 * @brief Converts a binary sequence to its clear text form (readable form).
 * @return char* The string corresponding to the message in clear text.
 */
char* reveal_text_from_binary_sequence(const char* binary_sequence);

/**
 * @brief Extracts the hidden message in the given PNG image, using the unhide by LSB logic.
 * @param image_filename The name of the image with hidden text.
 * @param text_file_destiny The text file where the extracted message will be saved.
 */
char* extract_text_from_image(const char* image_filename, const char* text_file_destiny);

#endif
