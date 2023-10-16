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
    if (this->adj[v][w] == 0) {
        this->adj[v][w] = p; // Adiciona apenas a aresta v -> w, pois o grafo é direcionado
        this->E++;
    }
}

int Grafo::countArestas() {
    return this->E;
}