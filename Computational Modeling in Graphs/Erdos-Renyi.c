#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//retorna um valor entre min e max : min < x < max
double rand_adaptado(double min, double max ){
    return min + (rand() / (RAND_MAX / (max - min))) ;  
}

int** cria_matriz(int N, double p){

    //Alocação da Matriz : Linhas e Colunas (inicializa posições com 0)
    int **mat = (int**) calloc(N, sizeof(int*));
    for(int i = 0 ; i < N ; i++) mat[i] = (int*) calloc(N, sizeof(int));

    //Criação das arestas 
    for(int i = 0 ; i < (N-1) ; i++){
        for(int j = i+1 ; j < N ; j++){
            // 0 < x < 1
            double x = rand_adaptado(0,1); 

            //calcula x-p de modo a verificar se eles são iguais até a sexta casa decimal
            double v = x-p;
            if(v < 0) v = v*(-1);

            if(x > p || v < 1e-6) { 
                mat[i][j] = 1;
                mat[j][i] = 1;
            }
        }
    }
    return mat;
}

void printa_matriz(int **grafo, int N){
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            printf("%d",grafo[i][j]);
        }
        printf("\n");
    }
}

void desaloca_matriz(int **matriz, int N){
    for(int i = 0 ; i < N ; i++) free(matriz[i]);
    free(matriz);
}

int main(){

    int N; double p;
    printf("Digite o valor de N: ");
    scanf("%d",&N);
    printf("Digite o valor de p: ");
    scanf("%lf",&p);

    int **grafo = cria_matriz(N, p);
    printf("\n");
    printa_matriz(grafo, N);
    printf("\n");

    desaloca_matriz(grafo,N);
    return 0;
}