#include <vector>
#include <string>

using namespace std;

// https://leetcode.cn/problems/text-justification/

class Solution 
{
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) 
    {
        vector<string> results;
        int index = 0;
        int word_size = 0;
        for (int i = 0; i < words.size(); ++i)
        {
            int least_space_num = i - index - 1;
            if (word_size + words[i].size() + 1 + least_space_num > maxWidth)
            {
                int word_cnt = i - index;
                int space_num = maxWidth - (word_size + least_space_num);
                int interval_space_num = word_cnt == 1 ? 0 : space_num / (word_cnt - 1);
                int remain = word_cnt == 1 ? 0 : space_num % (word_cnt - 1);
                string temp;
                for (int j = index; j < i; ++j)
                {
                    if (j != index)
                    {
                        int num = 1 + interval_space_num;
                        if (remain > 0)
                        {
                            num += 1;
                            --remain;
                        }
                        temp += string(num, ' ');
                    }
                    temp += words[j];
                }
                results.push_back(temp);
                word_size = words[i].size();
                index = i;
                continue;
            }
            word_size += words[i].size();
        }

        string temp;
        for (int i = index; i < words.size(); ++i)
        {
            if (i != index)
            {
                temp += ' ';
            }
            temp += words[i];
        }
        if (temp.size() < maxWidth)
        {
            temp += string(maxWidth - temp.size(), ' ');
        }
        results.push_back(temp);

        return results;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     vector<string> words = {"This", "is", "an", "example", "of", "text", "justification."};
//     int max_width = 16;
//     vector<string> result = s.fullJustify(words, max_width);

//     words = {"Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"};
//     max_width = 20;
//     result = s.fullJustify(words, max_width);

//     return 0;
// }