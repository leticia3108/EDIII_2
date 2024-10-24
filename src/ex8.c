/* 
    Algumas funções desse arquivo possui prints de debug que estão comentados.
    Eles ajudam a entender possíveis bugs ao decorrer da execução do programa
    e ajudam em eventuais manutenções.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/funcoes_fornecidas.h"
#include "../include/common.h"
#include "../include/main.h"
#include "../include/ex8.h"

// Função que busca um registro pela chave na árvore-B e retorna o PR (ponteiro do registro)
long busca_chave_arvoreB(FILE *arquivoIndice, int RRNraiz, long chaveBusca) {
    no_indice no;
    int RRNAtual = RRNraiz;

    // printf("DEBUG: Iniciando busca na árvore-B...\n");
    // printf("DEBUG: RRN da raiz: %d\n", RRNraiz);

    // Percorrer a árvore-B até encontrar a chave ou chegar em uma folha
    while (RRNAtual != -1) {
        // printf("DEBUG: Lendo nó da árvore com RRNAtual = %d\n", RRNAtual);

        // Ler o nó da árvore-B
        lerNo(&no, RRNAtual, arquivoIndice);

        // printf("DEBUG: Número de chaves no nó: %d\n", no.nroChavesNo);

        // Procurar a chave no nó atual
        for (int i = 0; i < no.nroChavesNo; i++) {
            // printf("DEBUG: Verificando chave %d no nó...\n", i + 1);
            if (chaveBusca == no.C1 && i == 0) {
                // printf("DEBUG: Chave encontrada no PR1\n");
                return no.PR1;
            }
            if (chaveBusca == no.C2 && i == 1) {
                // printf("DEBUG: Chave encontrada no PR2\n");
                return no.PR2;
            }
            if (chaveBusca == no.C3 && i == 2) {
                // printf("DEBUG: Chave encontrada no PR3\n");
                return no.PR3;
            }
            if (chaveBusca == no.C4 && i == 3) {
                // printf("DEBUG: Chave encontrada no PR4\n");
                return no.PR4;
            }
        }

        // Descer para o nó filho adequado, se a chave não for encontrada
        if (chaveBusca < no.C1) RRNAtual = no.P1;
        else if (no.nroChavesNo == 1 || chaveBusca < no.C2) RRNAtual = no.P2;
        else if (no.nroChavesNo == 2 || chaveBusca < no.C3) RRNAtual = no.P3;
        else if (no.nroChavesNo == 3 || chaveBusca < no.C4) RRNAtual = no.P4;
        else RRNAtual = no.P5;

        // printf("DEBUG: Descendo para o próximo nó com RRNAtual = %d\n", RRNAtual);
    }

    // printf("DEBUG: Chave não encontrada na árvore-B.\n");
    return -1; // Chave não encontrada
}

// Função que realiza a busca dos dados no arquivo de dados
void busca_dados(FILE *arquivoDados, long PR) {
    DADO dado;

    // Adicionar um print para verificar o PR (ponteiro de registro)
    // printf("DEBUG: PR (Ponteiro de Registro) recebido: %ld\n", PR);

    // Vai para o local do registro no arquivo de dados
    fseek(arquivoDados, PR, SEEK_SET);

    // Ler o primeiro byte (flag de remoção)
    fread(&dado.removido, sizeof(char), 1, arquivoDados);

    // Adicionar um print para verificar se o dado foi removido logicamente
    // printf("DEBUG: Flag de remoção do registro: %c\n", dado.removido);
    
    if (dado.removido == '1') {
        // Caso o registro tenha sido removido logicamente, informar
        printf("Registro inexistente.\n");
        return;
    }

    // Se o registro não foi removido, ler e exibir os dados
    imprime_dado(arquivoDados, &dado);
}


/* 
    Função responsável pela funcionalidade 8
        - Realiza a busca de um arquivo na arvore-B e exibe os dados do registro encontrado
 */
void ex8() {
    // Variáveis para os arquivos e o nome de busca
    char nomeArquivoDados[T_MAX];
    char nomeArquivoIndice[T_MAX];
    char nomeBusca[T_MAX];
    char string_auxiliar[T_MAX];
    long chaveBusca;

    // Leitura dos nomes dos arquivos e do campo de busca
    if (scanf("%s %s", nomeArquivoDados, nomeArquivoIndice) != 2) {
        printf("Erro: entrada inválida.\n");
        return;
    }

    // Adicionar um print para verificar os arquivos recebidos
    // printf("DEBUG: Arquivo de dados: %s\n", nomeArquivoDados);
    // printf("DEBUG: Arquivo de índice: %s\n", nomeArquivoIndice);

    // Leitura do campo de busca (nome) com a função scan_quote_string
    scanf("%s", string_auxiliar); // Buffer auxiliar para lidar com entrada antes da função
    scan_quote_string(nomeBusca);  // Função que processa a string entre aspas

    // Adicionar um print para verificar o nome recebido
    // printf("DEBUG: Nome buscado: %s\n", nomeBusca);

    // Abertura dos arquivos binários
    FILE *arquivoDados = fopen(nomeArquivoDados, "rb");
    FILE *arquivoIndice = fopen(nomeArquivoIndice, "rb");
    if (arquivoDados == NULL || arquivoIndice == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    // printf("DEBUG: Arquivos de dados e índice abertos com sucesso.\n");

    // Conversão do nome para chave
    chaveBusca = converteNome(nomeBusca);

    // Verificação da chave convertida
    // printf("DEBUG: Chave convertida do nome: %ld\n", chaveBusca);

    // Leitura do cabeçalho do arquivo de índice para obter a raiz da árvore-B
    int RRNraiz;
    fseek(arquivoIndice, 1, SEEK_SET);  // Pular o status do cabeçalho
    fread(&RRNraiz, sizeof(int), 1, arquivoIndice);

    // printf("DEBUG: RRN da raiz lido: %d\n", RRNraiz);

    // Busca pela chave na árvore-B
    long PR = busca_chave_arvoreB(arquivoIndice, RRNraiz, chaveBusca);

    // Caso a chave não seja encontrada
    if (PR == -1) {
        printf("Registro inexistente.\n");
    } else {
        // Buscar e exibir os dados do registro encontrado
        busca_dados(arquivoDados, PR);
    }

    // Fechar os arquivos
    fclose(arquivoDados);
    fclose(arquivoIndice);

    // printf("DEBUG: Fechamento dos arquivos concluído.\n");
}
