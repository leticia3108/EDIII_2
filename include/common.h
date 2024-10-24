#ifndef COMMON_H
#define COMMON_H

int leitura_variavel(char*, FILE*);
int sobreescreve_dado (FILE*, DADO);
void imprime_dado(FILE*, DADO*);
char* le_elemento(FILE*);
void criar_cabecalho(FILE*, CABECALHO);
void escreve_dados(FILE*, FILE*);
void le_dados(FILE*, FILE*);
no_indice cria_nova_raiz(FILE*, int);
void escrever(no_indice, FILE*);
void sobreescrever(no_indice, FILE*, int);
void lerNo(no_indice*, int, FILE*);
void reordena_no(FILE*, int, int, int);
void insere_com_espaco(FILE*, indice, int, int);
void insere_sem_espaco(FILE*, indice, no_indice*, int);
void ajustaCabecalho (FILE*, char, int, int);
void inserir(indice, FILE*, int);
void imprime_arvore(FILE*, int);



#endif