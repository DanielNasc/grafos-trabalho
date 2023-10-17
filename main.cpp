#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "grafo.h"

#define FILENAME "grafo.txt"

int main(void) {
    std::ifstream file(FILENAME);

    if (!file.is_open()) {
        std::cout << "Erro ao abrir o arquivo " << FILENAME << std::endl;
        return 1;
    }

    std::string graph_label;
    int V, E;

    // Pegar o label do grafo, o número de vértices e o número de arestas 
    file >> graph_label >> V >> E;

    std::cout << "O grafo " << graph_label << " tem " << V << " vértices." << std::endl;
    Grafo *g = new Grafo(V);

    int u, v;
    double p;

    std::cout << std::endl;
    while(file >> u >> v >> p) {
        std::cout << "\tAdicionando aresta (" << u << ", " << v << ") com peso " << p << " ao grafo G." << std::endl;
        g->addAresta(u, v, p);
    }
    std::cout << std::endl;

    if (g->countArestas() != E) {
        std::cout << "O número de arestas adicionadas é diferente do número de arestas do grafo." << std::endl;
        std::cout << "\tNúmero de arestas adicionadas: " << g->countArestas() << std::endl;
        std::cout << "\tNúmero de arestas do grafo: " << E << std::endl;
        return 1;
    }

    // Testando remoção
    g->removeAresta(1, 5, 11);
    std::cout << "E: " << g->countArestas() << std::endl;
    g->removeAresta(3, 9, 45);


    // Testando mudança de peso
    g->mudaPeso(4, 5, -15, -13); // Faz o L
    
    g->imprimeGrafo();
    if(g->isGrafoSimples()) {
        std::cout << "O grafo é simples." << std::endl;
    }
    else {
        std::cout << "O grafo NÃO é simples." << std::endl;
    }


    return 0;
}