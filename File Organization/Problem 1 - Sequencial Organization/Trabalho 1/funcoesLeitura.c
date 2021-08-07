//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include "funcoesLeitura.h"

//Pega a string lida no laço e faz a separação com base nas vírgulas
void filtrar_buffer_veiculo(char *buffer, cabecalho_veiculo *cabecalho, dados_veiculo *dados) {
    
    char *token, auxiliar[100];

    //Recebe o prefixo e passa para a struct dados
    token = strtok(buffer, ",");
    strcpy(dados->prefixo, token);

    //Trata os casos em que o registro está removido
    if (dados->prefixo[0] == '*')
    {
        //Trata os casos em que temos o * como primeiro byte : *XXX vira XXX\0
        for (int i = 0; i <= 4; i++)
        {
            if (i != 4)
                dados->prefixo[i] = dados->prefixo[i + 1];
            else
                dados->prefixo[i] = '\0';
        }
        cabecalho->nroRegRemovidos++;
        dados->removido = '0';
    }
    else
    {
        cabecalho->nroRegistros++;
        dados->removido = '1';
    }

    //Recebe a data e passa para a struct dados
    token = strtok(NULL, ",");
    strcpy(dados->data, token);

    //Trata os casos em que data é um campo NULO : NULO vira \0@@@@@@@@@
    if (strcmp(dados->data, "NULO") == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            if (i == 0)
                dados->data[i] = '\0';
            else
                dados->data[i] = '@';
        }
    }

    //Recebe a quantidade de lugares e passa para a string auxiliar
    token = strtok(NULL, ",");
    strcpy(auxiliar, token);

    //Trata os casos em que a variável é NULA; caso NULO, convertemos a string para inteiro
    if (strcmp(auxiliar, "NULO") == 0)
        dados->quantidadeLugares = -1;
    else
        dados->quantidadeLugares = atoi(auxiliar);

    //Recebe o código da linha e passa para a string auxiliar
    token = strtok(NULL, ",");
    strcpy(auxiliar, token);

    //Trata os casos em que a variável é NULA; caso NULO, convertemos a string para inteiro
    if (strcmp(auxiliar, "NULO") == 0)
        dados->codLinha = -1;
    else
        dados->codLinha = atoi(auxiliar);

    //Recebe o valor do modelo
    token = strtok(NULL, ",");

    //Se nulo, alocamos um único byte e preenchemos com o \0
    if (strcmp(token, "NULO") == 0)
    {
        dados->modelo = (char *)malloc(sizeof(char));
        dados->modelo[0] = '\0';
        dados->tamanhoModelo = 0;
    }
    //Caso contrário, alocamos o tamanho do token+1, para armazenarmos o \0
    else
    {
        dados->modelo = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(dados->modelo, token);
        dados->tamanhoModelo = strlen(token);
    }

    //Recebe o valor da categoria
    token = strtok(NULL, ",");

    //Se nulo, alocamos um único byte e preenchemos com o \0
    if (strcmp(token, "NULO") == 0)
    {
        dados->categoria = (char *)malloc(sizeof(char));
        dados->categoria[0] = '\0';
        dados->tamanhoCategoria = 0;
    }
    //Caso contrário, alocamos o tamanho de token e substituímos o \n recebido por um \0
    else
    {
        dados->categoria = malloc(sizeof(char) * (strlen(token)));
        strcpy(dados->categoria, token);
        dados->categoria[strlen(token) - 1] = '\0';
        dados->tamanhoCategoria = strlen(token) - 1;
    }

    dados->tamanhoRegistro = 31 + dados->tamanhoModelo + dados->tamanhoCategoria;
}

//Pega a string lida no laço e faz a separação com base nas vírgulas
void filtrar_buffer_linha(char *buffer, cabecalho_linha *cabecalho, dados_linha *dados)  {

    char *token, auxiliar[100];

    //Recebe o código da linha e passa pra string
    token = strtok(buffer, ",");
    strcpy(auxiliar, token);

    //Trata o caso em que o registro está removido; se não estiver, converte a string pra inteiro
    if (auxiliar[0] == '*')
    {
        for (int i = 0; i < 3; i++)
        {
            if (i != 2)
                auxiliar[i] = auxiliar[i + 1];
            else
                auxiliar[i] = '\0';
        }
        cabecalho->nroRegRemovidos++;
        dados->removido = '0';
    }
    else
    {
        cabecalho->nroRegistros++;
        dados->removido = '1';
    }
    dados->codLinha = atoi(auxiliar);

    //Recebe o aceita cartão e passa pra string auxiliar
    token = strtok(NULL, ",");
    strcpy(auxiliar, token);

    //Trata o caso em que temos uma variável nula
    if (strcmp(auxiliar, "NULO") == 0)
        dados->aceitaCartao = '\0';
    else
        dados->aceitaCartao = auxiliar[0];

    //Recebe o nome da linha
    token = strtok(NULL, ",");

    //Se nulo, alocamos um único byte e preenchemos ele com \0
    if (strcmp(token, "NULO") == 0)
    {
        dados->nomeLinha = (char *)malloc(sizeof(char));
        dados->nomeLinha[0] = '\0';
        dados->tamanhoNome = 0;
    }
    //Caso contrário, alocamos o tamanho do token+1, para armazenarmos o \0
    else
    {
        dados->nomeLinha = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(dados->nomeLinha, token);
        dados->tamanhoNome = strlen(token);
    }

    //Recebe nome da cor
    token = strtok(NULL, ",");

    //Se nulo, alocamos um único byte e preenchemos ele com \0
    if (strcmp(token, "NULO") == 0)
    {
        dados->corLinha = (char *)malloc(sizeof(char));
        dados->corLinha[0] = '\0';
        dados->tamanhoCor = 0;
    }
    //Caso contrário, alocamos o tamanho de token e substituímos o \n recebido por um \0
    else
    {
        dados->corLinha = malloc(sizeof(char) * (strlen(token)));
        strcpy(dados->corLinha, token);
        dados->corLinha[strlen(token) - 1] = '\0';
        dados->tamanhoCor = strlen(token) - 1;
    }

    dados->tamanhoRegistro = 13 + dados->tamanhoNome + dados->tamanhoCor;
}

//Funcao responsavle pela leitura do cabecalho dos veiculos no arquivo binario
void le_cabecalho_veiculo(FILE *fp_bin, cabecalho_veiculo *cabecalho){
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
void le_cabecalho_linha(FILE *fp_bin, cabecalho_linha *cabecalho){      

    fread(&cabecalho->status, sizeof(char), 1, fp_bin);
    fread(&cabecalho->byteProxReg, sizeof(long long), 1, fp_bin);
    fread(&cabecalho->nroRegistros, sizeof(int), 1, fp_bin);
    fread(&cabecalho->nroRegRemovidos, sizeof(int), 1, fp_bin);
    fread(&cabecalho->descreveCodigo, sizeof(char), 15, fp_bin);
    fread(&cabecalho->descreveCartao, sizeof(char), 13, fp_bin);
    fread(&cabecalho->descreveNome, sizeof(char), 13, fp_bin);
    fread(&cabecalho->descreveCor, sizeof(char), 24, fp_bin);
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
