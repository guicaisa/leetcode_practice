#include <vector>

// https://leetcode.cn/problems/spiral-matrix/

using namespace std;

class Solution 
{
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) 
    {
        vector<int> results;
        int top = 0;
        int bottom = matrix.size();
        int left = 0;
        int right = matrix[0].size();

        while (1)
        {
            for (int i = left; i < right; ++i)
            {
                results.push_back(matrix[top][i]);
            }
            for (int i = top+1; i < bottom; ++i)
            {
                results.push_back(matrix[i][right-1]);
            }
            if (left < right-1 && top < bottom-1) 
            {
                for (int i = right - 2; i >= left+1; --i)
                {
                    results.push_back(matrix[bottom-1][i]);
                }
                for (int i = bottom - 1; i >= top + 1; --i)
                {
                    results.push_back(matrix[i][left]);
                }
            }
          
            if (++top >= --bottom)
            {
                break;
            }
            if (++left >= --right)
            {
                break;
            }
        }

        return results;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
//     //输出：[1,2,3,6,9,8,7,4,5]
//     vector<vector<int>> matrix = {
//         {1, 2, 3},
//         {4, 5, 6},
//         {7, 8, 9}
//     };
//     vector<int> results = s.spiralOrder(matrix);

//     //输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
//     //输出：[1,2,3,4,8,12,11,10,9,5,6,7]
//     matrix = {
//         {1, 2, 3, 4},
//         {5, 6, 7, 8},
//         {9, 10, 11, 12},
//     };
//     results = s.spiralOrder(matrix);

//     matrix = {
//         {3},
//         {2},
//     };
//     results = s.spiralOrder(matrix);

//     return 0;
// }