class Solution {
public:
    // função para calcular a distância entre dois pontos (nós)
    int calcularDistancia(vector<int>& pontoA, vector<int>& pontoB) {
        return abs(pontoA[0] - pontoB[0]) + abs(pontoA[1] - pontoB[1]);
    }

    // função principal para calcular o menor custo de conectar os nós
    int minCostConnectPoints(vector<vector<int>>& graph) {
        int n = graph.size(); // número de nós no grafo

        // matriz que armazena as distâncias entre todos os pares de nós
        vector<vector<int>> grafo(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    grafo[i][j] = calcularDistancia(graph[i], graph[j]);
                }
            }
        }

        // vetor que armazena o menor custo de conectar cada nó
        vector<int> custo(n, INT_MAX);
        // vetor que armazena os nós que já foram conectados
        vector<bool> conectado(n, false);

        custo[0] = 0; // começa pelo primeiro nó e possui custo inicial e total = 0
        int custoTotal = 0;

        // algoritmo de Prim para conectar todos os nós, um por um, com o menor custo
        for (int count = 0; count < n; count++) {
            int noAtual = -1;
            for (int i = 0; i < n; i++) {
                if (!conectado[i] && (noAtual == -1 || custo[i] < custo[noAtual])) {
                    noAtual = i;
                }
            }

            // conecta o nó de menor custo e soma ao custoTotal o valor do nó atual
            conectado[noAtual] = true;
            custoTotal += custo[noAtual];

            // atualiza os custos para os nós restantes, ou seja, para cada nó ainda não conectado,
            // o algoritmo atualiza o custo caso ele seja menor que o custo atual armazenado
            for (int i = 0; i < n; i++) {
                if (!conectado[i] && grafo[noAtual][i] < custo[i]) {
                    custo[i] = grafo[noAtual][i];
                }
            }
        }

        return custoTotal; // retorna o custo total para conectar todos os pontos
    }
};