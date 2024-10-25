#include "header.h"
#include "../include/funcoes_fornecidas.h"

/* A Função cabecalho_indice gera uma versão inicial do cabeçalho 
do arquivo de índice. Para isso, o status é definido como o de um
arquivo inconsistente (0), o noRaiz indica que a árvore está vazia
(-1) e o proximo nó a ser inserido é definido como 0 */

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

/* A Função encontra_nome é utilizada para encontrarum nome no ar-
quivo de dados, ignorando registros logicamente removidos. Em segui-
da, o nome é convertido em uma chave com a função converteNome, e 
uma struct "indice" armazera essa chave, além de um ponteiro para o 
registro. */

int encontra_nome(FILE* fbin, char* nome, indice* ind){
    char c;


    if (fread(&c, sizeof(char), 1, fbin) != 1) {
        if (feof(fbin)) {
            return 1;
        } else {
            printf("Erro lendo o arquivo\n");
            return 1;
        }
    }

    while (c == '1') {
        fseek(fbin, T_REG_DADOS -1, SEEK_CUR);
        if (fread(&c, sizeof(char), 1, fbin) != 1) {
            if (feof(fbin)) {
               // printf("Fim do arquivo\n");
                return 1;
            } else {
                printf("Erro lendo o arquivo\n");
                return 1;
            }
        }

    }

    fseek(fbin, 17, SEEK_CUR);
    
    long pular = (long) leitura_variavel(nome, fbin);
    if (pular == -1) {
        printf("Erro ao ler o noe\n");
        return 1;
    }

    fseek(fbin, T_REG_DADOS - pular - 18, SEEK_CUR);

    ind->pr = ftell(fbin) - 160;
    ind->chave = converteNome(nome);

    return 0;
}

void ex7(int* proxRRN){

    // Ler o nome do arquivo de entrada, com tamanho máximo 30:
    char nome_entrada[T_MAX];

    // Ler o nome do arquivo de saída, com tamanho máximo 30:
    char nome_saida[T_MAX];

    scanf("%s", nome_entrada);
    scanf("%s", nome_saida);

    // Abertura do binário de entrada para leitura
    FILE *binario_entrada = fopen(nome_entrada,"rb");
    if (binario_entrada == NULL){
        printf("Erro ao abrir o arquivo de entrada");
        return;
    }

    // Abertura do arquivo de índice para escrita
    FILE *binario_saida = fopen(nome_saida,"wb+");
    if (binario_saida == NULL){
        printf("Erro ao criar o arquivo de indice");
        return;
    }

    // Criação do cabeçalho do índice
    cabecalho_indice(binario_entrada, binario_saida);

    // Pular cabeçalho do arquivo de dados
    fseek(binario_entrada, T_DADOS, SEEK_SET);

    // Encontrar os nomes da lista para adicionar à árvore B
    char* nome = malloc(T_MAX * sizeof(char));
    indice* ind = malloc(sizeof(indice));

    fseek(binario_saida, 1, SEEK_SET);

    //Iniciar a inserção de dados com o status 1
    char status = '1';

    fseek(binario_entrada, 0 , SEEK_SET);
    fwrite(&status, sizeof(char), 1, binario_entrada);

    //Armazena o RRN da raiz
    int RRNraiz;
    fread(&RRNraiz, sizeof(int), 1, binario_saida);

    int last_ptr_dado = 1600;

    int NumReg = 0; // Armazena o número de registros do arquivo de entrada;
    fseek(binario_entrada, 5, SEEK_SET);
    fread(&NumReg, sizeof(int), 1, binario_entrada);

    for (int i = 0; i<100000; i++){
        // Pular cabeçalho do arquivo de dados
        if(feof(binario_entrada)){
            //printf ("Fim do arquivo \n");
            break;}
        fseek(binario_entrada, last_ptr_dado, SEEK_SET);
        if( encontra_nome(binario_entrada, nome, ind) == 1){
            break;
        }
        //printf ("nome = %s\n", nome);
        last_ptr_dado = ind->pr + 160;
        ind->p1 = -1;
        ind->p2 = -1;
        fseek(binario_saida, 1, SEEK_SET);
        fread(&RRNraiz, sizeof(int), 1, binario_saida);
        inserir(*ind,binario_saida,RRNraiz,proxRRN);   //
    }


    // Imprime a árvore
    int RRN;
    fseek(binario_saida, 1, SEEK_SET);
    fread(&RRN, sizeof(int), 1, binario_saida);

    // Indicar que a escrita foi concluida corretamente
    ajustaCabecalho(binario_saida, '1', RRN, proxRRN);

    fclose(binario_entrada);
    fclose(binario_saida);

    binarioNaTela(nome_saida);

    free(nome);
    free(ind);
}
