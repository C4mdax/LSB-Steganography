#include "../src/utils.c"
#include <assert.h>

/**
 * @file test_revealer.c
 * @brief Test file for revealer.c file functions.
 */

void test_file_exists(){
  assert(file_exists("data/archivo_existente.txt") != 0 && "El archivo debería existir.");
  assert(file_exists("data/archivo_inexistente.txt") == 0 && "El archivo no debería existir.");
}

void test_binary_string_to_integer(){
  assert(binary_string_to_integer("1100101") == 101);
  assert(binary_string_to_integer("111001") == 57)
}

void test_is_valid_image_format() {
    // Archivos con extensiones válidas
    assert(is_valid_image_format("image.png") == 1 && "El archivo con extensión .png debería ser válido.");
    assert(is_valid_image_format("photo.jpg") == 1 && "El archivo con extensión .jpg debería ser válido.");
    assert(is_valid_image_format("graphic.jpeg") == 1 && "El archivo con extensión .jpeg debería ser válido.");
    assert(is_valid_image_format("picture.bmp") == 1 && "El archivo con extensión .bmp debería ser válido.");
    assert(is_valid_image_format("animation.gif") == 1 && "El archivo con extensión .gif debería ser válido.");

    // Archivos con extensiones no válidas
    assert(is_valid_image_format("document.pdf") == 0 && "El archivo con extensión .pdf no debería ser válido.");
    assert(is_valid_image_format("image.txt") == 0 && "El archivo con extensión .txt no debería ser válido.");
    assert(is_valid_image_format("no_extension") == 0 && "El archivo sin extensión no debería ser válido.");
}

int main(){
  test_file_exists();
  printf("PASSED.\n");

  test_binary_string_to_integer();
  printf("PASSED\n");
  return 0;
}

