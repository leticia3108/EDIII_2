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

#define TAM_ELEMENTO 50

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

int sobreescreve_dado (FILE* binario_entrada, DADO dado){

int encadeamento;
char rem = 0;

fwrite(&rem, 1, sizeof(char), binario_entrada);
fread(&encadeamento, sizeof(int), 1, binario_entrada);
fwrite(&dado.populacao, sizeof(int), 1, binario_entrada);
fwrite(&dado.tamanho, sizeof(float), 1, binario_entrada);
fwrite(&dado.unidadeMedida, sizeof(char), 1, binario_entrada);
fwrite(&dado.velocidade, sizeof(int), 1, binario_entrada);
fwrite(&dado.nome, strlen(dado.nome), 1, binario_entrada);
fwrite(&dado.especie, strlen(dado.especie), 1, binario_entrada);
fwrite(&dado.habitat, strlen(dado.habitat), 1, binario_entrada);
fwrite(&dado.tipo, strlen(dado.tipo), 1, binario_entrada);
fwrite(&dado.dieta, strlen(dado.dieta), 1, binario_entrada);
fwrite(&dado.alimento, strlen(dado.alimento), 1, binario_entrada);

return encadeamento;
}

void imprime_dado(FILE* binario_entrada, DADO* dado){

        int dado_removido;

        fread (&(dado->removido), sizeof(char), 1, binario_entrada);
        if (dado->removido == '0'){
            int pular = 0;
            fseek(binario_entrada, 8, SEEK_CUR);


            fread(&(dado->tamanho), sizeof(float), 1, binario_entrada);
            fread(&(dado->unidadeMedida), sizeof(char), 1, binario_entrada);
            fread(&(dado->velocidade), sizeof(int), 1, binario_entrada);
 
            pular += 18;          
            pular += leitura_variavel(dado->nome, binario_entrada);
            pular += leitura_variavel(dado->especie, binario_entrada);
            pular += leitura_variavel(dado->habitat, binario_entrada);
            pular += leitura_variavel(dado->tipo, binario_entrada);
            pular += leitura_variavel(dado->dieta, binario_entrada);
 

        printf("Nome: %s\nEspecie: %s\n", dado->nome, dado->especie);
        
        if (strcmp(dado->tipo, "") != 0)
            printf( "Tipo: %s\n", dado->tipo);

        if (strcmp(dado->dieta, "") != 0)
            printf( "Dieta: %s\n", dado->dieta);

        if (strcmp(dado->habitat, "") != 0)
            printf( "Lugar que habitava: %s\n", dado->habitat);
        
        if (dado->tamanho != -1)
            printf("Tamanho: %.1lf\n", dado->tamanho);
        
        if (dado->velocidade != -1)
            printf("Velocidade: %d %cm/h\n", dado->velocidade, dado->unidadeMedida);
        
        printf("\n");}

}

char* le_elemento(FILE* arquivo_entrada){

    char* elemento = malloc (TAM_ELEMENTO * sizeof(char));
    if (elemento == NULL) {
        printf("Falha na alocacao\n");
    }

    // Caractere lido no arquivo
    char caractere_lido = fgetc(arquivo_entrada);

    // Verifica que não está no final do arquivo
    if (caractere_lido == EOF) {
        // printf("\n\nNao ha nada no arquivo\n\n");
        return NULL;
    }

    // Captura o primeiro dado que não seja espaço ou \0
    while (caractere_lido == ' '|| caractere_lido == '\0'){
        caractere_lido = fgetc(arquivo_entrada);
    }

    int i = 0;
    while(
        caractere_lido != '\n' && 
        caractere_lido != ',' && 
        caractere_lido != EOF && 
        i < TAM_ELEMENTO
        ){

        elemento[i] = caractere_lido;
        i++;
        // printf("%c", caractere_lido);
        caractere_lido = fgetc(arquivo_entrada);
    }
    elemento[i] = '\0';

    // printf("Elemento = (%s) \n", elemento);

    return elemento;
}

void criar_cabecalho(FILE* arquivo_saida, CABECALHO cabecalho){

    fseek(arquivo_saida, 0, SEEK_SET);

    // Escreve os valores do cabeçalho no binário
    fwrite(&cabecalho.status,      sizeof(char), 1, arquivo_saida);
    fwrite(&cabecalho.topo,        sizeof(int),  1, arquivo_saida);
    fwrite(&cabecalho.proxRRN,     sizeof(int),  1, arquivo_saida);
    fwrite(&cabecalho.nroRegRem,   sizeof(int),  1, arquivo_saida);
    fwrite(&cabecalho.nroPagDisco, sizeof(int),  1, arquivo_saida);
    fwrite(&cabecalho.qttCompacta, sizeof(int),  1, arquivo_saida);

    // Deixa todas os demais endereços do disco setados com $
    for (int i = 0; i < (TAM_DISCO - 21); i++){
    fwrite("$", sizeof(char), 1, arquivo_saida);
    }

}


void escreve_dados(FILE* arquivo_entrada, FILE* arquivo_saida){

    // Escreve a versão inicial do cabeçalho
    CABECALHO cabecalho;

    cabecalho.status      =  '0';
    cabecalho.topo        =  -1;
    cabecalho.proxRRN     =   0;
    cabecalho.nroRegRem   =   0;
    cabecalho.nroPagDisco =   1; // Considera a página de cabeçalho
    cabecalho.qttCompacta =   0;

    criar_cabecalho(arquivo_saida, cabecalho);

    int reg     =  0; // Número de registros.
    int reg_pag =  0; // Número de registros em uma página.
    int num_pag =  2; // Número de páginas ocupadas pelo arquivo de dados.
    char* elem;
    DADO str;

    // Le a primeira linha do código e a remove
    char* linha1 = malloc(100 * sizeof(char));
    fgets(linha1, 100, arquivo_entrada);
    free(linha1);

    // Le o primeiro elemento da descricao
    int i = 0;  // Tipo de elemento a ser lido no csv.
    while( (elem = le_elemento(arquivo_entrada)) != NULL ){
        switch(i){
            case 0:
                strcpy(str.nome,elem);
                break;
            case 1:
                strcpy(str.dieta,elem);
                break;
            case 2:
                strcpy(str.habitat,elem);
                break;
            case 3:
                str.populacao = atoi(elem);
                break;
            case 4:
                strcpy(str.tipo,elem);
                break;
            case 5:
                str.velocidade = atoi(elem);
                break;
            case 6:
                str.unidadeMedida = elem[0];
                break;
            case 7:
                str.tamanho = atof(elem);
                break;
            case 8:
                strcpy(str.especie,elem);
                break;
            case 9:
                strcpy(str.alimento,elem);
                break;
        }
        
        // Faz com que passe para o proximo caso
        i = (i + 1) % 10;
        free(elem);

        if (i == 0) {
            char removido    = '0';
            int encadeamento = -1;
            char delim       = '#';
            char lixo        = '$';
            int ac           =  0;

            // Escrever a struct no arquivo binário:
            fwrite(&removido,          sizeof(char),  1, arquivo_saida);
            fwrite(&encadeamento,      sizeof(int),   1, arquivo_saida);
            fwrite(&str.populacao,     sizeof(int),   1, arquivo_saida);
            fwrite(&str.tamanho,       sizeof(float), 1, arquivo_saida);
            fwrite(&str.unidadeMedida, sizeof(char),  1, arquivo_saida);
            fwrite(&str.velocidade,    sizeof(int),   1, arquivo_saida);
            ac += 18;

            ac += strlen(str.nome)+1;
            fwrite(&str.nome, sizeof(char), strlen(str.nome), arquivo_saida);
            fwrite(&delim,    sizeof(char), 1,                arquivo_saida); // Delimitador

            ac += strlen(str.especie)+1;
            fwrite(&str.especie, sizeof(char), strlen(str.especie), arquivo_saida);
            fwrite(&delim,       sizeof(char), 1,                   arquivo_saida); // Delimitador
            ac += strlen(str.habitat)+1;
            fwrite(&str.habitat, sizeof(char), strlen(str.habitat), arquivo_saida);
            fwrite(&delim,       sizeof(char), 1,                   arquivo_saida); // Delimitador
            ac += strlen(str.tipo)+1;
            fwrite(&str.tipo, sizeof(char), strlen(str.tipo), arquivo_saida);
            fwrite(&delim,    sizeof(char), 1,                arquivo_saida); // Delimitador
            ac += strlen(str.dieta)+1;
            fwrite(&str.dieta, sizeof(char), strlen(str.dieta), arquivo_saida);
            fwrite(&delim,     sizeof(char), 1,                 arquivo_saida); // Delimitador
            ac += strlen(str.alimento)+1;
            fwrite(&str.alimento, sizeof(char), strlen(str.alimento), arquivo_saida);
            fwrite(&delim,        sizeof(char), 1,                    arquivo_saida); // Delimitador

            while( (160 - ac) > 0){
                fwrite(&lixo, sizeof(char), 1, arquivo_saida); //Identifica o lixo
                ac++;
            }
        }
    
        reg_pag = (reg_pag + 1) % 100;
        reg++;

        if (reg_pag == 0){
            num_pag++;
        }
    }

    // Escreve a versão final do cabeçalho
    cabecalho.status = '1';
    cabecalho.nroPagDisco = num_pag;
    cabecalho.proxRRN = reg / 10;
    criar_cabecalho(arquivo_saida, cabecalho);
}

// Função que lê os dados de um arquivo de entrada
void le_dados(FILE* arquivo_entrada, FILE* arquivo_saida){

    // Escreve a versão inicial do cabeçalho
    CABECALHO cabecalho;

    cabecalho.status      =  '0';
    cabecalho.topo        =  -1;
    cabecalho.proxRRN     =   0;
    cabecalho.nroRegRem   =   0;
    cabecalho.nroPagDisco =   1; // Considera a página de cabeçalho
    cabecalho.qttCompacta =   0;

    // criar_cabecalho(arquivo_saida, cabecalho);

    int reg     =  0; // Número de registros.
    int reg_pag =  0; // Número de registros em uma página.
    int num_pag =  2; // Número de páginas ocupadas pelo arquivo de dados.
    char* elem;
    DADO str;

    // Le a primeira linha do código e a remove
    char* linha1 = malloc(100 * sizeof(char));
    fgets(linha1, 100, arquivo_entrada);
    free(linha1);

    // Le o primeiro elemento da descricao
    int i = 0;  // Tipo de elemento a ser lido no csv.
    while( (elem = le_elemento(arquivo_entrada)) != NULL ){
        switch(i){
            case 0:
                strcpy(str.nome,elem);
                break;
            case 1:
                strcpy(str.dieta,elem);
                break;
            case 2:
                strcpy(str.habitat,elem);
                break;
            case 3:
                str.populacao = atoi(elem);
                break;
            case 4:
                strcpy(str.tipo,elem);
                break;
            case 5:
                str.velocidade = atoi(elem);
                break;
            case 6:
                str.unidadeMedida = elem[0];
                break;
            case 7:
                str.tamanho = atof(elem);
                break;
            case 8:
                strcpy(str.especie,elem);
                break;
            case 9:
                strcpy(str.alimento,elem);
                break;
        }
        
        // Faz com que passe para o proximo caso
        i = (i + 1) % 10;
        free(elem);

    }

    // Escreve a versão final do cabeçalho
    cabecalho.status = '1';
    cabecalho.nroPagDisco = num_pag;
    cabecalho.proxRRN = reg / 10;
    criar_cabecalho(arquivo_saida, cabecalho);
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
