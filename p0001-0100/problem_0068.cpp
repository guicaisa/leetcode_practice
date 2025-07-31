#include <vector>
#include <string>

using namespace std;

// https://leetcode.cn/problems/text-justification/

class Solution 
{
public:
    //1. 贪心
    //核心思路是在一行内放入足够多的单词，在超出一行上限的时候，根据某种策略分配空格的位置来满足题目要求
    //首先最基础的是，用line_word_size记录一行中所有单词的长度，再根据单词个数-1得到间隔数量，每个间隔最少需要一个空格
    //在这个基础上，用行长度maxWidth减去所有单词长度和间隔数量的空格数，获得多余的空格数，需要填充满整行
    //多余的空格数 / 间隔数量，可以获得每个间隔需要额外补充的空格数，除法可能会有余数，余数在遍历到每个间隔的时候，继续给补充一个空格(如果还有剩余的话)
    //有些情况可能一行只有一个单词，那直接在这个单词后面填满空格即可，一个单词的情况下，不需要单词顶到右边界
    //按照这种方式来分配空格，即可完成题目中的要求，剩下最后一行的话，每个单词间隔只需要一个空格，剩余的空格填满行即可
    vector<string> fullJustify(vector<string>& words, int maxWidth) 
    {
        if (words.size() == 0)
        {
            return vector<string>();
        }

        vector<string> results;
        int index = 0; //标识每一行第一个单词
        int line_word_size = words[0].size(); //记录当前行的所有单词长度
        for (int i = 1; i < words.size(); ++i)
        {
            //当前行至少需要的空格数，其实就是看当前行已经有的单词数量，再-1
            int least_space_num = i == index ? 0 : i - index - 1;
            //当前行的所有单词长度 + 至少需要的空格数 + 当前遍历到的单词的长度 + 一个额外的空格数，超出了maxWidth
            //表示words[i]需要另起一行，记录当前行上的所有单词
            if (line_word_size + least_space_num + words[i].size() + 1 > maxWidth)
            {
                //maxWidth - 当前行的所有单词长度 - 至少需要的空格数，就是剩余的空格数，用剩余的空格数填满一行
                int remain_space_num = maxWidth - line_word_size - least_space_num;
                int word_cnt = i - index; //当前行的单词数量
                int elapse_cnt = word_cnt - 1;//单词间隔数量 = 单词个数 - 1
                //每个单词间隔，除了固定的一个空格外，每个间隔处可以获得的多余的空格数
                int per_space_num = elapse_cnt == 0 ? 0 : remain_space_num / elapse_cnt;
                //剩余的空格，平分给每个间隔之外，可能还会有剩的空格数，遍历单词的时候，按遍历顺序优先往前分配
                remain_space_num = elapse_cnt == 0 ? remain_space_num : remain_space_num % elapse_cnt;
                string temp;
                for (int j = index; j < i; ++j)
                {
                    temp += words[j]; //加一个单词
                    //不是最后一个单词，补充空格
                    if (j != i - 1)
                    {
                        //空格数量，保底一个 + 多余的per_space_num个 + 如果有剩的给1个
                        int cnt = 1 + per_space_num + (remain_space_num ? 1 : 0);
                        temp += string(cnt, ' '); 
                        if (remain_space_num)
                        {
                            --remain_space_num;
                        }
                    }
                }
                //还有剩的，填满到尾部(一行只有一个单词的情况，用空格填尾)
                if (remain_space_num)
                {
                    temp += string(remain_space_num, ' '); 
                }
                results.push_back(temp); //记录结果
                index = i; //当前单词定位为下一行的头
                line_word_size = words[i].size(); //重置行单词总长度
            }
            else
            {
                //还没超出一行，继续累加行单词总长度
                line_word_size += words[i].size();
            }
        }

        //处理最后一行
        string temp;
        for (int i = index; i < words.size(); ++i)
        {
            temp += words[i];
            //不是最后一个单词，加一个空格，最后一行，每个单词间只需要一个空格
            if (i != words.size() - 1)
            {
                temp += " ";
            }
        }
        //剩下的空间全部补空格
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

//     words = {"Listen","to","many,","speak","to","a","few."};
//     max_width = 6;
//     result = s.fullJustify(words, max_width);

//     return 0;
// }