//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include "ORDENACAO.h"

void ORDENACAO(int c) {

    // Lê nome os nomes dos arquivos e dos campos que vão ser procurados
    char arq_desordenado[30], arq_ordenado[50], campo_ordenacao[30];
    scanf(" %s", arq_desordenado);
    scanf(" %s", arq_ordenado);
    scanf(" %s", campo_ordenacao);

    // Checando se tem falha na abertura dos arquivos
    FILE *fp_ord, *fp_des;
    if(!abertura_arquivo(&fp_des, arq_desordenado, "rb")) return;
    if(!abertura_arquivo(&fp_ord, arq_ordenado, "wb")) return;

    // Se for ordenação de veículo
    if(c == 17){

        cabecalho_veiculo *cabecalho_v = le_cabecalho_veiculo(fp_des);

        // Se houver inconsistência no arquivo, encerra
        if(cabecalho_v->status == '0') {
            printf("Falha no processamento do arquivo.\n");
            free(cabecalho_v);
            return;
        }

        // Se não houver registros no arquivo, encerra
        if(cabecalho_v->nroRegistros == 0) {
            printf("Registro inexistente.\n");
            free(cabecalho_v);
            return;
        }

        // Inicializamos o status como inconsistente
        cabecalho_v->status = '0';

        ordena_arquivo(fp_ord, fp_des, 17, NULL, cabecalho_v);
        free(cabecalho_v);

        // Atualiza cabecalho
        cabecalho_v->status = '1';
        escreve_cabecalho_veiculo(fp_des, *cabecalho_v);
    }

    // Se for ordenação de linha
    if(c == 18){
        cabecalho_linha *cabecalho_l = le_cabecalho_linha(fp_des);

        // Se houver inconsistência, encerra
        if(cabecalho_l->status == '0') {
            printf("Falha no processamento do arquivo.\n");
            free(cabecalho_l);
            return;
        }

        // Se não houver registros no arquivo, encerra
        if(cabecalho_l->nroRegistros == 0) {
            printf("Registro inexistente.\n");
            free(cabecalho_l);
            return;
        }

        // Inicializa status
        cabecalho_l->status = '0';

        ordena_arquivo(fp_ord, fp_des, 18, cabecalho_l, NULL);
        free(cabecalho_l);
        
        // Atualiza cabecalho
        cabecalho_l->status = '1';
        escreve_cabecalho_linha(fp_des, *cabecalho_l);
    }

    fclose(fp_ord);
    binarioNaTela(arq_ordenado);
}