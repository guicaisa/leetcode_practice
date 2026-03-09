#include <vector>

// https://leetcode.cn/problems/game-of-life/

using namespace std;

class Solution 
{
public:
    //1. 遍历
    //遍历过程中，如果直接更改某个元素的值，会破坏后续元素对邻居状态的判定
    //基础方案是引入辅助矩阵存储下一阶段状态，但这会产生额外的空间开销
    //考虑到题目中的进阶要求是不使用额外的内存空间，并且board中的元素都是0和1，所以可以通过位运算将每个元素的最终状态保存在整型的第二位中
    //然后在第二次遍历的时候，根据存储在第二位中的值来判断这个元素的最终结果
    void gameOfLife(vector<vector<int>>& board) 
    {
        if (board.size() == 0)
        {
            return ;
        }

        int m = board.size();
        int n = board[0].size();
        //周围8个元素的索引偏移值
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
                //计算周围8个元素的存活数量
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
                    //当前元素存活，则周围元素存活数量为2或3时才能继续保持存活状态
                    alive = 2 <= around_alive_cnt && around_alive_cnt <= 3;
                }
                else
                {
                    //当前元素死亡，则周围元素存活数量为3时才能变成存活状态
                    alive = around_alive_cnt == 3;
                }
                //记录存活状态在int的第二位中
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
                //根据int的第二位来判断最终存活状态
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