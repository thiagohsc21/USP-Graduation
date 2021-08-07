//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include "INSERT_INTO.h"
#include "funcoesLeitura.h"
#include "funcoesEscrita.h"
#include "funcao-fornecida.h"

void INSERT_INTO(char c){

    // Lê nome do binário que deseja inserir
    char nome_bin[15];
    scanf("%s", nome_bin); 

    // Checa se não há erro na abertura do arquivo 
    FILE *fp_bin = fopen(nome_bin, "rb+");
    if (fp_bin == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }      

    // Se for escolhida a opção de inserir registro no veículo
    if(c == '7'){   

        cabecalho_veiculo *cabecalho = (cabecalho_veiculo*) malloc(sizeof(cabecalho_veiculo));

        le_cabecalho_veiculo(fp_bin, cabecalho);

        // Se houver inconsistência no arquivo, encerra
        if(cabecalho->status == '0'){
            printf("Falha no processamento do arquivo.\n");
            return;
        }

        // Inicializa o status com 0
        cabecalho->status = '0';

        // Coloca o ponteiro no fim do arquivo, onde será inserido o novo registro
        fseek(fp_bin, cabecalho->byteProxReg, SEEK_SET);

        // Lê a quantidade de registros a ser inserido
        int n;
        scanf("%d", &n); 

        dados_veiculo *dados = (dados_veiculo*) malloc(sizeof(dados_veiculo));

        while(n--){

            // Insere veiculo 
            insere_veiculo(cabecalho, dados);

            // Insere os registros no arquivo
            escreve_dados_veiculo(fp_bin, dados);

            free(dados->categoria);
            free(dados->modelo);
            dados->categoria = NULL;
            dados->modelo = NULL;
        }
        
        //Seta o arquivo como estavel 
        cabecalho->status = '1';

        //Recebe a posição atual do ponteiro e após isso, o desloca para o início do arquivo
        cabecalho->byteProxReg = ftell(fp_bin);
        fseek(fp_bin, 0, SEEK_SET);

        //Escreve o novo registro de cabecalho no arquivo.bin
        escreve_cabecalho_veiculo(fp_bin, *cabecalho);

        free(dados);
        free(cabecalho);
    }


    // Se for escolhida a opção de inserir registro na linha
    if(c == '8'){

        cabecalho_linha *cabecalho = (cabecalho_linha*) malloc(sizeof(cabecalho_linha));

        //Coloca na RAM o cabecalho do arquivo binario
        le_cabecalho_linha(fp_bin, cabecalho);

        // Se houver inconsistência no arquivo, encerra
        if(cabecalho->status == '0'){
            printf("Falha no processamento do arquivo.\n");
            return;
        }

        // Inicializa o status com 0
        cabecalho->status = '0';

        // Coloca o ponteiro no fim do arquivo, onde será inserido o novo registro
        fseek(fp_bin, cabecalho->byteProxReg, SEEK_SET);

        // Lê a quantidade de registros a ser inserido
        int n;
        scanf("%d", &n); 

        dados_linha *dados = (dados_linha*) malloc(sizeof(dados_linha));

        while(n--){

            // Insere veiculo 
            insere_linha(cabecalho, dados);

            // Insere os registros no arquivo
            escreve_dados_linha(fp_bin, dados);

            free(dados->nomeLinha);
            free(dados->corLinha);
            dados->nomeLinha = NULL;
            dados->corLinha = NULL;
        }

        //Seta o arquivo como estavel 
        cabecalho->status = '1';

        //Recebe a posição atual do ponteiro e após isso, o desloca para o início do arquivo
        cabecalho->byteProxReg = ftell(fp_bin);
        fseek(fp_bin, 0, SEEK_SET);

        //Escreve o novo registro de cabecalho no arquivo.bin
        escreve_cabecalho_linha(fp_bin, *cabecalho);
        
        free(dados);
        free(cabecalho);
    }

    fclose(fp_bin);
    binarioNaTela(nome_bin);
}

