//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#ifndef FUNCOES_ESCRITA_H
#define FUNCOES_ESCRITA_H

#include "constants.h"

//Funcoes Gerais de Escrita:
void printa_veiculo(dados_veiculo *dados, cabecalho_veiculo *cabecalho);
void printa_linha(dados_linha *dados, cabecalho_linha *cabecalho);
void escreve_cabecalho_veiculo(FILE *fp_bin, cabecalho_veiculo cabecalho);
void escreve_cabecalho_linha(FILE *fp_bin, cabecalho_linha cabecalho);
void escreve_dados_veiculo(FILE *fp_bin, dados_veiculo *dados);
void escreve_dados_linha(FILE *fp_bin, dados_linha *dados);
void converte_e_printa_data(char *data);
void valor_cartao(char cartao);
void insere_veiculo(cabecalho_veiculo *cabecalho, dados_veiculo *dados);
void insere_linha(cabecalho_linha *cabecalho, dados_linha *dados);

#endif