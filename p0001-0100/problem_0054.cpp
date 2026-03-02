#include <vector>

// https://leetcode.cn/problems/spiral-matrix/

using namespace std;

class Solution 
{
public:
    //1. 遍历
    //设定四个边界变量top,bottom,left,right，分别代表当前尚未遍历区域的上,下,左,右边界
    //按照"左->右","上->下","右->左","下->上"的固定顺序循环遍历当前层
    //完成当前层的遍历之后，将边界向中心移动一位，++top,--bottom,++left,--right
    //在遍历每一层的后两个方向"右->左"和"下->上"之前，必须进行二次检查
    //如果top==bottom-1或者left==right-1，则表示最后一层已退化成了一维数组(单行或者单列)
    //此时应停止后续方向的遍历，否则会导致已访问过的元素被重复计入结果
    //当左边界超过右边界或者上边界超过下边界时，表示所有层级已处理完，结束遍历，返回结果
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