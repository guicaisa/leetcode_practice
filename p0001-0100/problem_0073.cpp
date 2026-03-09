#include <vector>

// https://leetcode.cn/problems/set-matrix-zeroes/

using namespace std;

class Solution 
{
public:
    //1. 遍历
    //最简单的方式是使用额外的空间，在遍历的过程中，发现值为0的元素，就将其所在行和列标记为0，然后在第二次遍历的时候将相应行列上的元素设置为0
    //为实现进阶要求的O(1)额外空间复杂度，可利用矩阵的第一行和第一列充当临时标记位，记录对应行列是否需要置零
    //由于matrix[0][0]被第一行和第一列共用，无法同时独立表达两者的初始状态，状态复用导致的冲突会让结果出现错误，所以需要引入额外2个bool值记录首行和首列的状态
    //遍历矩阵，如果matrix[i][j]==0，则将matrix[i][0]和matrix[0][j]置为0，如果该元素处于首行或者首列，则需要将对应的bool值置为true
    //首次遍历完成标记之后，二次遍历只处理非首行和首列的元素，根据标记将对应的值设置为0，然后根据2个bool值单独处理首行和首列
    void setZeroes(vector<vector<int>>& matrix)
    {
        if (matrix.size() == 0)
        {
            return;
        }

        bool first_row_zero = false; //首行是否有0
        bool first_col_zero = false; //首列是否有0

        for (int i = 0; i < matrix.size(); ++i)
        {
            for (int j = 0; j < matrix[i].size(); ++j)
            {
                //该元素为0，将该元素的所处行/列的首个元素置为0
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
    
        //只处理非首行/首列
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

        //根据2个bool值，处理首行/首列
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