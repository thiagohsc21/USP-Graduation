#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *nome;
    float valor;
}livro;

void recebe_entrada(livro *p);
void ordena_mergesort_3vias(float *v, int ini, int fim); 
void busca_sequencial(float *v, livro **p, int fim);
void desaloca(livro **p, int n, float *v);

int main(){
    int n;
    scanf("%d", &n);

    //aloca um ponteiro para cada livro, que possuirão uma struct com nome e valor
    livro **p = (livro**) malloc(n*sizeof(livro*));

    //armazenará os valores de cada livro, de modo que possamos ordenar com o mergesort
    float *precos = (float*) malloc(n*sizeof(float));

    for(int i = 0 ; i < n ; i++){
        p[i] = (livro*) malloc(sizeof(livro));
        recebe_entrada(p[i]);
        precos[i] = p[i]->valor;
    }

    ordena_mergesort_3vias(precos, 0, n-1);
    busca_sequencial(precos, p, n);
    
    desaloca(p, n, precos);
    return 0;
}

//funcao que recebe a entrada e armazena numa struct livro
void recebe_entrada(livro *p){
    char c = 0;
    int pos = 0;
    char *nomeaux = (char*) malloc(sizeof(char));

    //recebe os caracteres e vai colocando na regiao apontada pelo ponteiro nomeaux
    while(c != ','){
        c = getchar();

        if(c != '\n' && c != '\r'){
            nomeaux = realloc(nomeaux, (pos+1)*sizeof(char));
            nomeaux[pos++] = c;
        }
        
    }
    nomeaux[--pos] = '\0';

    //passa o end alocado pelo nomeaux para o p->nome da struct atual
    p->nome = nomeaux;
    nomeaux = NULL;

    scanf("%f", &p->valor);
}

//ordena segundo o algoritmo de mergesort, mas com 3 vias
void ordena_mergesort_3vias(float *v, int ini, int fim){   

    for(int i = ini; i <= fim; i++){
        printf("%.2f ", v[i]);
        if(i == fim) printf("\n");
    }

    if(fim <= ini) return;

    int c1 = ini + (fim-ini)/3;
    int c2 = c1 + (fim-c1+1)/2;

    ordena_mergesort_3vias(v, ini, c1); 
    ordena_mergesort_3vias(v, c1+1, c2);
    ordena_mergesort_3vias(v, c2+1, fim);

    //intercala as partes dentro desses três vetores
    float *aux = (float*) malloc((fim-ini+1)*sizeof(float));

    int i = ini;   //índice para a primeira parte (ini -> c1)
    int j = c1+1;   //índice para a segunda parte  (c1+1 -> c2)
    int k = c2+1;   //índice para a terceira parte (c2+1 -> fim)
    int pos = 0; //índice para o vetor auxiliar 
    

    while(i <= c1 && j <= c2 && k <= fim){
        //se o elemento da lista 1 for maior que o da lista 2 e 3, coloca ele no vetor
        if(v[i] <= v[j] && v[i] <= v[k]){
            aux[pos] = v[i];
            i++; //incrementa para que tenhamos acesso ao proximo elemento da lista 1
        }
        //se o elemento da lista 2 for maior que o da lista 1 e 3, coloca ele no vetor
        else if(v[j] <= v[i] && v[j] <= v[k]){
            aux[pos] = v[j];
            j++; //incrementa para que tenhamos acesso ao proximo elemento da lista 2
        }
        //se o elemento da lista 3 for maior que o da lista 1 e 2, coloca ele no vetor
        else{
            aux[pos] = v[k];
            k++; //incrementa para que tenhamos acesso ao proximo elemento da lista 3
        }
        pos++; //a cada rodada colocamos um elemento no vetor aux, portanto temos que avançar
                //uma posicao nele
    }

    //se a lista 1 tiver vazia e as outras ainda nao, compara os elementos delas
    if(i > c1 && (j <= c2 && k <= fim)){
        while(j <= c2 && k <= fim){
            if(v[j] <= v[k]){
                aux[pos] = v[j];
                j++;
            }
            else{
                aux[pos] = v[k];
                k++;
            }
            pos++;
        }
    }

    //se a lista 2 estiver vazia e as outras ainda nao, compara os elementos delas
    else if(j > c2 && (i <= c1 && k <= fim)){
        while(i <= c1 && k <= fim){
            if(v[i] <= v[k]){
                aux[pos] = v[i];
                i++;
            }
            else{
                aux[pos] = v[k];
                k++;
            }
            pos++;
        }
    }

    //se a lista 3 estiver vazia e as outas ainda nao, compara os elementos delas
    else if(k > fim && (j <= c2 && i <= c1)){
        while(i <= c1 && j <= c2){
            if(v[i] <= v[j]){
                aux[pos] = v[i];
                i++;
            }
            else{
                aux[pos] = v[j];
                j++;
            }
            pos++;
        }
    }

    //se a lista 1 e lista 2 estiverem vazias, copia a 3 para o vetor
    if(i > c1 && j > c2 && k <=fim){
        while(k <= fim){
            aux[pos] = v[k];
            k++;
            pos++;
        }
    }

    //se a lista 1 e lista 3 estiverem vazias, copia a 2 para o vetor
    else if(i > c1 && k > fim && j <= c2){
        while(j <= c2){
            aux[pos] = v[j];
            j++;
            pos++;
        }
    }

    //se a lista 2 e a lista 3 estiverem vazias, copia a 1 para o vetor
    else if(j > c2 && k > fim && i <= c1){
        while(i <= c1){
            aux[pos] = v[i];
            i++;
            pos++;
        }
    }

    //copia o vetor aux para o vetor original passado na entrada
    for(i = ini, pos = 0; i <= fim; i++, pos++) v[i] = aux[pos];

    free(aux);
}

//faz a busca dentro dos ponteiros contidos em p até achar o valor procurado, então
//imprime o nome do livro associado a esse valor e o próprio valor
void busca_sequencial(float *v, livro **p, int n){

    printf("\n"); //pulo de linha para respeitar a formatacao da saida

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            //procura de um em um o valor, quando encontra, imprime o nome associado a ele
            if(v[i] == p[j]->valor) printf("%s, R$%.2f\n", p[j]->nome, p[j]->valor);
        }
    }
}

//desaloca toda a memória alocada
void desaloca(livro **p, int n, float *v){
    for(int i = 0; i < n; i++) free(p[i]);

    free(p);
    free(v);
}