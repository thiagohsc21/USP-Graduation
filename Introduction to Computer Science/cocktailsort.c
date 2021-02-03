#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    char nome[100];
    char cidade[30];
}pessoa;

char* recebe_entrada(FILE* stream);
pessoa* coloca_na_struct(char *line);
void ordena(pessoa **info, int n);
char maiuscula_para_minuscula(char c);
char *recebe_nomes();
void busca(pessoa **info, char *nomes, int ini, int fim);
void imprime(pessoa **info, int n);
void libera(pessoa **info, int n, char **nome, int k);

int main(){
    int n;
    scanf("%d ", &n);
    pessoa **info = (pessoa**) malloc(n*sizeof(pessoa*));

    int i = 0;
    while(i < n){
        char *line = NULL;
        info[i] = NULL;
        line = recebe_entrada(stdin);

        if(strlen(line) > 0){
            info[i] = coloca_na_struct(line);
            i++;
        }

        if(line != NULL) free(line);
    }
    ordena(info, n);
    
    int k;
    scanf("%d", &k);
    char **nomes = (char**) calloc(k, sizeof(char*)); 

    imprime(info, n);
    for(int i = 0; i < k; i++){
        nomes[i] = recebe_nomes();
        busca(info, nomes[i], 0, n);
    }

    libera(info, n, nomes, k);
    return 0;
}

//recebe a string passada na entrada (nome e cidade) e a retorna
char* recebe_entrada(FILE* stream) {
  char *str = NULL;
	int pos = 0;
	
	do {
		str = realloc(str, pos + 1);
		str[pos] = fgetc(stream);
		pos++;
	} while (str[pos-1]!='\n' && !feof(stream));
	
	str[pos-1] = '\0';

	return str;
}

//atribui o que foi extraido através da funcao recebe_entrada a uma struct
pessoa* coloca_na_struct(char *line){
    pessoa *p = (pessoa*) malloc(sizeof(pessoa));
	int i = 0;
	
    do {
		p->nome[i] = line[i];
		i++;
	} while (line[i-1]!='.');

	p->nome[i-1] = '\0';

    i++; 
	int j = 0;
	do {
		p->cidade[j] = line[i];
		j++; i++;
	} while (line[i-1]!='.');
	p->cidade[j-1] = '\0';

    return p;
}

//transforma o que é maiúsculo em minúsculo
char maiuscula_para_minuscula(char c){
    if (c>=65 && c<=90) c += 32;
    return c;
}

//recebe um ponteiro que aponta para n ponteiros os quais apontam para n structs e ordena essas structs
//segundo o método do Cocktail Sort, não preciso retornar nada porque fazemos a mudança na própria memória
void ordena(pessoa **info, int n){
    int i, j, pos = 0, aux = 0, ini = 0, fim = n - 1;
    bool troca = true;
    pessoa *paux = NULL;

    char a, b;

    while(troca && ini < fim){

        troca = false;  //se não tiverem trocas, essa variável permanece falsa 
                        //o que contribui para a saída desse laço

        for(i = ini; i < fim; i++){
            a = maiuscula_para_minuscula(info[i]->nome[pos]);
            b = maiuscula_para_minuscula(info[i+1]->nome[pos]);
            //se a primeira letra do nome anterior for maior, faz a troca da struct toda
            if(a > b){
                paux = info[i+1];
                info[i+1] = info[i];
                info[i] = paux;
                paux = NULL;
                troca = true;                
            }   

            //se a primeira letra for igual, faz a comparação até verificar se existe diferença
            else if(a == b){
                aux = pos;
                while(aux != strlen(info[i]->nome)){
                    aux++;
                    a = maiuscula_para_minuscula(info[i]->nome[aux]);
                    b = maiuscula_para_minuscula(info[i+1]->nome[aux]);
                    //se a próxima letra for menor, faz a troca das structs
                    if(a > b){
                        paux = info[i+1];
                        info[i+1] = info[i];
                        info[i] = paux;
                        paux = NULL;
                        troca = true;
                        break;
                    }

                    //se a próxima letra for maior, passamos a examinar a partir do prox nome
                    else if(a < b) break;      
                }
            }
        }
        fim--; //decrementa o fim de modo a descartar o elemento já ordenado na posição final

        for(j = fim; j > ini; j--){
            a = maiuscula_para_minuscula(info[j]->nome[pos]);
            b = maiuscula_para_minuscula(info[j-1]->nome[pos]);
            //se a primeira letra do nome anterior for maior, faz a troca da struct toda
            if(a < b){
                paux = info[j-1];
                info[j-1] = info[j];
                info[j] = paux;
                paux = NULL;
                troca = true;
            }   

            //se a primeira letra for igual, faz a comparação até verificar se existe diferença
            else if(a == b){
                aux = pos;

                while(aux != strlen(info[j]->nome)){
                    aux++;//incrementa para mudarmos a letra da palavra
                    a = maiuscula_para_minuscula(info[j]->nome[aux]);
                    b = maiuscula_para_minuscula(info[j-1]->nome[aux]);
                    //se a próxima letra for menor, faz a troca das structs
                    if(a < b){
                        paux = info[j-1];
                        info[j-1] = info[j];
                        info[j] = paux;
                        paux = NULL;
                        troca = true;
                        break;
                    }

                    //se a próxima letra for maior, passamos a examinar a partir do prox nome
                    else if(a > b) break;      
                }
            }
        }
        ini++; //incrementa o inicio para não precisarmos olhar para o primeiro elemento que já está ordenado
    }

}

//recebe os nomes que buscaremos as cidades
char *recebe_nomes(){
    char c = 0;
    int pos = 0;
    char *p = (char*) calloc(1,sizeof(char));

    while(c != '.'){
        c = getchar();
        if(c != '.' && c != '\n' && c != '\r') {
            p = (char*) realloc(p, (pos+1)*sizeof(char));
            p[pos++] = c;
        } 
    }
    p[pos] = '\0';

    return p;
}

//faz a busca binaria usando os nomes já ordenados
void busca(pessoa **info, char *nomes, int ini, int fim){

    while(ini <= fim){
        int centro = (int) ((ini+fim)/2.0);
        int aux = 0;
        aux = strcasecmp(nomes, info[centro]->nome); 

        if(aux == 0){
            if(strcasecmp("Sao Carlos", info[centro]->cidade) == 0) printf("1\n");
            else printf("0\n");
            break;
        }

        else if(aux > 0) ini = centro + 1;
        else fim = centro - 1;
    }

}

//imprime o nome após ordenados
void imprime(pessoa **info, int n){
    for(int i = 0; i < n; i++) printf("%s.\n", info[i]->nome);
}

//desaloca a memória da heap
void libera(pessoa **info, int n, char **nomes, int k){
    for(int i = 0; i < n; i++) free(info[i]);
    free(info);

    for(int i = 0; i < k; i++) free(nomes[i]);
    free(nomes);
}