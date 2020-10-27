#include <stdio.h>
#include <vector>
#include <string>

/**
 * https://leetcode.com/problems/wildcard-matching/
 */

class Solution {
public:
	// 这个问题的核心点在于如何处理'*'，已知'*'可以匹配0个或多个字符
	// 从头开始遍历s和p，在遇到'*'的时候，首先假设'*'匹配的是0个字符
	// 保存当前的s的索引位置和'*'的索引位置，p向后移一位
	// 如果没遇到'*'的话，正常检测是否匹配，p[j] == '?' 或者 s[i] == p[j]
	// 匹配的话，同步向后移位，如果不匹配的话，检测之前是否有遇到的'*'
	// 如果没有，直接返回失败，如果有的话，将之前保存的s[start_index_i]定义为与之前的'*'匹配
	// 重置遍历位置为上次记录时的索引，s会根据上次记录的位置自动往后移动
	// p则定位到上一次'*'之后的索引位置，重新开始遍历
	bool IsMatch(const std::string& s, const std::string& p) {
		int i = 0;
		int j = 0;
		int star_index_i = -1;
		int star_index_j = -1;

		for (; i < s.size(); ) {
			if (j < p.size() && p[j] == '*') {
				star_index_i = i;
				star_index_j = j++;
			}
			else if (j < p.size() && (p[j] == '?' || s[i] == p[j])) {
				++i;
				++j;
			}
			else {
				if (star_index_i >= 0) {
					i = ++star_index_i;
					j = star_index_j + 1;
				}
				else {
					return false;
				}
			}
		}

		while (j < p.size() && p[j] == '*') {
			++j;
		}

		return j == p.size();
	}
};

//int main(int argc, char** argv) {
//	Solution s;
//
//	std::string str = "abds";
//	std::string p = "*ac";
//
//	bool ret = s.IsMatch(str, p);
//
//	return 0;
//}