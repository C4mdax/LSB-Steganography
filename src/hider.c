#include "../include/hider.h"
#include <assert.h>
#include <errno.h>
#include <getopt.h>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/**
 * @file hider.c
 * @brief File that contains the logic for hiding and processing necessary prior to hiding.
 */

/**
 * @brief Hides the text contained in the text file within a given PNG image, and saves the PNG image with the hidden message.
 * @param text_filename The name of the file that contains the text to hide.
 * @param image_filename The name of the image file.
 * @param image_destiny_name The name of the resulting image file with the hidden data.
 */
void hide_text_in_image(const char* text_filename, const char* image_filename, const char* image_destiny_name) {
  /* Opening text file and reading the content */
  FILE *text_file = fopen(text_filename, "rb");
  if (!text_file) {
    perror("Error al abrir el archivo de texto");
    return;
  }
  fseek(text_file, 0, SEEK_END);
  long text_length = ftell(text_file);
  fseek(text_file, 0, SEEK_SET);
    
  char *text = malloc(text_length + 1);
  fread(text, 1, text_length, text_file);
  fclose(text_file);
  text[text_length] = '\0'; /* Ensuring that text ends in "null" */

  /* Opening PNG image */
  FILE *image_file = fopen(image_filename, "rb");
  if (!image_file) {
    perror("Error al abrir la imagen");
    free(text);
    return;
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
  /* Hiding the text in the LSB's */
  int text_index = 0, bit_index = 0;
  for (int y = 0; y < height && (text_index <= text_length); y++) {
    for (int x = 0; x < width && (text_index <= text_length); x++) {
      png_bytep px = &(row_pointers[y][x * 4]);
      for (int color = 0; color < 4; color++) {
	char current_bit = (text_index < text_length) ? ((text[text_index] >> bit_index) & 1) : 0;
	px[color] &= 0xFE; /* Clearing the least significant bit */
	px[color] |= current_bit;
	bit_index++;
	if (bit_index == 8) {
	  bit_index = 0;
	  text_index++;
	}
      }
    }
  }
  /* Saving the image with hidden text */
  FILE *output_image = fopen(image_destiny_name, "wb");
  if (!output_image) {
    perror("Error al crear la imagen de salida");
    free(text);
    return;
  }
    
  png_structp png_out = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info_out = png_create_info_struct(png_out);
  png_init_io(png_out, output_image);
    
  png_set_IHDR(png_out, info_out, width, height, png_get_bit_depth(png, info),
	       PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  png_set_rows(png_out, info_out, row_pointers);
  png_write_png(png_out, info_out, PNG_TRANSFORM_IDENTITY, NULL);

  fclose(output_image);
  /* Freeing memory */
  png_destroy_read_struct(&png, &info, NULL);
  png_destroy_write_struct(&png_out, &info_out);
  for (int y = 0; y < height; y++) {
    free(row_pointers[y]);
  }
  free(row_pointers);
  free(text);
  printf("Texto ocultado con éxito en %s\n", image_destiny_name);
}

/**
 * @brief Gets the length of the message to hide in its binary form (the number of bits).
 * @param filename The name of the file that contains the text to hide.
 * @return unsigned long The number of bits in the binary form of the message.
 */
unsigned long get_message_length_in_bits(const char* filename){
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error al abrir el archivo");
    return -1; /* Error */
  }
  unsigned long length = 0;
  int ch;
  while ((ch = fgetc(file)) != EOF) {
    length++;
  }
  fclose(file);
  /* Each ASCII character represents 8 bits */
  return length * 8;
}
