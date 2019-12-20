#include <stdio.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

/**
 * https://leetcode.com/problems/group-anagrams/
 */

class Solution {
public:
	// ×Ö·û´®ÅÅÐòºó×ö¼ü¼´¿É
	std::vector<std::vector<std::string>> GroupAnagrams(const std::vector<std::string>& strs) {
		std::unordered_map<std::string, std::vector<std::string>> ms;
		std::vector<std::vector<std::string>> results;

		for (int i = 0; i < strs.size(); ++i) {
			std::string temp = strs[i];
			std::sort(temp.begin(), temp.end());
			ms[temp].emplace_back(strs[i]);
		}

		for (std::unordered_map<std::string, std::vector<std::string>>::iterator it = ms.begin(); it != ms.end(); ++it) {
			results.emplace_back(it->second);
		}

		return results;
	}
};

//int main(int argc, char** argv) {
//	Solution s;
//
//	std::vector<std::string> strs = { "eat", "tea", "tan", "ate", "nat", "bat" };
//	std::vector<std::vector<std::string>> results = s.GroupAnagrams(strs);
//
//	return 0;
//}
	
