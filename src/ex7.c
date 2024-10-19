#include "header.h"

/* A Função find_name salva o nome (chave) do registro,
 e pula para o próximo registro*/
void find_name(FILE* fbin, char* nome){
    char* c = malloc(1*sizeof(char)); 

    fread(c, sizeof(char), 1, fbin);
    while ((*c) == '1'){
        fseek(fbin, T_REG_DADOS-1, SEEK_CUR);
        fread(c, sizeof(char), 1, fbin);
    }

    fseek(fbin, 17, SEEK_CUR);
    long pular = (long) leitura_variavel(nome, fbin);
    printf("%s", nome);
    fseek(fbin, T_REG_DADOS - pular - 18, SEEK_CUR);

    free(c);
}

void ex7(){

    // Ler o nome do arquivo de entrada, com tamanho máximo 30:
    char nome_entrada[T_MAX];
    fgets(nome_entrada, T_MAX, stdin);
    nome_entrada[strlen(nome_entrada) - 1] = '\0';

    // Abertura do binário de entrada para leitura
    FILE *binario_entrada = fopen(nome_entrada,"rb");
    if (binario_entrada == NULL){
        printf("Erro ao abrir o arquivo de entrada");
        return;
    }

    // Ir para a primeira posição do registro de dados
    fseek(binario_entrada, T_DADOS, SEEK_SET);

    // Encontrar o primeiro nome da lista para adicionar à árvore B
    char* nome = malloc(T_MAX * sizeof(char));
    find_name(binario_entrada, nome);
    find_name(binario_entrada, nome);
 //   find_name(binario_entrada, nome);

    free(nome);
    fclose(binario_entrada);
}
