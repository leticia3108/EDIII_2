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

// Funções de uso comum
int leitura_variavel(char *, FILE*);

// Funções respectivas de cada funcionalidade do projeto
void ex7();

#endif