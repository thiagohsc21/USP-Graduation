//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Estruturas criadas para representaçao dos registros de cabecalho e dados dos arquivos de veiculo e linha
typedef struct {
    char status;
    long long int byteProxReg;
    int nroRegistros;
    int nroRegRemovidos; 
    char descrevePrefixo[18];
    char descreveData[35];
    char descreveLugares[42];
    char descreveLinha[26];
    char descreveModelo[17];
    char descreveCategoria[20];
} cabecalho_veiculo;

typedef struct {
    char prefixo[6];
    char data[11];
    int quantidadeLugares;
    int codLinha;
    char *modelo;
    char *categoria;
    char removido; 
    int tamanhoRegistro;
    int tamanhoModelo;
    int tamanhoCategoria;
} dados_veiculo;

typedef struct {
    char status;
    long long int byteProxReg;
    int nroRegistros;
    int nroRegRemovidos;
    char descreveCodigo[15];
    char descreveCartao[13];
    char descreveNome[13];
    char descreveCor[24];
} cabecalho_linha;

typedef struct {
    int codLinha;
    char aceitaCartao;
    char *nomeLinha;
    char *corLinha;
    char removido;
    int tamanhoRegistro;
    int tamanhoNome;
    int tamanhoCor;
} dados_linha;

#endif