#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>

#include "grafo.h"

Grafo::Grafo() {
    this->V = 1;
    this->E = 0;
}

// Construtor para criar um grafo com um número especificado de vértices
Grafo::Grafo(int V) {
    this->V = V;
    this->E = 0;
    listaAdj.resize(V);
}

void Grafo::addAresta(int v, int w, int p) {
    if (this->isVertice(v) && this->isVertice(w)) {
        //emplace_back adiciona o par (destino, peso) à lista de adjacências do vértice de origem
        listaAdj[v].emplace_back(w, p);
        this->E++;
    } else {
        std::cerr << "Erro: v e/ou w não pertencem ao conjunto de vértices V(G)." << std::endl;
    }
    
}

void Grafo::imprimeGrafo() {
    for (int i = 0; i < V; i++) {
        std::cout << "Vértice " << i << " está conectado a:";
        for (const auto& E : listaAdj[i]) {
            int w = E.first;
            int p = E.second;
            std::cout << " (" << w << ", peso " << p << ")";
        }
        std::cout << std::endl;
    }
}

bool Grafo::isVertice(int v) {
    return (v >= 0 && v < this->V);
}

int Grafo::countArestas() {
    return this->E;
}

int Grafo::countVertices() {
    return this->V;
}    

// Remove a aresta (v, w) com peso p de um grafo direcionado e ponderado
bool Grafo::removeAresta(int v, int w, int p) {
    if (this->isVertice(v) && this->isVertice(w)) {
        for (auto it = listaAdj[v].begin(); it != listaAdj[v].end(); ++it) {
            if (it->first == w && it->second == p) {
                listaAdj[v].erase(it);
                this->E--;
                return true; // Aresta encontrada e removida
            }
        }
        std::cerr << "Erro: Aresta (" << v << ", " << w << ")com peso "<< p <<" não encontrada." << std::endl;
        return false;
    } else {
        std::cerr << "Erro: v e/ou w não pertencem ao conjunto de vértices V(G)." << std::endl;
        return false;
    }
}

bool Grafo::existeAresta(int v, int w, int p) {
    for (const auto& E : listaAdj[v]) {
        if (E.first == w && E.second == p) {
            return true; // Aresta encontrada
        }
    }
    return false; // Aresta não encontrada
}

bool Grafo::mudaPeso(int v, int w, int p, int np) {
    if (this->isVertice(v) && this->isVertice(w)) {
        for (auto& E : listaAdj[v]) {
            if (E.first == w && E.second == p) {
                E.second = np;
                return true; // Peso da aresta modificado com sucesso
            }
        }
        std::cerr << "Erro: Aresta (" << v << ", " << w << ")com peso p não encontrada." << std::endl;
        return false;
    } else {
        std::cerr << "Erro: v = " << v << "e/ou w = " << w << "não pertencem ao conjunto de vértices V(G)." << std::endl;
        return false;
    }
}

void Grafo::removeGrafo() {
    V = 0;
    E = 0;
    listaAdj.clear();
}

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

bool Grafo::isGrafoSimples() {
    for (int v = 0; v < this->V; v++) {
        for (const auto& E : listaAdj[v]) {
            int w = E.first;

            // Verifica se há laços (arestas que ligam um vértice a ele mesmo)
            if (v == w) {
                return false;
            }

            // Verifica se há múltiplas arestas direcionadas entre o mesmo par de vértices
            for (const auto& outraAresta : this->listaAdj[w]) {
                if (outraAresta.first == v) {
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
    4. Número correto de arestas: tem exatamente n - 1 arestas, onde n é o número de vértices na árvore.*/

bool Grafo::isArvore() {
    // Verifica se o grafo é acíclico (não contém ciclos)
    if (ContemCiclo()) {
        return false;
    }

    // Verifica se o grafo é conectado
    std::set<int> visitados;

    // Comece a DFS a partir do primeiro vértice (pode ser qualquer vértice)
    DFS(0, visitados);

    // Verifique se todos os vértices foram visitados
    if (visitados.size() != this->V) {
        return false;
    }

    return true;
}

bool Grafo::isBipartido() {
    // Inicializa os conjuntos de vértices das partições
    std::set<int> particaoA;
    std::set<int> particaoB;

    // Inicializa a fila de vértices para a BFS
    std::queue<int> fila;

    // Começa a BFS a partir de um vértice arbitrário (pode ser qualquer vértice)
    int verticeInicial = 0;

    // Adiciona o vértice inicial à Partição A
    particaoA.insert(verticeInicial);

    fila.push(verticeInicial);

    while (!fila.empty()) {
        int v = fila.front();
        fila.pop();

        // Verifica a partição atual
        bool estaEmParticaoA = (particaoA.find(v) != particaoA.end());

        for (const auto& aresta : listaAdj[v]) {
            int w = aresta.first;

            // Se w não está em nenhuma partição, coloque-o na outra partição
            if (particaoA.find(w) == particaoA.end() && particaoB.find(w) == particaoB.end()) {
                if (estaEmParticaoA) {
                    particaoB.insert(w);
                } else {
                    particaoA.insert(w);
                }

                fila.push(w);
            } else if ((estaEmParticaoA && particaoA.find(w) != particaoA.end()) || (!estaEmParticaoA && particaoB.find(w) != particaoB.end())) {
                // Se w já está na mesma partição que v, o grafo não é bipartido
                return false;
            }
        }
    }

    // Se todos os vértices foram coloridos e não houve conflitos de partição, o grafo é bipartido
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

    // Comece a DFS a partir do primeiro vértice (pode ser qualquer vértice)
    DFS(0, visitados);

    // Verifique se todos os vértices foram visitados
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
