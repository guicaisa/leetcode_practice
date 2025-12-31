#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution 
{
public:
    Solution()
    {
        this->num_to_chars_['2'] = vector<char>{'a', 'b', 'c'};
        this->num_to_chars_['3'] = vector<char>{'d', 'e', 'f'};
        this->num_to_chars_['4'] = vector<char>{'g', 'h', 'i'};
        this->num_to_chars_['5'] = vector<char>{'j', 'k', 'l'};
        this->num_to_chars_['6'] = vector<char>{'m', 'n', 'o'};
        this->num_to_chars_['7'] = vector<char>{'p', 'q', 'r', 's'};
        this->num_to_chars_['8'] = vector<char>{'t', 'u', 'v'};
        this->num_to_chars_['9'] = vector<char>{'w', 'x', 'y', 'z'};
    }

    vector<string> letterCombinations(string digits) 
    {
        if (digits.size() == 0)
        {
            return vector<string>();
        }

        string str(digits.size(), 0);
        vector<string> results;
        this->recursive(digits, 0, str, results);

        return results;
    }

    void recursive(const string& digits, int index, string& str, vector<string>& results)
    {
        char ch = digits[index];
        vector<char> chars = this->num_to_chars_[ch];
        for (int i = 0; i < chars.size(); ++i)
        {
            str[index] = chars[i];
            if (index == digits.size() - 1)
            {
                results.push_back(str);
            }
            else 
            {
                this->recursive(digits, index+1, str, results);
            }
        }
    }

private:
    unordered_map<char, vector<char>> num_to_chars_;
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: digits = "23"
//     //输出: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
//     string digits = "23";
//     vector<string> results = s.letterCombinations(digits);

//     //输入: digits = "2"
//     //输出: ["a","b","c"]
//     digits = "2";
//     results = s.letterCombinations(digits);

//     return 0;
// }