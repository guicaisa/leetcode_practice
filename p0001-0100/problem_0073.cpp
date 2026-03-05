#include <vector>

// https://leetcode.cn/problems/set-matrix-zeroes/

using namespace std;

class Solution 
{
public:
    void setZeroes(vector<vector<int>>& matrix)
    {
        if (matrix.size() == 0)
        {
            return;
        }

        bool first_row_zero = false;
        bool first_col_zero = false;

        for (int i = 0; i < matrix.size(); ++i)
        {
            for (int j = 0; j < matrix[i].size(); ++j)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                    if (j == 0)
                    {
                        first_col_zero = true;
                    }
                    if (i == 0)
                    {
                        first_row_zero = true;
                    }
                }
            }
        }

        for (int i = 1; i < matrix.size(); ++i)
        {
            for (int j = 1; j < matrix[i].size(); ++j)
            {
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                {
                    matrix[i][j] = 0;
                }
            }
        }

        if (matrix[0][0] == 0)
        {
            if (first_row_zero)
            {
                for (int j = 0; j < matrix[0].size(); ++j)
                {
                    matrix[0][j] = 0;
                }
            }
            if (first_col_zero)
            {
                for (int i = 0; i < matrix.size(); ++i)
                {
                    matrix[i][0] = 0;
                }
            }
        }
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
//     //输出：[[1,0,1],[0,0,0],[1,0,1]]
//     vector<vector<int>> matrix = {
//         {1, 1, 1},
//         {1, 0, 1},
//         {1, 1, 1},
//     };
//     s.setZeroes(matrix);

//     //输入：matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
//     //输出：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]
//     matrix = {
//         {0, 1, 2, 0},
//         {3, 4, 5, 2},
//         {1, 3, 1, 5},
//     };
//     s.setZeroes(matrix);

//     //输入：matrix = [[1,2,3,4],[5,0,7,8],[0,10,11,12],[13,14,15,0]]
//     //输出：[[0,0,3,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
//     matrix = {
//         {1,2,3,4},
//         {5,0,7,8},
//         {0,10,11,12},
//         {13,14,15,0},
//     };
//     s.setZeroes(matrix);

//     return 0;
// }