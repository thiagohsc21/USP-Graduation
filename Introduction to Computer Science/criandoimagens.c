#include <stdio.h>
#include <stdlib.h>

//funcao que realiza a recursao pedida, percorrendo e mudando os valores, até encontrarmos
//um dos critérios de parada passado no exercício
void funcao(int **m, int x, int y, int t, int n){

    int p = m[x][y];

    //elemento acima 
    if(x > 0 && abs(p - m[x-1][y]) <= t && abs(p - m[x-1][y]) != 0){
        m[x-1][y] = p;
        funcao(m, x-1, y, t, n);
    }
    //elemento a direita
    if(y < n-1 && abs(p - m[x][y+1]) <= t && abs(p - m[x][y+1]) != 0){
        m[x][y+1] = p;
        funcao(m, x, y+1, t, n);
    }
    //elemento abaixo
    if(x < n-1 && abs(p - m[x+1][y]) <= t && abs(p - m[x+1][y]) != 0){
        m[x+1][y] = p;
        funcao(m, x+1, y, t, n);
    }   
    //elemento a esquerda
    if(y > 0 && abs(p - m[x][y-1]) <= t && abs(p - m[x][y-1]) != 0){
        m[x][y-1] = p;
        funcao(m, x, y-1, t, n);
    }
}

void imprime(int **m, int n){
    int i,j;
    for(i = 0 ; i < n ; i++){
        for(j = 0 ; j < n ; j++){
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
}

void cria_imagem(int **m, int n, FILE *fp){
    fprintf(fp, "P2\n");
    fprintf(fp, "%d %d\n", n, n);
    
    int i,j;
    for(i = 0 ; i < n ; i++){
        for(j = 0 ; j < n ; j++){
            fprintf(fp, "%d ", m[i][j]);
        }
        fprintf(fp, "\n");
    }
}

int main(){

    int n, x, y, t;
    scanf("%d %d %d %d", &n, &x, &y, &t);

    srand(t);
    int **mat = (int**) malloc(n*sizeof(int*));

    int i, j;
    for(i = 0 ; i < n ; i++){
        mat[i] = (int*) malloc(n*sizeof(int));
            for(j = 0 ; j < n ; j++){
                mat[i][j] = rand()%256;
            }
    }

    imprime(mat, n);
    printf("\n");
    FILE *fp = fopen("aleatoria.pgm", "w");
    cria_imagem(mat, n, fp);
    fclose(fp);
    fp = NULL;

    funcao(mat, x, y, t, n);

    imprime(mat, n);
    fp = fopen("atualizada.pgm", "w");
    cria_imagem(mat, n, fp);
    fclose(fp);
    fp = NULL;

    for(i = 0 ; i < n ; i++) free(mat[i]);
    free(mat);
    return 0;
}