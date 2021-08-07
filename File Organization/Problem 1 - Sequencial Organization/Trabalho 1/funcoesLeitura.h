//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#ifndef FUNCOES_LEITURA_H
#define FUNCOES_LEITURA_H

#include "constants.h"

//Funcoes Gerais de Leitura:
void filtrar_buffer_veiculo(char *buffer, cabecalho_veiculo *cabecalho, dados_veiculo *dados);
void filtrar_buffer_linha(char *buffer, cabecalho_linha *cabecalho, dados_linha *dados);
void le_cabecalho_veiculo(FILE *fp_bin, cabecalho_veiculo *cabecalho);
void le_cabecalho_linha(FILE *fp_bin, cabecalho_linha *cabecalho);
void recebe_dados_veiculo(FILE *fp_bin, dados_veiculo *dados);
void recebe_dados_linha(FILE *fp_bin, dados_linha *dados);

#endif