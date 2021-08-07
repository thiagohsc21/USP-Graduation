//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include "LOOP_UNICO.h"

void LOOP_UNICO() {

    // Lê nome os nomes dos arquivos e dos campos que vão ser procurados
    char nome_veiculo[30], nome_linha[30], codLinha_v[15], codLinha_l[15], indiceLinha[30];
    scanf(" %s", nome_veiculo);
    scanf(" %s", nome_linha);
    scanf(" %s", codLinha_v);   
    scanf(" %s", codLinha_l);
    scanf(" %s", indiceLinha);    

    // Checando se tem falha na abertura dos arquivos
    FILE *fp_v, *fp_l, *fp_index;
    if(!abertura_arquivo(&fp_v, nome_veiculo, "rb")) return;
    if(!abertura_arquivo(&fp_l, nome_linha, "rb")) return;
    if(!abertura_arquivo(&fp_index, indiceLinha, "rb")) return;

    cabecalho_veiculo *cabecalho_v = le_cabecalho_veiculo(fp_v);
    cabecalho_linha *cabecalho_l = le_cabecalho_linha(fp_l);
    cabecalho_arvB *cabecalho_arv = le_cabecalho_arvore(fp_index);

    // Checa o caso de haver inconsistencia em algum dos arquivos e, portanto, não terá junção
    if(cabecalho_v->status == '0' || cabecalho_l->status == '0' || cabecalho_arv->status == '0') {
        printf("Falha no processamento do arquivo.\n");
        free(cabecalho_v);
        free(cabecalho_l);
        free(cabecalho_arv);
        return;
    }

    // Checa o caso de não haver registros em algum dos arquivos e, portanto, não terá junção
    if(cabecalho_v->nroRegistros == 0 || cabecalho_l->nroRegistros == 0 || cabecalho_arv->noRaiz == -1){
        printf("Registro inexistente.\n");
        free(cabecalho_v);
        free(cabecalho_l);
        free(cabecalho_arv);
        return;
    }

    // Inicializamos o status como inconsistente
    cabecalho_v->status = '0';
    cabecalho_l->status = '0';
    cabecalho_arv->status = '0';

    dados_veiculo *dados_v = (dados_veiculo*) malloc(sizeof(dados_veiculo));
    int existe_reg;

    // Percorre registros de veiculo
    while(fread(&dados_v->removido, sizeof(char), 1, fp_v) != 0) {
        
        fread(&dados_v->tamanhoRegistro, sizeof(int), 1, fp_v);

        //Se o registro estiver marcado como removido, pulamos ele
        if(dados_v->removido == '0') fseek(fp_v, dados_v->tamanhoRegistro, SEEK_CUR);
    
        // Realiza a busca do valor passado como parâmetro no índice da árvore B
        else {
            recebe_dados_veiculo(fp_v, dados_v);

            // existe_reg = 1 se encontrou, 0 se não encontrou
            existe_reg = busca_dados_indice(fp_l, fp_index, dados_v, cabecalho_v, cabecalho_l, cabecalho_arv);
        }

        free(dados_v->modelo);
        free(dados_v->categoria);
        dados_v->modelo = NULL;
        dados_v->categoria = NULL;
    }

    // Caso não tenha encontrado
    if(!existe_reg) printf("Registro inexistente.\n");

    // Atualizamos cabecalhos
    cabecalho_v->status = '1';
    cabecalho_l->status = '1';
    cabecalho_arv->status = '1';
    escreve_cabecalho_veiculo(fp_v, *cabecalho_v);
    escreve_cabecalho_linha(fp_l, *cabecalho_l);
    escreve_cabecalho_arvore(fp_index, cabecalho_arv);

    free(fp_v);
    free(fp_l);
    free(fp_index);
    free(dados_v);
    free(cabecalho_v);
    free(cabecalho_l);
    free(cabecalho_arv);
}