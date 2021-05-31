#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define infinito -1

// Realiza a Busca em Largura para v_ini e armazena as distâncias na matriz
void busca_em_largura(vector<vector<int>> &grafo, vector<vector<int>> &matriz, int v_ini, int n_vertices){

    // Crio a lista que define todos os vértices como "brancos" e os ainda não visitados "pretos"
    vector<int> brancos(n_vertices, infinito);
    
    // Crio a fila com os próximos vértices que devemos visitar "cinza"
    queue <int> cinzas;

    brancos[v_ini] = 0;
    cinzas.push(v_ini);

    while(cinzas.empty() != true){

        // Recebe o que está na frente da fila e remove 
        int v_atual = cinzas.front(); cinzas.pop();

        // Assinalo na matriz a distância de v_ini a v_atual
        matriz[v_ini][v_atual] = brancos[v_atual];

        // Verifica se já está e coloca as arestas ligadas a v_atual na lista cinza caso não
        for(int i = 0 ; i < (int) grafo[v_atual].size() ; i++){

            int v_futuro = grafo[v_atual][i];

            // Subtraio 1 porque se v_futuro = N, sua representação está na posição/linha  N-1
            if(brancos[v_futuro-1] == infinito){
                brancos[v_futuro-1] = brancos[v_atual] + 1;
                cinzas.push(v_futuro-1);
            }
        }
    }
}

// Realiza a leitura do arquivo e a estruturação do Grafo / retorna o Grafo 
vector<vector<int>> le_arquivo(int *n_vertices){
    
    char nome_arq[20];
    scanf("%s", nome_arq);

    FILE *fp = fopen(nome_arq, "r"); 
    if(fp == NULL){
        cout << "Erro na abertura do arquivo.\n";
        exit(0);
    }

    // Percorre o cabeçalho do arquivo .pajek extraindo a quantidade de vértices
    fseek(fp, 10, SEEK_CUR);
    fscanf(fp, "%d", n_vertices);
    fseek(fp, 8, SEEK_CUR);

    // Declara uma lista para cada um dos vértices
    vector<vector<int>> grafo(*n_vertices, vector<int>(0,0));

    // Cria o Grafo
    int x, y;
    while(fscanf(fp, "%d %d", &x, &y) == 2){
        grafo[x-1].push_back(y);
        grafo[y-1].push_back(x);
    }

    fclose(fp);
    return grafo;
}

int main(){

    int n_vertices;
    vector<vector<int>> grafo = le_arquivo(&n_vertices);

    // Declara a matriz com tamanho [n_vertices, n_vertices] e inicializa com 0
    vector<vector<int>> matriz(n_vertices, vector<int>(n_vertices, 0));

    // Uma busca para cada vértice, de modo a criarmos a matriz de distâncias
    for(int i = 0 ; i < n_vertices ; i++) busca_em_largura(grafo, matriz, i, n_vertices);

    // Impressao da matriz pedida
    for(int i = 0 ; i < n_vertices ; i++){
        for(int j = 0 ; j < n_vertices ; j++) cout << matriz[i][j] << " ";
        cout << endl;
    }

    return 0;
}