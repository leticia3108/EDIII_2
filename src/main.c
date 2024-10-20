
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "../include/main.h"


int main() {
    // Leitura da entrada inicial do usuário
    int opcao = 0;
    scanf("%d", &opcao);
    getc(stdin);

    switch (opcao){
        case 7:
            ex7();
            break;
    }

    return 0;
}