class Grafo {
    private:
        int V;
        int E;
        // Lista de adjacência com pares (destino, peso)
        std::vector<std::vector<std::pair<int, int>>> listaAdj;
    public:
        Grafo();                                                // Construtor de G com V = 1;
        Grafo(int V);                                           // Construtor de G;
        bool isVertice(int v);                                  // Verifica se v ∈ V (G) ou não;  
        void addAresta(int v, int w, int p);                    // Adiciona uma aresta em G entre os vértices v e w com peso p.
        bool removeAresta(int v, int w, int p);                 // Remove uma e existe uma aresta em G entre os vértices v e w com peso p.
        bool mudaPeso(int v, int w, int p, int np);             // Modifica valor de peso de umaaresta em G entre os vértices v e w com peso p.
        bool existeAresta(int v, int w, int p);                 // Verifica s aresta em G entre os vértices v e w de valor p para o valor np
        void imprimeGrafo();                                    // Imprime todos os vértices e arestas de G;
        void removeGrafo();                                     // Libera todo o espaço utilizado pela representação de G;
        std::vector<int>recuperaPeso(int v, int w);             // Devolve a lista de pesos de todas as arestas entre os vértices v e w em V(G).
        bool isGrafoSimples();                                  // Retorna se o grafo G é um grafo simples ou não
        bool isArvore();                                        // Retorna se o grafo G é uma árvore ou não;
        bool isBipartido();                                     // Retorna se o grafo G é bipartido ou não;
        Grafo complemento();                                    // Retorna o grafo complementar de G;
        bool isAdjacente(int v, int w);                         // Verifica se vw ∈ E(G);
        std::vector<std::pair<int, int>> adjacentes(int v);     // Devolve a lista de adjacência de v em G.
        int *incidentes(int v);                                 // Devolve as arestas incidentes a v em G.
        int **matrizAdj();                                      // Constrói a matriz de adjacência de G, onde a posição ai,j corresponde ao peso da aresta vivj, para todo 1 ≤ i ≤ j ≤ n
        void imprimeMatrizAdj();                                // Imprime a matriz de adjacência de G;
        bool isConexo();                                        // Retorna se G é conexo ou não
        int countArestas();                                     // Retorna o número de arestas de G;
        int countVertices();                                    // Retorna o número de vértices de G;
        void DFS(int v, std::set<int>& visitados);
        void BFS(int v);                                        // Percorre o grafo em largura a partir do vértice v;
        bool ContemCiclo();
        bool DFSContemCiclo(int v, std::set<int>& visitados, std::set<int>& pilhaRecursao);
        std::vector<int> caminhoMinimo(int v, int w);            // Retorna o caminho mínimo entre os vértices v e w em G;
        std::vector<int> custoMinimo(int v, int w);              // Retorna o custo mínimo entre os vértices v e w em G;
};