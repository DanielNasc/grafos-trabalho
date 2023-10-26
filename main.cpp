#include <iostream>
#include <fstream>
#include <utility>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>

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

    g->addAresta(2, 1, 10);

    g->imprimeGrafo();

    // Testando remoção
    if (g->removeAresta(1, 3, 12)) {
        std::cout << "Aresta removida com sucesso." << std::endl;
    } else {
        std::cerr << "Falha na remoção da aresta." << std::endl;
    }

    if (g->removeAresta(3, 1, 10)) {
        std::cout << "Aresta removida com sucesso." << std::endl;
    } else {
        std::cerr << "Falha na remoção da aresta." << std::endl;
    }

    if (g->removeAresta(6, 1, 7)) {
        std::cout << "Aresta removida com sucesso." << std::endl;
    } else {
        std::cerr << "Falha na remoção da aresta." << std::endl;
    }

    if (g->removeAresta(3, 0, 10)) {
        std::cout << "Aresta removida com sucesso." << std::endl;
    } else {
        std::cerr << "Falha na remoção da aresta." << std::endl;
    }
    

    g->imprimeGrafo();

    // Testando mudança de peso
    if (g->mudaPeso(4, 5, -15, -13)) {
        std::cout << "Peso da aresta modificado com sucesso." << std::endl;
    } else {
        std::cerr << "Falha na modificação do peso da aresta." << std::endl;
    }

    g->imprimeGrafo();

    // Testando recupera peso
    std::vector<int> pesos = g->recuperaPeso(6, 1);

    if (!pesos.empty()) {
        std::cout << "Pesos das arestas entre " << 6 << " e " << 1 << ": ";
        for (int peso : pesos) {
            std::cout << peso << " ";
        }
        std::cout << std::endl;
    } else {
        std::cerr << "Não foram encontradas arestas entre " << 6 << " e " << 1 << "." << std::endl;
    }

    // Testando grafo simples
    if (g->isGrafoSimples()) {
        std::cout << "O grafo é simples." << std::endl;
    } else {
        std::cout << "O grafo não é simples." << std::endl;
    }

    // Testando se é uma árvore
    if (g->isArvore()) {
        std::cout << "O grafo é uma árvore." << std::endl;
    } else {
        std::cout << "O grafo não é uma árvore." << std::endl;
    }

    if (g->removeAresta(4, 5, -13)) {
        std::cout << "Aresta removida com sucesso." << std::endl;
    } else {
        std::cerr << "Falha na remoção da aresta." << std::endl;
    }

    if (g->removeAresta(1, 3, 45)) {
        std::cout << "Aresta removida com sucesso." << std::endl;
    } else {
        std::cerr << "Falha na remoção da aresta." << std::endl;
    }

    if (g->removeAresta(3, 0, 13)) {
        std::cout << "Aresta removida com sucesso." << std::endl;
    } else {
        std::cerr << "Falha na remoção da aresta." << std::endl;
    }

    if (g->removeAresta(2, 1, 10)) {
        std::cout << "Aresta removida com sucesso." << std::endl;
    } else {
        std::cerr << "Falha na remoção da aresta." << std::endl;
    }

    if (g->removeAresta(5, 6, 3)) {
        std::cout << "Aresta removida com sucesso." << std::endl;
    } else {
        std::cerr << "Falha na remoção da aresta." << std::endl;
    }

    g->addAresta(1, 3, 7);
    g->addAresta(2, 6, 3);
    g->addAresta(4, 1, 3);

    g->imprimeGrafo();

    if (g->isArvore()) {
        std::cout << "O grafo é uma árvore." << std::endl;
    } else {
        std::cout << "O grafo não é uma árvore." << std::endl;
    }

    std::cout << "Arestas " << g->countArestas() << std::endl;; 
    std::cout << "Vértices: " << g->countVertices() << std::endl;

    // Verificando se o grafo é bipartido
    bool eBipartido = g->isBipartido();

    if (eBipartido) {
        std::cout << "O grafo G é bipartido." << std::endl;
    } else {
        std::cout << "O grafo G não é bipartido." << std::endl;
    }
    
    // Testando Complemento de um grafo
    Grafo complementog = g->complemento();

    std::cout << "Complemento de G:" << std::endl;
    complementog.imprimeGrafo();

    // Testando isAdjacente
    g->isAdjacente(1, 4);
    g->isAdjacente(0, 3);
    g->isAdjacente(5, 1);

    // Testando Adjacentes
    std::vector<std::pair<int, int>> adjacencia = g->adjacentes(0);
    if (adjacencia.empty()) {
        std::cout << "A lista de adjacência de v não pôde ser obtida." << std::endl;
    } else {
        std::cout << "Lista de adjacência do vértice " << v << ":" << std::endl;
        for (const auto &E : adjacencia) {
            std::cout << "Destino: " << E.first << " Peso: " << E.second << std::endl;
        }
    }

    // Testando Incidentes
    std::vector<std::pair<int, int>> incidentes = g->incidentes(1);

    if (incidentes.empty()) {
        std::cout << "Não há arestas incidentes ao vértice "<< v << std::endl;
    } else {
        std::cout << "Arestas incidentes ao vértice " << v << ":" << std::endl;
        for (const auto &E : incidentes) {
            std::cout << "Origem: " << E.first << " Peso: " << E.second << std::endl;
        }
    }

    // Testando DFS
    std::cout << "Iniciando a DFS a partir do vértice " << 0 << ":" << std::endl;
    g->iniciarDFS(0);

    g->removeGrafo();
    std::cout << "Grafo removido." << std::endl;

}