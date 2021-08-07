//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include "SELECT.h"
#include "funcoesLeitura.h"
#include "funcoesEscrita.h"
#include "funcao-fornecida.h"


void SELECT_FROM(char c){

    // Recebe nome do binário que deseja ler
    char nome_bin[15];
    scanf("%s", nome_bin); 

    // Caso haja falha na abertura do arquivo
    FILE *fp_bin = fopen(nome_bin, "rb");
    if (fp_bin == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }  

    // Se for escolhida a opção de select_from no veículo
    if(c == '3'){

        cabecalho_veiculo *cabecalho = (cabecalho_veiculo*) malloc(sizeof(cabecalho_veiculo));

        //Coloca na RAM o cabecalho do arquivo binario
        le_cabecalho_veiculo(fp_bin, cabecalho);
        
        // Checa o caso de não haver registros no arquivo
        if(cabecalho->nroRegistros == 0) {
            printf("Registro inexistente.\n");
            return;
        }

        dados_veiculo *dados = (dados_veiculo*) malloc(sizeof(dados_veiculo));

        //Laço para ler cada uma das linhas do arquivo binario
        while(fread(&dados->removido, sizeof(char), 1, fp_bin) != 0){

            fread(&dados->tamanhoRegistro, sizeof(int), 1, fp_bin);

            //Se o registro estiver marcado como removido, pulamos ele
            if(dados->removido == '0') fseek(fp_bin, dados->tamanhoRegistro, SEEK_CUR);

            //Caso contrário, recebemos cada um dos dados e imprimimos na tela
            else{
                recebe_dados_veiculo(fp_bin, dados);
                printa_veiculo(dados, cabecalho);

                free(dados->modelo);
                free(dados->categoria);
                dados->modelo = NULL;
                dados->categoria = NULL;
            }
        }

        free(cabecalho);
        free(dados);
    }

    // Se for escolhida a opção de select_from na linha
    if(c == '4'){

        cabecalho_linha *cabecalho = (cabecalho_linha*) malloc(sizeof(cabecalho_linha));

        //Coloca na RAM o cabecalho do arquivo binario
        le_cabecalho_linha(fp_bin, cabecalho);

        // Checa o caso de não haver registros no arquivo
        if(cabecalho->nroRegistros == 0) {
            printf("Registro inexistente.\n");
            return;
        }

        dados_linha *dados = (dados_linha*) malloc(sizeof(dados_linha));
        
        //Laço para ler cada uma das linhas do arquivo binario
        while(fread(&dados->removido, sizeof(char), 1, fp_bin) != 0){

            fread(&dados->tamanhoRegistro, sizeof(int), 1, fp_bin);

            //Se o registro estiver marcado como removido, pulamos ele
            if(dados->removido == '0') fseek(fp_bin, dados->tamanhoRegistro, SEEK_CUR);

            //Caso contrário, recebemos cada um dos dados e imprimimos na tela
            else{         
                recebe_dados_linha(fp_bin, dados);
                printa_linha(dados, cabecalho);

                free(dados->nomeLinha);
                free(dados->corLinha);
                dados->nomeLinha = NULL;
                dados->corLinha = NULL;
            }
        }

        free(cabecalho);
        free(dados);
    }

    fclose(fp_bin);
}


void SELECT_WHERE(char c){
    
    char nome_bin[15], nome_campo[30], valor[30];
    scanf("%s", nome_bin); 
    scanf("%s", nome_campo); 
    scan_quote_string(valor); 

    FILE *fp_bin = fopen(nome_bin, "rb");
    if (fp_bin == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }  

    // Se for escolhida a opção de select_where no veículo
    if(c == '5'){

        cabecalho_veiculo *cabecalho = (cabecalho_veiculo*) malloc(sizeof(cabecalho_veiculo));

        //Coloca na RAM o cabecalho do arquivo binario
        le_cabecalho_veiculo(fp_bin, cabecalho);
        
        int existe_registro = 0;
        dados_veiculo *dados = (dados_veiculo*) malloc(sizeof(dados_veiculo));

        //Laço para ler cada uma das linhas do arquivo binario
        while(fread(&dados->removido, sizeof(char), 1, fp_bin) != 0){

            fread(&dados->tamanhoRegistro, sizeof(int), 1, fp_bin);

            //Se o registro estiver marcado como removido, pulamos ele
            if(dados->removido == '0') fseek(fp_bin, dados->tamanhoRegistro, SEEK_CUR);

            //Caso contrário, recebemos cada um dos dados e imprimimos na tela os buscados
            else{   
                recebe_dados_veiculo(fp_bin, dados);

                //Verifica se o valor passado é igual a pelo menos um dos valores do registro
                if(strcmp(valor, dados->prefixo) == 0 || strcmp(valor, dados->data) == 0 ||atoi(valor) == 
                dados->quantidadeLugares || strcmp(valor, dados->modelo) == 0 || strcmp(valor, dados->categoria) == 0){
                    printa_veiculo(dados, cabecalho);
                    existe_registro = 1;
                }              

                free(dados->modelo);
                free(dados->categoria);
                dados->modelo = NULL;
                dados->categoria = NULL;
            }
        }

        free(dados);
        free(cabecalho);
        
        // Caso não exista o registro
        if(!existe_registro) printf("Registro inexistente.\n");
    }

    // Se for escolhida a opção de select_where na linha
    if(c == '6'){

         cabecalho_linha *cabecalho = (cabecalho_linha*) malloc(sizeof(cabecalho_linha));

        //Coloca na RAM o cabecalho do arquivo binario
        le_cabecalho_linha(fp_bin, cabecalho);
        
        int existe_registro = 0;
        dados_linha *dados = (dados_linha*) malloc(sizeof(dados_linha));

        //Laço para ler cada uma das linhas do arquivo binario
        while(fread(&dados->removido, sizeof(char), 1, fp_bin) != 0){

            fread(&dados->tamanhoRegistro, sizeof(int), 1, fp_bin);

            //Se o registro estiver marcado como removido, pulamos ele
            if(dados->removido == '0') fseek(fp_bin, dados->tamanhoRegistro, SEEK_CUR);

            //Caso contrário, recebemos cada um dos dados e imprimimos na tela
            else{
                recebe_dados_linha(fp_bin, dados);

                //Verifica se o valor passado é igual a pelo menos um dos valores do registro
                if(atoi(valor) == dados->codLinha || valor[0] == dados->aceitaCartao || 
                strcmp(valor, dados->nomeLinha) == 0 || strcmp(valor, dados->corLinha) == 0){
                    printa_linha(dados, cabecalho);
                    existe_registro = 1;
                }

                free(dados->nomeLinha);
                free(dados->corLinha);
                dados->nomeLinha = NULL;
                dados->corLinha = NULL;
            }
        }

        free(cabecalho);
        free(dados);

        // Caso não exista o registro
        if(!existe_registro) printf("Registro inexistente.\n");
    }

    fclose(fp_bin);
}

