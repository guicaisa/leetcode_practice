#include <stdio.h>
#include <string>
#include <unordered_map>

/**
 * https://leetcode.com/problems/longest-palindromic-substring/
 */

class Solution
{
public:
	/**
	 * 暴力求解，遍历每种字串，判断是否为回文，再判断长度
	 */
	std::string LongestPalindrome(const std::string& s) 
	{
		if (s == "")
		{
			return "";
		}

		size_t size = s.size();
		size_t left_index = 0;
		int length = 0;
		int max_length = 1;

		for (size_t i = 0; i < size - 1; ++i)
		{
			for (size_t j = size - 1; j >= i + 1; --j)
			{
				length = j - i + 1;
				if (length <= max_length)
				{
					break;
				}

				if (this->IsPalindrome(s, i, j))
				{
					max_length = length;
					left_index = i;
				}
			}
		}
		
		return s.substr(left_index, max_length);
	}

	/**
	 * 使用动态规划的方式，减少判断字串是否是回文的时间
	 * 通过公式:
	 * dp[i, i] = true 
	 * dp[i, i + 1] == s[i] == s[i + 1] 
	 * dp[i, j] == dp[i + 1, j - 1] && s[i] == s[j]
	 * 先处理自己本身以及相邻位置的结果，再从尾部向前遍历(前面的子串依赖后面子串的结果)，得到所有子串是否为回文的结果
	 */
	std::string LongestPalindromeBetter(const std::string& s)
	{
		if (s == "")
		{
			return "";
		}

		size_t size = s.size();
		size_t left_index = 0;
		int length = 0;
		int max_length = 1;

		std::vector<bool> temp(size, false);
		std::vector<std::vector<bool> > dp_result(size, temp);

		for (size_t i = 0; i < size; ++i)
		{
			dp_result[i][i] = true;
			if (i == size - 1)
			{
				break;
			}

			dp_result[i][i + 1] = (s[i] == s[i + 1]);
		}

		if (size >= 3)
		{
			for (int i = size - 3; i >= 0; --i)
			{
				for (int j = i + 2; j < size; ++j)
				{
					dp_result[i][j] = (s[i] == s[j] && dp_result[i + 1][j - 1] == 1);
				}
			}
		}

		for (size_t i = 0; i < size - 1; ++i)
		{
			for (size_t j = i + 1; j < size; ++j)
			{
				length = j - i + 1;
				if (length > max_length && dp_result[i][j])
				{
					max_length = length;
					left_index = i;
				}
			}
		}

		return s.substr(left_index, max_length);
	}

	/**
	 * 以每个字符为中心，向两边扩张，找到最长的回文子串
	 * 但是需要区分回文的奇偶，所以一个字符要做两次扩张
	 */
	std::string LongestPalindromeBetter2(const std::string& s)
	{
		if (s == "")
		{
			return "";
		}

		size_t size = s.size();
		size_t left_index = 0;
		int max_length = 1;

		for (size_t i = 0; i < size; ++i)
		{
			size_t temp_left_1 = 0;
			size_t temp_left_2 = 0;
			int length_1 = PalindromeLength(s, i, i, temp_left_1);
			int length_2 = PalindromeLength(s, i, i + 1, temp_left_2);

			if (length_1 > length_2 && length_1 > max_length)
			{
				max_length = length_1;
				left_index = temp_left_1;
			}
			else if (length_2 >= length_1 && length_2 > max_length)
			{
				max_length = length_2;
				left_index = temp_left_2;
			}
		}

		return s.substr(left_index, max_length);
	}

	/**
	 * 中心扩展的另一种更高效的方式
	 * 找到重复的字符的头尾，略过中间的重复部分，再扩展
	 * 不用区分奇偶，只用同一种方式就可以统一处理
	 */
	std::string LongestPalindromeBetter3(const std::string& s)
	{
		if (s == "")
		{
			return s;
		}

		size_t size = s.size();
		size_t left_index = 0;
		int max_length = 1;

		for (size_t i = 0; i < size; )
		{
			if (size - i - 1 <= max_length / 2)
			{
				break;
			}

			size_t begin = i;
			size_t end = i;

			while (end < size - 1 && s[begin] == s[end + 1])
			{
				++end;
			}

			i = end + 1;

			while (begin > 0 && end < size && s[begin - 1] == s[end + 1])
			{
				--begin;
				++end;
			}

			if (end - begin + 1 > max_length)
			{
				max_length = end - begin + 1;
				left_index = begin;
			}
		}

		return s.substr(left_index, max_length);
	}

	/**
	 * Manacher算法
	 * 首先给字符串中每个字符的间隔添加一个额外字符，假定为"#"
	 * 这样可以使回文子串无论是奇数长度，还是偶数长度，都变为奇数长度，方便统一处理
	 * 之后首尾分别加上不同的2个任意字符，假定为"$"和"^"，为了不用特意处理边界问题
	 * 简单处理之后就构成了一个新字符串str
	 *
	 * 这个算法的核心思想是保持一个与新字符串str长度相同的数组radius
	 * 数组中radius[i]的值表示以新字符串str[i]所对应的字符为中心构成的回文的最大半径
	 * 如"abc"中b对应的值就是0，"aba"中b对应的就是1，通过遍历一次字符串，求出每个位置上的字符对应的radius数组中的值
	 * 然后只要找出最大的值对应的那个字符，就能找出最长的回文子串
	 * 这个算法还是需要用到中心扩展，但是并不是每个字符都需要中心扩展
	 * 根据回文的对称性规则，我们可以简化很多字符的中心扩展计算过程，可以很轻易的得到其对应的radius[i]的半径值
	 *
	 * 举例：
	 * i: 0 1 2 3 4 5 6 7 8 9 10
	 * s: # a # b # a # b # a #
	 * r: 0 1 0 3 0 5
	 * 第一行是索引，第二行是新字符串中的字符，第三行是对应的半径值的数组
	 * 肉眼可见，中间的a构成的回文是最长的，假设此时我们已经遍历完这个a，得到当前的中心点为索引为5的'a'，并且扩展的右边界为索引为10的'#'
	 * 此时需要求索引6的'#'对应的半径值，由于这个索引6处于从中心'a'扩展到右边界'#'的中间 5 < 6 < 10，通过公式我们可以获得它的镜像索引
	 * mirror = 2 * center - i = 2 * 5 - 6 = 4，索引4处的'#'是索引6在以索引5的'a'的为中心的回文中的镜像，索引我们可以得到radius[6] = radius[4]
	 * 根据已有的值求出后面的值，也算是一种动态规划的方式，但是也有特例
	 * 
	 * 举例：
	 * i: 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20
	 * s: #  b  #  a  #  b  #  c  #  b  #  a  #  b  #  c  #  b  #  a  #  c  #  c  #  b  #  a  # 
	 * r: 0  1  0  3  0  1  0  7  0  1  0  9  0  1  0 
	 * 假设当前的字符串正在求radius[15]的值，现在可知的当前center是索引11处的'a'，半径为9，右边界是索引为20的'#'
	 * 此时的mirror索引为 2 * 11 - 15 = 7，即索引为7的'c'，但是此处不可以直接镜像赋值，因为虽然str[7]为当前回文中的值，但是注意其radius[7]为7
	 * 即以该s[7]为中心的回文半径为7，即s[7]构成的回文的左边一部分在当前大回文的外部，再观察需要求值的索引15与右边界20相差为5
	 * 但是对应半径的值为7，如果以7的半径值进行扩展就会超出大回文的边界，在回文外部无法保证对称性，所以radius[15]的最小值为5(保证在大回文内部)
	 * 然后以此为基础，在以str[15]为新的中心的情况下，进行中心扩展，更新radius[15]的值，得到正确的回文半径
	 * 仔细观察也能发现，索引11的'a'也在索引7的'c'的回文半径内，但是由于镜像str[3]对应的radius[3]的值是3，11 + 3 >= 14到达了以str[7]为中心的右边界
	 * 所以需要以半径为3开始，进行中心扩展，获得正确的回文半径，对于i大于右边界的情况，也是需要单独中心扩展
	 *
	 * 首先确定几个变量，当前回文中心点索引center，右边界right
	 * 归纳一下三种情况
	 * 1. i > right，以i为中心进行扩展，获得回文半径，更新center，right
	 * 2. i <= right，根据公式mirror = 2 * center - i，如果radius[mirror] < right - i，radius[i] = radius[mirror]
	 * 3. i <= right，根据公式mirror = 2 * center - i，如果radius[mirror] >= right - i, radius[i] = right - i，再此基础上进行中心扩展
	 * 更新center，right
	 */
	std::string LongestPalindromeBetter4(const std::string& s)
	{
		if (s == "")
		{
			return s;
		}

		size_t size = s.size();
		std::string new_str;
		for (size_t i = 0; i < size; ++i)
		{
			new_str = new_str + s[i] + "#";
		}
		new_str = "&#" + new_str + "^";

		size = new_str.size();
		std::vector<int> radius(size, 0);
		int center = 0;
		int right = 0;
		int mirror = 0;

		for (size_t i = 1; i < size - 1; ++i)
		{
			if (right >= i)
			{
				mirror = 2 * center - i;
				if (radius[mirror] < right - i)
				{
					radius[i] = radius[mirror];
				}
				else
				{
					radius[i] = right - i;
					while (new_str[i - radius[i] - 1] == new_str[i + radius[i] + 1])
					{
						++radius[i];
					}

					center = i;
					right = i + radius[i];
				}
			}
			else
			{
				while (new_str[i - radius[i] - 1] == new_str[i + radius[i] + 1])
				{
					++radius[i];
				}

				center = i;
				right = i + radius[i];
			}
		}

		int max_length = 0;
		size_t left_index = 0;
		for (size_t i = 0; i < size; ++i)
		{
			if (radius[i] > max_length)
			{
				max_length = radius[i];
				left_index = i;
			}
		}

		return s.substr((left_index - max_length - 1) / 2, max_length);
	}

private:
	bool IsPalindrome(const std::string& s, const size_t begin, const size_t end)
	{
		size_t mid = (begin + end) / 2;
		size_t base = begin + end;

		for (size_t i = begin; i <= mid; ++i)
		{
			if (s[i] != s[base - i])
			{
				return false;
			}
		}

		return true;
	}

	int PalindromeLength(const std::string& s, size_t begin, size_t end, size_t& left)
	{
		int length = 0;

		while (s[begin] == s[end])
		{
			length = end - begin + 1;
			left = begin;
			if (begin > 0 && end < s.size())
			{
				--begin;
				++end;
			}
			else
			{
				break;
			}
		}

		return length;
	}
};

int main(int argc, char** argv)
{
	Solution s;

	std::string str = "ababa";

	std::string ret = s.LongestPalindromeBetter4(str);


	return 0;
}