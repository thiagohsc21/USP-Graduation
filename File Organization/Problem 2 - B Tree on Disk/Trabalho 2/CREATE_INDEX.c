//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include "CREATE_INDEX.h"
#include "funcoesFornecidas.h"
#include "funcoesLeitura.h"

void CREATE_INDEX(int c) {

    // Lê nome do csv que será lido e nome do binário que será criado
    char nome_bin[30], nome_index[30];
    scanf(" %s", nome_bin);
    scanf(" %s", nome_index);

    // Checando se ocorreram falhas na abertura de um dos arquivos
    FILE *fp_bin, *fp_index;
    if(!abertura_arquivo(&fp_bin, &fp_index, nome_bin, nome_index, "rb", "wb+")) return;

    // Função responsável por criar a árvore e preenchê-la
    cria_arvB(fp_bin, fp_index, c);

    fclose(fp_bin);
    fclose(fp_index);
    binarioNaTela(nome_index);  
}