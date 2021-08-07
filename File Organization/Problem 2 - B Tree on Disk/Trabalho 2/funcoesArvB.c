//Laís Saloum Deghaide, nUSP: 11369767
//Thiago Henrique dos Santos Cardoso, nUSP: 11796594

#include "funcoesArvB.h"
#include "funcoesLeitura.h"
#include "funcoesEscrita.h"
#include "funcoesFornecidas.h"

// Função que nos auxilia na escrita de cada um dos campos do cabecalho da arvore, alocando lixo no fim
void escreve_cabecalho_arvore(FILE *fp, cabecalho_arvB *cabecalho) {

    fseek(fp, 0, SEEK_SET);
    fwrite(&cabecalho->status, sizeof(char), 1, fp);
    fwrite(&cabecalho->noRaiz, sizeof(int), 1, fp);
    fwrite(&cabecalho->RRNproxNo, sizeof(int), 1, fp);

    char aux = '@'; 
    for(int i=0; i<68; i++) fwrite(&aux, sizeof(char), 1, fp);

}

// Função responsável pela leitura dos campos do cabecalho da arvore
cabecalho_arvB *le_cabecalho_arvore(FILE *fp) {

    cabecalho_arvB *cabecalho = (cabecalho_arvB*) malloc(sizeof(cabecalho_arvB));
    fseek(fp, 0, SEEK_SET);
    fread(&cabecalho->status, sizeof(char), 1, fp);
    fread(&cabecalho->noRaiz, sizeof(int), 1, fp);
    fread(&cabecalho->RRNproxNo, sizeof(int), 1, fp);

    char lixo[68];
    fread(lixo, sizeof(char), 68, fp);

    return cabecalho;
}

// Função responsável pela escrita das paginas de disco
void escreve_no_arvore(FILE *fp, no_arvB *no, int RRN) {

    fseek(fp, (RRN+1)*77, SEEK_SET);
    fwrite(&no->folha, sizeof(char), 1, fp);
    fwrite(&no->nroChavesIndexadas, sizeof(int), 1, fp);
    fwrite(&no->RRNdoNo, sizeof(int), 1, fp);

    for(int i=0; i<ordem_arvB-1; i++) {
        fwrite(&no->P[i], sizeof(int), 1, fp);
        fwrite(&no->C[i], sizeof(int), 1, fp);
        fwrite(&no->Pr[i], sizeof(long long), 1, fp);
    }

    fwrite(&no->P[ordem_arvB-1], sizeof(int), 1, fp);
}

// Função responsável por ler página de disco
no_arvB *le_no_arvore(FILE *fp, int RRN) {

    fseek(fp, (RRN+1)*77, SEEK_SET);
    no_arvB *no = cria_no();
    fread(&no->folha, sizeof(char), 1, fp);
    fread(&no->nroChavesIndexadas, sizeof(int), 1, fp);
    fread(&no->RRNdoNo, sizeof(int), 1, fp);

    for(int i=0; i<ordem_arvB-1; i++) {
        fread(&no->P[i], sizeof(int), 1, fp);
        fread(&no->C[i], sizeof(int), 1, fp);
        fread(&no->Pr[i], sizeof(long long), 1, fp);
    }
    fread(&no->P[ordem_arvB-1], sizeof(int), 1, fp);

    return no;
}

// Função que cria nó da árvore, preenchendo com -1 todas as posições
no_arvB *cria_no() {

    no_arvB *no = (no_arvB*) malloc(sizeof(no_arvB));
    no->folha = '0';
    no->nroChavesIndexadas = 0;

    for(int i=0; i<ordem_arvB-1; i++) {
        no->P[i] = -1;
        no->C[i] = -1;
        no->Pr[i] = -1;
    }
    no->P[ordem_arvB-1] = -1;

    return no;
}

// Função responsável pela criação do índice 
void cria_arvB(FILE *fp_bin, FILE *fp_index, int tipo) {

    // Inicializando a arvore
    cabecalho_arvB *cabecalho_arv = (cabecalho_arvB*) malloc(sizeof(cabecalho_arvB));
    cabecalho_arv->status = '0';
    cabecalho_arv->noRaiz = -1;
    cabecalho_arv->RRNproxNo = 0;
    escreve_cabecalho_arvore(fp_index, cabecalho_arv);
    
    // Se for veiculo, lê cada um dos registros e insere seus indices na árvore
    if(tipo == 9) {

        // Aloca espaço para o cabecalho, o lê e armazena os valores em cabecalho
        cabecalho_veiculo *cabecalho = le_cabecalho_veiculo(fp_bin);

        // Se houver inconsistência no arquivo, encerra
        if(cabecalho->status == '0'){
            printf("Falha no processamento do arquivo.\n");
            free(cabecalho);
            free(cabecalho_arv);
            exit(0);
        }

        // Variável que receberá cada um dos registros do arquivo de veículos 
        dados_veiculo *dados = (dados_veiculo*) malloc(sizeof(dados_veiculo));
        
        // Lê cada um dos registros de veiculo e insere os indices na arvore
        while(fread(&dados->removido, sizeof(char), 1, fp_bin) != 0) {

            fread(&dados->tamanhoRegistro, sizeof(int), 1, fp_bin);

            //Se o registro estiver marcado como removido, pulamos ele
            if(dados->removido == '0') fseek(fp_bin, dados->tamanhoRegistro, SEEK_CUR);

            else {
                // Lê o byteoffset do registro e recebe os dados
                int offset = ftell(fp_bin);
                recebe_dados_veiculo(fp_bin, dados);

                // Converte a chave para int e insere os indices na árvore
                int chave = convertePrefixo(dados->prefixo);
                insere_no(fp_index, chave, (offset-5), cabecalho_arv);

                free(dados->modelo);
                free(dados->categoria);
                dados->modelo = NULL;
                dados->categoria = NULL;
            }
        }

        free(cabecalho);
        free(dados);
    }

    // Se for linha, lê cada um dos registros e insere seus indices na árvore
    else if(tipo == 10) {
        
        // Aloca espaço para o cabecalho, lê ele e armazena os valores em cabecalho
        cabecalho_linha *cabecalho = le_cabecalho_linha(fp_bin);

        // Se houver inconsistência no arquivo, encerra
        if(cabecalho->status == '0'){
            printf("Falha no processamento do arquivo.\n");
            free(cabecalho);
            free(cabecalho_arv);
            exit(0);
        }

        // Variável que receberá cada um dos registros do arquivo de linhas
        dados_linha *dados = (dados_linha*) malloc(sizeof(dados_linha));

        // Lê cada um dos registros de veiculo e insere os indices na arvore
        while(fread(&dados->removido, sizeof(char), 1, fp_bin) != 0) {

            fread(&dados->tamanhoRegistro, sizeof(int), 1, fp_bin);

            //Se o registro estiver marcado como removido, pulamos ele
            if(dados->removido == '0') fseek(fp_bin, dados->tamanhoRegistro, SEEK_CUR);

            else{
                // Lê o byteoffset do registro e recebe os dados
                int offset = ftell(fp_bin);
                recebe_dados_linha(fp_bin, dados);

                // Insere os dados na árvore
                insere_no(fp_index, dados->codLinha, (offset-5), cabecalho_arv);

                free(dados->nomeLinha);
                free(dados->corLinha);
                dados->nomeLinha = NULL;
                dados->corLinha = NULL;
            }
        }

        free(cabecalho);
        free(dados);
    }

    // Seta como consistente e atuliza o cabecalho
    cabecalho_arv->status = '1';
    escreve_cabecalho_arvore(fp_index, cabecalho_arv);

    free(cabecalho_arv);
}

// Função recursiva da busca
int busca_recursiva(int RRN, int *byteoffset, int chave, FILE *fp_index) {

    // Chave de busca não encontrada / Caso Base
    if(RRN == -1) return 0;
    
    // Posiciona o ponteiro na pagina de disco desejada e a coloca na RAM
    no_arvB *no = le_no_arvore(fp_index, RRN);

    // Pesquisa na página, procurando a chave de busca
    for(int i = 0; i < ordem_arvB-1; i++) {

        // Se encontrou, então armazenamos seu byteoffset e saímos
        if(chave == no->C[i]) {
            *byteoffset = no->Pr[i];
            free(no);
            return 1;
        }

        // Se a chave buscada é menor que a chave[i] ou chave vazia, entao devemos descer no RRN exatamente anterior a chave[i]
        if(chave < no->C[i] || no->C[i] == -1) {
            RRN = no->P[i];
            break;
        }

        // Se entrou no if, então a chave buscada é maior que todas as outras chaves no nó, então usamos o último RRN da página (da esquerda para a direita)
        if(i == ordem_arvB-2)  RRN = no->P[ordem_arvB-1];
    }

    free(no);
    busca_recursiva(RRN, byteoffset, chave, fp_index);
}

// Função que encontra o registro que contém a chave passada no arquivo csv e o imprime
void busca_dados_indice(FILE *fp_bin, FILE *fp_index, int valor, int tipo) {

    cabecalho_arvB *cabecalho = le_cabecalho_arvore(fp_index);

    // Se houver inconsistência no arquivo, encerra
    if(cabecalho->status == '0'){
        printf("Falha no processamento do arquivo.\n");
        free(cabecalho);
        return;
    }
    
    int encontrou, byteoffset = 0;
    encontrou = busca_recursiva(cabecalho->noRaiz, &byteoffset, valor, fp_index);
    
    // Se encontramos a chave associada ao valor passado, então
    if(encontrou) {

        // Se tipo for veiculo 
        if(tipo == 11) {
            
            // Lê o cabecalho e armazena, já que o usaremos para a impressão
            cabecalho_veiculo *cabecalho_v = le_cabecalho_veiculo(fp_bin);

            // Se houver inconsistência no arquivo, encerra
            if(cabecalho_v->status == '0'){
                printf("Falha no processamento do arquivo.\n");
                free(cabecalho_v);
                free(cabecalho);
                return;
            }

            // Posiciona o ponteiro no registro que possui a chave encontrada
            fseek(fp_bin, (byteoffset+5), SEEK_SET);
            dados_veiculo *dados = (dados_veiculo*) malloc(sizeof(dados_veiculo));

            // Lê os valores do registro e printa na tela
            recebe_dados_veiculo(fp_bin, dados);
            printa_veiculo(dados, cabecalho_v);

            free(dados->modelo);
            free(dados->categoria);
            dados->modelo = NULL;
            dados->categoria = NULL;

            free(dados);
            free(cabecalho_v);
        }

        // Se tipo for linha
        else if(tipo == 12) {
            
            // Lê o cabecalho e armazena, já que o usaremos para a impressão
            cabecalho_linha *cabecalho_l = le_cabecalho_linha(fp_bin);

            // Se houver inconsistência no arquivo, encerra
            if(cabecalho_l->status == '0'){
                printf("Falha no processamento do arquivo.\n");
                free(cabecalho_l);
                free(cabecalho);
                return;
            }
                
            // Então posiciona o ponteiro no registro que possui a chave encontrada
            fseek(fp_bin, (byteoffset+5), SEEK_SET);
            dados_linha *dados = (dados_linha*) malloc(sizeof(dados_linha));

            // Lê os valores do registro e printa na tela
            recebe_dados_linha(fp_bin, dados);
            printa_linha(dados, cabecalho_l);

            free(dados->nomeLinha);
            free(dados->corLinha);
            dados->nomeLinha = NULL;
            dados->corLinha = NULL;

            free(dados);
            free(cabecalho_l);
        }
    }

    // Se o byteoffset não foi encontrado, printa "registro inexistente"
    else printf("Registro inexistente.\n");
    
    free(cabecalho);
}

// Função que trata os casos de overflow nos nós, criando uma nova página de disco e promovendo uma chave
void split(no_arvB *pagina, int *c_promo, int *pr_promo, int *p_promo, no_arvB *nova_pagina, cabecalho_arvB *cabecalho_arv) {

    // Criando pagina temporária aux que comporta uma chave a mais e inicializando todos os espaços com -1
    int aux_P[ordem_arvB+1] = {-1}; 
    int aux_C[ordem_arvB] = {-1}; 
    long long aux_Pr[ordem_arvB] = {-1}; 

    // Copia de todas as chaves e ponteiros de pagina para a pagina temporária
    for(int i=0; i<ordem_arvB-1; i++) { 
        aux_P[i] = pagina->P[i];
        aux_C[i] = pagina->C[i];
        aux_Pr[i] = pagina->Pr[i];
    }
    // Copia o RRN que faltou no laço acima
    aux_P[ordem_arvB-1] = pagina->P[ordem_arvB-1]; 

    // Shiftando todas as posições até encontrar a posição certa para inserção
    int pos = ordem_arvB-1;
    while(pos > 0 && aux_C[pos-1] > *c_promo) {
        aux_P[pos + 1] = aux_P[pos];
        aux_C[pos] = aux_C[pos - 1];
        aux_Pr[pos] = aux_Pr[pos - 1];
        pos--;
    }

    // Inserindo no local correto
    aux_P[pos+1] = *p_promo;
    aux_C[pos] = *c_promo;
    aux_Pr[pos] = *pr_promo;

    // Chave que vai ser promovida
    *pr_promo = aux_Pr[ordem_arvB/2];
    *c_promo = aux_C[ordem_arvB/2];
    *p_promo = cabecalho_arv->RRNproxNo;
    
    // Atualiza a quantidade de chaves indexadas na pagina e na nova_pagina originada do split
    pagina->nroChavesIndexadas = ordem_arvB/2;
    nova_pagina->nroChavesIndexadas = ordem_arvB/2;

    // Passa para a página inicial todas as chaves a esquerda da chave promovida e seta como -1 o restante
    for(int i=0; i<ordem_arvB-1; i++) {
        if(i < pagina->nroChavesIndexadas) {
            pagina->P[i] = aux_P[i]; 
            pagina->C[i] = aux_C[i];
            pagina->Pr[i] = aux_Pr[i];
        }
        else {
            if(i != pagina->nroChavesIndexadas) pagina->P[i] = -1;
            else pagina->P[i] = aux_P[i];
            pagina->C[i] = -1;
            pagina->Pr[i] = -1;
        }
    }
    // Preenche a última posição da página 
    pagina->P[ordem_arvB-1] = -1; 

    // Passa para a nova página as chaves a direita da que fora promovida e seta como -1 o restante  
    int i=0;   
    for(; i<nova_pagina->nroChavesIndexadas; i++) {
        nova_pagina->P[i] = aux_P [nova_pagina->nroChavesIndexadas + i + 1];
        nova_pagina->C[i] = aux_C[nova_pagina->nroChavesIndexadas + i + 1];
        nova_pagina->Pr[i] = aux_Pr[nova_pagina->nroChavesIndexadas + i + 1];
    }

    // Como i nunca é dois (nroChavesIndexadas), recebo esse último RRN
    nova_pagina->P[nova_pagina->nroChavesIndexadas] = aux_P[nova_pagina->nroChavesIndexadas + i + 1];
}

// Função que realiza a inserção propriamente dita do registro no arquivo de índices
//                          P             C            Pr      C promovido   Pr promovido   P promovido
int insere_recursivo(int RRN_atual, int chave, int byteoffset, int *c_promo, int *pr_promo, int *p_promo, FILE *fp_index, cabecalho_arvB *cabecalho_arv) {
   
    // Se chegar em um nó folha, então é necessário inserir em um nó acima / Retorna da chamada recursiva atual
    if(RRN_atual == -1) {
        *c_promo = chave;
        *pr_promo = byteoffset;
        *p_promo = -1;
        return 1;
    }

    // Armazena na RAM a página de disco pertencente a chamada recursiva atual
    no_arvB *pagina = le_no_arvore(fp_index, RRN_atual);
    int aux = pagina->nroChavesIndexadas, RRN;

    // Se a página não é um nó folha, a função é chamada recursivamente até que ela encontre a chave ou chegue no nó folha
    for(int i = 0; i < ordem_arvB-1; i++) {

        // Se chave de busca já existe
        if(chave == pagina->C[i]) {
            free(pagina);
            return -1;
        }

        // Se a chave buscada é menor que a chave[i] ou chave vazia, entao devemos descer no RRN exatamente anterior a chave[i]
        if(chave < pagina->C[i] || pagina->C[i] == -1) {
            RRN = pagina->P[i];
            break;
        }

        // Se entrou no if, então a chave buscada é maior que todas as outras chaves no nó, então usamos o último RRN da página (da esquerda para a direita)
        if(i == ordem_arvB-2)  RRN = pagina->P[ordem_arvB-1];
    }

    int insercao = insere_recursivo(RRN, chave, byteoffset, c_promo, pr_promo, p_promo, fp_index, cabecalho_arv);

    // Insercão em chave com espaço (0) ou erro durante processamento do arquivo (-1)
    if(insercao == 0 || insercao == -1) {
        free(pagina);
        return insercao;
    }

    // Se ainda tem espaço no nó, então insere sem promoção
    else if(aux < ordem_arvB-1) {

        // Shiftando todas as posições até encontrar a posição certa para inserção
        while(aux > 0 && pagina->C[aux-1] > chave) {
            pagina->P[aux + 1] = pagina->P[aux];
            pagina->C[aux] = pagina->C[aux - 1];
            pagina->Pr[aux] = pagina->Pr[aux - 1];
            aux--;
        }

        // Insere a nova chave e o byteoffset associado
        pagina->P[aux + 1] = *p_promo;
        pagina->C[aux] = *c_promo;
        pagina->Pr[aux] = *pr_promo;
        pagina->nroChavesIndexadas++;

        // Reseta os valores dos parâmetros 
        *p_promo = -1;
        *c_promo = -1;
        *pr_promo = -1;

        escreve_no_arvore(fp_index, pagina, pagina->RRNdoNo); 

        free(pagina);
        return 0;
    }

    // Nó cheio, então necessário realizar split e promover
    else {

        // Novo nó que sera inserido a direita do nó atual
        no_arvB *nova_pagina = cria_no();
        split(pagina, c_promo, pr_promo, p_promo, nova_pagina, cabecalho_arv);

        // Se splitei uma folha, cria outra folha, caso contrário, mantém o char 0 que indica não ser folha
        if(pagina->folha == '1') nova_pagina->folha = '1';
        nova_pagina->RRNdoNo = cabecalho_arv->RRNproxNo;

        escreve_no_arvore(fp_index, pagina, pagina->RRNdoNo);
        escreve_no_arvore(fp_index, nova_pagina, *p_promo);
        cabecalho_arv->RRNproxNo++;

        free(pagina);
        free(nova_pagina);
        return 1;
    }
}

// Função que dá início a inserção do registro no arquivo de índices
void insere_no(FILE *fp_index, int chave, int byteoffset, cabecalho_arvB *cabecalho_arv) {

    // Se árvore ainda não existe, cria o primeiro nó
    if(cabecalho_arv->noRaiz == -1){

        no_arvB *no = cria_no();
        no->folha = '1';
        no->nroChavesIndexadas = 1;
        no->RRNdoNo = 0;
        no->C[0] = chave;
        no->Pr[0] = byteoffset;

        escreve_no_arvore(fp_index, no, no->RRNdoNo);

        cabecalho_arv->noRaiz++; 
        cabecalho_arv->RRNproxNo++;

        free(no);
    }

    // Árvore já existe, basta inserir 
    else {
        int c_promo = -1, filho_promo = -1, bytepr_promo = -1;
        int insercao = insere_recursivo(cabecalho_arv->noRaiz, chave, byteoffset, &c_promo, &bytepr_promo, &filho_promo, fp_index, cabecalho_arv);

        // Se for necessário promoção, então cria nova raiz e a preenche com os valores que foram promovidos
        if(insercao == 1) {

            no_arvB *novo_no = cria_no();
            novo_no->nroChavesIndexadas = 1;
            novo_no->RRNdoNo = cabecalho_arv->RRNproxNo;
            novo_no->P[0] = cabecalho_arv->noRaiz;
            novo_no->C[0] = c_promo;
            novo_no->Pr[0] = bytepr_promo;
            novo_no->P[1] = filho_promo;

            // Escrevendo a nova página na árvore
            escreve_no_arvore(fp_index, novo_no, novo_no->RRNdoNo);
            free(novo_no);
            
            // Atualizando o cabeçalho
            cabecalho_arv->noRaiz = cabecalho_arv->RRNproxNo;
            cabecalho_arv->RRNproxNo++;            
        }

        // Se houve algum erro durante a inserção
        else if(insercao == -1) printf("Falha no processamento do arquivo.\n");
    }
}
