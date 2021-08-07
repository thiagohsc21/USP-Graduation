//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#ifndef FUNCOES_ARVB_H
#define FUNCOES_ARVB_H

#include "arvB.h"
#include "constants.h"

void escreve_cabecalho_arvore(FILE *fp_index, cabecalho_arvB *cabecalho);
cabecalho_arvB *le_cabecalho_arvore(FILE *fp);

no_arvB* le_no_arvore(FILE *fp_index, int RRN);
no_arvB* cria_no();

int busca_recursiva(int RRN, int *byteoffset_encontrado, int chave, FILE *fp_index);
int busca_dados_indice(FILE *fp_bin, FILE *fp_index, dados_veiculo *dados, cabecalho_veiculo *cabecalho_v, cabecalho_linha *cabecalho_l, cabecalho_arvB *cabecalho);

#endif