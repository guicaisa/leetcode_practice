#include <stdio.h>
#include <stdlib.h>
#include <vector>

/**
 * https://leetcode.com/problems/sudoku-solver/
 */

class Solution 
{
public:
	/**
	 * 事先将已经存在的值相关的行，列，块的部分进行设置
	 * 然后先找到一个为'.'的索引位置为开始，进行递归操作
	 * 遍历'1' - '9'，判断是否在同行，同列，同块中间存在该值
	 * 如果没有的话，将相关索引位置以及列，行，块中的相关值进行设置
	 * 从下一个是'.'的位置开始继续上述的判断操作
	 * 如果向下展开的递归操作失败，说明当前这个节点的值选择的有问题
	 * 将当前选择的值的相关列，行，块中的值重置，继续遍历'1' - '9'中剩下的可选值
	 * 直到向下展开的递归操作成功，返回结束
	 */
	void SolveSudoku(std::vector<std::vector<char>>& board)
	{
		int vr[9][9] = { 0 };
		int vc[9][9] = { 0 };
		int vs[9][9] = { 0 };

		int x = 0;
		int y = 0;
		int first = 0;

		for (int i = 0; i < board.size(); ++i)
		{
			for (int j = 0; j < board[i].size(); ++j)
			{
				if (board[i][j] != '.')
				{
					int t = board[i][j] - '0' - 1;
					int n = (i / 3 * 3) + (j / 3);

					vr[i][t] = vc[j][t] = vs[n][t] = 1;
				}
				else
				{
					if (first == 0)
					{
						first = 1;
						x = i;
						y = j;
					}
				}
			}
		}

		Recursive(board, vr, vc, vs, x, y);
	}

	bool Recursive(std::vector<std::vector<char> >& board, int(*vr)[9], int(*vc)[9], int(*vs)[9], int x, int y)
	{
		int n = (x / 3 * 3) + (y / 3);

		for (char i = '1'; i <= '9'; ++i)
		{
			int t = i - '0' - 1;
			if (vr[x][t] == 0 && vc[y][t] == 0 && vs[n][t] == 0)
			{
				vr[x][t] = vc[y][t] = vs[n][t] = 1;
				board[x][y] = i;

				int n_x = 0;
				int n_y = 0;
				int first = 0;

				for (int i = y == 8 ? x + 1 : x; i < board.size(); ++i)
				{
					for (int j = i == x ? y + 1 : 0; j < board[i].size(); ++j)
					{
						if (board[i][j] == '.')
						{
							first = 1;
							n_x = i;
							n_y = j;
							break;
						}
					}

					if (first == 1)
					{
						break;
					}
				}

				if (n_x == 0 && n_y == 0)
				{
					return true;
				}

				bool flag = Recursive(board, vr, vc, vs, n_x, n_y);

				if (flag)
				{
					return true;
				}

				vr[x][t] = vc[y][t] = vs[n][t] = 0;
				board[x][y] = '.';
			}
		}

		return false;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::vector<std::vector<char> > board;
//	board.emplace_back(std::vector<char>{'5', '3', '.', '.', '7', '.', '.', '.', '.'});
//	board.emplace_back(std::vector<char>{'6', '.', '.', '1', '9', '5', '.', '.', '.'});
//	board.emplace_back(std::vector<char>{'.', '9', '8', '.', '.', '.', '.', '6', '.'});
//	board.emplace_back(std::vector<char>{'8', '.', '.', '.', '6', '.', '.', '.', '3'});
//	board.emplace_back(std::vector<char>{'4', '.', '.', '8', '.', '3', '.', '.', '1'});
//	board.emplace_back(std::vector<char>{'7', '.', '.', '.', '2', '.', '.', '.', '6'});
//	board.emplace_back(std::vector<char>{'.', '6', '.', '.', '.', '.', '2', '8', '.'});
//	board.emplace_back(std::vector<char>{'.', '.', '.', '4', '1', '9', '.', '.', '5'});
//	board.emplace_back(std::vector<char>{'.', '.', '.', '.', '8', '.', '.', '7', '9'});
//
//	s.SolveSudoku(board);
//
//	for (int i = 0; i < board.size(); ++i)
//	{
//		for (int j = 0; j < board[i].size(); ++j)
//		{
//			printf("%c ", board[i][j]);
//		}
//
//		printf("\n");
//	}
//
//	return 0;
//}