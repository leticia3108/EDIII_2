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
