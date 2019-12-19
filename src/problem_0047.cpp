#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>

/**
 * https://leetcode.com/problems/permutations-ii/
 */

class Solution {
public:
	// 递归回溯，遍历的时候首先注意避免重复运算相同的数字，使用这个条件 i + 1 == nums.size() || nums[i + 1] != n
	// 贯穿所有递归中加入一个nums_map，用于保存每个数字使用的次数，确保相同的数字出现的次数正确
	// 在遍历的同时使用条件temp_map[n] > nums_map[n] || nums_map[n] == 0，判断当前递归中该数字出现的次数是否超过了
	// 历史递归层次中该数字出现的次数，与第一个条件并列使用进行判断，该数字是否可以使用
	std::vector<std::vector<int>> PermuteUnique(std::vector<int>& nums) {
		std::map<int, int> nums_map;
		std::vector<int> temp_result;
		std::vector<std::vector<int>> results;

		sort(nums.begin(), nums.end());

		Function(nums, nums_map, temp_result, results);

		return results;
	}

	void Function(const std::vector<int>& nums, std::map<int, int>& nums_map, std::vector<int>& temp_result, std::vector<std::vector<int>>& results) {
		std::map<int, int> temp_map;

		for (int i = 0; i < nums.size(); ++i) {
			int n = nums[i];
			++temp_map[n];

			if ((i + 1 == nums.size() || nums[i + 1] != n) && (temp_map[n] > nums_map[n] || nums_map[n] == 0)) {
				temp_result.emplace_back(n);
				if (temp_result.size() == nums.size()) {
					results.emplace_back(temp_result);
				}
				else {
					++nums_map[n];
					Function(nums, nums_map, temp_result, results);
					--nums_map[n];
				}

				temp_result.pop_back();
			}
		}
	}

	std::vector<std::vector<int>> PermuteUnique2(std::vector<int>& nums) {
		std::vector<std::vector<int>> results;

		sort(nums.begin(), nums.end());

		Recursive(nums, 0, nums.size(), results);

		return results;
	}

	void Recursive(std::vector<int> nums, int start, int end, std::vector<std::vector<int>>& results) {
		if (start == end - 1) {
			results.emplace_back(nums);
			return;
		}

		for (int i = start; i < end; ++i) {
			if (i != start && nums[i] == nums[start]) {
				continue;
			}

			std::swap(nums[start], nums[i]);

			Recursive(nums, start + 1, end, results);
		}
	}
};

//int main(int argc, char** argv) {
//	Solution s;
//
//	std::vector<int> si = {1, 1, 1, 2};
//
//	std::vector<std::vector<int>> results = s.PermuteUnique2(si);
//
//	return 0;
//}