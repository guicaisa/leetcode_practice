#include <stdio.h>
#include <string>
#include <unordered_map>
#include <unordered_set>

class Solution
{
public:
	int LengthOfLongestSubstring(const std::string& s)
	{
		if (s == "")
		{
			return 0;
		}

		std::unordered_map<char, int> char_to_index;
		int max_length = 1;

		for (size_t i = 0; i < s.size(); )
		{
			if (char_to_index.find(s[i]) == char_to_index.end())
			{
				char_to_index[s[i]] = i;
				++i;

				if (i == s.size())
				{
					max_length = char_to_index.size() > max_length ? char_to_index.size() : max_length;
				}
			}
			else
			{
				if (char_to_index.size() > 1)
				{
					max_length = char_to_index.size() > max_length ? char_to_index.size() : max_length;
					i = char_to_index[s[i]] + 1;
					char_to_index.clear();
				}
				else
				{
					char_to_index[s[i]] = i;
					++i;
				}
			}
		}

		return max_length;
	}

	int LengthOfLongestSubstringBetter(const std::string& s)
	{
		std::unordered_set<int> char_set;
		int max_length = 0;

		for (size_t i = 0, j = 0; i < s.size() && j < s.size(); )
		{
			if (char_set.find(s[j]) == char_set.end())
			{
				char_set.insert(s[j++]);
				max_length = char_set.size() > max_length ? char_set.size() : max_length;
			}
			else
			{
				char_set.erase(s[i++]);
			}
		}

		return max_length;
	}

	int LengthOfLongestSubstringBetter2(const std::string& s)
	{
		std::unordered_map<char, int> char_to_index;
		int max_length = 0;

		for (size_t i = 0, j = 0; i < s.size() && j < s.size(); ++j)
		{
			if (char_to_index.find(s[j]) != char_to_index.end())
			{
				i = char_to_index[s[j]] + 1;
				char_to_index[s[j]] = j;
			}
			else
			{
				char_to_index[s[j]] = j;
			}

			max_length = j - i + 1 > max_length ? j - i + 1 : max_length;
		}

		return max_length;
	}
	
};

int main(int argc, char** argv)
{
	Solution s;
	std::string str = "abba";

	int len = s.LengthOfLongestSubstringBetter2(str);


	return 0;
}