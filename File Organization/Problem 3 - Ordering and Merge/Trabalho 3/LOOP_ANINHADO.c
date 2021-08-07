//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include "LOOP_ANINHADO.h"

void LOOP_ANINHADO(int c) {
    
    // Lê nome os nomes dos arquivos e dos campos que vão ser procurados
    char nome_veiculo[30], nome_linha[30], codLinha_v[15], codLinha_l[15];
    scanf(" %s", nome_veiculo);
    scanf(" %s", nome_linha);
    scanf(" %s", codLinha_v);
    scanf(" %s", codLinha_l);    

    // Checando se tem falha na abertura dos arquivos
    FILE *fp_v, *fp_l;
    if(!abertura_arquivo(&fp_v, nome_veiculo, "rb")) return;
    if(!abertura_arquivo(&fp_l, nome_linha, "rb")) return;

    cabecalho_veiculo *cabecalho_v = le_cabecalho_veiculo(fp_v);
    cabecalho_linha *cabecalho_l = le_cabecalho_linha(fp_l);
        
    // Checa o caso de não haver inconsistência em algum dos dois arquivos e, portanto, não terá junção
    if(cabecalho_v->status == '0' || cabecalho_l->status == '0') {
        printf("Falha no processamento do arquivo.\n");
        free(cabecalho_l);
        free(cabecalho_v);        
        return;
    }

    // Checa o caso de não haver registros em algum dos dois arquivos e, portanto, não terá junção
    if(cabecalho_v->nroRegistros == 0 || cabecalho_l->nroRegistros == 0) {
        printf("Registro Inexistente.\n");
        free(cabecalho_l);
        free(cabecalho_v);
        return;
    }

    // Inicializamos o status como inconsistente
    cabecalho_v->status = '0';
    cabecalho_l->status = '0';

    // Aloca espaço para dados de veiculo e de linha
    dados_veiculo *dados_v = (dados_veiculo*) malloc(sizeof(dados_veiculo));
    dados_linha *dados_l = (dados_linha*) malloc(sizeof(dados_linha));

    int existe_registro = 0;

    // Para cada um dos registros lidos de veiculo, lê todos os registros de linha e checa se veiculo.codLinha = linha.codLinha
    while(fread(&dados_v->removido, sizeof(char), 1, fp_v) != 0) {

        fread(&dados_v->tamanhoRegistro, sizeof(int), 1, fp_v);

        // Se o registro estiver marcado como removido, pulamos ele
        if(dados_v->removido == '0') fseek(fp_v, dados_v->tamanhoRegistro, SEEK_CUR);

        else{
            
            recebe_dados_veiculo(fp_v, dados_v);

            // Percorre os registros de linha
            while(fread(&dados_l->removido, sizeof(char), 1, fp_l) != 0) {
                
                fread(&dados_l->tamanhoRegistro, sizeof(int), 1, fp_l); 

                //Se o registro estiver marcado como removido, pulamos ele
                if(dados_l->removido == '0') fseek(fp_l, dados_l->tamanhoRegistro, SEEK_CUR);

                else {
                    recebe_dados_linha(fp_l, dados_l);

                    // Se veiculo.codLinha = linha.codLinha, printa os dados do veiculo e depois da linha
                    if(dados_v->codLinha == dados_l->codLinha) {
                        printa_veiculo(dados_v, cabecalho_v);
                        printa_linha(dados_l, cabecalho_l);
                        existe_registro = 1;
                        break;
                    }
                }

                free(dados_l->nomeLinha);
                free(dados_l->corLinha);
                dados_l->nomeLinha = NULL;
                dados_l->corLinha = NULL;
            }

            // Reposiciona o ponteiro do arquivo de linhas no início dos registros
            fseek(fp_l, 82*sizeof(char), SEEK_SET);
        }
  
        free(dados_v->modelo);
        free(dados_v->categoria);
        dados_v->modelo = NULL;
        dados_v->categoria = NULL;
    }

    // Se não exisitir nenhum veiculo.codLinha = linha.codLinha
    if(!existe_registro) printf("Registro inexistente.\n");

    // Atualiza cabecalho
    cabecalho_v->status = '1';
    cabecalho_l->status = '1';
    escreve_cabecalho_veiculo(fp_v, *cabecalho_v);
    escreve_cabecalho_linha(fp_l, *cabecalho_l);

    free(fp_l);
    free(fp_v);    
    free(dados_l);
    free(dados_v);
    free(cabecalho_l);
    free(cabecalho_v);
}