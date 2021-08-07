//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include "CREATE_TABLE.h"
#include "funcoesLeitura.h"
#include "funcoesEscrita.h"
#include "funcao-fornecida.h"


void CREATE_TABLE(char c) {

    // Lê nome do csv que será lido e nome do binário que será criado
    char nome_csv[15], nome_bin[15];
    scanf("%s", nome_csv);
    scanf("%s", nome_bin);

    // Checa caso de falha na abertura dos arquivos
    FILE *fp_csv = fopen(nome_csv, "r");
    if (fp_csv == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }   

    FILE *fp_bin = fopen(nome_bin, "wb");
    if (fp_bin == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }   
    
    // Se for escolhida a opção de criar um arquivo de veículo
    if(c == '1') {

        //Inicializa o cabecalho; recebemos com fread um valor a mais para processar as vírgulas
        cabecalho_veiculo cabecalho;
        cabecalho.status = '0';
        cabecalho.byteProxReg = 175;
        cabecalho.nroRegistros = 0;
        cabecalho.nroRegRemovidos = 0;
        fread(&cabecalho.descrevePrefixo, sizeof(char), 19, fp_csv);
        fread(&cabecalho.descreveData, sizeof(char), 36, fp_csv);
        fread(&cabecalho.descreveLugares, sizeof(char), 43, fp_csv);
        fread(&cabecalho.descreveLinha, sizeof(char), 27, fp_csv);
        fread(&cabecalho.descreveModelo, sizeof(char), 18, fp_csv);
        fread(&cabecalho.descreveCategoria, sizeof(char), 21, fp_csv);       

        //Escreve o cabecalho no arquivo binario
        escreve_cabecalho_veiculo(fp_bin, cabecalho);

        dados_veiculo *dados = (dados_veiculo*) malloc(sizeof(dados_veiculo));

        //Percorre linha a linha do csv
        char buffer[70];
        while(fgets(buffer, sizeof(buffer), fp_csv) != NULL) {  
            
            //Trata cada um dos campos e armazena na struct dados
            filtrar_buffer_veiculo(buffer, &cabecalho, dados);
                        
            //Passa pro arquivo binário o que foi lido
            escreve_dados_veiculo(fp_bin, dados);

            free(dados->categoria);
            free(dados->modelo);
            dados->categoria = NULL;
            dados->modelo = NULL;        
        }

        //Seta o arquivo como estável
        cabecalho.status = '1';
        
        //Recebe a posição atual do ponteiro e após isso, o desloca para o início do arquivo
        cabecalho.byteProxReg = ftell(fp_bin);
        fseek(fp_bin, 0, SEEK_SET);

        //Escreve o novo cabecalho no arquivo binário
        escreve_cabecalho_veiculo(fp_bin, cabecalho);

        free(dados);
    }


    // Se for escolhida a opção de criar um arquivo de linha
    else if(c == '2') {

        //Inicializa o cabecalho; recebemos com fread um valor a mais para processar as vírgulas
        cabecalho_linha cabecalho;
        cabecalho.status = '0';
        cabecalho.byteProxReg = 82;
        cabecalho.nroRegistros = 0;
        cabecalho.nroRegRemovidos = 0;
        fread(&cabecalho.descreveCodigo, sizeof(char), 16, fp_csv);
        fread(&cabecalho.descreveCartao, sizeof(char), 14, fp_csv);
        fread(&cabecalho.descreveNome, sizeof(char), 14, fp_csv);
        fread(&cabecalho.descreveCor, sizeof(char), 25, fp_csv);

        //Escreve o cabecalho no arquivo binario
        escreve_cabecalho_linha(fp_bin, cabecalho);

        dados_linha *dados = (dados_linha*) malloc(sizeof(dados_linha));

        //Percorre linha a linha do csv
        char buffer[50];
        while(fgets(buffer, sizeof(buffer), fp_csv) != NULL){

            //Trata cada um dos campos e armazena na struct dados
            filtrar_buffer_linha(buffer, &cabecalho, dados);

            //Passa pro arquivo binário o que foi lido
            escreve_dados_linha(fp_bin, dados);            

            free(dados->nomeLinha);
            free(dados->corLinha);
            dados->nomeLinha = NULL;
            dados->corLinha = NULL;
        }

        //Seta o arquivo como estável 
        cabecalho.status = '1';

        //Recebe a posição atual do ponteiro e após isso, o desloca para o início do arquivo
        cabecalho.byteProxReg = ftell(fp_bin);
        fseek(fp_bin, 0, SEEK_SET);

        //Escreve o novo registro de cabecalho no arquivo.bin
        escreve_cabecalho_linha(fp_bin, cabecalho);

        free(dados);
    }
    
    fclose(fp_csv);
    fclose(fp_bin);
    binarioNaTela(nome_bin);   
}

