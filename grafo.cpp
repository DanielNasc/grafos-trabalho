#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "grafo.h"

Grafo::Grafo() {
    this->V = 1;
    this->E = 0;
    this->adj = NULL;
}

Grafo::Grafo(int V) {
    this->V = V;
    this->E = 0;
    this->adj = new int*[V]; // Aloca um vetor de V posições

    for(int i = 0; i < V; i++) {
        this->adj[i] = new int[V]; // Aloca um vetor de V posições para cada posição do vetor de V posições

        for(int j = 0; j < V; j++) {
            this->adj[i][j] = 0;  // Inicializa todas as posições com 0
        }
    }
}

void Grafo::addAresta(int v, int w, int p) {
    if (this->isVertice(v) && this->isVertice(w) && this->adj[v][w] == 0) {
        this->adj[v][w] = p; // Adiciona apenas a aresta v -> w, pois o grafo é direcionado
        this->E++;
    }
}

int Grafo::countArestas() {
    return this->E;
}

bool Grafo::isVertice(int v) {
    return (v <= (this->V)-1);
}

void Grafo::removeAresta(int v, int w, int p) {
    if (this->existeAresta(v, w, p)) {
        this->adj[v][w] = 0; // Remove a aresta
        this->E--;
    }
}

bool Grafo::existeAresta(int v, int w, int p) {
    return (this->isVertice(v) && this->isVertice(w) && this->adj[v][w] == p);
}

void Grafo::mudaPeso(int v, int w, int p, int np) {
    if (this->existeAresta(v, w, p)) {
        this->adj[v][w] = np;
    }
}

void Grafo::imprimeGrafo() {

    std::cout << "Matriz de Adjacências\n"<< std::endl;
    std::cout << "V | ";
    
    for (int i = 0; i < this->V; i++ ) {
        std::cout << "\t" << i;
    }
    std::cout << std::endl;

    for(int i = 0; i < this->V; i++) {
        std::cout << "---------------------------------------------------------------"<< std::endl;
        std::cout << i << " | ";
        for (int j = 0; j < this->V; j++) {
            std::cout << "\t" << this->adj[i][j];
        }
        std::cout << std::endl;
    }
}

bool Grafo::isGrafoSimples() {
    for(int i = 0; i < this->V; i++) {
        for (int j = 0; j < this->V; j++) {
            if(i == j) {
                if(this->adj[i][j] != 0) return false;
            }
            else {
                if (this->adj[i][j] != 0 && this->adj[j][i] != 0) return false;
            }
        }
        std::cout << std::endl;
    }
    return true;
}   
