#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/main.h"
#include "../include/funcoes_fornecidas.h"
#include "../include/common.h"
#include "../include/ex8.h"

void ex8() {
    // Ler o nome do arquivo binário de entrada, com tamanho máximo 30
    char nome_entrada[T_MAX];
    fgets(nome_entrada, T_MAX, stdin);
    nome_entrada[strcspn(nome_entrada, "\n")] = '\0';

    // Ler o nome do arquivo de índice, com tamanho máximo 30
    char nome_indice[T_MAX];
    fgets(nome_indice, T_MAX, stdin);
    nome_indice[strcspn(nome_indice, "\n")] = '\0';

    // Ler o campo (deve ser 'nome')
    char nome_campo[T_MAX];
    fgets(nome_campo, T_MAX, stdin);
    nome_campo[strcspn(nome_campo, "\n")] = '\0';

    // Verificar se o campo é 'nome'
    if (strcmp(nome_campo, "nome") != 0) {
        printf("Campo de busca inválido.\n");
        return;
    }

    // Usa a função scan_quote_string para ler o nome dentro das aspas
    char nome_pesquisado[T_MAX];
    scan_quote_string(nome_pesquisado);

    // Abertura do binário de entrada para leitura
    FILE *arquivo_binario = fopen(nome_entrada, "rb");
    if (arquivo_binario == NULL) {
        printf("Falha no processamento do arquivo de entrada.\n");
        return;
    }

    // Abertura do arquivo de índice para leitura
    FILE *arquivo_indice = fopen(nome_indice, "rb");
    if (arquivo_indice == NULL) {
        printf("Falha no processamento do arquivo de índice.\n");
        fclose(arquivo_binario);
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

        // Pular para o RRN correto (ajuste no cálculo)
        fseek(arquivo_binario, 1600 + RRN_registro * 160, SEEK_SET);

        DADO registro;
        fread(&registro, sizeof(DADO), 1, arquivo_binario);

        // Verificar se o registro está logicamente removido antes de exibi-lo
        if (registro.removido == '1') {
            printf("Registro inexistente.\n");
        } else {
            // Exibir os campos do registro encontrado
            printf("Nome: %s\n", registro.nome);
            if (strcmp(registro.especie, "") != 0) {
                printf("Especie: %s\n", registro.especie);
            }
            if (strcmp(registro.tipo, "") != 0) {
                printf("Tipo: %s\n", registro.tipo);
            }
            if (strcmp(registro.dieta, "") != 0) {
                printf("Dieta: %s\n", registro.dieta);
            }
            if (strcmp(registro.habitat, "") != 0) {
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
