//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include "RECOVER_DATA.h"
#include "funcoesFornecidas.h"
#include "funcoesLeitura.h"

void RECOVER_DATA(int c) {

    // Lê nome do csv que será lido e nome do binário que será criado
    char nome_bin[30], nome_index[30];
    scanf(" %s", nome_bin);
    scanf(" %s", nome_index);

    // Checando se tem falha na abertura dos arquivos
    FILE *fp_bin, *fp_index;
    if(!abertura_arquivo(&fp_bin, &fp_index, nome_bin, nome_index, "rb", "rb")) exit(EXIT_FAILURE);
    
    // Se for busca no arquivo de veiculo
    if(c == 11) {
        // Lê o "prefixo" e o valor
        char prefixo[8], valor[15];
        scanf("%s", prefixo);
        scan_quote_string(valor);
        
        // Converte o valor para inteiro e o passa para função de busca
        int valor_chave = convertePrefixo(valor);
        busca_dados_indice(fp_bin, fp_index, valor_chave, c);
    }

    // Se for busca no arquivo de linha
    else if(c == 12) {
        // Lê o "codLinha" e o valor
        char codLinha[10];
        int valor;
        scanf("%s", codLinha);
        scanf("%d", &valor);

        // Passa o valor para a função de busca
        busca_dados_indice(fp_bin, fp_index, valor, c);
    }

    fclose(fp_bin);
    fclose(fp_index);
}