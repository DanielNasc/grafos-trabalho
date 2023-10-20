#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <string>
#include <vector>

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
    1. Deve ser um grafo conexo.
    2. Não deve conter ciclos.
    3. Deve ter exatamente n - 1 arestas, onde n é o número de vértices.*/

bool Grafo::isArvore() {
    // Número de vértices alcançáveis
    int numVerticesAlcancaveis = 0;
    std::vector<bool> visitado(this->V, false);

    for (int v = 0; v < this->V; v++) {
        if (!visitado[v]) {
            numVerticesAlcancaveis++;
            visitado[v] = true;
            for (const auto& E : this->listaAdj[v]) {
                int w = E.first;
                if (visitado[w]) {
                    return false; // Ciclo encontrado
                }
                visitado[w] = true;
            }
        }
    }

    return numVerticesAlcancaveis == this->V && this->E == (this->V - 1);
}
