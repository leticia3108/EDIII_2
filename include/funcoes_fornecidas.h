#ifndef FUNCOES_FORNECIDAS_H
#define FUNCOES_FORNECIDAS_H

void binarioNaTela(char *);
void scan_quote_string(char *);
long converteNome (char*);


typedef struct {
    char removido;
    int encadeamento;
    int populacao;
    float tamanho;
    char unidadeMedida;
    int velocidade;
    char nome[50];
    char especie[50];
    char habitat[50];
    char tipo[50];
    char dieta[50];
    char alimento[50];
} DADO;

typedef struct {
    char status;
    int topo;
    int proxRRN;
    int nroRegRem;
    int nroPagDisco;
    int qttCompacta;
} CABECALHO;

#endif