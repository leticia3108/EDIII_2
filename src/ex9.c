/*
* O código a seguir é responsável pela inserção de novos registros em um
* arquivo binário, a ser ecolhido pelo usuário.
* 
* Ele irá usar o espaço de lixo, onde foi removido anteriormente outros dados,
* representado pelo caractere '$', para a inserção desses novos dados.
* 
* Essa funcionalidade deverá se repetir 'n' vezes, sendo esse valor também
* escolhido pelo usuário.
* 
* Aqui será feita a etapa principal, solicitando funções criadas no
* módulo 'common.c'
*/

#include "header.h"
#include "ex9.h"

int sobreescreve_dado (FILE* binario, DADO dado){

char delim       = '#';
char lixo        = '$';
int ac           =  0;

// Escrever a struct no arquivo binário:
fwrite(&dado.removido,          sizeof(char),  1, binario);
fwrite(&dado.encadeamento,      sizeof(int),   1, binario);
fwrite(&dado.populacao,     sizeof(int),   1, binario);
fwrite(&dado.tamanho,       sizeof(float), 1, binario);
fwrite(&dado.unidadeMedida, sizeof(char),  1, binario);
fwrite(&dado.velocidade,    sizeof(int),   1, binario);
ac += 18;

ac += strlen(dado.nome)+1;
fwrite(&dado.nome, sizeof(char), strlen(dado.nome), binario);
fwrite(&delim,    sizeof(char), 1,                binario); // Delimitador
printf("%s", dado.nome);

ac += strlen(dado.especie)+1;
fwrite(&dado.especie, sizeof(char), strlen(dado.especie), binario);
fwrite(&delim,       sizeof(char), 1,                   binario); // Delimitador
ac += strlen(dado.habitat)+1;
fwrite(&dado.habitat, sizeof(char), strlen(dado.habitat), binario);
fwrite(&delim,       sizeof(char), 1,                   binario); // Delimitador
ac += strlen(dado.tipo)+1;
fwrite(&dado.tipo, sizeof(char), strlen(dado.tipo), binario);
fwrite(&delim,    sizeof(char), 1,                binario); // Delimitador
ac += strlen(dado.dieta)+1;
fwrite(&dado.dieta, sizeof(char), strlen(dado.dieta), binario);
fwrite(&delim,     sizeof(char), 1,                 binario); // Delimitador
ac += strlen(dado.alimento)+1;
fwrite(&dado.alimento, sizeof(char), strlen(dado.alimento), binario);
fwrite(&delim,        sizeof(char), 1,                    binario); // Delimitador

while( (160 - ac) > 0){
    fwrite(&lixo, sizeof(char), 1, binario); //Identifica o lixo
    ac++;
}

return dado.encadeamento;
}

void ex9(){

char nome_entrada[T_MAX];
scanf("%s", nome_entrada);

// Abertura do binário de entrada para leitura e gravação
FILE *binario_entrada = fopen(nome_entrada,"rb+");

int n; // Número de inserções
scanf("%d", &n);
printf("n = %d ", n);

DADO* dado = malloc (n * sizeof(DADO));

//nome, dieta, habitat, populacao, tipo,
//velocidade, medidaVelocidade, tamanho, especie, alimento

char unidade[1];

for (int i = 0; i < n; i++) {
    scan_quote_string_mod(dado[i].nome);
    scan_quote_string_mod(dado[i].dieta);
    scan_quote_string_mod(dado[i].habitat);
    scanf("%d", &dado[i].populacao);
    scan_quote_string_mod(dado[i].tipo);
    scanf("%d", &dado[i].velocidade);
    scan_quote_string_mod(unidade);
    dado[i].unidadeMedida = unidade[0];
    scanf("%f", &dado[i].tamanho);
    scan_quote_string_mod(dado[i].especie);
    scan_quote_string_mod(dado[i].alimento);

    // Ler a primeira RRN removida
    int topo;
    fseek(binario_entrada, 1, SEEK_CUR);
    fread(&topo, sizeof(int), 1, binario_entrada);

    fseek(binario_entrada, 1600 + topo*160, SEEK_CUR);
    printf("Inserção realizada no RRN %d\n", topo);
    topo = sobreescreve_dado(binario_entrada, dado[i]);
    
}

free(dado);
return;
}