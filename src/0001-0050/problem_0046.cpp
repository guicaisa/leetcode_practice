#include <stdio.h>
#include <vector>
#include <set>

/**
 * https://leetcode.com/problems/permutations/
 */

class Solution {
public:
	// 递归回溯，用set保存使用过的数字防止重复
	std::vector<std::vector<int>> Permute(const std::vector<int>& nums) {
		std::set<int> nums_set;
		std::vector<int> temp_result;
		std::vector<std::vector<int>> results;

		Function(nums, nums_set, temp_result, results);

		return results;
	}

	void Function(const std::vector<int>& nums, std::set<int>& nums_set, std::vector<int>& temp_result, std::vector<std::vector<int>>& results) {
		for (int i = 0; i < nums.size(); ++i) {
			if (nums_set.find(nums[i]) == nums_set.end()) {
				temp_result.emplace_back(nums[i]);
				if (temp_result.size() == nums.size()) {
					results.emplace_back(temp_result);
				}
				else {
					nums_set.insert(nums[i]);
					Function(nums, nums_set, temp_result, results);
					nums_set.erase(nums[i]);
				}

				temp_result.pop_back();
			}
		}
	}
};

//int main(int argc, char** argv) {
//	Solution s;
//
//	std::vector<int> si = { 1, 2, 3 };
//
//	std::vector<std::vector<int>> results = s.Permute(si);
//
//	return 0;
//}