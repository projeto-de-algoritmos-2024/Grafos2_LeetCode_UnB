class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {

        // pega o número de nós do grafo
        int n = graph.size();

        // máscara de bits que vai auxiliar para armazenar os nós já visitados
        int mascaraTotal = (1 << n) - 1;

        // armazenando {nó, {distância, máscara}}
        queue<pair<int, pair<int, int>>> fila;
        set<pair<int, int>> visitados;

        // colocando cada nó na fila com a máscara
        // como exemplo, se colocarmos o nó 3, entraremos {3, {0, 0 0 0 1 1}}
        for (int i = 0; i < n; i++) {
            int mascara = (1 << i);
            visitados.insert({i, mascara});
            fila.push({i, {0, mascara}});
        }

        // faz a BFS
        while (!fila.empty()) {
            int no = fila.front().first;
            int dist = fila.front().second.first;
            int mascara = fila.front().second.second;
            fila.pop();

            for (int vizinho : graph[no]) {
                // cria uma nova máscara de bits incluindo o nó atual (vizinho)
                int novaMascara = (mascara | (1 << vizinho));
                
                // verifica se todos os nós foram visitados
                if (novaMascara == mascaraTotal) 
                    return dist + 1; // retorna a distância total (caminho mais curto)
                
                // se o nó já foi visitado, continua para o próximo
                else if (visitados.count({vizinho, novaMascara})) 
                    continue;
                
                // caso contrário, adiciona o novo vizinho na fila
                else {
                    fila.push({vizinho, {dist + 1, novaMascara}});
                    visitados.insert({vizinho, novaMascara}); // marca como visitado
                }
            }

        }
        return 0;
    }
};
