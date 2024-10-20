/*
* Header principal do projeto.
* 
* Aqui se concentra a declaração das funções utilizadas ao longo do projeto,
* bem como as funções fornecidas pelo professor e pelos monitores da disciplina
* 
*/
#ifndef HEADER_H
#define HEADER_H

// Bibliotecas utilizadas
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
//#include "../include/funcoes_fornecidas.h"

// Definições
#define T_MAX 30
#define T_REG_DADOS 160
#define T_DADOS 1600
#define T_CAB_IND 93

// Struct para um índice
typedef struct {
    long chave;
    long ptr;
} indice;

// Struct para o cabeçalho do arquivo de índice
typedef struct{
    char status;
    int noRaiz;
    int RRNproxNo;
} cab_indice;

typedef struct{
    char folha;
    int nroChavesNo;
    int RRNdoNo;
    int P1;
    long C1;
    long PR1;
    int P2;
    long C2;
    long PR2;
    int P3;
    long C3;
    long PR3;
    int P4;
    long C4;
    long PR4;
    int P5;
} no_indice;

// Funções de uso comum
int leitura_variavel(char *, FILE*);
void escrever(no_indice, FILE*);

// Funções respectivas de cada funcionalidade do projeto
void ex7();
void cabecalho_indice(FILE*, FILE*);
void encontra_nome(FILE*, char*, indice*);
void inserir(indice, FILE*);

#endif