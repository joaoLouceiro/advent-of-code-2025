#define _DEFAULT_SOURCE

#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    char buf[BUFSIZ];
    int fd;
    ssize_t bytes_read; // read returns the number of bites read. If no bytes
                        // were read, we have reached the end of the file.
    int read_count;
    char *token;
    char *saveptr1;
    char *saveptr2;
    long ret = 0;

    fd = open("input", O_RDONLY);
    if (fd == -1) {
        printf("Error opening file");
        return EXIT_FAILURE;
    }

    bytes_read = read(fd, buf, BUFSIZ);
    if (bytes_read == -1) {
        printf("Error reading file");
        return EXIT_FAILURE;
    }
    buf[bytes_read] = '\0';

    close(fd);

    token = strtok_r(buf, ",", &saveptr1);
    while (token) {
        if (token) {
            char *low_str = strtok_r(token, "-", &saveptr2);
            char *high_str = strtok_r(NULL, "-", &saveptr2);

            long low_int = atol(low_str);
            long high_int = atol(high_str);

            size_t arr_size = strlen(high_str);
            size_t half_arr = arr_size / 2;
            char arr[arr_size];

            // Aqui quero pegar no low_int e transformá-lo num array.
            // Se esse array tiver um tamanho impar, nem vale a pena verificar.
            // Caso contrário, posso só comparar a primeira metade desse array
            // com a segunda, caracter a caracter
            while (low_int <= high_int) {
                sprintf(low_str, "%ld", low_int);
                if (strlen(low_str) % 2 == 0) {
                    char first_half[half_arr];
                    strncpy(first_half, low_str, half_arr);
                    first_half[half_arr] = '\0';

                    char *second_half = low_str + (half_arr);

                    if (strcmp((char *) first_half, second_half) == 0) {
                        ret += low_int;
                    }
                }
                low_int++;
            }

            printf("%s\t%s\n", low_str, high_str);
        }
        token = strtok_r(NULL, ",", &saveptr1);
    }

    printf("%ld\n", ret);

    return EXIT_SUCCESS;
}
