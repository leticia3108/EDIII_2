/*
* Header principal do projeto.
* 
* Aqui se concentra a declaração das funções utilizadas ao longo do projeto,
* bem como as funções fornecidas pelo professor e pelos monitores da disciplina
* 
*/
#ifndef MAIN_H
#define MAIN_H


// Definições
#define T_MAX 30
#define T_REG_DADOS 160
#define T_DADOS 1600
#define T_CAB_IND 93
#define ORDEM_B 5
#define TAM_DISCO 1600

// Struct para um índice
typedef struct {
    int p1;
    long chave;
    long pr;
    int p2;
    int novo;
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


#endif