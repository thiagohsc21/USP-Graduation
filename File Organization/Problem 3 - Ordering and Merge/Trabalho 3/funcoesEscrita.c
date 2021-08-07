//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include "funcoesEscrita.h"
#include "funcoesFornecidas.h"

/* 
 * Funcionalidades do Trabalho 1 Utilizadas 
 */

// Funcao responsavel pela escrita do cabecalho do veiculo no arquivo binário
void escreve_cabecalho_veiculo(FILE *fp_bin, cabecalho_veiculo cabecalho){
    fseek(fp_bin, 0, SEEK_SET);
    fwrite(&cabecalho.status, sizeof(char), 1, fp_bin);
    fwrite(&cabecalho.byteProxReg, sizeof(long long), 1, fp_bin);
    fwrite(&cabecalho.nroRegistros, sizeof(int), 1, fp_bin);
    fwrite(&cabecalho.nroRegRemovidos, sizeof(int), 1, fp_bin);
    fwrite(&cabecalho.descrevePrefixo, sizeof(char), 18, fp_bin);
    fwrite(&cabecalho.descreveData, sizeof(char), 35, fp_bin);
    fwrite(&cabecalho.descreveLugares, sizeof(char), 42, fp_bin);
    fwrite(&cabecalho.descreveLinha, sizeof(char), 26, fp_bin);
    fwrite(&cabecalho.descreveModelo, sizeof(char), 17, fp_bin);
    fwrite(&cabecalho.descreveCategoria, sizeof(char), 20, fp_bin);
}

// Funçãp responsavel pela escrita dos dados do veiculo no arquivo binário
void escreve_dados_veiculo(FILE *fp_bin, dados_veiculo *dados){
    fwrite(&dados->removido, sizeof(char), 1, fp_bin);
    fwrite(&dados->tamanhoRegistro, sizeof(int), 1, fp_bin);
    fwrite(&dados->prefixo, sizeof(char), 5, fp_bin);
    fwrite(&dados->data, sizeof(char), 10, fp_bin);
    fwrite(&dados->quantidadeLugares, sizeof(int), 1, fp_bin);
    fwrite(&dados->codLinha, sizeof(int), 1, fp_bin);
    fwrite(&dados->tamanhoModelo, sizeof(int), 1, fp_bin);
    fwrite(dados->modelo, sizeof(char), dados->tamanhoModelo, fp_bin);
    fwrite(&dados->tamanhoCategoria, sizeof(int), 1, fp_bin);
    fwrite(dados->categoria, sizeof(char), dados->tamanhoCategoria, fp_bin);
}

// Funcao responsavel pela escrita do cabecalho da linha no arquivo binário
void escreve_cabecalho_linha(FILE *fp_bin, cabecalho_linha cabecalho){
    fseek(fp_bin, 0, SEEK_SET);
    fwrite(&cabecalho.status, sizeof(char), 1, fp_bin);
    fwrite(&cabecalho.byteProxReg, sizeof(long long), 1, fp_bin);
    fwrite(&cabecalho.nroRegistros, sizeof(int), 1, fp_bin);
    fwrite(&cabecalho.nroRegRemovidos, sizeof(int), 1, fp_bin);
    fwrite(&cabecalho.descreveCodigo, sizeof(char), 15, fp_bin);
    fwrite(&cabecalho.descreveCartao, sizeof(char), 13, fp_bin);
    fwrite(&cabecalho.descreveNome, sizeof(char), 13, fp_bin);
    fwrite(&cabecalho.descreveCor, sizeof(char), 24, fp_bin);
}

// Funçãp responsavel pela escrita dos dados da linha no arquivo binário
void escreve_dados_linha(FILE *fp_bin, dados_linha *dados){
    fwrite(&dados->removido, sizeof(char), 1, fp_bin);
    fwrite(&dados->tamanhoRegistro, sizeof(int), 1, fp_bin);
    fwrite(&dados->codLinha, sizeof(int), 1, fp_bin);
    fwrite(&dados->aceitaCartao, sizeof(char), 1, fp_bin);
    fwrite(&dados->tamanhoNome, sizeof(int), 1, fp_bin);
    fwrite(dados->nomeLinha, sizeof(char), dados->tamanhoNome, fp_bin);
    fwrite(&dados->tamanhoCor, sizeof(int), 1, fp_bin);
    fwrite(dados->corLinha, sizeof(char), dados->tamanhoCor, fp_bin);
}

//Funcao responsavel pela simples impressao dos dados na tela usando a struct cabecalho e a struct dados
void printa_veiculo(dados_veiculo *dados, cabecalho_veiculo *cabecalho){
    for(int i = 0; i < 18; i++) printf("%c", cabecalho->descrevePrefixo[i]); 
    printf(": %s\n", dados->prefixo);

    for(int i = 0; i < 17; i++) printf("%c", cabecalho->descreveModelo[i]);
    if(dados->tamanhoModelo == 0) printf(": campo com valor nulo\n");
    else printf(": %s\n", dados->modelo);

    for(int i = 0 ; i < 20 ; i++) printf("%c", cabecalho->descreveCategoria[i]); 
    if(dados->tamanhoCategoria == 0) printf(": campo com valor nulo\n");
    else printf(": %s\n", dados->categoria);

    for(int i = 0 ; i < 35 ; i++) printf("%c", cabecalho->descreveData[i]); printf(": ");
    if(dados->data[0] != '\0') converte_e_printa_data(dados->data);
    else printf("campo com valor nulo");
    printf("\n");

    for(int i = 0 ; i < 42 ; i++) printf("%c", cabecalho->descreveLugares[i]);
    if(dados->quantidadeLugares == -1)  printf(": campo com valor nulo\n");
    else printf(": %d\n", dados->quantidadeLugares);
}

//Funcao responsavel pela simples impressao dos dados na tela usando a struct cabecalho e a struct dados
void printa_linha(dados_linha *dados, cabecalho_linha *cabecalho){
    for(int i = 0; i < 15; i++) printf("%c", cabecalho->descreveCodigo[i]);
    printf(": %d\n", dados->codLinha); 

    for(int i = 0; i < 13; i++) printf("%c", cabecalho->descreveNome[i]);
    if(dados->tamanhoNome == 0) printf(": campo com valor nulo\n");
    else printf(": %s\n", dados->nomeLinha); 

    for(int i = 0; i < 24; i++) printf("%c", cabecalho->descreveCor[i]);
    if(dados->tamanhoCor == 0) printf(": campo com valor nulo\n");
    else printf(": %s\n", dados->corLinha); 

    for(int i = 0; i < 13; i++) printf("%c", cabecalho->descreveCartao[i]); printf(": ");
    if(dados->aceitaCartao != '\0') valor_cartao(dados->aceitaCartao);
    else printf("campo com valor nulo");
    printf("\n\n");
}

// Funcao responsavel por ler a data e converter para o formato dia - mes por extenso - ano
void converte_e_printa_data(char *data){
    int dia, ano, mes;
    char nome_mes[25], *aux;

    aux = strtok(data, "-");
    ano = atoi(aux);

    aux = strtok(NULL, "-");
    mes = atoi(aux);

    if (mes == 1)
        strcpy(nome_mes, "janeiro");
    else if (mes == 2)
        strcpy(nome_mes, "fevereiro");
    else if (mes == 3)
        strcpy(nome_mes, "março");
    else if (mes == 4)
        strcpy(nome_mes, "abril");
    else if (mes == 5)
        strcpy(nome_mes, "maio");
    else if (mes == 6)
        strcpy(nome_mes, "junho");
    else if (mes == 7)
        strcpy(nome_mes, "julho");
    else if (mes == 8)
        strcpy(nome_mes, "agosto");
    else if (mes == 9)
        strcpy(nome_mes, "setembro");
    else if (mes == 10)
        strcpy(nome_mes, "outubro");
    else if (mes == 11)
        strcpy(nome_mes, "novembro");
    else if (mes == 12)
        strcpy(nome_mes, "dezembro");

    aux = strtok(NULL, "-");
    dia = atoi(aux);

    if (dia >= 10)
        printf("%d de %s de %d", dia, nome_mes, ano);
    else
        printf("0%d de %s de %d", dia, nome_mes, ano);
}

//Funcao resposavel por pegar o valor do aceita cartao e printar a frase correspondente
void valor_cartao(char cartao){
    if (cartao == 'S')
        printf("PAGAMENTO SOMENTE COM CARTAO SEM PRESENCA DE COBRADOR");
    else if (cartao == 'N')
        printf("PAGAMENTO EM CARTAO E DINHEIRO");
    else if (cartao == 'F')
        printf("PAGAMENTO EM CARTAO SOMENTE NO FINAL DE SEMANA");
}
