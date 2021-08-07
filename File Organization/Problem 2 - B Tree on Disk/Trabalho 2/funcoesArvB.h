//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#ifndef FUNCOES_ARVB_H
#define FUNCOES_ARVB_H

#include "arvB.h"
#include "constants.h"

void escreve_cabecalho_arvore(FILE *fp_index, cabecalho_arvB *cabecalho);
cabecalho_arvB *le_cabecalho_arvore(FILE *fp);

void escreve_no_arvore(FILE *fp_index, no_arvB *no, int RRN);
no_arvB* le_no_arvore(FILE *fp_index, int RRN);

no_arvB* cria_no();
void cria_arvB(FILE *fp_bin, FILE *fp_index, int tipo);

int busca_recursiva(int RRN, int *byteoffset_encontrado, int chave, FILE *fp_index);
void busca_dados_indice(FILE *fp_bin, FILE *fp_index, int valor, int tipo);

void insere_no(FILE *fp_index, int chave, int byteoffset, cabecalho_arvB *cabecalho_arv);
int insere_recursivo(int RRN_atual, int chave, int byteoffset, int *filho_promo, int *chave_promo, int *byteoffset_promo, FILE *fp_index, cabecalho_arvB *cabecalho_arv);
void split(no_arvB *pagina, int *chave_promo, int *filho_promo_r, int *offset_promo, no_arvB *nova_pagina, cabecalho_arvB *cabecalho_arv);

#endif