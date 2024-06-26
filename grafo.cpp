#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <climits>
#include <boost/heap/fibonacci_heap.hpp>

#include "grafo.h"

Grafo::Grafo() {
    // Inicializa o grafo com 1 vértice
    this->V = 1;
    this->E = 0;
    listaAdj.resize(this->V);
}

// Construtor que cria um grafo com um número especificado de vértices
Grafo::Grafo(int V) {
    this->V = V;
    this->E = 0;
    listaAdj.resize(V);
}

int **Grafo::matrizAdj() {
    int **matriz = new int*[this->V];

    for (int i = 0; i < this->V; ++i) {
        matriz[i] = new int[this->V];

        for (int j = 0; j < this->V; ++j) {
            matriz[i][j] = 0;
        }
    }

    for (int i = 0; i < this->V; ++i) {
        for (const auto& E : listaAdj[i]) {
            int j = E.first;
            int peso = E.second;

            matriz[i][j] = peso;
        }
    }

    return matriz;
}

int *Grafo::incidentes(int v) {
    if (!this->isVertice(v)) {
        std::cerr << "Vértice inválido!" << std::endl;
        return nullptr;
    }

    int *incidentes = new int[this->V];

    for (int i = 0; i < this->V; ++i) {
        incidentes[i] = 0;
    }

    for (const auto& E : listaAdj[v]) {
        int w = E.first;
        incidentes[w]++;
    }

    return incidentes;
}

void Grafo::imprimeMatrizAdj() {
    int **matriz = this->matrizAdj();

    for (int i = 0; i < this->V; ++i) {
        for (int j = 0; j < this->V; ++j) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < this->V; ++i) {
        delete[] matriz[i];
    }

    delete[] matriz;
}



 /*
 Função que adiciona uma aresta direcionada com peso
 Entradas:
    v -> vértice origem
    w -> vértice destino
    p -> peso da aresta
 */ 
void Grafo::addAresta(int v, int w, int p) {
    if (this->isVertice(v) && this->isVertice(w)) {
        //emplace_back adiciona o par (destino, peso) à lista de adjacências do vértice de origem
        listaAdj[v].emplace_back(w, p);
        this->E++;
    } else {
        // Saída de erro
        std::cerr << "Erro: v e/ou w não pertencem ao conjunto de vértices V(G)." << std::endl;
    }
    
}

// Função para imprimir o grafo
void Grafo::imprimeGrafo() {
    for (int i = 0; i < V; i++) {
        std::cout << "Vértice " << i << " está conectado a:";

        if (listaAdj[i].empty()) {
            std::cout << " -";
        } else {
            for (const auto& E : listaAdj[i]) {
                int w = E.first;
                int p = E.second;
                std::cout << " (" << w << ", peso " << p << ")";
            }
        }

        std::cout << std::endl;
    }
}

 /*
 Função que verifica se o vértice passado como parâmetro pertence ao grafo.
 Entradas:
    v -> vértice
Saídas:
    true -> se v pertence ao grafo.
    false -> se v não pertence ao grafo.
 */ 
bool Grafo::isVertice(int v) {
    return (v >= 0 && v < this->V);
}

// Função que retorna o número de arestas do grafo
int Grafo::countArestas() {
    return this->E;
}

// Função que retorna o número de vértices do grafo
int Grafo::countVertices() {
    return this->V;
}    

 /*
 Função que remove a aresta (v, w) com peso p de um grafo direcionado e ponderado
 Entradas:
    v -> vértice origem
    w -> vértice destino
    p -> peso da aresta
Saídas:
    true -> aresta removida com sucesso
    false -> resulta em algum erro
 */ 
bool Grafo::removeAresta(int v, int w, int p) {
    if (this->isVertice(v) && this->isVertice(w)) {
        for (auto it = listaAdj[v].begin(); it != listaAdj[v].end(); ++it) {
            if (it->first == w && it->second == p) {
                listaAdj[v].erase(it);
                this->E--;
                return true; // Aresta encontrada e removida
            }
        }
        // Saída de erro
        std::cerr << "Erro: Aresta (" << v << ", " << w << ")com peso "<< p <<" não encontrada." << std::endl;
        return false;
    } else {
        // Saída de erro
        std::cerr << "Erro: v e/ou w não pertencem ao conjunto de vértices V(G)." << std::endl;
        return false;
    }
}

 /*
 Função que verifica se a aresta existe no grafo
 Entradas:
    v -> vértice origem
    w -> vértice destino
    p -> peso da aresta
Saídas: 
    true -> se a aresta existe
    false -> se a aresta não existe
 */ 
bool Grafo::existeAresta(int v, int w, int p) {
    for (const auto& E : listaAdj[v]) {
        if (E.first == w && E.second == p) {
            return true; // Aresta encontrada
        }
    }
    return false; // Aresta não encontrada
}

/*
 Função que modifica o peso da aresta (v, w) de um valor p -> pn
 Entradas:
    @param v vértice origem
    @param w vértice destino
    @param p peso da aresta (v, w)
    @param np novo peso da aresta (v, w)
Saídas: 
    @return true se a mudança ocorre com sucesso
    @return false se ocorrerem erros
 */ 
bool Grafo::mudaPeso(int v, int w, int p, int np) {
    if (this->isVertice(v) && this->isVertice(w)) {
        for (auto& E : listaAdj[v]) {
            if (E.first == w && E.second == p) {
                E.second = np;
                return true; // Peso da aresta modificado com sucesso
            }
        }
        // Saída de erro
        std::cerr << "Erro: Aresta (" << v << ", " << w << ")com peso p não encontrada." << std::endl;
        return false;
    } else {
        // Saída de erro
        std::cerr << "Erro: v = " << v << "e/ou w = " << w << "não pertencem ao conjunto de vértices V(G)." << std::endl;
        return false;
    }
}

// Função que libera todo o espaço utilizado pela representação de G
void Grafo::removeGrafo() {
    V = 0;
    E = 0;
    listaAdj.clear();
}

/*
 Função que devolve a lista de pesos de todas as arestas entre os vértices v e w em V (G). 
 Entradas:
    v -> vértice origem
    w -> vértice destino
Saídas: 
    Um vetor de pesos
 */ 
std::vector<int>Grafo::recuperaPeso(int v, int w) {
    std::vector<int> pesos;

    if (this->isVertice(v) && this->isVertice(w)) {
        for (const auto& E : listaAdj[v]) {
            if (E.first == w) {
                pesos.push_back(E.second);
            }
        }
    } else {
        std::cerr << "Erro: v = " << v << "e/ou w = " << w << "não pertencem ao conjunto de vértices V(G)." << std::endl;
    }

    return pesos;
}

// Função que retorna se o grafo G é um grafo simples ou não
bool Grafo::isGrafoSimples() {
    for (int v = 0; v < this->V; v++) {
        for (const auto& E : listaAdj[v]) {
            int w = E.first;

            // Verifica se há laços
            if (v == w) {
                return false;
            }

            // Verifica se há múltiplas arestas direcionadas entre o mesmo par de vértices
            for (const auto& AnotherE : this->listaAdj[w]) {
                if (AnotherE.first == v) {
                    return false;
                }
            }
        }
    }

    return true; // O grafo é simples
}

/*
Um grafo é uma árvore quando obedece as seguintes propriedades:
    1. Acíclico
    2. Conexo
    3. Tem exatamente n - 1 arestas, onde n é o número de vértices na árvore.*/
bool Grafo::isArvore() {
    // Verifica se o grafo é acíclico (não contém ciclos)
    if (ContemCiclo()) {
        return false;
    }

    // Verifica se o grafo é conexo
    std::set<int> visitados;

    // DFS a partir do primeiro vértice
    DFS(0, visitados);

    // Verificando se todos os vértices foram visitados
    if (visitados.size() != this->V) {
        return false;
    }

    return true;
}

bool Grafo::isBipartido() {
    // Inicializamos os conjuntos de vértices das partições
    std::set<int> particaoA;
    std::set<int> particaoB;

    // Inicializamos a fila de vértices para a BFS
    std::queue<int> fila;

    // Começamos a BFS a partir de um vértice arbitrário
    int v = 0;

    // Adicionamos o vértice inicial à partição A
    particaoA.insert(v);

    fila.push(v);

    while (!fila.empty()) {
        int v = fila.front();
        fila.pop();

        // Verificando a partição atual
        bool estaNaParticaoA = (particaoA.find(v) != particaoA.end());

        for (const auto& aresta : listaAdj[v]) {
            int w = aresta.first;

            // Se w não está em nenhuma partição, o colocamos na outra partição
            if (particaoA.find(w) == particaoA.end() && particaoB.find(w) == particaoB.end()) {
                if (estaNaParticaoA) {
                    particaoB.insert(w);
                } else {
                    particaoA.insert(w);
                }

                fila.push(w);
            } else if ((estaNaParticaoA && particaoA.find(w) != particaoA.end()) || (!estaNaParticaoA && particaoB.find(w) != particaoB.end())) {
                // Se w já está na mesma partição que v, o grafo não é bipartido
                return false;
            }
        }
    }

    // Se todos os vértices foram coloridos e aconteceram conflitos de partição, o grafo é bipartido
    return true;
}

void Grafo::DFS(int v, std::set<int>& visitados) {
    visitados.insert(v);

    for (const auto& E : listaAdj[v]) {
        int w = E.first;
        if (visitados.find(w) == visitados.end()) {
            DFS(w, visitados);
        }
    }
}


bool Grafo::isConexo() {
    std::set<int> visitados;

    // DFS a partir do primeiro vértice
    DFS(0, visitados);

    // Verificando se todos os vértices foram visitados
    return visitados.size() == this->V;
}

bool Grafo::DFSContemCiclo(int v, std::set<int>& visitados, std::set<int>& pilhaRecursao) {
    visitados.insert(v);
    pilhaRecursao.insert(v);

    for (const auto& E : listaAdj[v]) {
        int w = E.first;

        if (pilhaRecursao.find(w) != pilhaRecursao.end()) {
            // Um ciclo foi encontrado
            return true;
        }

        if (visitados.find(w) == visitados.end() && DFSContemCiclo(w, visitados, pilhaRecursao)) {
            return true;
        }
    }

    pilhaRecursao.erase(v);
    return false;
}

bool Grafo::ContemCiclo() {
    std::set<int> visitados;
    std::set<int> pilhaRecursao;

    for (int i = 0; i < this->V; i++) {
        if (DFSContemCiclo(i, visitados, pilhaRecursao)) {
            return true;
        }
    }

    return false;
}

// Função para criar o complemento do grafo
Grafo Grafo::complemento() {
    Grafo complementoGrafo(this->V);

    for (int i = 0; i < this->V; i++) {
        for (int j = 0; j < this->V; j++) {
            if (i != j) {
                bool arestaEncontrada = false;
                for (const auto &E : this->listaAdj[i]) {
                    if (E.first == j) {
                        arestaEncontrada = true;
                        break;
                    }
                }

                if (!arestaEncontrada) {
                    // Se não houver uma aresta de i para j em G, adiciona em G'
                    complementoGrafo.addAresta(i, j, 1); // Pode escolher qualquer peso
                }
            }
        }
    }

    return complementoGrafo;
}

// Função para verificar se uma aresta (v, w) existe em G
bool Grafo::isAdjacente(int v, int w) {
    // Verifica se os vértices de vi e vj são válidos
    if (this->isVertice(v) && this->isVertice(w)) {
        for (const auto &E : listaAdj[v]) {
            if (E.first == w) {
                std::cout << "A aresta (" << v << ", " << w << ") existe!" << std::endl;
                return true; // A aresta existe
            }
        }
        std::cout << "A aresta (" << v << ", " << w << ") NÃO existe!" << std::endl;
        return false; // A aresta não existe
    }
    else {
        std::cout << "Vértices inválidos!" << std::endl;
        return false;
    }
}

// Função para obter a lista de adjacência de um vértice v
std::vector<std::pair<int, int>> Grafo::adjacentes(int v) {
        // Verifica se o vértice v é válido
        if (!this->isVertice(v)) {
            std::cout << "Vértice inválido!" << std::endl;
            return std::vector<std::pair<int, int>>();
        }

        return listaAdj[v];
    }


void Grafo::BFS(int v) {
    if (!this->isVertice(v)) {
        std::cerr << "Vértice inválido!" << std::endl;
        return;
    }

    std::queue<int> q;
    std::set<int> visitados;
    std::map<int, int> arvore_de_busca;
    
    q.push(v);
    visitados.insert(v);
    arvore_de_busca[v] = -1;

    while(!q.empty()) {
        int v = q.front();
        std::cout << "Queue: " << v << std::endl;
        q.pop(); // Remove o primeiro elemento da fila


        std::cout << "Visitando o vértice " << v << std::endl;
        for (const auto& E: listaAdj[v]) {
            int w = E.first;

            if (visitados.find(w) == visitados.end()) {
                visitados.insert(w);
                q.push(w);
                arvore_de_busca[w] = v;
            }
        }
    }

    std::cout << std::endl;
    std::cout << "Árvore de busca em largura: " << std::endl;
    
    for (const auto& entry: arvore_de_busca) {
        int vi = entry.first;
        int parent = entry.second;

        if (parent != -1) {
            std::cout << "(" << vi << ", " << parent << ")" << std::endl;
        } else {
            std::cout << "(" << vi << ", " << "raiz" << ")" << std::endl;
        }
    }
}


std::vector<int> Grafo::caminhoMinimo(int v, int w) {
    if (!this->isVertice(v) || !this->isVertice(w)) {
        std::cerr << "Vértice inválido!" << std::endl;
        return std::vector<int>();
    }

    // Criar uma lista de distâncias (dist) e inicializá-la com infinito para todos os vértices do grafo.
    std::vector<int> dist(this->V, INT_MAX);
    dist[v] = 0;

    std::vector<int> pai(this->V, -1);
    pai[v] = INT_MIN;

    std::set<int> onHeap;

    // Criar um heap de Fibonacci e inserir o nó de origem com distância 0.
    boost::heap::fibonacci_heap<std::pair<int, int>, boost::heap::compare<std::greater<std::pair<int, int>>>> heap;
    std::map<int, boost::heap::fibonacci_heap<std::pair<int, int>, boost::heap::compare<std::greater<std::pair<int, int>>>>::handle_type> handles;
    handles[v] = heap.push(std::make_pair(v, 0));
    onHeap.insert(v);

    // Enquanto o heap não estiver vazio, faça:
    while(!heap.empty()) {
        // Remover o nó com menor distância do heap. Vamos chamá-lo de nó atual.
        int u = heap.top().first;
        heap.pop();
        onHeap.erase(u);

        // Para cada vizinho v do nó atual, faça:
        for (const auto& E : listaAdj[u]) {
            int v = E.first;
            int peso = E.second;

            // Se a distância do nó atual + peso da aresta (u, v) for menor que a distância de v, então atualize a distância de v.
            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pai[v] = u;

                if (onHeap.find(v) == onHeap.end()) {
                    // Inserir v no heap
                    handles[v] = heap.push(std::make_pair(v, dist[v]));
                    onHeap.insert(v);
                } else {
                    // Atualizar a distância de v no heap
                    heap.update(handles[v], std::make_pair(v, dist[v]));
                }
            }
        }
    }

    // Retornar a lista de distâncias
    std::vector<int> caminho;

    int u = w;

    while (u != v) {
        caminho.push_back(u);
        u = pai[u];
    }

    caminho.push_back(v);

    std::reverse(caminho.begin(), caminho.end());

    return caminho;
}

// Bellman-Ford
int **Grafo::custoMinimo(int v) {
    std::vector<int> dist(this->V, INT_MAX);
    std::vector<int> predecessor(this->V, null_parent);

    dist[v] = 0;

    // Relaxar todas as arestas V - 1 vezes
    for (int i = 0; i < this->V -1; ++i) {
        for (int u = 0; u < this->V; ++u) {
            for (const auto& edge : listaAdj[u]) {
                int w = edge.first;
                int peso = edge.second;

                if (dist[u] != INT_MAX && dist[u] + peso < dist[w]) {
                    dist[w] = dist[u] + peso;
                    predecessor[w] = u;
                }
            }
        }
    }

    // Verificar se há ciclos negativos
    for (int u = 0; u < this->V - 1; ++u) {
        for (const auto& edge : listaAdj[u]) {
            int w = edge.first;
            int peso = edge.second;

            if (dist[u] != INT_MAX && dist[u] + peso < dist[w]) {
                std::cerr << "O grafo contém ciclos negativos!" << std::endl;
                return nullptr;
            }
        }
    }

    int **dist_predecessor = new int*[2];
    dist_predecessor[0] = dist.data();
    dist_predecessor[1] = predecessor.data();

    return dist_predecessor;
}

// Devolve os caminhos mínimos entre vi ∈ V (G) e todos os demais vértices de G;
// Usando o algoritmo de Dijkstra
std::vector<std::pair<int, int>> Grafo::caminhoMinimo(int v) {
    std::vector<int> dist(this->V, INT_MAX);
    std::vector<int> predecessor(this->V, null_parent);

    dist[v] = 0;

    // Criar um heap de Fibonacci e inserir o nó de origem com distância 0.
    boost::heap::fibonacci_heap<std::pair<int, int>, boost::heap::compare<std::greater<std::pair<int, int>>>> heap;
    std::map<int, boost::heap::fibonacci_heap<std::pair<int, int>, boost::heap::compare<std::greater<std::pair<int, int>>>>::handle_type> handles;

    handles[v] = heap.push(std::make_pair(v, 0));

    // Enquanto o heap não estiver vazio, faça:
    while(!heap.empty()) {
        // Remover o nó com menor distância do heap. Vamos chamá-lo de nó atual.
        int u = heap.top().first;
        heap.pop();

        // Para cada vizinho v do nó atual, faça:
        for (const auto& E : listaAdj[u]) {
            int w = E.first;
            int peso = E.second;

            // Se a distância do nó atual + peso da aresta (u, v) for menor que a distância de v, então atualize a distância de v.
            if (dist[u] + peso < dist[w]) {
                dist[w] = dist[u] + peso;
                predecessor[w] = u;

                if (handles.find(w) == handles.end()) {
                    // Inserir v no heap
                    handles[w] = heap.push(std::make_pair(w, dist[w]));
                } else {
                    // Atualizar a distância de v no heap
                    heap.update(handles[w], std::make_pair(w, dist[w]));
                }
            }
        }
    }

    std::vector<std::pair<int, int>> dist_predecessor;

    for (int i = 0; i < this->V; ++i) {
        dist_predecessor.push_back(std::make_pair(dist[i], predecessor[i]));
    }

    return dist_predecessor;
}