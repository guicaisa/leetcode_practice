#include <vector>

// https://leetcode.cn/problems/game-of-life/

using namespace std;

class Solution 
{
public:
    //1. 遍历
    //遍历过程中，如果直接更改某个元素的值，会导致后续与之关联的元素的状态判断有误
    //所以最简单的方法应该是第一次遍历，确定每个元素的最终状态，保存在额外的数组中，然后第二次遍历的时候将额外数组中的结果覆盖到原数组中
    //考虑到题目中的进阶要求是不使用额外的内存空间，并且board中的元素都是0和1，所以可以通过位运算将每个元素的最终状态保存在整型数字的第二位中
    //然后在第二次遍历的时候，根据实现存储在第二位中的值来判断这个元素的最终结果，并进行赋值
    void gameOfLife(vector<vector<int>>& board) 
    {
        if (board.size() == 0)
        {
            return ;
        }

        int m = board.size();
        int n = board[0].size();
        vector<vector<int>> offsets = {
            {
                {-1, -1},
                {-1, 0},
                {-1, 1},
                {0, -1},
                {0, 1},
                {1, -1},
                {1, 0},
                {1, 1},
            }
        };
        for (int i = 0; i < board.size(); ++i)
        {
            for (int j = 0; j < board[i].size(); ++j)
            {
                int around_alive_cnt = 0;
                for (int k = 0; k < offsets.size(); ++k)
                {
                    int temp_i = i + offsets[k][0];
                    int temp_j = j + offsets[k][1];
                    if (0 <= temp_i && temp_i < m && 0 <= temp_j && temp_j < n)
                    {
                        if (board[temp_i][temp_j] & 1)
                        {
                            ++around_alive_cnt;
                        }
                    }
                }

                bool alive = board[i][j] & 1;
                if (alive)
                {
                    alive = 2 <= around_alive_cnt && around_alive_cnt <= 3;
                }
                else
                {
                    alive = around_alive_cnt == 3;
                }
                if (alive)
                {
                    board[i][j] |= 2;
                }
            }
        }

        for (int i = 0; i < board.size(); ++i)
        {
            for (int j = 0; j < board[i].size(); ++j)
            {
                board[i][j] = (board[i][j] & 2) ? 1 : 0;
            }
        }
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入：board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
//     //输出：[[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
//     vector<vector<int>> board = vector<vector<int>>{
//         {0,1,0},
//         {0,0,1},
//         {1,1,1},
//         {0,0,0},
//     };
//     s.gameOfLife(board);

//     //输入：board = [[1,1],[1,0]]
//     //输出：[[1,1],[1,1]]
//     board = vector<vector<int>>{
//         {1,1},
//         {1,0},
//     };
//     s.gameOfLife(board);

//     return 0;
// }