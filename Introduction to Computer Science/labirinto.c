#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE* Le_Entradas_e_Retorna_PonteiroArquivo(int *linhas, int *colunas, int *posicaox, int *posicaoy);
char** Aloca_Matriz(FILE *fp, int linhas, int colunas, int *npessoas, int *caminhos);
int Percorre_Matriz(char **m, int linhas, int colunas, int *visitados, int x, int y);
void Printa_Tudo(char **labirinto, int linhas, int colunas, int npessoas, int caminhos, int visitados);
void Desaloca_Tudo_e_Fecha_Arquivo(FILE *fp, char **matriz, int linhas);

int main(){
    int linhas, colunas, posicaox, posicaoy, npessoas = 0, caminhos= 0, visitados = 0;
    
    FILE *fp = Le_Entradas_e_Retorna_PonteiroArquivo(&linhas, &colunas, &posicaox, &posicaoy);
    char **labirinto = Aloca_Matriz(fp, linhas, colunas, &npessoas, &caminhos);    
    Percorre_Matriz(labirinto, linhas, colunas, &visitados, posicaox, posicaoy);
    Printa_Tudo(labirinto, linhas, colunas, npessoas, caminhos, visitados);
    Desaloca_Tudo_e_Fecha_Arquivo(fp, labirinto, linhas);

    return 0;
}

//le por referencia todas as entradas e retorna o ponteiro pro arquivo
FILE* Le_Entradas_e_Retorna_PonteiroArquivo(int *linhas, int *colunas, int *posicaox, int *posicaoy){
    char name[25];
    scanf("%s",name);
    FILE* fp = fopen(name,"r");
    fscanf(fp, "%d %d", linhas, colunas);
    fscanf(fp, "%d %d", posicaox, posicaoy);

    return fp;
}

//le a matriz do arquivo e a retorna, ja passando por referencia o numero de pessoas e a quantidade de caminhos
char** Aloca_Matriz(FILE *fp, int linhas, int colunas, int *npessoas, int *caminhos){  
    fgetc(fp); // consome o \n que existe após a posiçãoy
    int i, j;
    char **matriz = (char**) malloc(linhas*sizeof(char*));
    for(i = 0; i < linhas; i++) matriz[i] = (char*) malloc(colunas*sizeof(char));

    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            matriz[i][j] = fgetc(fp);
            if(matriz[i][j] == '#') (*npessoas)++; 
            if(matriz[i][j] == '.') (*caminhos)++;
        }
        fgetc(fp); //consome o \n ao final de cada linha
    }
   return matriz;
}

//percorre a matriz por meio da recursao até encontrar o caso base, que é a posição na borda do labirinto
int Percorre_Matriz(char **labirinto, int linhas, int colunas, int *visitados, int x, int y){
    (*visitados)++;
    labirinto[x][y] = '*'; 
    int retorno;

    //caso base é na borda do labirinto
    if(x == 0 || y == 0 || x == linhas-1 || y == colunas-1) return 1;                                                               

    //passo recursivo                                                                 
    if(labirinto[x-1][y] == '.'){              //CIMA
        retorno = Percorre_Matriz(labirinto, linhas, colunas, visitados, x-1, y);
        if(retorno) return 1;
    }

    if(labirinto[x][y+1] == '.'){        //DIREITA                       
        retorno = Percorre_Matriz(labirinto, linhas, colunas, visitados, x, y+1);
        if(retorno) return 1;
    }

    if(labirinto[x+1][y] == '.'){         //BAIXO 
        retorno = Percorre_Matriz(labirinto, linhas, colunas, visitados, x+1, y);
        if(retorno) return 1;
    }

    if(labirinto[x][y-1] == '.'){         //ESQUERDA 
        retorno = Percorre_Matriz(labirinto, linhas, colunas, visitados, x, y-1);
        if(retorno) return 1;
    }

    return 0;
}

//printa tudo o que é pedido no exercício e para isso é declarado o valor da exploracao
void Printa_Tudo(char **labirinto, int linhas, int colunas, int npessoas, int caminhos, int visitados){
    int i,j;
    double exploracao = 100*(double) visitados/caminhos;

    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            printf("%c", labirinto[i][j]);
        }
        printf("\n");
    }

    printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
    printf("Veja abaixo os detalhes da sua fuga:\n");
    printf("----Pessoas te procurando: %d\n", npessoas);
    printf("----Numero total de caminhos validos:   %d\n", caminhos);
    printf("----Numero total de caminhos visitados: %d\n", visitados);
    printf("----Exploracao total do labirinto: %.1lf%%\n", floor(exploracao));
}

//desaloca toda a memoria alocada dinamicamente na heap
void Desaloca_Tudo_e_Fecha_Arquivo(FILE *fp, char **labirinto, int linhas){
    for(int i = 0; i < linhas; i++) free(labirinto[i]);
    free(labirinto);
    fclose(fp);
}