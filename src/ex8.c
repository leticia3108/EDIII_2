#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/main.h"
#include "../include/funcoes_fornecidas.h"
#include "../include/common.h"
#include "../include/ex8.h"

void ex8() {

    char nome_arquivo_binario[T_MAX];
    char nome_arquivo_indice[T_MAX];
    char string_auxiliar[T_MAX];
    char nome_pesquisado[T_MAX];

    scanf("%s", nome_arquivo_binario);
    scanf("%s", nome_arquivo_indice);
    scanf("%s", string_auxiliar);
    scan_quote_string(nome_pesquisado);


    // Abertura do binário de entrada para leitura
    FILE *arquivo_binario = fopen(nome_arquivo_binario, "rb");
    if (arquivo_binario == NULL) {
        printf("Falha no processamento do arquivo de entrada.\n");
        return;
    }

    // Abertura do arquivo de índice para leitura
    FILE *arquivo_indice = fopen(nome_arquivo_indice, "rb");
    if (arquivo_indice == NULL) {
        printf("Falha no processamento do arquivo de índice.\n");
        return;
    }    

    // Converte nome para chave long
    long chave_busca = converteNome(nome_pesquisado);

    // Busca no índice da arvore-b
    no_indice no;
    int encontrado = 0;
    fseek(arquivo_indice, 93, SEEK_SET); // Pula o cabeçalho

    while (fread(&no.folha, sizeof(char), 1, arquivo_indice)) {
        fread(&no.nroChavesNo, sizeof(int), 1, arquivo_indice);
        fread(&no.RRNdoNo, sizeof(int), 1, arquivo_indice);

        fread(&no.P1, sizeof(int), 1, arquivo_indice);
        fread(&no.C1, sizeof(long), 1, arquivo_indice);
        fread(&no.PR1, sizeof(long), 1, arquivo_indice);

        fread(&no.P2, sizeof(int), 1, arquivo_indice);
        fread(&no.C2, sizeof(long), 1, arquivo_indice);
        fread(&no.PR2, sizeof(long), 1, arquivo_indice);

        fread(&no.P3, sizeof(int), 1, arquivo_indice);
        fread(&no.C3, sizeof(long), 1, arquivo_indice);
        fread(&no.PR3, sizeof(long), 1, arquivo_indice);

        fread(&no.P4, sizeof(int), 1, arquivo_indice);
        fread(&no.C4, sizeof(long), 1, arquivo_indice);
        fread(&no.PR4, sizeof(long), 1, arquivo_indice);

        fread(&no.P5, sizeof(int), 1, arquivo_indice);

        // Verifica se a chave é correspondente ao valor buscado
        if (chave_busca == no.C1 || chave_busca == no.C2 || chave_busca == no.C3 || chave_busca == no.C4) {
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        // Localiza o registro no arquivo de dados usando RRN
        long RRN_registro = (chave_busca == no.C1) ? no.PR1 :
                            (chave_busca == no.C2) ? no.PR2 :
                            (chave_busca == no.C3) ? no.PR3 :
                            no.PR4;

        // Pular para o RRN correto
        long posicao_registro = 1600 + RRN_registro * 160;
        fseek(arquivo_binario, posicao_registro, SEEK_SET);

        DADO registro;
        fread(&registro, sizeof(DADO), 1, arquivo_binario);

        // Verificar se o registro está logicamente removido antes de exibi-lo
        if (registro.removido == '1') {
            printf("Registro logicamente removido.\n");
        } else {
            // Exibir os campos do registro encontrado, verificando se estão preenchidos
            if (strcmp(registro.nome, "$") != 0) {
                printf("Nome: %s\n", registro.nome);
            }
            if (strcmp(registro.especie, "$") != 0 && strcmp(registro.especie, "") != 0) {
                printf("Especie: %s\n", registro.especie);
            }
            if (strcmp(registro.tipo, "$") != 0 && strcmp(registro.tipo, "") != 0) {
                printf("Tipo: %s\n", registro.tipo);
            }
            if (strcmp(registro.dieta, "$") != 0 && strcmp(registro.dieta, "") != 0) {
                printf("Dieta: %s\n", registro.dieta);
            }
            if (strcmp(registro.habitat, "$") != 0 && strcmp(registro.habitat, "") != 0) {
                printf("Lugar que habitava: %s\n", registro.habitat);
            }
            if (registro.tamanho > 0) {
                printf("Tamanho: %.1f m\n", registro.tamanho);
            }
            if (registro.velocidade > 0) {
                printf("Velocidade: %d %cm/h\n", registro.velocidade, registro.unidadeMedida);
            }
        }
    } else {
        printf("Registro inexistente.\n");
    }

    fclose(arquivo_binario);
    fclose(arquivo_indice);
}
