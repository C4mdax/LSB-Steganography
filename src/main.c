#include "../include/hider.h"
#include "../include/revealer.h"
#include "../include/image.h"
#include "../include/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * @file main.c
 * @brief HiddenInk Program: Hiding text in PNG images using the LSB steganography technique.
 * @author Luis Angel Moreno Delgado: Software Architect and Repository Administrator.
 * @author Egdar Salgado González: Principal Software Engineer.
 * @author Patricio Salvador González Castillo: Software Quality and Optimization Engineer.
 *
 * Main logic file for program execution.
 */

/**
 * @brief Method to speed up the handling error message.
 */
void handle_error() {
  printf("Error de manejo.\n");
}

/**
 * @brief Method to speed up the reveal option error message.
 */
void reveal_use() {
  printf("Uso para develar: -u <nombre_imagen_con_datos_ocultos> <nombre_archivo_destino>\n");
}

/**
 * @brief Method to speed up the hide option error message.
 */
void hide_use() {
  printf("Uso para ocultar: -h <nombre_archivo_texto_a_ocultar> <nombre_archivo_imagen> <nombre_archivo_resultante>\n");  
}

/**
 * @brief Main method for executing the program.
 * @param argc The number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Returns 0 on successful execution. Returns another value in an execution error.
 *
 * The program works with 2 respective flags:
 * - Hide option "-h": Hides the text within the indicated text file in the indicated PNG image.
 * - Reveal/Unhide "-u": Unhide hidden text in given PNG image.
 */
int main(int argc, char *argv[]) {
  if (argc < 2) {
    reveal_use();
    hide_use();
    return 1;
  }

  char *option = argv[1];
  
  /* Hide option */
  if (strcmp(option, "-h") == 0) {
    if (argc < 4) {
      printf("Faltan argumentos para la opción de ocultar.\n");
      hide_use();
      return 1;
    }
    printf("Opción para ocultar seleccionada.\n");

    char *filetext_name = argv[2];
    char *filepng_name = argv[3];
    char *filepng_destiny = argv[4];
    if (file_exists(filetext_name)) {

      /* Logic to Hide */
      printf("Archivo de texto '%s' encontrado.\n", filetext_name);
      unsigned long length_binary = get_message_length_in_bits(filetext_name);
      if (is_valid_image_format((filepng_name))){
	if (has_sufficient_space(filepng_name, length_binary)){
	  hide_text_in_image(filetext_name, filepng_name, filepng_destiny);
	  /* Successfully hidden message*/
	}
	else{
	  printf("Error: La imagen no tiene el tamaño adecuado para guardar el mensaje.\n");
	  printf("Utiliza una imagen de mayor resolución.\n");
	}
      } else{
	printf("Error: El archivo '%s' no es de tipo PNG.\n", filepng_name);
      }
    } else {
      printf("El archivo '%s' no existe.\n", filetext_name);
    }
  }
  
  /* Reveal option */
  else if (strcmp(option, "-u") == 0) {
    if (argc < 4) {
      printf("Faltan argumentos para la opción de develar.\n");
      reveal_use();
      return 1;
    }
    printf("Opción para revelar seleccionada.\n");
    char *image_with_hiden_message = argv[2];
    char *text_destiny = argv[3];
    char* binary_message = extract_text_from_image(image_with_hiden_message, text_destiny);
    printf("Texto develado correctamente: Consulte en su archivo de texto destino.\n");
    /* Successfully unhidden message*/
    if (binary_message == NULL){
      printf("Error al extraer el mensaje de la imagen .\n");
      return 1;
    }
  }
  
  /* Program execution or call error */
  else {
    handle_error();
    reveal_use();
    hide_use();
    return 1;
  }
  return 0;
}
