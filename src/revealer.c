#include "../include/revealer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <png.h>

/**
 * @file revealer.c
 * @brief File that contains the logic for revealing and processing necessary to reveal.
 */

/**
 * @brief Converts a binary sequence to its clear text form (readable form).
 * @return char* The string corresponding to the message in clear text.
 */

char* reveal_text_from_binary_sequence(const char* binary_message){
  size_t len = strlen(binary_message) / 2;
  char* decoded_message = (char*)malloc(len + 1);

  for (size_t i = 0; i < len; i++) {
    sscanf(binary_message + 2 * i, "%2hhx", &decoded_message[i]);
  }
  decoded_message[len] = '\0';

  return decoded_message;
}

/**
 * @brief Extracts the hidden message in the given PNG image, using the unhide by LSB logic.
 * @param image_filename The name of the image with hidden text.
 * @param text_file_destiny The text file where the extracted message will be saved.
 */

char* extract_text_from_image(const char* image_filename, const char* text_file_destiny) {
  FILE *image_file = fopen(image_filename, "rb");
  if (!image_file) {
    perror("Error al abrir la imagen");
    return NULL;
  }    
  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info = png_create_info_struct(png);
  png_init_io(png, image_file);
  png_read_info(png, info);
    
  int width = png_get_image_width(png, info);
  int height = png_get_image_height(png, info);
  png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
  for (int y = 0; y < height; y++) {
    row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png, info));
  }
  png_read_image(png, row_pointers);
  fclose(image_file);

  char *text = malloc(width * height * 4 / 8);
  int text_index = 0, bit_index = 0;
  char current_char = 0;

  for (int y = 0; y < height && text_index < width * height * 4 / 8; y++) {
    for (int x = 0; x < width; x++) {
      png_bytep px = &(row_pointers[y][x * 4]);
      for (int color = 0; color < 4; color++) {
	current_char |= (px[color] & 1) << bit_index;
	bit_index++;
	if (bit_index == 8) {
	  if (current_char == '\0') {
	    text[text_index] = '\0';
	    goto end_extraction;
	  }
	  text[text_index++] = current_char;
	  current_char = 0;
	  bit_index = 0;
	}
      }
    }
  }
 end_extraction:

  /* Saving the extracted text to the file */
  FILE *output_file = fopen(text_file_destiny, "wb");
  if (output_file) {
    fwrite(text, sizeof(char), text_index, output_file);
    fclose(output_file);
  }

  png_destroy_read_struct(&png, &info, NULL);
  for (int y = 0; y < height; y++) {
    free(row_pointers[y]);
  }
  free(row_pointers);

  printf("Texto extraído y guardado en el archivo %s\n", text_file_destiny);
  return text;
}
