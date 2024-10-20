#ifndef COMMON_H
#define COMMON_H

int leitura_variavel(char*, FILE*);
void escrever(no_indice, FILE*);
void inserir(indice ind, FILE* binario_saida, int RRNraiz);
void cabecalho_indice(FILE*, FILE*);
void encontra_nome(FILE*, char*, indice*);


#endif