#include "header.h"

int main() {
    // Leitura da entrada inicial do usuário

    int* proxRRN = malloc(sizeof(int));
    *proxRRN = 0; 

    int opcao = 0;
    scanf("%d", &opcao);
    getc(stdin);

    switch (opcao){
        case 7:
            ex7(proxRRN);
            break;
        case 9:
            ex9(proxRRN);
            break;
        case 10:
            binarioNaTela("d9.bin");
            break;
    }

    free(proxRRN);
    return 0;
}