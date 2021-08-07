#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>  
#include <utility>
using namespace std;

// Realiza a leitura do arquivo e a estruturação do Grafo / retorna o Grafo 
vector<vector<pair<int,int>>> le_arquivo(int *numVertices){
    
    char nome_arq[20];
    scanf("%s", nome_arq);

    FILE *fp = fopen(nome_arq, "r"); 
    if(fp == NULL){
        cout << "Erro na abertura do arquivo.\n";
        exit(0);
    }

    // Percorre o cabeçalho do arquivo .pajek extraindo a quantidade de vértices
    fseek(fp, 10, SEEK_CUR);
    fscanf(fp, "%d", numVertices);
    fseek(fp, 7, SEEK_CUR);

    // Declara meu grafo no qual cada posicao da linha armazena um par (vertice, peso)
    vector<pair<int,int>> linha;
    vector<vector<pair<int,int>>> grafo(*(numVertices)+1, linha);

    // Cria o Grafo direcionado e valorado
    int x, y, p;
    while(fscanf(fp, "%d %d %d", &x, &y, &p) == 3){
        //emplace_back
        grafo[x].push_back(make_pair(y,p));
    }

    fclose(fp);
    return grafo;
}

// Funcao que realiza o algoritmo de dijkstra saindo do vértice v e percorrendo os n vertices no grafo g
int* dijkstra(int *maiorNum, int n, int v, vector<vector<pair<int,int>>> g){

    // Vetor que armazenará as distâncias / Inicializo com "infinito" 
    int *d = (int*) malloc(sizeof(int)*(n+1));
    for(int i = 1 ; i <= n ; i++) d[i] = 10e8;
       
    // Distância do vértice a ele mesmo é 0 
    d[v] = 0;

    // Declaro uma fila de prioridade que me retornará sempre a menor distância
    // Armazena pares de inteiro num vetor e usa como comparador a classe greater, garantindo que sempre teremos a menor distância no topo
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> filaPrioridade;

    // Insiro o primeiro par (distancia, vertice) na fila / distancia vem no primeiro parametro pois é o mais importante na comparação
    filaPrioridade.push(make_pair(d[v], v));

    // Enquanto ainda existem elementos na fila de prioridade
    while((int)filaPrioridade.size() > 0){

        // Recebo o vértice no topo (menor distância) e depois removo
        int vAtual = filaPrioridade.top().second;
        int aux = filaPrioridade.top().first;
        filaPrioridade.pop();

        // Verifico se já processei o vAtual
        if(aux > d[vAtual]) continue;

        *maiorNum = max(*maiorNum, d[vAtual]);

        // Relaxo todas as arestas saindo do vertice atual
        for(int i = 0 ; i < (int) g[vAtual].size() ; i++){

            // vertice adjacente e peso associado
            int vAdjacente, peso;

            // Recebo esse par de valores
            tie(vAdjacente, peso) = g[vAtual][i];

            // Relaxo, comparando a distancia do vertice atual acrescida do peso com seus vizinhos
            if(d[vAtual] + peso < d[vAdjacente]){

                // Se for menor, recebo esse valor e passo para a fila de prioridade
                d[vAdjacente] = d[vAtual] + peso;
                filaPrioridade.push(make_pair(d[vAdjacente], vAdjacente));

            }
        }
    }

    return d;
}

int main(){

    int numVertices, maiorNum = 0;
    vector<vector<pair<int,int>>> grafo = le_arquivo(&numVertices);

    // Matriz de distancias
    int **matriz = (int**) malloc((numVertices+1)*sizeof(int*));

    // Realizo um dijkstra para cada um dos vértices
    for(int i = 1 ; i <= numVertices ; i++) {
        matriz[i] = (int*) malloc(numVertices*sizeof(int));
        matriz[i] = dijkstra(&maiorNum, numVertices, i, grafo);
    }

    // Formatação da saída
    for(int i = 1 ; i <= numVertices ; i++){
        for(int j = 1 ; j <= numVertices ; j++){
			for(int k = 0 ; k < (int)(to_string(maiorNum).size() - to_string(matriz[i][j]).size()) ; k++) cout << ' ';
			cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

