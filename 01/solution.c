#include <fcntl.h>
#include <stdcountof.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define INIT_DIAL 50
#define BUFF_SIZE 5
#define ASCII_OFFSET 48

// Pensei que podia usar o fread para ir buscar os elementos do stream, mas não
// dá para o que eu quero.
//
// Tenho de arranjar alguma forma de ir buscar todos os chars até ao \n
//
// Então, a ideia é ter um loop que itera pelo ficheiro todo, enquanto outro
// itera pelos chars
//
// De certeza que dá para fazer esta porra com o fgets
//

void clear_buff(char *Buffer) {
    for (size_t i = 0; i < BUFF_SIZE; i++) {
        Buffer[i] = 0;
    }
}

int main(int argc, char *argv[]) {
    FILE *File;
    char Buffer[BUFF_SIZE];
    int Ret = 0;
    int DialPosition = INIT_DIAL;

    File = fopen("input", "r");

    if (!File) {
        perror("Error opening file (perror)");
        return -1;
    }

    int Character;
    do {
        for (size_t i = 0;
             ((Character = getc(File)) != '\n' && Character != EOF); i++) {
            Buffer[i] = (char)Character;
        };

        int Multiplier = 1;
        if (Buffer[0] == 'L') {
            Multiplier = -1;
        }

        // TODO: use atoi
        int CurrentNumber = 0;
        for (size_t i = 1; Buffer[i] != 0; i++) {
            CurrentNumber = (CurrentNumber * 10) + (Buffer[i] - ASCII_OFFSET);
        }

        if (CurrentNumber >= 100) {
            Ret += CurrentNumber / 100;
        }

        int CurrentNumberMod = CurrentNumber % 100;
        int CurrentNumberMul = CurrentNumberMod * Multiplier;

        int NewDialPosition = (((DialPosition + CurrentNumberMul) % 100) + 100) % 100;

        if (NewDialPosition == 0 ||
            DialPosition != 0 && ((Multiplier == -1 && NewDialPosition > DialPosition) ||
            (Multiplier == 1 && NewDialPosition < DialPosition))) {
            Ret++;
        }

        DialPosition = NewDialPosition;
        clear_buff(Buffer);
    } while (Character != EOF);

    printf("%d\n", Ret);

    return EXIT_SUCCESS;
}
