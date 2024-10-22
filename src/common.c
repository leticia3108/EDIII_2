/*
Arquivo com as funções usadas no resto do projeto
*/

#include "header.h"

int proxRRN = 0;

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

int cria_nova_raiz(FILE* binario_saida, int RRNNovaRaiz){
    no_indice* no = malloc (sizeof(no));
    no->folha = '0';
    no->nroChavesNo = 0;
    no->RRNdoNo = RRNNovaRaiz;
    no->C1 = -1;
    no->C2 = -1;
    no->C3 = -1;
    no->C4 = -1;
    no->P1 = -1;
    no->P2 = -1;
    no->P3 = -1;
    no->P4 = -1;
    no->P5 = -1;
    no->PR1 = -1;
    no->PR2 = -1;
    no->PR3 = -1;
    no->PR4 = -1;
    
    escrever(*no, binario_saida);

    // Atualização do RRN da raiz (cabeçalho)
    fseek(binario_saida, 1, SEEK_SET);
    fwrite(&RRNNovaRaiz, sizeof(int), 1, binario_saida);

    return RRNNovaRaiz;
}

void escrever(no_indice no, FILE* binario_saida){

//printf("Escrevendo...\n");

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

void reordena_no(FILE* binario_saida, int RRNno, int nroChaves){

    indice ind_vect[ORDEM_B-1];
    indice temp;

    fseek(binario_saida, (RRNno+1)*93 + 9, SEEK_SET);

    for (int i = 0; i < nroChaves; i++){
    fread(&ind_vect[i].p1, sizeof(int), 1, binario_saida);
    fread(&ind_vect[i].chave, sizeof(long), 1, binario_saida);
    fread(&ind_vect[i].pr, sizeof(long), 1, binario_saida);
    fread(&ind_vect[i].p2, sizeof(int), 1, binario_saida);
    }

  //  printf("nroChave = %d, chaves = %ld %ld %ld %ld\n",
  //   nroChaves, ind_vect[0].chave, ind_vect[1].chave,ind_vect[2].chave,ind_vect[3].chave);

    for (int j = 0; j < nroChaves-1; j++){
    for(int i = 0; i < nroChaves-1; i++){

    if (ind_vect[i].chave > ind_vect[i+1].chave){

    temp.p1 = ind_vect[i].p1;
    temp.chave = ind_vect[i].chave;
    temp.pr = ind_vect[i].pr;
    temp.p2 = ind_vect[i].p2;

    ind_vect[i].p1 = ind_vect[i+1].p1;
    ind_vect[i].chave = ind_vect[i+1].chave;
    ind_vect[i].pr = ind_vect[i+1].pr;
    ind_vect[i].p2 = ind_vect[i+1].p2;

    ind_vect[i+1].p1 =  temp.p1;
    ind_vect[i+1].chave =  temp.chave;
    ind_vect[i+1].pr = temp.pr;
    ind_vect[i+1].p2 =  temp.p2;

    } }}

  //  printf("nroChave = %d, chaves = %ld %ld %ld %ld\n",
   // nroChaves, ind_vect[0].chave, ind_vect[1].chave,ind_vect[2].chave,ind_vect[3].chave);

    fseek(binario_saida, (RRNno+1)*93 + 9, SEEK_SET);

    fwrite(&ind_vect[0].p1, sizeof(int), 1, binario_saida);

        for (int i = 0; i < nroChaves; i++){
            fwrite(&ind_vect[i].chave, sizeof(long), 1, binario_saida);
            fwrite(&ind_vect[i].pr, sizeof(long), 1, binario_saida);
            fwrite(&ind_vect[i].p2, sizeof(long), 1, binario_saida);
        }
}

void insere_com_espaco(FILE* binario_saida, indice ind, int nroChaves, int RRNraiz){

    fseek(binario_saida, (RRNraiz+1)*93 + 13 + 20*nroChaves, SEEK_SET);
    fwrite(&ind.chave, sizeof(long),1, binario_saida);

   // printf("Inserindo chave %ld com ponteiro %ld em %d\n (com espaço)", ind.chave, ind.pr, (RRNraiz+1)*93 + 13 + 20*nroChaves);

    nroChaves++;
    reordena_no(binario_saida, RRNraiz, nroChaves);

}

void insere_sem_espaco(FILE* binario_saida, indice ind, int RRNraiz, int RRNpai, char folha){

indice ind_vect[ORDEM_B];
indice temp;

//printf("Inserindo chave %ld com ponteiro %ld em %d \n (sem espaço)", ind.chave, ind.pr, RRNpai);

proxRRN++;

fseek(binario_saida, (RRNraiz+1)*93 + 9, SEEK_SET);

for (int i = 0; i < ORDEM_B; i++){
    fread(&ind_vect[i].p1, sizeof(int), 1, binario_saida);
    fread(&ind_vect[i].chave, sizeof(long), 1, binario_saida);
    fread(&ind_vect[i].pr, sizeof(long), 1, binario_saida);
}

ind_vect[4].p1 = ind.p1;
ind_vect[4].chave = ind.chave;
ind_vect[4].pr =  ind.pr;
ind_vect[4].p2 = ind.p2;

// Ordenar o vetor de indices
for (int j = 0; j < ORDEM_B-1; j++){
    for(int i = 0; i < ORDEM_B-1; i++){

        if (ind_vect[i].chave > ind_vect[i+1].chave){

        temp.p1 = ind_vect[i].p1;
        temp.chave = ind_vect[i].chave;
        temp.pr = ind_vect[i].pr;
        temp.p2 = ind_vect[i].p2;

        ind_vect[i].p1 = ind_vect[i+1].p1;
        ind_vect[i].chave = ind_vect[i+1].chave;
        ind_vect[i].pr = ind_vect[i+1].pr;
        ind_vect[i].p2 = ind_vect[i+1].p2;

        ind_vect[i+1].p1 =  temp.p1;
        ind_vect[i+1].chave =  temp.chave;
        ind_vect[i+1].pr = temp.pr;
        ind_vect[i+1].p2 =  temp.p2;

    } }}

    no_indice* no = malloc(sizeof(no_indice));

    no->folha = folha;
    no->nroChavesNo = 2;
    no->RRNdoNo = proxRRN;

    no->P1= ind_vect[3].p1;
    no->C1 = ind_vect[3].chave;
    no->PR1 = ind_vect[3].pr;

    no->P2 = ind_vect[4].p1;
    no->C2 = ind_vect[4].chave;
    no->PR2 = ind_vect[4].pr;

    no->P3 = -1;
    no->PR3 = -1;
    no->C3 = -1;
    no->P4 = -1;
    no->PR4 = -1;
    no->P5 = -1;

    // Criar um novo registro com a metade direita do atual
    escrever(*no, binario_saida);
    
    // Atualizar o nroChaves do registro atual
    fseek(binario_saida, (RRNraiz+1)*93 + 1, SEEK_SET);
    fwrite(&(no->nroChavesNo), sizeof(int), 1, binario_saida);

    // Apagar a segunda metade do registro atual
    fseek(binario_saida, (RRNraiz+1)*93 + 9 + 2*20, SEEK_SET);

    for (int i = 0; i < 2; i++){
    fwrite(&(no->P3), sizeof(int), 1, binario_saida);
    fwrite(&(no->PR3), sizeof(long), 1, binario_saida);
    fwrite(&(no->C3), sizeof(long), 1, binario_saida);
    }
    fwrite(&(no->P3), sizeof(int), 1, binario_saida);

    ind_vect[2].p1 = RRNraiz;
    ind_vect[2].p2 = proxRRN;

    int PRaiz = 0;
    int nroChavesPai = 0;

    fseek(binario_saida, 1, SEEK_SET);
    fread(&PRaiz, sizeof(int), 1, binario_saida);

    fseek(binario_saida, 96*(RRNpai+1)+1, SEEK_SET);
    fread(&nroChavesPai, sizeof(int), 1, binario_saida);

    if (nroChavesPai < (ORDEM_B-1))
        insere_com_espaco(binario_saida, ind_vect[ORDEM_B/2], nroChavesPai, RRNpai);
    else{
        if(PRaiz == RRNpai){
            RRNpai = cria_nova_raiz(binario_saida, proxRRN+1);}
        insere_sem_espaco(binario_saida,ind_vect[ORDEM_B/2], RRNraiz, RRNpai, folha);
    }
    free(no);
}

/* Faz a inserção do nó índice na árvore B    */
void inserir(indice ind, FILE* binario_saida, int RRNraiz, int RRNpai){

   // printf("Inserindo... \n");
   // printf("(%ld-%d)\n", pos, RRNraiz);

    no_indice* no = malloc (sizeof(no_indice));
  
    char folha;
    int nroChaves = 0;
    long chave, PR;
    int P1, P2;


    if (RRNraiz == -1){

        no->folha = '1';
        no->nroChavesNo = 1;
        no->RRNdoNo = 0;
        no->P1 = -1;
        no->C1 = ind.chave;
        no->PR1 = ind.pr;
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
        RRNraiz = 0;
        fseek(binario_saida, 1, SEEK_SET);
        fwrite(&RRNraiz, sizeof(int), 1, binario_saida);

    } else {

        //Ir para o nó raiz
        fseek(binario_saida, (RRNraiz+1)*93, SEEK_SET);

        fread(&folha, sizeof(char), 1, binario_saida);
       // printf("folha = (%c)", folha);
        fread(&nroChaves,sizeof(int),1,binario_saida);
        fread(&RRNpai, sizeof(int), 1, binario_saida); //Atualizar



        if(folha == '0'){

        for (int i=0; i<nroChaves; i++){

          
          fseek(binario_saida, (RRNraiz+1)*93 + 9 + (i*20), SEEK_SET);

          fread(&P1,sizeof(int),1,binario_saida);
          fread(&chave,sizeof(long),1,binario_saida);
          fread(&PR,sizeof(long),1,binario_saida);
          fread(&P2,sizeof(int),1,binario_saida);

          if(ind.chave < chave){
            inserir(ind, binario_saida, P1, RRNpai);
            break;
          } 
        }
            inserir(ind, binario_saida, P2, RRNpai);
        } else if(folha == '1'){

            // Caso seja um nó folha:

            //printf("Inserindo em uma folha\n");
            // Inserir o elemento na árvore caso tenha espaço
            if (nroChaves < 4){
                insere_com_espaco(binario_saida, ind, nroChaves, RRNraiz);
               // printf("Inserindo no nó folha com espaço\n");

                // Atualizar nroChaves
                fseek(binario_saida, (RRNraiz+1)*93 + 1, SEEK_SET);
                nroChaves++;
                fwrite(&nroChaves,sizeof(int),1,binario_saida);

                return;
            } else {
            // Inserir um elemento caso não tenha espaço
                insere_sem_espaco(binario_saida, ind, RRNraiz, RRNpai, folha);
                return;
            }
        }

    }

    free(no);
}