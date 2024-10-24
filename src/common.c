/*
Arquivo com as funções usadas no resto do projeto
*/

#include "header.h"
int proxRRN = 0;

/* A seguinte função lê uma string variável do arquivo binário na posição
atual e retorna o desvio do arquivo (considerando o delimitador) */
int leitura_variavel(char* str, FILE* binario_entrada){

    char* c = malloc(sizeof(char));
    if (feof(binario_entrada)){
        free(c);
        return -1;
    }
    fread(c, sizeof(char), 1, binario_entrada);

    int i = 0;
    while (*c != '#'){
        str[i] = *c;
        if (feof(binario_entrada)){
            free(c);
            return -1;
        }
        fread(c, sizeof(char), 1, binario_entrada);
        i++;
    }
        str[i] = '\0';
        i++;
        free(c);
    return i;
}

no_indice cria_nova_raiz(FILE* binario_saida, int RRNNovaRaiz){
    no_indice no;
    no.folha = '0';
    no.nroChavesNo = 0;
    no.RRNdoNo = RRNNovaRaiz;
    no.C1 = -1;
    no.C2 = -1;
    no.C3 = -1;
    no.C4 = -1;
    no.P1 = -1;
    no.P2 = -1;
    no.P3 = -1;
    no.P4 = -1;
    no.P5 = -1;
    no.PR1 = -1;
    no.PR2 = -1;
    no.PR3 = -1;
    no.PR4 = -1;
    
    printf("# Criando nova raiz\n");
    escrever(no, binario_saida);

    // Atualização do RRN da raiz (cabeçalho)
    fseek(binario_saida, 1, SEEK_SET);
    fwrite(&RRNNovaRaiz, sizeof(int), 1, binario_saida);

    printf ("#Novo RRN da raiz = %d\n", RRNNovaRaiz);
    return no;
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

void sobreescrever(no_indice no, FILE* binario_saida, int RRN){

//printf("Escrevendo...\n");

fseek(binario_saida,(1+RRN)*93,SEEK_SET);

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

void lerNo(no_indice* no, int RRN, FILE* bin){

        fseek(bin, (RRN+1)*93, SEEK_SET);
        fread(&(no->folha), sizeof(char), 1, bin);
        fread(&(no->nroChavesNo), sizeof(int), 1, bin);
        fread(&(no->RRNdoNo), sizeof(int), 1, bin);

        fread(&(no->P1), sizeof(int), 1, bin);

        fread(&(no->C1), sizeof(long), 1, bin);
        fread(&(no->PR1), sizeof(long), 1, bin);

        fread(&(no->P2), sizeof(int), 1, bin);

        fread(&(no->C2), sizeof(long), 1, bin);
        fread(&(no->PR2), sizeof(long), 1, bin);

        fread(&(no->P3), sizeof(int), 1, bin);

        fread(&(no->C3), sizeof(long), 1, bin);
        fread(&(no->PR3), sizeof(long), 1, bin);

        fread(&(no->P4), sizeof(int), 1, bin);

        fread(&(no->C4), sizeof(long), 1, bin);
        fread(&(no->PR4), sizeof(long), 1, bin);

        fread(&(no->P5), sizeof(int), 1, bin); 
}

void reordena_no(FILE* binario_saida, int RRNno, int nroChaves, int p1){

    indice ind_vect[ORDEM_B-1];
    indice temp;

    fseek(binario_saida, (RRNno+1)*93 + 9, SEEK_SET);

    fread(&ind_vect[0].p1, sizeof(int), 1, binario_saida);

    printf("ind_vect[0].p1 = %d\n", ind_vect[0].p1);

    fread(&ind_vect[0].chave, sizeof(long), 1, binario_saida);
    fread(&ind_vect[0].pr, sizeof(long), 1, binario_saida);
    ind_vect[0].novo = 0;

    for (int i = 1; i < nroChaves; i++){
        fread(&ind_vect[i].p1, sizeof(int), 1, binario_saida);
        ind_vect[i-1].p2 = ind_vect[i].p1;
        printf("ind_vect[%d].p2 = %d\n", i, ind_vect[i-1].p2);
        fread(&ind_vect[i].chave, sizeof(long), 1, binario_saida);
        fread(&ind_vect[i].pr, sizeof(long), 1, binario_saida);
        ind_vect[i].novo = 0;
    }

    ind_vect[nroChaves-1].novo = 1;
    ind_vect[nroChaves-1].p1 = p1;

    fread(&ind_vect[nroChaves-1].p2, sizeof(int), 1, binario_saida);

  //  printf("nroChave = %d, chaves = %ld %ld %ld %ld\n",
  //  nroChaves, ind_vect[0].chave, ind_vect[1].chave,ind_vect[2].chave,ind_vect[3].chave);

    for (int j = 0; j < nroChaves-1; j++){
    for(int i = 0; i < nroChaves-1; i++){

    if (ind_vect[i].chave > ind_vect[i+1].chave){

    temp.p1 = ind_vect[i].p1;
    temp.chave = ind_vect[i].chave;
    temp.pr = ind_vect[i].pr;
    temp.p2 = ind_vect[i].p2;
    temp.novo = ind_vect[i].novo;

    ind_vect[i].p1 = ind_vect[i+1].p1;
    ind_vect[i].chave = ind_vect[i+1].chave;
    ind_vect[i].pr = ind_vect[i+1].pr;
    ind_vect[i].p2 = ind_vect[i+1].p2;
    ind_vect[i].novo = ind_vect[i+1].novo;

    ind_vect[i+1].p1 =  temp.p1;
    ind_vect[i+1].chave =  temp.chave;
    ind_vect[i+1].pr = temp.pr;
    ind_vect[i+1].p2 =  temp.p2;
    ind_vect[i+1].novo = temp.novo;

    } }}

  //  printf("nroChave = %d, chaves = %ld %ld %ld %ld\n",
   // nroChaves, ind_vect[0].chave, ind_vect[1].chave,ind_vect[2].chave,ind_vect[3].chave);

    fseek(binario_saida, (RRNno+1)*93 + 9, SEEK_SET);

    fwrite(&ind_vect[0].p1, sizeof(int), 1, binario_saida);

    printf("#(%d) ", ind_vect[0].p1);

        for (int i = 0; i < nroChaves; i++){
            fwrite(&ind_vect[i].chave, sizeof(long), 1, binario_saida);
            fwrite(&ind_vect[i].pr, sizeof(long), 1, binario_saida);
            fwrite(&ind_vect[i].p2, sizeof(int), 1, binario_saida);
            printf("#%ld (%d)", ind_vect[i].chave, ind_vect[i].p2);
        }
    printf("#\n");
}

void insere_com_espaco(FILE* binario_saida, indice ind, int nroChaves, int RRN){

    nroChaves++;
    fseek(binario_saida, (RRN+1)*93+ 1, SEEK_SET);
    fwrite(&nroChaves, sizeof(int), 1, binario_saida);

    printf("#(%d %d)\n ",ind.p1, ind.p2);

    if (nroChaves == 1){
        printf("Inserindo nova raiz (%d) %ld (%d) com ponteiro %ld em %d (com espaço - nroChaves = %d) \n",ind.p1, ind.chave, ind.p2, ind.pr, RRN, nroChaves);
        fseek(binario_saida, (RRN+1)*93 + 9 + 20*(nroChaves-1), SEEK_SET);
        fwrite(&ind.p1, sizeof(int),1, binario_saida);
        fwrite(&ind.chave, sizeof(long),1, binario_saida);
        fwrite(&ind.pr, sizeof(long),1, binario_saida);
        fwrite(&ind.p2, sizeof(int),1, binario_saida);
        return;
    }

    fseek(binario_saida, (RRN+1)*93 + 13 + 20*(nroChaves-1), SEEK_SET);
    fwrite(&ind.chave, sizeof(long),1, binario_saida);
    fwrite(&ind.pr, sizeof(long),1, binario_saida);
    fwrite(&ind.p2, sizeof(int),1, binario_saida);

    printf("Inserindo chave %ld com ponteiro %ld em %d (com espaço - nroChaves = %d) \n", ind.chave, ind.pr, RRN, nroChaves);

    reordena_no(binario_saida, RRN, nroChaves, ind.p1);

}

void insere_sem_espaco(FILE* binario_saida, indice ind, no_indice* caminho, int i){

    printf("Inserindo (%ld) sem espaço em (%d), int i = %d", ind.chave, caminho[i].RRNdoNo, i);

    int RRN = caminho[i].RRNdoNo;
    indice ind_vect[ORDEM_B];
    indice temp;

    // Inserir todos os elementos do nó em ind_vect
    ind_vect[0].p1 = caminho[i].P1;
    ind_vect[0].chave = caminho[i].C1;
    ind_vect[0].pr = caminho[i].PR1;
    ind_vect[0].p2 = caminho[i].P2;
    ind_vect[0].novo = 0;

    ind_vect[1].p1 = caminho[i].P2;
    ind_vect[1].chave = caminho[i].C2;
    ind_vect[1].pr = caminho[i].PR2;
    ind_vect[1].p2 = caminho[i].P3;
    ind_vect[1].novo = 0;

    ind_vect[2].p1 = caminho[i].P3;
    ind_vect[2].chave = caminho[i].C3;
    ind_vect[2].pr = caminho[i].PR3;
    ind_vect[2].p2 = caminho[i].P4;
    ind_vect[2].novo = 0;

    ind_vect[3].p1 = caminho[i].P4;
    ind_vect[3].chave = caminho[i].C4;
    ind_vect[3].pr = caminho[i].PR4;
    ind_vect[3].p2 = caminho[i].P5;
    ind_vect[3].novo = 0;

    // Inserir o novo elemento em ind_vect
    ind_vect[4].p1 = ind.p1;
    ind_vect[4].chave = ind.chave;
    ind_vect[4].pr = ind.pr;
    ind_vect[4].p2 = ind.p2;
    ind_vect[4].novo = 1;
    
    // Ordenar o vetor de indices
    for (int j = 0; j < ORDEM_B-1; j++){
        for(int k = 0; k < ORDEM_B-1; k++){

            if (ind_vect[k].chave > ind_vect[k+1].chave){

            temp.p1 = ind_vect[k].p1;
            temp.chave = ind_vect[k].chave;
            temp.pr = ind_vect[k].pr;
            temp.p2 = ind_vect[k].p2;
            temp.novo = ind_vect[k].novo;

            ind_vect[k].p1 = ind_vect[k+1].p1;
            ind_vect[k].chave = ind_vect[k+1].chave;
            ind_vect[k].pr = ind_vect[k+1].pr;
            ind_vect[k].p2 = ind_vect[k+1].p2;
            ind_vect[k].novo = ind_vect[k+1].novo;

            ind_vect[k+1].p1 =  temp.p1;
            ind_vect[k+1].chave =  temp.chave;
            ind_vect[k+1].pr = temp.pr;
            ind_vect[k+1].p2 =  temp.p2;
            ind_vect[k+1].novo = temp.novo;

        } }}

    no_indice* no = malloc(sizeof(no_indice));

    no->folha = caminho[i].folha;
    no->nroChavesNo = 2;
    no->RRNdoNo = ++proxRRN;

    if(ind_vect[3].novo == 1)
        no->P1= ind_vect[3].p1;
    else
        no->P1 = ind_vect[2].p2;

    no->C1 = ind_vect[3].chave;
    no->PR1 = ind_vect[3].pr;

    if(ind_vect[3].novo == 1)
        no->P2 = ind_vect[3].p2;
    else
        no->P2 = ind_vect[4].p1;

    no->C2 = ind_vect[4].chave;
    no->PR2 = ind_vect[4].pr;

    no->P3 = ind_vect[4].p2;
    

    no->PR3 = -1;
    no->C3 = -1;
    no->P4 = -1;
    no->PR4 = -1;
    no->P5 = -1;

    // Criar um novo registro com a metade direita do atual
    escrever(*no, binario_saida);

    // Atualizar o registro atual com a metade esquerda
    no->folha = caminho[i].folha;
    no->nroChavesNo = 2;
    no->RRNdoNo = caminho[i].RRNdoNo;

    no->P1= ind_vect[0].p1;
    no->C1 = ind_vect[0].chave;
    no->PR1 = ind_vect[0].pr;

    if(ind_vect[0].novo == 1)
        no->P2 = ind_vect[0].p2;
    else
        no->P2 = ind_vect[1].p1;

    no->C2 = ind_vect[1].chave;
    no->PR2 = ind_vect[1].pr;

    if(ind_vect[2].novo == 1)
        no->P3 = ind_vect[2].p1;
    else
        no->P3 = ind_vect[1].p2;

    no->PR3 = -1;
    no->C3 = -1;
    no->P4 = -1;
    no->PR4 = -1;
    no->P5 = -1;

    sobreescrever(*no, binario_saida, caminho[i].RRNdoNo);

    // Atualizar os ponteiros do nó que sobe
    ind_vect[2].p1 = RRN;
    ind_vect[2].p2 = proxRRN;
    printf("#\n SOBE COM RRN = %d proxRRN = %d (%d %d)\n ",RRN, proxRRN, ind_vect[2].p1, ind_vect[2].p2);

    if ((caminho[i-1].nroChavesNo < (ORDEM_B-1)) && i >= 1){
        insere_com_espaco(binario_saida, ind_vect[2], caminho[i-1].nroChavesNo, caminho[i-1].RRNdoNo);
        printf("#->insere com espaco caminho[%d].RRNdoNo = %d\n", i-1, caminho[i-1].RRNdoNo);
    } else {
        if (i == 0){
            no_indice noNovaRaiz = cria_nova_raiz(binario_saida, proxRRN+1);
            printf("#\n RRN = %d proxRRN = %d (%d %d)\n ",RRN, proxRRN, ind_vect[2].p1, ind_vect[2].p2);
            proxRRN++;
            printf("->->-> Uma nova raiz foi criada com RRN = %d", noNovaRaiz.RRNdoNo);
            insere_com_espaco(binario_saida, ind_vect[2], 0, noNovaRaiz.RRNdoNo);
        } else {
            i--;
            insere_sem_espaco(binario_saida, ind_vect[2], caminho, i);
        }
    }

    free(no);

}

void ajustaCabecalho (FILE* fbin, char status, int noRaiz, int RRNproxNo){
    
    fseek (fbin, 0, SEEK_SET);
    fwrite (&status, sizeof(char), 1, fbin);
    fwrite (&noRaiz, sizeof(int), 1, fbin);
    fwrite (&proxRRN, sizeof(int), 1, fbin);

    // Reescrever
}

void inserir(indice ind, FILE* binario_saida, int RRNraiz){

    no_indice* no = malloc (sizeof(no_indice));
    no_indice* caminho = malloc (sizeof(indice) * 30);
    int i = 0;
    int RRN;

    // Se o arquivo ainda não tiver um registro raiz, cria um
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
        ajustaCabecalho (binario_saida, '0', 0, 1);
    } else{

        // Ler o nó raiz e adicioná-lo ao vetor de caminho
        lerNo(no, RRNraiz, binario_saida);
        lerNo(&(caminho[i]), RRNraiz, binario_saida);

        RRN = RRNraiz;

        // Se o no da raiz não for um nó folha, encontre o nó folha e armazene o caminho até ele
        if(no->folha == '0'){
            if (ind.chave < no->C1){
                RRN = no->P1;}
            else if(ind.chave < no->C2){
                RRN = no->P2;
            }
            else if(ind.chave < no->C3)
                RRN = no->P3;
            else if(ind.chave < no->C4)
                RRN = no->P4;
            else
                if (no->C2 == -1)
                    RRN = no->P2;
                else if (no->C3 == -1)
                    RRN = no->P3;
                else if (no->C4 == -1)
                    RRN = no->P4;
                else
                    RRN = no->P5;

            i++;
            lerNo(no, RRN, binario_saida);
            lerNo(&(caminho[i]), RRN, binario_saida);

            while(no->folha == 0){

                if (ind.chave < no->C1)
                    RRN = no->P1;
                else if(ind.chave < no->C2)
                    RRN = no->P2;
                else if(ind.chave < no->C3)
                    RRN = no->P3;
                else if(ind.chave < no->C4)
                    RRN = no->P4;
                else
                    RRN = no->P5;
            
            i++;
            lerNo(no, RRN, binario_saida);
            lerNo(&(caminho[i]), RRN, binario_saida);
            }

        }
        // Inserir no nó folha

            if (no->nroChavesNo < ORDEM_B - 1){
                insere_com_espaco(binario_saida, ind, no->nroChavesNo, RRN);
            } else {
                insere_sem_espaco(binario_saida, ind, caminho, i);
            }
    
    }

    //free(no);
    free(caminho);
}

void imprime_arvore(FILE* binario_saida, int RRN){

    no_indice no;

    fseek(binario_saida, 93*(1+30), SEEK_SET);

    fread(&no.folha, sizeof(char), 1, binario_saida);
    fread(&no.nroChavesNo, sizeof(int), 1, binario_saida);
    fread(&no.RRNdoNo, sizeof(int), 1, binario_saida);

    fread(&no.P1, sizeof(int), 1, binario_saida);

    fread(&no.C1, sizeof(long), 1, binario_saida);
    fread(&no.PR1, sizeof(long), 1, binario_saida);

    fread(&no.P2, sizeof(int), 1, binario_saida);

    fread(&no.C2, sizeof(long), 1, binario_saida);
    fread(&no.PR2, sizeof(long), 1, binario_saida);

    fread(&no.P3, sizeof(int), 1, binario_saida);

    fread(&no.C3, sizeof(long), 1, binario_saida);
    fread(&no.PR3, sizeof(long), 1, binario_saida);

    fread(&no.P4, sizeof(int), 1, binario_saida);

    fread(&no.C4, sizeof(long), 1, binario_saida);
    fread(&no.PR4, sizeof(long), 1, binario_saida);

    fread(&no.P5, sizeof(int), 1, binario_saida);

    printf(" = (%d) %ld (%d) %ld (%d) %ld (%d) %ld (%d)\n", no.P1, no.C1, no.P2, no.C2, no.P3, no.C3, no.P4, no.C4, no.P5);
    
    if (no.P1 != -1){
        printf("P1");
        imprime_arvore(binario_saida, no.P1);}
    if (no.P2 != -1){
        printf("P2");
        imprime_arvore(binario_saida, no.P2);}
    if (no.P3!= -1){
        printf("P3");
        imprime_arvore(binario_saida, no.P3);}
    if (no.P4!= -1){
        printf("P4");
        imprime_arvore(binario_saida, no.P4);}
    if (no.P5!= -1){
        printf("P5");
        imprime_arvore(binario_saida, no.P5);}
}
