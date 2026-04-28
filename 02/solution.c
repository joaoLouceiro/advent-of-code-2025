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

    char *token;
    char *saveptr1;
    long ret = 0;
    token = strtok_r(buf, ",", &saveptr1);
    while (token) {
        char *high_str;
        char *low_str = strtok_r(token, "-", &high_str);
        // printf("%s\t%s\n", low_str, high_str);

        long low_int = atol(low_str);
        long high_int = atol(high_str);

        // Aqui quero pegar no low_int e transformá-lo num arrayi.
        // Se esse array tiver um tamanho impar, nem vale a pena verificar.
        // Caso contrário, posso só comparar a primeira metade desse array
        // com a segunda, caracter a caracter
        while (low_int <= high_int) {
            // A segunda parte do exercício bate aqui.
            // Quero ver se há padrões repetidos uma qualquer quantidade
            // de vezes. Isso que dizer que vou começar por olhar para o
            // meu array dividido em dois, como já estava a fazer,
            // depois dividido em três, até só estar a comparar item a
            // item. O problema: como raio é que eu faço isso sem saber
            // QUANTOS arrays tenho de criar?
            //
            // Na verdade, só preciso de dois:
            // Imaginemos que estou na minha terceira iteração, ou seja,
            // tenho o meu número "partido" em três.
            // 1) Comparo a primeira parte com a segunda.
            // 2) Se essas duas partes forem iguais, repito o processo,
            // substituindo a segunda com a terceira parte.
            sprintf((char *)low_str, "%ld", low_int);
            size_t whole_array_size = strlen(low_str);
            size_t section_size = whole_array_size / 2;
            long prev_val = 0;
            while (section_size >= 1) {
                if (whole_array_size % section_size == 0) {
                    size_t offset = section_size;

                    char first_part[section_size];
                    memcpy(first_part, low_str, section_size);
                    first_part[section_size] = '\0';

                    int is_equal = 1;

                    while (is_equal && offset < whole_array_size) {
                        char next_part[section_size];
                        memcpy(next_part, low_str + offset, section_size);
                        next_part[section_size] = '\0';
                        is_equal =
                            strcmp((char *)first_part, (char *)next_part) == 0;
                        offset += section_size;
                    }

                    // Um último problema: quando tenho um número composto pelo
                    // mesmo dígito, estou a ter resultados duplicados:
                    // 2222 é contabilizado quer como 22 22, quer como 2 2 2 2
                    if (is_equal && low_int != prev_val) {
                        ret += low_int;
                        prev_val = low_int;
                    }
                }
                section_size--;
            }

            low_int++;
        }
        token = strtok_r(NULL, ",", &saveptr1);
    }
    printf("%ld\n", ret);

    return EXIT_SUCCESS;
}
