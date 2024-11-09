#include "../include/hider.h"

#include "../include/hider.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file test_hider.c
 * @brief Test file for hider.c file functions.
 */

int main() {
  /* Test to get_message_length_in_bits function */
    {
        const char* test_text_file = "test_message.txt";
        FILE *file = fopen(test_text_file, "w");
        assert(file != NULL);
        fprintf(file, "Hola Mundo!");
        fclose(file);

        unsigned long expected_bits = 8 * strlen("Hola Mundo!");
        unsigned long result_bits = get_message_length_in_bits(test_text_file);
        assert(result_bits == expected_bits);
        printf("Test 1 (get_message_length_in_bits): OK\n");
        remove(test_text_file);
    }

    /* Test to hide_text_in_image function */
    {
        const char* test_text_file = "test_message.txt";
        const char* test_image_file = "test_image.png";
        const char* output_image_file = "test_output_image.png";

        FILE *file = fopen(test_text_file, "w");
        assert(file != NULL);
        fprintf(file, "Este es un mensaje oculto");
        fclose(file);

        file = fopen(test_image_file, "wb");
        assert(file != NULL);
        unsigned char empty_image[8] = {0};
        fwrite(empty_image, sizeof(empty_image), 1, file);
        fclose(file);

        hide_text_in_image(test_text_file, test_image_file, output_image_file);

        FILE *output_file = fopen(output_image_file, "rb");
        assert(output_file != NULL);
        fclose(output_file);

        printf("Test 2 (hide_text_in_image): PASSED\n");

        remove(test_text_file);
        remove(test_image_file);
        remove(output_image_file);
    }

    return 0;
}



