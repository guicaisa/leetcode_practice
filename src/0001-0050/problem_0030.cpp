#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * https://leetcode.com/problems/substring-with-concatenation-of-all-words/
 */

class Solution
{
public:
	std::vector<int> FindSubString(const std::string& s, const std::vector<std::string>& words) 
	{
		std::vector<int> vi;
		std::unordered_map<std::string, int> sm;

		if (s == "" || words.size() == 0)
		{
			return vi;
		}

		for (int i = 0; i < words.size(); ++i)
		{
			++sm[words[i]];
		}

		int p1 = 0;
		int p2 = 0;
		int len = words[0].size();
		int count = words.size();
		int n = s.size();

		for (; p1 < n - (count * len) + 1; ++p1)
		{
			std::unordered_map<std::string, int> tsm;

			p2 = 0;
			for (; p2 < count; ++p2)
			{
				std::string ts = s.substr(p1 + (p2 * len), len);
				if (sm.find(ts) != sm.end())
				{
					++tsm[ts];
					if (tsm[ts] > sm[ts])
					{
						break;
					}
				} 
				else
				{
					break;
				}
			}

			if (p2 == count)
			{
				vi.push_back(p1);
			}
		}

		return vi;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//
//	std::string str = "wordgoodgoodgoodbestword";
//	std::vector<std::string> vs = { "word", "good", "best", "word" };
//
//	std::vector<int> vi = s.FindSubString(str, vs);
//
//	return 0;
//}


