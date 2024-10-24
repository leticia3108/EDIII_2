/*
*************************************************
* Trabalho Prático 02 de Estrutura de Dados III *
*************************************************

 Alunos:
    Paulo Nunes de Azevedo    - Nº USP: 13839010
    Leticia Crepaldi da Cunha - Nº USP: 11800879
 
 
 ********* Desenvolvimento de cada integrante no projeto: *********
 
 -------------------------------------------------------------------------
 Leticia:
    Implementou as funcionalidades 7 e 9, além de refazer o Makefile, 
    tornando-o mais e limpo e melhor parr futuras manutenções no projeto.
    
 Porcentagem de participação da sua parte: 
 -------------------------------------------------------------------------
 
 -------------------------------------------------------------------------
 Paulo:
    Implementou a funcionalidade 8 e fez adaptações da modularização do 
    trabalho para o trabalho 2

 Porcentagem de participação da sua parte: 
 -------------------------------------------------------------------------
 
*/


#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "../include/main.h"
#include "../include/funcoes_fornecidas.h"
#include "../include/common.h"
#include "../include/ex2.h"
#include "../include/ex5.h"
#include "../include/ex7.h"
#include "../include/ex8.h"
#include "../include/ex9.h"


int main() {

    // Leitura da entrada inicial do usuário
    int opcao = 0;
    scanf("%d", &opcao);
    getc(stdin);

    switch (opcao) {
        case 7:
            ex7();
            break;
        case 8:
            ex8();
            break;
        default:
            printf("Opcao invalida!\n");
            break;
    }

    return 0;
}