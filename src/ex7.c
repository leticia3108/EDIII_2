#include "header.h"
#include "../include/funcoes_fornecidas.h"

/* A Função find_name busca o nome e a chave do registro, pula para 
o próximo registro e salva os resultados na struct de indice */

void cabecalho_indice(FILE* fbin, FILE* fbin_ind){
    // Escreve a versão inicial do cabeçalho
    cab_indice cabecalho;

    cabecalho.status = '0';
    cabecalho.noRaiz = -1;
    cabecalho.RRNproxNo = 0;

    fwrite(&cabecalho.status, sizeof(char), 1, fbin_ind);
    fwrite(&cabecalho.noRaiz, sizeof(int), 1, fbin_ind);
    fwrite(&cabecalho.RRNproxNo, sizeof(int), 1, fbin_ind);

    // Deixa todas os demais endereços do disco setados com $
    for (int i = 0; i < (T_CAB_IND - 9); i++){
        fwrite("$", sizeof(char), 1, fbin_ind);
    }
}

void encontra_nome(FILE* fbin, char* nome, indice* ind){
    char* c = malloc(1*sizeof(char)); 

    fread(c, sizeof(char), 1, fbin);
    while ((*c) == '1'){
        fseek(fbin, T_REG_DADOS-1, SEEK_CUR);
       // printf("ftell = %ld\n", ftell(fbin));
        fread(c, sizeof(char), 1, fbin);
    }

    fseek(fbin, 17, SEEK_CUR);
    long pular = (long) leitura_variavel(nome, fbin);
   // printf("%s", nome);
    fseek(fbin, T_REG_DADOS - pular - 18, SEEK_CUR);

    free(c);
    ind->pr = (ftell(fbin)-1600)/160 - 1;
    ind->chave = converteNome(nome);

    printf("Inserido dado (%s)(%ld)-%ld\n", nome, ind->chave, ind->pr);
}

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

    // Encontrar os nomes da lista para adicionar à árvore B
    char* nome = malloc(T_MAX * sizeof(char));
    indice* ind = malloc(sizeof(indice));

    fseek(binario_saida, 1, SEEK_SET);

    //Armazena o RRN da raiz
    int RRNraiz;
    fread(&RRNraiz, sizeof(int), 1, binario_saida);

    int last_ptr_dado = -1;

    for (int i = 0; i<4; i++){
    // Pular cabeçalho do arquivo de dados
    fseek(binario_entrada, T_DADOS + 160*(last_ptr_dado+1), SEEK_SET);
    encontra_nome(binario_entrada, nome, ind);
    last_ptr_dado = ind->pr;
    fseek(binario_saida, 1, SEEK_SET);
    fread(&RRNraiz, sizeof(int), 1, binario_saida);
    inserir(*ind,binario_saida,RRNraiz);
    }

    free(nome);
    free(ind);
    fclose(binario_entrada);
    fclose(binario_saida);
}
