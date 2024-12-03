/*  
    Link do problema: https://leetcode.com/problems/cheapest-flights-within-k-stops/
    787. Cheapest Flights Within K Stops

    A ideia principal desta questão é encontrar o voo mais barato entre duas cidades com uma restrição importante: 
    você só pode fazer no máximo K paradas no meio do caminho.

    Para isso, usamos uma tabela para guardar os preços para cada cidade com cada número de paradas possíveis.
*/

#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution
{
public:
    // Esta função encontra o voo mais barato de uma cidade para outra!
    // n = número total de cidades
    // flights = lista de todos os voos disponíveis (origem, destino e preço)
    // src = cidade de onde queremos partir
    // dst = cidade para onde queremos ir
    // k = número máximo de paradas que podemos fazer
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
    {
        // Primeiro, vamos criar uma tabela para guardar os preços
        // Para cada cidade, vamos guardar quanto custa chegar até ela fazendo 0, 1, 2... até k paradas
        // Começamos com INT_MAX (preço infinito) para todas as cidades
        vector<vector<int>> custos(k + 2, vector<int>(n, INT_MAX));
        
        // Ei, para chegar na cidade de partida não custa nada! É só estar lá
        custos[0][src] = 0;
        
        // Agora vem a parte legal: vamos tentar todas as combinações possíveis
        // Começando com 0 paradas até o máximo de paradas permitidas
        for (int paradas = 0; paradas <= k; paradas++)
        {
            // Para cada voo disponível na nossa lista...
            for (const auto &voo : flights)
            {
                // Pega as informações deste voo
                int origem = voo[0];     // De onde sai
                int destino = voo[1];    // Para onde vai
                int preco = voo[2];      // Quanto custa
                
                // Se não conseguimos nem chegar na cidade de origem deste voo
                // não tem como usá-lo, né? Vamos para o próximo
                if (custos[paradas][origem] == INT_MAX)
                {
                    continue;
                }
                
                // Vamos calcular quanto custaria usar este voo
                // Usamos long long porque a soma pode ficar muito grande!
                long long precoTotal = (long long)custos[paradas][origem] + preco;
                
                // Se o preço total não ficou absurdamente alto...
                if (precoTotal < INT_MAX)
                {
                    // Guardamos este preço se for menor que o que já tínhamos
                    // Note que estamos usando paradas + 1 porque este voo adiciona uma parada
                    custos[paradas + 1][destino] = min(custos[paradas + 1][destino], 
                                                      (int)precoTotal);
                }
            }
        }
        
        // Beleza! Agora vamos ver qual é o menor preço que conseguimos
        // para chegar no nosso destino, não importa quantas paradas fizemos
        int melhorPreco = INT_MAX;
        for (int paradas = 0; paradas <= k + 1; paradas++)
        {
            melhorPreco = min(melhorPreco, custos[paradas][dst]);
        }
        
        // Se o melhorPreco ainda é infinito, significa que não achamos nenhum caminho :(
        // Neste caso retornamos -1
        // Senão, retornamos o melhor preço que encontramos!
        return melhorPreco == INT_MAX ? -1 : melhorPreco;
    }
};