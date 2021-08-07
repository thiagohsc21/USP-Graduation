//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include "funcoesLeitura.h"

/* 
 * Funcionalidades do Trabalho 1 Utilizadas 
 */

// Função responsável pela abertura do arquivo, retornando se houve erro ou não
int abertura_arquivo(FILE **fp, char *nome, char *modo) {
 
    (*fp) = fopen(nome, modo);
    if ((*fp) == NULL){
        printf("Falha no processamento do arquivo.\n");
        return 0;
    }  
    return 1;
}

//Funcao responsavle pela leitura do cabecalho dos veiculos no arquivo binario
cabecalho_veiculo *le_cabecalho_veiculo(FILE *fp_bin) {
    cabecalho_veiculo *cabecalho = (cabecalho_veiculo*) malloc(sizeof(cabecalho_veiculo));

    fseek(fp_bin, 0, SEEK_SET);
    fread(&cabecalho->status, sizeof(char), 1, fp_bin);
    fread(&cabecalho->byteProxReg, sizeof(long long), 1, fp_bin);
    fread(&cabecalho->nroRegistros, sizeof(int), 1, fp_bin);
    fread(&cabecalho->nroRegRemovidos, sizeof(int), 1, fp_bin);
    fread(&cabecalho->descrevePrefixo, sizeof(char), 18, fp_bin);
    fread(&cabecalho->descreveData, sizeof(char), 35, fp_bin);
    fread(&cabecalho->descreveLugares, sizeof(char), 42, fp_bin);
    fread(&cabecalho->descreveLinha, sizeof(char), 26, fp_bin);
    fread(&cabecalho->descreveModelo, sizeof(char), 17, fp_bin);
    fread(&cabecalho->descreveCategoria, sizeof(char), 20, fp_bin);  

    return cabecalho;
}

//Funcao responsavel pela leitura dos campos do registro no arquivo binario veiculos
void recebe_dados_veiculo(FILE *fp_bin, dados_veiculo *dados){
    fread(&dados->prefixo, sizeof(char), 5, fp_bin);
    dados->prefixo[5] = '\0';
    fread(&dados->data, sizeof(char), 10, fp_bin);
    dados->data[11] = '\0';
    fread(&dados->quantidadeLugares, sizeof(int), 1, fp_bin);
    fread(&dados->codLinha, sizeof(int), 1, fp_bin);

    fread(&dados->tamanhoModelo, sizeof(int), 1, fp_bin);
    dados->modelo = (char*) malloc((dados->tamanhoModelo+1) * sizeof(char));
    fread(dados->modelo, sizeof(char), dados->tamanhoModelo, fp_bin);
    dados->modelo [dados->tamanhoModelo] = '\0';

    fread(&dados->tamanhoCategoria, sizeof(int), 1, fp_bin);
    dados->categoria = (char*) malloc((dados->tamanhoCategoria+1) * sizeof(char));
    fread(dados->categoria, sizeof(char), dados->tamanhoCategoria, fp_bin);
    dados->categoria [dados->tamanhoCategoria] = '\0';
}

//Funcao responsavel pela leitura do cabecalho das linhas no arquivo binario
cabecalho_linha *le_cabecalho_linha(FILE *fp_bin){   
    cabecalho_linha *cabecalho = (cabecalho_linha*) malloc(sizeof(cabecalho_linha));

    fseek(fp_bin, 0, SEEK_SET);
    fread(&cabecalho->status, sizeof(char), 1, fp_bin);
    fread(&cabecalho->byteProxReg, sizeof(long long), 1, fp_bin);
    fread(&cabecalho->nroRegistros, sizeof(int), 1, fp_bin);
    fread(&cabecalho->nroRegRemovidos, sizeof(int), 1, fp_bin);
    fread(&cabecalho->descreveCodigo, sizeof(char), 15, fp_bin);
    fread(&cabecalho->descreveCartao, sizeof(char), 13, fp_bin);
    fread(&cabecalho->descreveNome, sizeof(char), 13, fp_bin);
    fread(&cabecalho->descreveCor, sizeof(char), 24, fp_bin);

    return cabecalho;
}

//Funcao responsavel pela leitura dos campos do registro no arquivo binario linhas
void recebe_dados_linha(FILE *fp_bin, dados_linha *dados){
    fread(&dados->codLinha, sizeof(int), 1, fp_bin);
    fread(&dados->aceitaCartao, sizeof(char), 1, fp_bin);

    fread(&dados->tamanhoNome, sizeof(int), 1, fp_bin);
    dados->nomeLinha = (char*) malloc((dados->tamanhoNome+1) * sizeof(char));
    fread(dados->nomeLinha, sizeof(char), dados->tamanhoNome, fp_bin);
    dados->nomeLinha [dados->tamanhoNome] = '\0';

    fread(&dados->tamanhoCor, sizeof(int), 1, fp_bin);
    dados->corLinha = (char*) malloc((dados->tamanhoCor+1) * sizeof(char));
    fread(dados->corLinha, sizeof(char), dados->tamanhoCor, fp_bin);
    dados->corLinha [dados->tamanhoCor] = '\0';
}

