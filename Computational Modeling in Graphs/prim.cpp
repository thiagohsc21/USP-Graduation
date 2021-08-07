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
    fseek(fp, 8, SEEK_CUR);

    // Declara meu grafo no qual cada posicao da linha armazena um par (vertice, peso)
    vector<pair<int,int>> linha;
    vector<vector<pair<int,int>>> grafo(*(numVertices)+1, linha);

    // Cria o Grafo não direcionado e valorado
    int x, y, p;
    while(fscanf(fp, "%d %d %d", &x, &y, &p) == 3){
        grafo[x].emplace_back(y,p);
        grafo[y].emplace_back(x,p);
    }

    fclose(fp);
    return grafo;
}

// Funcao que realiza o algoritmo de dijkstra saindo do vértice v e percorrendo os n vertices no grafo g
int prim(int n, int v, vector<vector<pair<int,int>>> g){

    // Declaro uma fila de prioridade que me retornará sempre a menor distância
    // Armazena pares de inteiro num vetor e usa como comparador a classe greater, garantindo que sempre teremos a menor distância no topo
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> filaPrioridade;

    // Insiro o primeiro par (distancia, vertice) na fila / distancia vem no primeiro parametro pois é o mais importante na comparação
    filaPrioridade.emplace(0, v);

    // Vetor que armazena se vertice ainda deve ser visitado
    int vis[n+1] = {0};

    int sum = 0;
    
    // Enquanto ainda existem elementos na fila de prioridade
    while((int)filaPrioridade.size() > 0){

        // Recebo o vértice no topo (menor distância) e depois removo
        int vAtual = filaPrioridade.top().second;
        
        // Se vértice ainda não foi visitado, soma o valor da aresta correspondente
        if(vis[vAtual] == 0) {
            sum += filaPrioridade.top().first;
            vis[vAtual] = 1;
        }

        // Remove o elemento da fila
        filaPrioridade.pop();

        // Percorro todas as arestas saindo do vertice atual
        for(int i = 0 ; i < (int) g[vAtual].size() ; i++){

            // vertice adjacente e peso associado
            int vAdjacente, peso;

            // Recebo esse par de valores
            tie(vAdjacente, peso) = g[vAtual][i];

            // Se vertice nao foi visitado, adiciona na fila
            if(vis[vAdjacente] == 0) filaPrioridade.emplace(peso, vAdjacente);
            
        }
    }

    return sum;
}

int main(){

    int numVertices;
    vector<vector<pair<int,int>>> grafo = le_arquivo(&numVertices);

    // Realizo o cálculo saindo do vértice de número 1
    cout << prim(numVertices, 1, grafo) << endl;

    return 0;
}

