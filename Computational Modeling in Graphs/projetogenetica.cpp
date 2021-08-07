/* Thiago Henrique dos Santos Cardoso - 11796594 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>  
#include <utility>
using namespace std;
#define infinito -1

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

    // Cria o Grafo direcionado
    int x, y;
    while(fscanf(fp, "%d %d", &x, &y) == 2){
        grafo[x].push_back(y);
    }

    fclose(fp);
    return grafo;
}

// Realiza a busca em profundidade no grafo dado / retorna nulo
int busca_em_profundidade(vector<vector<int>> &grafo, int v_inicial, vector<int> &riscados, vector<int> &buscados, vector<pair<int,int>> &pais_sorvedouros){
    
    // Encontrei um vertice sorvedouro
    if((int) grafo[v_inicial].size() == 0) return v_inicial;

    // Marco o vértice como riscado
    riscados[v_inicial] = -1;
    
    // Verifica se o vizinho está riscado / SIM - incrementa o i, NAO - chama a funcao novamente passando o vizinho
    for(int i = 0; i < (int) grafo[v_inicial].size() ; i++){

        int vizinho = grafo[v_inicial][i];

        if(riscados[vizinho] == 0) {
            int aux = busca_em_profundidade(grafo, vizinho, riscados, buscados, pais_sorvedouros);

            // Encontrei um vertice sorvedouro e devo armazenar seu pai
            if(aux != 0){
                if(pais_sorvedouros[aux].first == 0) pais_sorvedouros[aux].first = v_inicial;
                else {
                    pais_sorvedouros[aux].second = v_inicial;
                    buscados.push_back(aux);
                }
            }
        }
    }

    return 0;
}

// Realiza a Busca em Largura para v_ini e armazena as distâncias no vetor
void busca_em_largura(vector<vector<int>> &grafo, vector<int> &vetor, int v_ini, int n_vertices){

    // Crio a lista que define todos os vértices como "brancos" e os ainda não visitados "pretos"
    vector<int> brancos(n_vertices+1, infinito);
    
    // Crio a fila com os próximos vértices que devemos visitar "cinza"
    queue <int> cinzas;

    brancos[v_ini] = 0;
    cinzas.push(v_ini);

    while(cinzas.empty() != true){

        // Recebe o que está na frente da fila e remove 
        int v_atual = cinzas.front(); cinzas.pop();

        // Assinalo na matriz a distância de v_ini a v_atual
        vetor[v_atual] = brancos[v_atual];

        // Verifica se já está e coloca as arestas ligadas a v_atual na lista cinza caso não
        for(int i = 0 ; i < (int) grafo[v_atual].size() ; i++){

            int v_futuro = grafo[v_atual][i];

            if(brancos[v_futuro] == infinito){
                brancos[v_futuro] = brancos[v_atual] + 1;
                cinzas.push(v_futuro);
            }
        }
    }
}

// a) Marco num vetor todos os vertices que possuem pai / Ex: se o vertice 3 tem pai, entao temPai[3] = 1
void verifica_vertices_fonte(vector<vector<int>> &grafo, int n_vertices){

    // Indica se um nó tem pai / 1 - SIM ou 0 - NAO
    vector<int> temPai(n_vertices+1, 0);

    // Pego todos os vertices adjacentes ao atual (i) e marco que possuem pai
    for(int i = 1 ; i <= n_vertices ; i++){
        for(int j = 1 ; j < (int) grafo[i].size() ; j++){
            temPai[grafo[i][j]] = 1;
        }
    }

    int ans = 0;
    for(int i = 1 ; i <= n_vertices ; i++) if(temPai[i] == 0) ans++;
    cout << ans << endl;
}

// b) Passo por todos os nós e verifico se ele possui filhos / SIM - printo e adiciono no vetor ou NAO - continuo o laco
vector<int> verifica_vertices_sorvedouros(vector<vector<int>> grafo, int n_vertices){

    vector<int> sorvedouros(n_vertices+1, 0);
    int ans = 0;

    for(int i = 2 ; i <= n_vertices ; i++){
        // Se o número de filhos for 0, então encontrei um sorvedouro
        if(grafo[i].size() == 0) {
            sorvedouros[i] = 1;
            ans++;
        }
    }
    
    cout << ans << endl;
    return sorvedouros;
}

// c) Busco quais sao os vertices sorvedouros descendentes de um e armazeno seus pais 
vector<pair<int,int>> verifica_vertices_sorvedouros_descendentes1(vector<vector<int>> &grafo, int num_vertices){

    // Armazeno os decendentes de um
    vector<int> descendentes_um(num_vertices+1, 0);

    // Armazeno os sorvedouros com pais descendentes de um
    vector<int> buscados;

    // Armazeno os pais dos vertices sorvedouros
    vector<pair<int, int>> pais_sorvedouros(num_vertices+1, make_pair(0,0));
    
    // Busca todos os descendentes de um e armazena no vetor "descendentes_um", guardando também os pais dos vertices sorvedouros
    busca_em_profundidade(grafo, 1, descendentes_um, buscados, pais_sorvedouros);

    sort(buscados.begin(), buscados.end());
    for(int i = 0 ; i < (int) buscados.size(); i++) cout << buscados[i] << endl;

    return pais_sorvedouros;
}

// d) Uso os pais e sorvedouros encontrados na funcionalidad c) e encontro a soma minima entre um par de pais
void verifica_soma_minima(vector<vector<int>> &grafo, int num_vertices, vector<int> &sorvedouros, vector<pair<int,int>> &pais){
    
    // Vetor que armazena as distancias ao vertice 1
    vector<int> d(num_vertices+1, 0);

    // Busca em largura de modo a encontrarmos as distancias 
    busca_em_largura(grafo, d, 1, num_vertices);

    // Encontro qual a soma d[X] + d[Y] minima dos pais de um vertice sorvedouro descendente de 1 e armazeno no vetor abaixo
    vector<int> vertices_procurados;
    int menor_valor = 2147483647;

    for(int i = 1 ; i <= num_vertices ; i++){

        // Se é um vertice sorvedouro
        if(sorvedouros[i] == 1){
            
            // Se é descendente de um, todos os pais foram inicializados e não valem mais zero
            if(pais[i].first != 0 and pais[i].second != 0){

                // Se encontro uma distancia menor que a minima, removo todos os elementos antes encontrados, adiciono o novo e atualizo o menor_valor
                if(d[pais[i].first] + d[pais[i].second] < menor_valor) {
                    
                    // Removo todos os elementos do vetor 
                    for(int j = 0 ; j < (int) vertices_procurados.size() ; j++) vertices_procurados.pop_back();

                    vertices_procurados.push_back(i);
                    menor_valor = d[pais[i].first] + d[pais[i].second];
                }

                // Se encontro uma distancia igual a minima, adiciono vertice na resposta
                else if(d[pais[i].first] + d[pais[i].second] == menor_valor) vertices_procurados.push_back(i);
                
            }
        }
    }

    // Imprimo todos os vertices nos quais as somas de seus pais dao o menor_valor
    for(int i = 0 ; i < (int) vertices_procurados.size() ; i++) cout << vertices_procurados[i] << endl; 

}

int main(){

    int numVertices;
    vector<vector<int>> grafo = le_arquivo(&numVertices);

    // a) Quantos vertices sao vertices fontes? 
    verifica_vertices_fonte(grafo, numVertices);

    // b) Quantos vertices sao sorvedouros?
    //vector<int> sorvedouros = verifica_vertices_sorvedouros(grafo, numVertices);

    // c) Quais sao os vertices sorvedouros nos quais ambos os pais sao descendentes de 1?
    //vector<pair<int,int>> pais_sorvedouros = verifica_vertices_sorvedouros_descendentes1(grafo, numVertices);

    // d) (iv) Seja d o vetor de distâncias de cada vértice em relação ao vértice 1. Seja X e Y os pais de um dado vértice obtido na
    // parte c. Quais são os vértices na parte (c) tais que a soma d[X] + d[Y] é o mínimo? 
    //verifica_soma_minima(grafo, numVertices, sorvedouros, pais_sorvedouros);

    return 0;
}
