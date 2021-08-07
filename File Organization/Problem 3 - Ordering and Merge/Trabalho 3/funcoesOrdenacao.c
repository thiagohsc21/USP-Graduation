//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include "funcoesOrdenacao.h"

// Função de comparação usada no qsort()
int comparadorRegistrosVeiculo(const void *p1, const void *p2){
    if((*(dados_veiculo**)p1)->codLinha < (*(dados_veiculo**)p2)->codLinha) return -1;
    if((*(dados_veiculo**)p1)->codLinha == (*(dados_veiculo**)p2)->codLinha) return 0;
    if((*(dados_veiculo**)p1)->codLinha > (*(dados_veiculo**)p2)->codLinha) return 1;
}

// Função de comparação usada no qsort()
int comparadorRegistrosLinha(const void *p1, const void *p2){
    if((*(dados_linha**)p1)->codLinha < (*(dados_linha**)p2)->codLinha) return -1;
    if((*(dados_linha**)p1)->codLinha == (*(dados_linha**)p2)->codLinha) return 0;
    if((*(dados_linha**)p1)->codLinha > (*(dados_linha**)p2)->codLinha) return 1;
}

// Função responsável pela ordenação do arquivo
void ordena_arquivo(FILE *fp_ord, FILE *fp_des, int tipo, cabecalho_linha *cabecalho_l, cabecalho_veiculo *cabecalho_v){

    // Se quisermos ordenar um arquivo do tipo veículo
    if(tipo == 17){
        
        // Inicializamos o status como inconsistente
        cabecalho_v->status = '0';

        // Aloca uma matriz na qual cada linha representará um dos dados do veículo
        dados_veiculo **dados_ram = (dados_veiculo**) malloc(cabecalho_v->nroRegistros*sizeof(dados_veiculo*));
        dados_ram[0] = (dados_veiculo*) malloc(sizeof(dados_veiculo));

        // (i) Passa para a RAM todo o arquivo de dados desordenado
        for(int i = 0; i < cabecalho_v->nroRegistros; i++) {

            fread(&dados_ram[i]->removido, sizeof(char), 1, fp_des);
            fread(&dados_ram[i]->tamanhoRegistro, sizeof(int), 1, fp_des);

            // Se o registro estiver marcado como removido, pulamos ele
            if(dados_ram[i]->removido == '0') {
                fseek(fp_des, dados_ram[i]->tamanhoRegistro, SEEK_CUR);
                i--; // Subtraimos 1 de i pois não devemos computar registros removidos
            }

            else {
                recebe_dados_veiculo(fp_des, dados_ram[i]);
                if(i != cabecalho_v->nroRegistros-1) dados_ram[i+1] = (dados_veiculo*) malloc(sizeof(dados_veiculo));
            }
        }

        fclose(fp_des);
       
        // (ii) Realiza a ordenação desses dados armazenados na matriz dados_ram
        qsort(dados_ram, cabecalho_v->nroRegistros, sizeof(dados_veiculo*), comparadorRegistrosVeiculo);

        // (iii) Escreve os dados ordenados para um arquivo de saída apontado por fp_ord
        escreve_cabecalho_veiculo(fp_ord, *cabecalho_v);

        for(int i = 0; i < cabecalho_v->nroRegistros; i++) {
            escreve_dados_veiculo(fp_ord, dados_ram[i]);
            free(dados_ram[i]);
        }

        free(dados_ram);
        
        // Como o registro ordenado não deve ter registros logicamente removidos,
        // então setamos o numero de registros removidos como zero
        cabecalho_v->nroRegRemovidos = 0;
        cabecalho_v->status = '1';
        cabecalho_v->byteProxReg = ftell(fp_ord);
        escreve_cabecalho_veiculo(fp_ord, *cabecalho_v);
    }

    // Se quisermos ordenar um arquivo do tipo linha
    if(tipo == 18){
        
        // Inicializamos o status como inconsistente
        cabecalho_l->status = '0';

        // Aloca uma matriz na qual cada linha representará um dos dados da linha
        dados_linha **dados_ram = (dados_linha**) malloc(cabecalho_l->nroRegistros*sizeof(dados_linha*));
        dados_ram[0] = (dados_linha*) malloc(sizeof(dados_linha));

        // (i) Passa para a RAM todo o arquivo de dados desordenado
        for(int i = 0 ; i < cabecalho_l->nroRegistros ; i++) {

            fread(&dados_ram[i]->removido, sizeof(char), 1, fp_des);
            fread(&dados_ram[i]->tamanhoRegistro, sizeof(int), 1, fp_des);

            // Se o registro estiver marcado como removido, pulamos ele
            if(dados_ram[i]->removido == '0') {
                fseek(fp_des, dados_ram[i]->tamanhoRegistro, SEEK_CUR);
                i--; // Subtraimos um de i pois para registros removidos, não devemos armazenar
            }

            else {
                recebe_dados_linha(fp_des, dados_ram[i]);
                if(i != cabecalho_l->nroRegistros-1) dados_ram[i+1] = (dados_linha*) malloc(sizeof(dados_linha));
            }
        }
        fclose(fp_des);

        // (ii) Realiza a ordenação desses dados armazenados na matriz dados_ram
        qsort(dados_ram, cabecalho_l->nroRegistros, sizeof(dados_linha*), comparadorRegistrosLinha);

        // (iii) Escreve os dados ordenados para um arquivo de saída apontado por fp_ord
        escreve_cabecalho_linha(fp_ord, *cabecalho_l);

        for(int i = 0 ; i < cabecalho_l->nroRegistros ; i++) {
            escreve_dados_linha(fp_ord, dados_ram[i]);
            free(dados_ram[i]);
        }
        free(dados_ram);

        // Como o registro ordenado não deve ter registros logicamente removidos,
        // então setamos o numero de registros removidos como zero
        cabecalho_l->nroRegRemovidos = 0;
        cabecalho_l->status = '1';
        cabecalho_l->byteProxReg = ftell(fp_ord); 
        escreve_cabecalho_linha(fp_ord, *cabecalho_l);
    }
}
