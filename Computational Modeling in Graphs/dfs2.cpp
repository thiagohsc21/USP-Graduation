#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Realiza a busca em profundidade no grafo dado / retorna nulo
bool busca_em_profundidade(vector<vector<int>> grafo, int v_inicial, vector<int> &fila, vector<int> &riscados){

    // Marco o vértice como riscado, sendo componente a variavel que vai guardar a componente de cada vertice
    riscados[v_inicial] = -1;

    // Marco a posição do vértice na fila como visitado durante essa chamada
    fila[v_inicial] = -1;

    // Verifica se o vizinho está riscado / SIM - incrementa o i, NAO - chama a funcao novamente passando o vizinho
    for(int i = 0; i < (int) grafo[v_inicial].size() ; i++){
       
        int vizinho = grafo[v_inicial][i];

        // Vizinho já visitado nessa mesma chamada, então achamos um ciclo
        if(fila[vizinho] == -1) return true;

        // Se o vizinho ainda não foi visitado, chama a funcao pra ele recebendo seu retorno
        if(riscados[vizinho] == 0) {
            bool ciclo = busca_em_profundidade(grafo, vizinho, fila, riscados);
            if(ciclo) return true;
        }
    }

    // Desmarco a posição do vértice na fila como visitado durante essa chamada
    fila[v_inicial] = 0;

    // E se chegou até aqui, então não achou ciclo
    return false;
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
    fseek(fp, 7, SEEK_CUR);

    // Declara uma lista para cada um dos vértices
    vector<vector<int>> grafo(*(n_vertices)+1, vector<int>(0,0));
    
    int x,y;
    while(fscanf(fp, "%d %d", &x, &y) == 2){
        grafo[x].push_back(y);
    }

    fclose(fp);
    return grafo;
}

int main(){
    
    int n_vertices;
    vector<vector<int>> grafo = le_arquivo(&n_vertices);

    // Vetor que armazenará os vértices já visitados (riscados)
    vector<int> riscados(n_vertices+1, 0);

    // Vetor que armazenará os vértices já visitados
    vector<int> fila_dfs(n_vertices+1, 0);

    bool ciclo = false;
    // Realizo a dfs para todos os vértices ainda não riscados
    for(int i = 1 ; i <= n_vertices ; i++){
        
        // Verifico se o vértice i já foi riscado, acessando o valor de seu índice no vetor de riscados
        // SIM - Incrementa o i, NÃO - Realizo a DFS
        if(riscados[i] == 0) ciclo = busca_em_profundidade(grafo, i, fila_dfs, riscados);

        // Se temos um ciclo, não precisamos continuar a busca
        if(ciclo == true) break;
    }

    // Impressão da resposta no formato pedido
    if(ciclo) cout << 'S';
    else cout << 'N';

    return 0;

}