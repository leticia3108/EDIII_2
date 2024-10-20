#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "../include/main.h"
#include "../include/funcoes_fornecidas.h"
#include "../include/common.h"
#include "../include/ex7.h"


void ex7(){

    // Ler o nome do arquivo de entrada, com tamanho máximo 30:
    char nome_entrada[T_MAX];
    fgets(nome_entrada, T_MAX, stdin);
    nome_entrada[strlen(nome_entrada) - 1] = '\0';

    // Ler o nome do arquivo de saída, com tamanho máximo 30:
    char nome_saida[T_MAX];
    fgets(nome_saida, T_MAX, stdin);
    nome_entrada[strlen(nome_saida) - 1] = '\0';

    // Abertura do binário de entrada para leitura
    FILE *binario_entrada = fopen(nome_entrada,"rb");
    if (binario_entrada == NULL){
        printf("Erro ao abrir o arquivo de entrada");
        return;
    }

    // Abertura do arquivo de índice para escrita
    FILE *binario_saida = fopen(nome_saida,"wb+");
    if (binario_saida == NULL){
        printf("Erro ao criar o arquivo de indice");
        return;
    }

    // Criação do cabeçalho do índice
    cabecalho_indice(binario_entrada, binario_saida);

    // Pular cabeçalho do arquivo de dados
    fseek(binario_entrada, T_DADOS, SEEK_SET);

    // Encontrar o primeiro nome da lista para adicionar à árvore B
    char* nome = malloc(T_MAX * sizeof(char));
    indice* ind = malloc(sizeof(indice));
    encontra_nome(binario_entrada, nome, ind);

    fseek(binario_saida, 1, SEEK_SET);

    //Armazena o RRN da raiz
    int RRNraiz;
    fread(&RRNraiz, sizeof(int), 1, binario_saida);

    //Incluir o índice na árvore B
    inserir(*ind,binario_saida, RRNraiz);

    free(nome);
    free(ind);
    fclose(binario_entrada);
    fclose(binario_saida);
}
