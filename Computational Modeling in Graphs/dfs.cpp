#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Realiza a busca em profundidade no grafo dado / retorna nulo
void busca_em_profundidade(vector<vector<int>> grafo, int v_inicial, vector<int> &riscados, int *num_riscados){

    // Marco o vértice como riscado
    riscados[v_inicial] = -1;
    (*num_riscados)++;

    // Verifica se o vizinho está riscado / SIM - incrementa o i, NAO - chama a funcao novamente passando o vizinho
    for(int i = 0; i < (int) grafo[v_inicial].size() ; i++){
        int vizinho = grafo[v_inicial][i];

        if(riscados[vizinho] == 0) 
            busca_em_profundidade(grafo, vizinho, riscados, num_riscados);
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
    vector<vector<int>> grafo(*(n_vertices)+1, vector<int>(0,0));

    // Cria o Grafo não direcionado
    int x, y;
    while(fscanf(fp, "%d %d", &x, &y) == 2){
        grafo[x].push_back(y);
        grafo[y].push_back(x);
    }

    fclose(fp);
    return grafo;
}

bool comparador(int p, int q){
    return p > q;
}

int main(){

    int n_vertices;
    vector<vector<int>> grafo = le_arquivo(&n_vertices);

    // Vetor que armazenará os vértices já visitados (riscados)
    vector<int> riscados(n_vertices+1, 0);
    
    // Vetor com o número de vértices em cada componente 
    vector<int> componentes;

    // Realizo a dfs para todos os vértices ainda não riscados
    for(int i = 1 ; i <= n_vertices ; i++){
        int num_componentes = 0;
        
        // Verifico se o vértice i já foi riscado, acessando o valor de seu índice no vetor de riscados
        // SIM - Incrementa o i, NÃO - Realizo a DFS
        if(riscados[i] == 0) {
            busca_em_profundidade(grafo, i, riscados, &num_componentes);
            componentes.push_back(num_componentes);
        }
    }

    // Ordeno os componentes do grafo
    sort(componentes.begin(), componentes.end(), comparador);

    // Impressão da resposta no formato pedido
    cout << componentes.size() << "\n";
    for(int i = 0 ; i < (int) componentes.size() ; i++) cout << componentes[i] << endl;

    return 0;
}

