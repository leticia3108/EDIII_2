/*
    ****************************************************************************
    O código a seguir é responsável pela inserção de novos registros em um
    arquivo binário, a ser ecolhido pelo usuário.

    Ele irá usar o espaço de lixo, onde foi removido anteriormente outros dados,
    representado pelo caractere '$', para a inserção desses novos dados.

    Essa funcionalidade deverá se repetir 'n' vezes, sendo esse valor também
    escolhido pelo usuário.

    Aqui será feita a etapa principal, solicitando funções criadas no
    módulo 'common.c'
    ****************************************************************************
*/


#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "../include/main.h"
#include "../include/funcoes_fornecidas.h"
#include "../include/ex5.h"
#include "../include/common.h"

void ex5(){

char nome_entrada[T_MAX];
scanf("%s", nome_entrada);
nome_entrada[strlen(nome_entrada)-1] = '\0';

// Abertura do binário de entrada para leitura e gravação
FILE *binario_entrada = fopen(nome_entrada,"r+b");

int n; // Número de inserções
scanf("%d", &n);
printf("n = %d ", n);

DADO** dado = malloc (n * sizeof(DADO*));
for (int i = 0; i < n; i++){
    dado[i] = malloc (sizeof(DADO));
}
//nome, dieta, habitat, populacao, tipo,
//velocidade, medidaVelocidade, tamanho, especie, alimento

char unidade[1];
int i = 0;

for (int i = 0; i < n; i++) {
    scan_quote_string(dado[i]->nome);
    scan_quote_string(dado[i]->dieta);
    scan_quote_string(dado[i]->habitat);
    scanf("%d", &dado[i]->populacao);
    scan_quote_string(dado[i]->tipo);
    scanf("%d", &dado[i]->velocidade);
    scan_quote_string(unidade);
    dado[i]->unidadeMedida = unidade[0];
    scanf("%f", &dado[i]->tamanho);
    scan_quote_string(dado[i]->especie);
    scan_quote_string(dado[i]->alimento);

    // Ler a primeira RRN removida
    int topo;
    fseek(binario_entrada, 1, SEEK_CUR);
    fread(&topo, sizeof(int), 1, binario_entrada);

    fseek(binario_entrada, 1600 + topo*160, SEEK_CUR);
    topo = sobreescreve_dado(binario_entrada, *dado[i]);
    
}

for (int i = 0; i < n; i++){
    free(dado[i]);
}

free(dado);
return;
}