/*
* O código a seguir é responsável pela inserção de novos registros em um
* arquivo binário, a ser ecolhido pelo usuário.
* 
* Ele irá usar o espaço de lixo, onde foi removido anteriormente outros dados,
* representado pelo caractere '$', para a inserção desses novos dados.
* 
* Essa funcionalidade deverá se repetir 'n' vezes, sendo esse valor também
* escolhido pelo usuário.
* 
* Aqui será feita a etapa principal, solicitando funções criadas no
* módulo 'common.c'
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/funcoes_fornecidas.h"
#include "../include/common.h"
#include "../include/main.h"
#include "../include/ex9.h"

// Para utilizar essa função posicionar corretamente o inicio do arquivo
// int sobreescreve_dado (FILE* binario, DADO dado){

// char delim       = '#';
// char lixo        = '$';
// int ac           =  0;

// // Escrever a struct no arquivo binário:
// fwrite(&dado.removido,          sizeof(char),  1, binario);
// fwrite(&dado.encadeamento,      sizeof(int),   1, binario);
// fwrite(&dado.populacao,     sizeof(int),   1, binario);
// fwrite(&dado.tamanho,       sizeof(float), 1, binario);
// fwrite(&dado.unidadeMedida, sizeof(char),  1, binario);
// fwrite(&dado.velocidade,    sizeof(int),   1, binario);
// ac += 18;

// ac += strlen(dado.nome)+1;
// fwrite(&dado.nome, sizeof(char), strlen(dado.nome), binario);
// fwrite(&delim,    sizeof(char), 1,                binario); // Delimitador
// //printf("%s", dado.nome);

// ac += strlen(dado.especie)+1;
// fwrite(&dado.especie, sizeof(char), strlen(dado.especie), binario);
// fwrite(&delim,       sizeof(char), 1,                   binario); // Delimitador
// ac += strlen(dado.habitat)+1;
// fwrite(&dado.habitat, sizeof(char), strlen(dado.habitat), binario);
// fwrite(&delim,       sizeof(char), 1,                   binario); // Delimitador
// ac += strlen(dado.tipo)+1;
// fwrite(&dado.tipo, sizeof(char), strlen(dado.tipo), binario);
// fwrite(&delim,    sizeof(char), 1,                binario); // Delimitador
// ac += strlen(dado.dieta)+1;
// fwrite(&dado.dieta, sizeof(char), strlen(dado.dieta), binario);
// fwrite(&delim,     sizeof(char), 1,                 binario); // Delimitador
// ac += strlen(dado.alimento)+1;
// fwrite(&dado.alimento, sizeof(char), strlen(dado.alimento), binario);
// fwrite(&delim,        sizeof(char), 1,                    binario); // Delimitador

// while( (160 - ac) > 0){
//     fwrite(&lixo, sizeof(char), 1, binario); //Identifica o lixo
//     ac++;
// }

// return dado.encadeamento;
// }

void ex9(int* proxRRN){

char nome_1[T_MAX];
scanf("%s", nome_1);

char nome_2[T_MAX];
scanf("%s", nome_2);

// Abertura do binário de entrada para leitura e gravação
FILE *binario_reescrita = fopen(nome_1,"rb+");

// Abertura do binário de entrada para leitura e gravação
FILE *binario_indice = fopen(nome_2,"rb+");

int n; // Número de inserções
scanf("%d", &n);

DADO* dado = malloc (n * sizeof(DADO));

char* unidade = malloc (sizeof(char) * T_MAX);
int topo;
char* pop = malloc (sizeof(char) * T_MAX);
char* vel = malloc (sizeof(char) * T_MAX);
char* tam = malloc (sizeof(char) * T_MAX);
long chave;
int RRNraiz = -1;
int i;

fflush(stdin);
for (i = 0; i < n; i++) {

   
    my_scan(dado[i].nome);
    chave = converteNome(dado[i].nome);
    my_scan(dado[i].dieta);
    my_scan(dado[i].habitat);
    my_scan(pop);
    if(strcmp(pop, "") == 0){
        dado[i].populacao = -1;
    } else {
        dado[i].populacao = atoi(pop);}
    my_scan(dado[i].tipo);
    my_scan(vel);
    if(strcmp(vel, "") == 0){
        dado[i].velocidade = -1;
    } else {
        dado[i].velocidade = atoi(vel);}
    my_scan(unidade);
    if(strcmp(unidade, "") == 0){
        dado[i].unidadeMedida = '$';
    } else {
        dado[i].unidadeMedida = unidade[0];}
    my_scan(tam);
    if(strcmp(tam, "") == 0){
        dado[i].tamanho = -1;
    } else {
        dado[i].tamanho = atof(tam);}
    my_scan(dado[i].especie);
    my_scan(dado[i].alimento);
    dado[i].removido = '0'; 


    /*
    my_scan(dado[i].nome);
    chave = converteNome(dado[i].nome);
    my_scan(dado[i].dieta);
    my_scan(pop);
    if(strcmp(pop, "") == 0){
        dado[i].populacao = -1;
    } else {
        dado[i].populacao = atoi(pop);}
    //
    my_scan(dado[i].tipo);
    //
    my_scan(vel);
    dado[i].velocidade = atoi(vel);
    if(strcmp(vel, "") == 0){
        dado[i].velocidade = -1;
    } else {
        dado[i].velocidade = atoi(vel);}
    //
    my_scan(unidade);
    if(strcmp(unidade, "") == 0){
        dado[i].unidadeMedida = '$';
    } else {
        dado[i].unidadeMedida = unidade[0];}
    //
    my_scan(dado[i].habitat);
    //
    my_scan(tam);
    //
    if(strcmp(tam, "") == 0){
        dado[i].tamanho = -1;
    } else {
        dado[i].tamanho = atof(tam);}
    my_scan(dado[i].especie);
    //
    my_scan(dado[i].alimento);
    dado[i].removido = '0';
    // */

/*
    printf("nome = %s ", dado[i].nome);
    printf("dieta = %s ", dado[i].dieta);
    printf("habitat = %s ", dado[i].habitat);
    printf("populacao = %d ", dado[i].populacao);
    printf("tipo = %s ", dado[i].tipo);
    printf("velocidade = %d ", dado[i].velocidade);
    printf("unidade= %c ", dado[i].unidadeMedida);
    printf("tamanho= %f ", dado[i].tamanho);
    printf("especie = %s ", dado[i].especie);
    printf("alimento = %s\n", dado[i].alimento);  */

    indice ind;
    ind.chave = chave;
    //printf("Chave = %ld, nome=%s\n", chave, dado[i].nome);
    ind.novo = 0;
    ind.p1 = -1;
    ind.p2 = -1;

    // Ler a primeira RRN removida
    fseek(binario_reescrita, 1, SEEK_SET);
    fread(&topo, sizeof(int), 1, binario_reescrita);
   // printf("Inserção realizada no RRN (dado) %d\n", topo);

    if (topo != -1){
        fseek(binario_reescrita, 1600 + topo*160 + 1, SEEK_SET);
        fread(&dado[i].encadeamento, sizeof(int), 1, binario_reescrita);
        fseek(binario_reescrita, 1600 + topo*160, SEEK_SET);
        ind.pr = ftell(binario_reescrita);}
    else{
        dado[i].encadeamento = -1;
        fseek(binario_reescrita, 0, SEEK_END);
        ind.pr = ftell(binario_reescrita);
    }
    //printf("encadeamento = %d\n", dado[i].encadeamento);

    sobreescreve_dado(binario_reescrita, dado[i]);

    fseek(binario_indice, 1, SEEK_SET);
    fread(&RRNraiz, sizeof(int), 1, binario_indice);
    fread(proxRRN, sizeof(int), 1, binario_indice);
    
    *(proxRRN)=*(proxRRN)-1;

    //printf("Inserção realizada no indice, proxRRN = %d\n", *proxRRN);
    inserir(ind, binario_indice, *proxRRN);
    // inserir(ind, binario_indice, RRNraiz);

    fseek(binario_reescrita, 1, SEEK_SET);
    fwrite(&dado[i].encadeamento, sizeof(int), 1, binario_reescrita);
}
    *(proxRRN)=*(proxRRN)+1;
    ajustaCabecalho(binario_indice,'1',RRNraiz, *proxRRN);
    binarioNaTela(nome_2);

free(dado);
free(pop);
free(vel);
free(tam);
free(unidade);
fclose(binario_indice);
fclose(binario_reescrita);
return;
}