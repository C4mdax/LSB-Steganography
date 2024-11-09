#include "../include/image.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file test_image.c
 * @brief Test file for image.c file functions.
 */

int main() {
    // Test para la función calculate_image_size_in_bits
    {
        const char* test_image_file = "test_image.png";

        // Crea una imagen PNG simple de prueba (en este caso, una imagen de 2x2 píxeles de 4 canales - RGBA)
        FILE *file = fopen(test_image_file, "wb");
        assert(file != NULL);

        // Imagen de 2x2 con 4 bytes por píxel (RGBA)
        unsigned char image_data[16] = {
            255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 0, 255, 0, 0, 255, 255
        };
        fwrite(image_data, sizeof(image_data), 1, file);
        fclose(file);

        // Llamar a la función calculate_image_size_in_bits
        unsigned long expected_size_in_bits = 2 * 2 * 4 * 8; // 2x2 píxeles * 4 canales * 8 bits por canal
        unsigned long image_size_in_bits = calculate_image_size_in_bits(test_image_file);

        // Verificar si el tamaño calculado es correcto
        assert(image_size_in_bits == expected_size_in_bits);
        printf("Test 1 (calculate_image_size_in_bits): OK\n");

        // Limpieza del archivo de prueba
        remove(test_image_file);
    }

    // Test para la función has_sufficient_space
    {
        const char* test_image_file = "test_image.png";
        const char* test_text_file = "test_message.txt";

        // Crea una imagen PNG simple de prueba (igual que en el test anterior)
        FILE *file = fopen(test_image_file, "wb");
        assert(file != NULL);

        unsigned char image_data[16] = {
            255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 0, 255, 0, 0, 255, 255
        };
        fwrite(image_data, sizeof(image_data), 1, file);
        fclose(file);

        // Crea un archivo de texto con el mensaje a ocultar
        file = fopen(test_text_file, "w");
        assert(file != NULL);
        fprintf(file, "Este es un mensaje oculto");
        fclose(file);

        // Calcular el tamaño en bits del mensaje
        unsigned long message_size_in_bits = get_message_length_in_bits(test_text_file);

        // Verificar si la imagen tiene suficiente espacio para ocultar el mensaje
        int sufficient_space = has_sufficient_space(test_image_file, message_size_in_bits);
        assert(sufficient_space == 1);  // Debería haber suficiente espacio

        printf("Test 2 (has_sufficient_space): OK\n");

        // Limpieza de archivos de prueba
        remove(test_image_file);
        remove(test_text_file);
    }

    return 0;
}
