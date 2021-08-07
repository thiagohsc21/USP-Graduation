//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#ifndef ARVB_H
#define ARVB_H

#include <stdlib.h>
#include <stdio.h>
#define ordem_arvB 5

// Estrutura do cabeçalho
typedef struct {
    char status;
    int noRaiz;
    int RRNproxNo;
} cabecalho_arvB;

// Estrutura dos nós da árvore
typedef struct {
    char folha;
    int nroChavesIndexadas; //numeros de chaves presentes do nó (max=4)
    int RRNdoNo;
    int P[ordem_arvB];  //RRN das subárvores
    int C[ordem_arvB-1]; // chave de busca dos registros
    long long Pr[ordem_arvB-1]; // byteoffset do registro no arquivo de registros
} no_arvB;

#endif