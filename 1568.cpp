
/*
    Link do problema: https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/
    1568. Minimum Number of Days to Disconnect Island


    Foco do problema, é descobrir o numero minimo de dias para desconectar a ilha.
    Para isso, é necessario contar o numero de ilhas e o numero de celulas de terra.
    Se o numero de ilhas é 0 ou maior que 1, retorna 0.
    Se o numero de celulas de terra é 1, retorna 1.
    Caso contrario, tenta desconectar a ilha removendo uma celula de terra por vez e verificando o numero de ilhas resultante.
    Se o numero de ilhas resultante for diferente de 1, retorna 1.
    Caso contrario, retorna 2.
*/

#include <vector>
using namespace std;

class Solution
{
private:
    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};

public:
    // Verifica se a posição é válida
    bool ehPosicaoValida(int x, int y, int linhas, int colunas)
    {
        // retorna true se:
        // - x e y não são negativos
        // - x é menor que o n de linhas
        // - y é menor que o n de colunas
        return (x >= 0 && x < linhas && y >= 0 && y < colunas);
    }

    void buscaProfundidade(vector<vector<int>> &matrix, int x, int y)
    {
        int linhas = matrix.size();
        int colunas = matrix[0].size();

        matrix[x][y] = 0;

        // P/ cada uma das 4 direcoes vai verificar se a posição é válida e se é terra
        for (int i = 0; i < 4; i++)
        {
            int novo_x = x + dx[i]; 
            int novo_y = y + dy[i];

            if (ehPosicaoValida(novo_x, novo_y, linhas, colunas) && matrix[novo_x][novo_y] == 1) 
            // se a posição é válida e é terra chama recursivamente
            {
                buscaProfundidade(matrix, novo_x, novo_y);
            }
        }
    }

    int contaIlhas(vector<vector<int>> matrix)
    {
        int linhas = matrix.size();
        int colunas = matrix[0].size();
        int numeroDeIlhas = 0;

        // P/ cada uma das linhas e colunas
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                // se é terra
                if (matrix[i][j] == 1)
                {
                    numeroDeIlhas++; // incrementa o numero de ilhas
                    buscaProfundidade(matrix, i, j); // chama a dfs
                }
            }
        }

        return numeroDeIlhas;
    }

    int minDays(vector<vector<int>>& matrix) {
        // verifica o estado inicial
        int numeroDeIlhas = contaIlhas(matrix);
        
        // Se já está desconectado ou não tem ilhas
        if(numeroDeIlhas == 0 || numeroDeIlhas >= 2) {
            return 0;
        }
        
        int totalCelulas = 0;
        // Conta o numero de celulas de terra
        for(int i = 0; i < matrix.size(); i++) {
            for(int j = 0; j < matrix[0].size(); j++) {
                if(matrix[i][j] == 1) totalCelulas++; // incrementa o numero de celulas de terra
            }
        }
        if(totalCelulas == 1) return 1; // se tem apenas uma celula de terra, precisa de 1 dia
        
        // Tenta remover uma célula por vez
        for(int i = 0; i < matrix.size(); i++) {
            for(int j = 0; j < matrix[0].size(); j++) {
                if(matrix[i][j] == 1) {// se é terra
                    vector<vector<int>> temp = matrix; // faz uma copia da matrix
                    temp[i][j] = 0; // remove a celula de terra
                    if(contaIlhas(temp) != 1) return 1; // se o numero de ilhas é diferente de 1, retorna 1
                }
            }
        }
        
        return 2;// se não conseguiu desconectar em 1 dia, precisa de 2 dias
    }

    // Conta quantas células de terra existem
    int contaCelulas(vector<vector<int>> &matrix)
    {
        int total = 0;
        for (int i = 0; i < matrix.size(); i++) // p/ cada uma das linhas e colunas
        {
            for (int j = 0; j < matrix[0].size(); j++)
            {
                if (matrix[i][j] == 1)// se é terra
                    total++; // incrementa o total
            }
        }
        return total;
    }
};