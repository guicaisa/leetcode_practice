#include <stdio.h>
#include <vector>

/**
 * https://leetcode.com/problems/jump-game-ii/
 */

class Solution {
public:
	// 使用两个索引start和end，确定每次移动阶段时的移动范围
	// 如[2,3,1,1,4]，从头开始，确定第一次的移动后的范围为1-2
	// 下一次遍历时，从索引1开始，找到最大移动的范围，即下一次移动范围的结束位置
	// 下一次移动范围的开始位置为当前移动范围的开始索引+1
	// 直到移动范围超出数组长度，即结束，得到结果
	int Jump(const std::vector<int>& nums) {
		int num = 0;
		int start = 0;
		int end = 0;

		for (; end < nums.size() - 1; ) {
			++num;
			int max_end = end + 1;

			for (int i = start; i <= end; ++i) {
				if (i + nums[i] >= nums.size() - 1) {
					return num;
				}

				if (i + nums[i] > max_end) {
					max_end = i + nums[i];
				}
			}

			start = end + 1;
			end = max_end;
		}

		return num;
	}
};

//int main(int argc, char** argv) {
//	Solution s;
//
//	std::vector<int> si = { 2, 3, 1, 1, 4, 2 };
//
//	int ret = s.Jump(si);
//
//	return 0;
//}