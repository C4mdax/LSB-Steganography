#include "../include/utils.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

/**
 * @file utils.c
 * @brief File that contains utility methods for correct program logic.
 */

/**
 * @brief Verifies that the file given as a parameter exists.
 * @param filename The file path/name.
 * @return The entire Boolean condition of existence.
 */
int file_exists(const char* filename){
  FILE *file;
  if ((file = fopen(filename, "r"))){
    fclose(file);
    return 1;
  }
  return 0;
}

/**
 * @brief Verify that the image given as a parameter has a valid PNG extension for the program.
 * @param image_filename The image file path/name.
 * @return The boolean integer validity condition. 
 */
int is_valid_image_format(const char* image_filename){
  const char* dot = strrchr(image_filename, '.');
  if (dot && strcmp(dot, ".png") == 0)
    return 1;
  return 0;
}

