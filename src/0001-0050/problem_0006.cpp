#include <stdio.h>
#include <string>
#include <vector>

// https://leetcode-cn.com/problems/zigzag-conversion/

class Solution
{
public:
	// 这个问题其实就是把字符串排成Z字形状，不过是反过来的
	// 行数就是z字边的长度，以字符串中字符索引代替字符举例如下，假设行数为5
	// 
	// 0       8           16          24
	// 1     7 9        15 17       23
	// 2   6   10    14    18    22
	// 3 5     11 13       19 21 
	// 4       12          20
	// 
	// 观察后得到规律，竖着的边是从上往下，然后再一条斜线到达第二条边的上方
	// 即每次从字符串中先获取num_rows个字符，再获取num_rows - 2个字符，依此往复，直到遍历完字符串
	// 我们可以使用一个数组，保存每行的字符串，在遍历字符串的时候，模拟画Z字的过程
	// 使用一个变量current_row在num_rows之间来回摆动，并在达到顶部和尾部的时候反弹回去
	// 从而得到每一行的字符，最后再拼接起来就是结果
	std::string Convert(const std::string& s, const int num_rows) 
	{
		if (num_rows <= 1)
		{
			return s;
		}

		int current_row = 0;
		bool direction_down = false;
		std::vector<std::string> result_vec(num_rows);

		for (size_t i = 0; i < s.size(); ++i)
		{
			result_vec[current_row] += s[i];
			if (current_row == 0 || current_row == num_rows - 1)
			{
				direction_down = !direction_down;
			}

			current_row = current_row + (direction_down ? 1 : -1);
		}

		std::string result;
		for (size_t i = 0; i < result_vec.size(); ++i)
		{
			result += result_vec[i];
		}

		return result;
	}

	// 使用字符串中的索引代替字符显示，继续观察这个图案，发现规律
	// 每条竖线的每个索引相差得值为 2 * num_rows - 2，假设这个固定间隔为interval
	// 所以对于每一行的竖线上的值，直接使用i + j * interval就可以得到其索引
	// i是[0, num_rows)，j是从0不断自增1的变量，自增结束条件是是否超过了字符串的长度
	// 对于处于中间位置行上的斜线上的索引值，可以通过其后面那根竖线上的第一行的值推算出来
	// (j + 1) * interval - i
	// 这个表里填的都是字符的索引
	// 0       8           16          24
	// 1     7 9        15 17       23 25
	// 2   6   10    14    18    22    26 
	// 3 5     11 13       19 21       27
	// 4       12          20          28
	std::string Convert2(const std::string& s, const int num_rows)
	{
		if (num_rows <= 1)
		{
			return s;
		}

		int interval = 2 * num_rows - 2;
		std::string result;

		for (int i = 0; i < num_rows; ++i)
		{
			for (int j = 0; (i + j * interval) < s.size(); ++j)
			{
				result = result + s[i + j * interval];
				if (i != 0 && i != num_rows - 1) 
				{
					// (j + 1) * interval 代表后面的完整一列的第一行的字符
					// 完整的两列之间的数字是斜着顺序排列的，上面提到的 4 - 5 - 6 - 7 - 8
					// 所以斜着的字符的索引是由其后面的完整一列的第一行字符的索引减去其所在的行数来决定的
					// i代表行数
					int inner_index = (j + 1) * interval - i;
					if (inner_index >= 0 && inner_index < s.size())
					{
						result = result + s[inner_index];
					}
				}
			}
		}

		return result;
	}

	// 低效解法，不建议使用
	std::string Convert3(const std::string& s, const int num_rows)
	{
		if (num_rows <= 1)
		{
			return s;
		}

		int fill = num_rows - 2;
		int size = s.size();
		int group_size = num_rows + fill;
		int group_num = size / (group_size);
		int group_col_wide = 1 + fill;
		int rest_num = size % (group_size);
		int fill_col = 1 + (rest_num > num_rows ?  rest_num % num_rows : 0);

 		std::vector<char> temp(group_col_wide * group_num + fill_col, '#');
		std::vector<std::vector<char>> vvi(num_rows, temp);

		int index = 0;
		for (int i = 0; i < group_num; ++i)
		{
			int col = i * group_col_wide;
			for (int j = 0; j < num_rows; ++j)
			{
				vvi[j][col] = s[index++];
			}

			for (int j = 0; j < fill; ++j)
			{
				vvi[num_rows - 2 - j][col + 1 + j] = s[index++];
			}
		}

		if (rest_num > 0)
		{
			int col = group_num * group_col_wide;
			for (int i = 0; i < rest_num && i < num_rows; ++i)
			{
				vvi[i][col] = s[index++];
			}
			
			if (rest_num > num_rows)
			{
				for (int i = 0; i < rest_num - num_rows; ++i)
				{
					vvi[num_rows - 2 - i][col + i + 1] = s[index++];
				}
			}
		}

		std::string new_str;
		for (int i = 0; i < vvi.size(); ++i)
		{
			for (int j = 0; j < vvi[i].size(); ++j)
			{
				if (vvi[i][j] != '#')
				{
					new_str += vvi[i][j];
				}
			}
		}

		return new_str;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//	std::string str = "ABCDE";
//
//	std::string result = s.Convert3(str, 4);
//
//
//
//	return 0;
//}