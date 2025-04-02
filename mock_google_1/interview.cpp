#include <vector>

#define max(a,b) (a>b)?(a):(b)

/**
 * m[x][y] && getBoundries()
 * visitados[x][y]
 * m[x][y][0] = tamanho da maior sequencia crescente partindo de xy e indo para cima
 * 
 * M[x][y] = 0, 1234 ou elas sao invalidas ou visitada[x][y]
 * m[x][y][d] = max[0 <= d <= 3](m[x'][y'][d] + 1) | m[x'][y'] > m[x][y] + 1, cc
 * 
 * visitados[x][y]
 * 
 * [[9,9,4],[6,6,8],[2,1,1]]
*/

class Solution {
public:
    int rows = 0, columns = 0;
    bool isInBoundaries(int x, int y) {
        return (y >= 0 && y < this->columns) && (x >= 0 && x < this->rows);
    }
    int longestIncreasingPath(std::vector<std::vector<int>>& matrix) {
        this->columns = matrix.size();
        this->rows = matrix[0].size();

        std::vector<std::vector<int>> memoization(this->columns, std::vector(this->rows, -1));
        
        for(int i = 0; i < this->rows; i++) {
            for(int j = 0; j < this->columns; j++) {
                if(memoization[i][j] == -1) {
                    memoLongestIncreasingPath(matrix, i, j, memoization);
                }
            }
        }

        int bestValue = 0;
        for(int i = 0; i < this->rows; i++) {
            for(int j = 0; j < this->columns; j++) {
                bestValue = max(bestValue, memoization[i][j]);
            }
        }

        return bestValue;
    }

    int memoLongestIncreasingPath(std::vector<std::vector<int>>& matrix, int x, int y, std::vector<std::vector<int>>& memoization) {
        if(memoization[x][y] != -1) return memoization[x][y];

        int bestValue = 1;

        if(this->isInBoundaries(x, y+1)) {
            if(matrix[x][y+1] > matrix[x][y])
                bestValue = max(bestValue, memoLongestIncreasingPath(matrix, x, y+1, memoization) + 1);
        }

        if(this->isInBoundaries(x, y-1)) {
            if(matrix[x][y-1] > matrix[x][y])
                bestValue = max(bestValue, memoLongestIncreasingPath(matrix, x, y-1, memoization) + 1);
        }

        if(this->isInBoundaries(x+1, y)) {
            if(matrix[x+1][y] > matrix[x][y])
                bestValue = max(bestValue, memoLongestIncreasingPath(matrix, x+1, y, memoization) + 1);
        }

        if(this->isInBoundaries(x-1, y)) {
            if(matrix[x-1][y] > matrix[x][y])
                bestValue = max(bestValue, memoLongestIncreasingPath(matrix, x-1, y, memoization) + 1);
        }
        memoization[x][y] = bestValue;

        return bestValue;
    }
};