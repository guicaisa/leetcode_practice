#include <stdio.h>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>

// https://leetcode-cn.com/problems/string-to-integer-atoi/

class Automaton
{
public:
	Automaton()
		: positive_(true),
		result_(0),
		state_("start")
	{
		this->table_["start"] = std::vector<std::string>{ "start", "signed", "in_number", "end" };
		this->table_["signed"] = std::vector<std::string>{ "end", "end", "in_number", "end" };
		this->table_["in_number"] = std::vector<std::string>{ "end", "end", "in_number", "end" };
		this->table_["end"] = std::vector<std::string>{ "end", "end", "end", "end" };
	}

	void Get(const char c)
	{
		this->state_ = this->table_[this->state_][this->GetCol(c)];
		if (this->state_ == "in_number")
		{
			int step = c - '0';

			if (this->result_ > INT_MAX / 10)
			{
				this->result_ = INT_MAX;
				if (!this->positive_)
				{
					this->result_ = INT_MIN;
					this->positive_ = true;
				}
				this->state_ = "end";
			}  
			else if (this->result_ == INT_MAX / 10 && step > 7)
			{
				this->result_ = INT_MAX;
				if (!this->positive_ && step >= 8)
				{
					this->result_ = INT_MIN;
					this->positive_ = true;
					this->state_ = "end";
				}
			}
			else
			{
				this->result_ = this->result_ * 10 + step;
			}
		}
		else if (this->state_ == "signed")
		{
			this->positive_ = c == '+';
		}
	}

private:
	int GetCol(const char c)
	{
		if (isspace(c))
		{
			return 0;
		}

		if (c == '+' || c == '-')
		{
			return 1;
		}

		if (isdigit(c))
		{
			return 2;
		}

		return 3;
	}

public:
	bool positive_;

	int result_;

	std::string state_;

private:
	std::unordered_map<std::string, std::vector<std::string> > table_;
};

class Solution
{
public:
	// 遍历字符串，以遇到第一个数字字符或者'+'或者'-'为开端，之后如果遇到任何非数字字符，直接break
	// 如果在这之前遇到其他无意义的字符，则直接返回0，最终获得一个数字数组，保存每一位的数字
	// 遍历数组，每次进位，计算最终结果，在每次当前进位计算之前判断越界的可能
	int MyAtoi(const std::string& str) 
	{
		int character_flag = 0;
		bool positive = true;
		std::vector<int> digit_vec;

		for (size_t i = 0; i < str.size(); ++i)
		{
			if (character_flag == 0)
			{
				if (str[i] != ' ' && str[i] != '-' && str[i] != '+' && !isdigit(str[i]))
				{
					return 0;
				}

				if (str[i] != ' ')
				{
					character_flag = 1;
				}

				if (str[i] == '-')
				{
					positive = false;
				}
				else if (isdigit(str[i]))
				{
					digit_vec.emplace_back((str[i] - '0') * (positive ? 1 : -1));
				}
			}
			else
			{
				if (!isdigit(str[i]))
				{
					break;
				}

				digit_vec.emplace_back((str[i] - '0') * (positive ? 1 : -1));
			}
		}

		int result = 0;
		for (size_t i = 0; i < digit_vec.size(); ++i)
		{
			if (result > INT_MAX / 10 || (result == INT_MAX / 10 && digit_vec[i] > 7))
			{
				return INT_MAX;
			}
			
			if (result < INT_MIN / 10 || (result == INT_MIN / 10 && digit_vec[i] < -8))
			{
				return INT_MIN;
			}

			result = result * 10 + digit_vec[i];
		}

		return result;
	}

	// 不使用临时数组，优化代码结构
	int MyAtoiBetter(const std::string& str)
	{
		bool positive = true;
		size_t i = 0;
		int result = 0;

		while (i < str.size() && str[i] == ' ')
		{
			++i;
		}

		if (i < str.size() && (str[i] == '+' || str[i] == '-'))
		{
				positive = str[i] == '+';
				++i;
		}

		while (i < str.size() && isdigit(str[i]))
		{
			int step = (str[i] - '0') * (positive ? 1 : -1);

			if (result > INT_MAX / 10 || (result == INT_MAX / 10 && step > 7))
			{
				return INT_MAX;
			}

			if (result < INT_MIN / 10 || (result == INT_MIN / 10 && step < -8))
			{
				return INT_MIN;
			}

			result = result * 10 + step;
			++i;
		}

		return result;
	}

	// 使用自动状态机
	// 首先我们需要一个表
	//				| ' '	| +/-	 | number	 | other
	// -------------|-------|--------|-----------|--------
	// start		| start	| signed | in_number | end
	// -------------|-------|--------|-----------|--------
	// signed		| end	| end	 | in_number | end
	// -------------|-------|--------|-----------|--------
	// in_number	| end	| end	 | in_number | end
	// -------------|-------|--------|-----------|--------
	// end			| end	| end	 | end		 | end
	// ---------------------------------------------------
	// 第一列表示当前的状态是什么，第一行表示当前遇到的字符是什么情况
	// 根据行和列得到的结果就是当前状态下，遇到了什么类型的字符，之后需要转移的状态
	// 这个表我们使用一个嵌套的map表示，这个算法非常简单
	// 直接遍历字符串，把每个字符传入状态机，状态机会自己改变状态
	// 决定需要进行的操作，遍历完字符串之后，就可以直接得到结果
	int MyAtoiAutomaton(const std::string& str)
	{
		Automaton a;

		for (size_t i = 0; i < str.size(); ++i)
		{
			a.Get(str[i]);
			if (a.state_ == "end")
			{
				break;
			}
		}

		return a.result_ * (a.positive_ ? 1 : -1);
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//	std::string str = "42";
//
//	int ret = s.MyAtoiBetter(str);
//
//
//	return 0;
//}