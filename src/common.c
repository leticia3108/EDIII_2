/*
Arquivo com as funções usadas no resto do projeto
*/


#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "../include/main.h"
#include "../include/funcoes_fornecidas.h"
#include "../include/common.h"


/* A seguinte função lê uma string variável do arquivo binário na posição
atual e retorna o desvio do arquivo (considerando o delimitador) */
int leitura_variavel(char* str, FILE* binario_entrada){

    char* c = malloc(sizeof(char));
    fread(c, sizeof(char), 1, binario_entrada);

    int i = 0;
    while (*c != '#'){
        str[i] = *c;
        fread(c, sizeof(char), 1, binario_entrada);
        i++;
    }
        str[i] = '\0';
        i++;
        free(c);
    return i;
}

void escrever(no_indice no, FILE* binario_saida){

    printf("Escrevendo...\n");

fseek(binario_saida,0,SEEK_END);

fwrite(&no.folha, sizeof(char), 1, binario_saida);
fwrite(&no.nroChavesNo, sizeof(int), 1, binario_saida);
fwrite(&no.RRNdoNo, sizeof(int), 1, binario_saida);


fwrite(&no.P1, sizeof(int), 1, binario_saida);


fwrite(&no.C1, sizeof(long), 1, binario_saida);

fwrite(&no.PR1, sizeof(long), 1, binario_saida);

fwrite(&no.P2, sizeof(int), 1, binario_saida);

fwrite(&no.C2, sizeof(long), 1, binario_saida);
fwrite(&no.PR2, sizeof(long), 1, binario_saida);

fwrite(&no.P3, sizeof(int), 1, binario_saida);

fwrite(&no.C3, sizeof(long), 1, binario_saida);
fwrite(&no.PR3, sizeof(long), 1, binario_saida);

fwrite(&no.P4, sizeof(int), 1, binario_saida);

fwrite(&no.C4, sizeof(long), 1, binario_saida);
fwrite(&no.PR4, sizeof(long), 1, binario_saida);

fwrite(&no.P5, sizeof(int), 1, binario_saida); 
fflush(binario_saida);

}

/* Faz a inserção do nó índice na árvore B    */
void inserir(indice ind, FILE* binario_saida, int RRNraiz){

    printf("Inserindo... \n");
   // printf("(%ld-%d)\n", pos, RRNraiz);

    no_indice* no = malloc (sizeof(no_indice));
  
    char folha;
    int nroChaves;
    int RRRdoNo;
    long chave1;
    long P;

    if (RRNraiz == -1){

        no->folha = '1';
        no->nroChavesNo = 1;
        no->RRNdoNo = 0;
        no->P1 = -1;
        no->C1 = ind.chave;
        no->PR1 = ind.ptr;
        no->P2 = -1;
        no->C2 = -1;
        no->PR2 = -1;
        no->P3 = -1;
        no->C3 = -1;
        no->PR3 = -1;
        no->P4 = -1;
        no->C4 = -1;
        no->PR4 = -1;
        no->P5 = -1;

        escrever(*no, binario_saida);
    } else {

        //Ir para o nó raiz
        fseek(binario_saida, (RRNraiz+1)*93, SEEK_SET);

        fread(&folha, sizeof(char), 1, binario_saida);
        fread(&nroChaves,sizeof(int),1,binario_saida);

        if(folha == '0'){

        for (int i=0; i<nroChaves; i++){

          
          fseek(binario_saida, (RRNraiz+1)*93 + 9 + (i*20), SEEK_SET);

          fread(&P,sizeof(int),1,binario_saida);
          fread(&(ind.chave),sizeof(long),1,binario_saida);

          if(ind.chave < chave1){
            inserir(ind, binario_saida, P);
          } 
        }
        } else if(folha == '1'){

            // Caso seja um nó folha:

            // Inserir o elemento na árvore caso tenha espaço
            if (nroChaves < 4){
            
            fseek(binario_saida, (RRNraiz+1)*93 + 13 + 20*nroChaves, SEEK_SET);
            fwrite(&(ind.chave), sizeof(long),1, binario_saida);
            fwrite(&ind.ptr, sizeof(int), 1, binario_saida);


            // FUNÇÃO PARA REORDENAR A ÁRVORE AQUI

            }
        }

    }

    free(no);
}

/* A Função find_name busca o nome e a chave do registro, pula para 
o próximo registro e salva os resultados na struct de indice */

void cabecalho_indice(FILE* fbin, FILE* fbin_ind){
    // Escreve a versão inicial do cabeçalho
    cab_indice cabecalho;

    cabecalho.status = '0';
    cabecalho.noRaiz = -1;
    cabecalho.RRNproxNo = 0;

    fwrite(&cabecalho.status, sizeof(char), 1, fbin_ind);
    fwrite(&cabecalho.noRaiz, sizeof(int), 1, fbin_ind);
    fwrite(&cabecalho.RRNproxNo, sizeof(int), 1, fbin_ind);

    // Deixa todas os demais endereços do disco setados com $
    for (int i = 0; i < (T_CAB_IND - 9); i++){
    fwrite("$", sizeof(char), 1, fbin_ind);
    }
}

void encontra_nome(FILE* fbin, char* nome, indice* ind){
    char* c = malloc(1*sizeof(char)); 

    fread(c, sizeof(char), 1, fbin);
    while ((*c) == '1'){
        fseek(fbin, T_REG_DADOS-1, SEEK_CUR);
        fread(c, sizeof(char), 1, fbin);
    }

    fseek(fbin, 17, SEEK_CUR);
    long pular = (long) leitura_variavel(nome, fbin);
   // printf("%s", nome);
    fseek(fbin, T_REG_DADOS - pular - 18, SEEK_CUR);

    free(c);
    ind->ptr = (ftell(fbin)-1600)/160 - 1;
    ind->chave = converteNome(nome);
 //   printf("Inserido dado %ld-%ld\n", ind->chave, ind->ptr);
}
