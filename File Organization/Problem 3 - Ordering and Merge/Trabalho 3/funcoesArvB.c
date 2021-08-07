//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include "funcoesArvB.h"
#include "funcoesLeitura.h"
#include "funcoesEscrita.h"
#include "funcoesFornecidas.h"

/* 
 * Funcionalidades do Trabalho 2 Utilizadas 
 */

// Função que nos auxilia na escrita de cada um dos campos do cabecalho da arvore, alocando lixo no fim
void escreve_cabecalho_arvore(FILE *fp, cabecalho_arvB *cabecalho) {
    fseek(fp, 0, SEEK_SET);
    fwrite(&cabecalho->status, sizeof(char), 1, fp);
    fwrite(&cabecalho->noRaiz, sizeof(int), 1, fp);
    fwrite(&cabecalho->RRNproxNo, sizeof(int), 1, fp);
    char aux = '@'; 
    for(int i=0; i<68; i++) fwrite(&aux, sizeof(char), 1, fp);
}

// Função responsável pela leitura dos campos do cabecalho da arvore
cabecalho_arvB *le_cabecalho_arvore(FILE *fp) {
    cabecalho_arvB *cabecalho = (cabecalho_arvB*) malloc(sizeof(cabecalho_arvB));

    fseek(fp, 0, SEEK_SET);
    fread(&cabecalho->status, sizeof(char), 1, fp);
    fread(&cabecalho->noRaiz, sizeof(int), 1, fp);
    fread(&cabecalho->RRNproxNo, sizeof(int), 1, fp);

    char lixo[69];
    fread(lixo, sizeof(char), 68, fp);

    return cabecalho;
}

// Função que cria nó da árvore, preenchendo com -1 todas as posições
no_arvB *cria_no() {

    no_arvB *no = (no_arvB*) malloc(sizeof(no_arvB));
    no->folha = '0';
    no->nroChavesIndexadas = 0;

    for(int i=0; i<ordem_arvB-1; i++) {
        no->P[i] = -1;
        no->C[i] = -1;
        no->Pr[i] = -1;
    }
    no->P[ordem_arvB-1] = -1;

    return no;
}

// Função responsável por ler página de disco
no_arvB *le_no_arvore(FILE *fp, int RRN) {
    fseek(fp, (RRN+1)*77, SEEK_SET);

    no_arvB *no = cria_no();
    fread(&no->folha, sizeof(char), 1, fp);
    fread(&no->nroChavesIndexadas, sizeof(int), 1, fp);
    fread(&no->RRNdoNo, sizeof(int), 1, fp);

    for(int i=0; i<ordem_arvB-1; i++) {
        fread(&no->P[i], sizeof(int), 1, fp);
        fread(&no->C[i], sizeof(int), 1, fp);
        fread(&no->Pr[i], sizeof(long long), 1, fp);
    }

    fread(&no->P[ordem_arvB-1], sizeof(int), 1, fp);

    return no;
}

// Função recursiva da busca
int busca_recursiva(int RRN, int *byteoffset, int chave, FILE *fp_index) {

    // Chave de busca não encontrada / Caso Base
    if(RRN == -1) return 0;
    
    // Posiciona o ponteiro na pagina de disco desejada e a coloca na RAM
    no_arvB *no = le_no_arvore(fp_index, RRN);

    // Pesquisa na página, procurando a chave de busca
    for(int i = 0; i < ordem_arvB-1; i++) {

        // Se encontrou, então armazenamos seu byteoffset e saímos
        if(chave == no->C[i]) {
            *byteoffset = no->Pr[i];
            free(no);
            return 1;
        }

        // Se a chave buscada é menor que a chave[i] ou chave vazia, entao devemos descer no rrn exatamente anterior a chave[i]
        if(chave < no->C[i] || no->C[i] == -1) {
            RRN = no->P[i];
            break;
        }

        // Se entrou no if, então a chave buscada é maior que todas as outras chaves no nó, então usamos o último rrn da página
        if(i == ordem_arvB-2)  RRN = no->P[ordem_arvB-1];
    }

    free(no);
    busca_recursiva(RRN, byteoffset, chave, fp_index);
}

// Função que encontra o registro que contém a chave (valor) passada
int busca_dados_indice(FILE *fp_bin, FILE *fp_index, dados_veiculo *dados_v, cabecalho_veiculo *cabecalho_v, cabecalho_linha *cabecalho_l, cabecalho_arvB *cabecalho) {

    int encontrou, byteoffset_linha = 0;
    encontrou = busca_recursiva(cabecalho->noRaiz, &byteoffset_linha, dados_v->codLinha, fp_index);

    // Se encontramos a chave associada ao valor passado, então
    if(encontrou) {

        // Printa os valores do registro para o arquivo de veículos
        printa_veiculo(dados_v, cabecalho_v);

        // Posiciona o ponteiro no registro que possui a chave encontrada
        fseek(fp_bin, byteoffset_linha+5, SEEK_SET);
        dados_linha *dados = (dados_linha*) malloc(sizeof(dados_linha));

        // Lê os valores do registro e printa na tela
        recebe_dados_linha(fp_bin, dados);
        printa_linha(dados, cabecalho_l);

        free(dados->nomeLinha);
        free(dados->corLinha);
        dados->nomeLinha = NULL;
        dados->corLinha = NULL;

        free(dados);
    }
    
    return encontrou;
}


