#include <stdio.h>
#include <vector>
#include <algorithm>

/**
 * https://leetcode.com/problems/rotate-image/
 */

class Solution {
public:
	// 根据转换公式，new_matrix[j][n - i - 1] = matrix[i][j]
	// 先反向排列一下matrix，得到 matrix[n - i - 1][j] = matrix[i][j]
	// 推导公式，new_matrix[j][n - i - 1] = matrix[j][i]
	// 置换matrix[i][j] 和 matrix[j][i]即可
	void Rotate(std::vector<std::vector<int>>& matrix) {
		std::reverse(matrix.begin(), matrix.end());

		for (int i = 0; i < matrix.size(); ++i) {
			for (int j = i + 1; j < matrix[i].size(); ++j) {
				std::swap(matrix[i][j], matrix[j][i]);
			}
		}
	}
};

//int main(int argc, char** argv) {
//	Solution s;
//
//	std::vector<std::vector<int>> vvi;
//
//	vvi.emplace_back(std::vector<int>{1, 2, 3});
//	vvi.emplace_back(std::vector<int>{4, 5, 6});
//	vvi.emplace_back(std::vector<int>{7, 8, 9});
//
//	s.Rotate(vvi);
//
//	return 0;
//}