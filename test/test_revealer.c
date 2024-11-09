#include "../include/revealer.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file test_revealer.c
 * @brief Test file for revealer.c file functions.
 */

int main() {
  /* Test to reveal_text_from_binary_sequence function */
    {
        const char* binary_message = "0100100001100101011011000110110001101111";
        char* decoded_message = reveal_text_from_binary_sequence(binary_message);
        assert(strcmp(decoded_message, "Hello") == 0);
        printf("Test 1 (reveal_text_from_binary_sequence): PASSED\n");

        free(decoded_message);
    }

    /* Test to extract_text_from_image function */
    {
        const char* test_image_file = "test_image_with_hidden_message.png";
        const char* extracted_text_file = "extracted_message.txt";

        char* extracted_text = extract_text_from_image(test_image_file, extracted_text_file);

        FILE* file = fopen(extracted_text_file, "r");
        assert(file != NULL);

        char extracted_message[100];
        fread(extracted_message, sizeof(char), sizeof(extracted_message), file);
        fclose(file);

        assert(strcmp(extracted_message, "Hello World") == 0);
        printf("Test 2 (extract_text_from_image): PASSED\n");

        remove(extracted_text_file);
    }

    return 0;
}
