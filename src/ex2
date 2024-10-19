/*
* O código abaixo tem como objetivo a recuperação de dados obtidos
* através de um arquivo binário, que será solicitado pelo usuário.
*
* Aqui será feita a etapa principal, solicitando funções criadas no
* módulo 'common.c'
*/


#include "header.h"

/* Funções para execução do ex 2 */

void ex2(){

    // Ler o nome do arquivo de entrada, com tamanho máximo 30:
    char nome_entrada[T_MAX];
    fgets(nome_entrada, T_MAX, stdin);
    nome_entrada[strlen(nome_entrada) - 1] = '\0';

    // Abertura do binário de entrada para leitura
    FILE *binario_entrada = fopen(nome_entrada,"rb");
    if (binario_entrada == NULL){
        printf("Erro ao abrir o arquivo de entrada");
    }

    DADO dado;
    CABECALHO cabecalho;
    int num_reg = 0;
    int pular   = 0;
    int proxRRN = 0;

    // Ir para o primeiro registro de dados disponível
    fseek(binario_entrada, 13, SEEK_SET);
    fread(&proxRRN, sizeof(int), 1, binario_entrada);
    fseek(binario_entrada, TAM_DISCO, SEEK_SET);

    // Enquanto não encontrar um arquivo disponível, pule 160 bytes.
    while (fread (&dado.removido, sizeof(char), 1, binario_entrada)){
        if (dado.removido == '0'){
            pular = 0;
            // Leitura do registro: nome especie tipo dieta lugar tam vel
            fseek(binario_entrada, 8, SEEK_CUR);

            fread(&dado.tamanho,       sizeof(float), 1, binario_entrada);
            fread(&dado.unidadeMedida, sizeof(char),  1, binario_entrada);
            fread(&dado.velocidade,    sizeof(int),   1, binario_entrada);

            pular += 18;          
            pular += leitura_variavel(dado.nome,    binario_entrada);
            pular += leitura_variavel(dado.especie, binario_entrada);
            pular += leitura_variavel(dado.habitat, binario_entrada);
            pular += leitura_variavel(dado.tipo,    binario_entrada);
            pular += leitura_variavel(dado.dieta,   binario_entrada);
            num_reg++;


        printf("Nome: %s\nEspecie: %s\n", dado.nome, dado.especie);
        
        if (strcmp(dado.tipo, "") != 0)
            printf( "Tipo: %s\n", dado.tipo);

        if (strcmp(dado.dieta, "") != 0)
            printf( "Dieta: %s\n", dado.dieta);

        if (strcmp(dado.habitat, "") != 0)
            printf( "Lugar que habitava: (%s)\n", dado.habitat);
        
        if (dado.tamanho != -1)
            printf("Tamanho: %.1lf\n", dado.tamanho);
        
        if (dado.velocidade != -1)
            printf("Velocidade: %d %cm/h\n", dado.velocidade, dado.unidadeMedida);
        
        printf("\n");

            fseek (binario_entrada, 160-pular, SEEK_CUR);
        } else {
            fseek (binario_entrada, 160, SEEK_CUR);
        }
        }

        if(num_reg == 0)
            printf("Registro inexistente");
        else{
            printf("Numero de paginas de disco: %d\n\n", proxRRN);
        }

    fclose(binario_entrada);

}