/*
Arquivo com as funções usadas no resto do projeto
*/

#include "header.h"

/* A seguinte função lê uma string variável do arquivo binário na posição atual
e retorna o desvio do arquivo (considerando o delimitador) */
int leitura_variavel(char* str, FILE* binario_entrada){

    char* c = malloc(sizeof(char));
    fread(c, sizeof(char), 1, binario_entrada);

    int i = 0;
    while (*c != '#'){
        str[i] = *c;
        fread(c, sizeof(char), 1, binario_entrada);
        i++;
    }
        str[i] = '\0';
        i++;
        free(c);
    return i;
}
