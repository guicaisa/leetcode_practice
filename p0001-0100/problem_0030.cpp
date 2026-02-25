#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

// https://leetcode.cn/problems/substring-with-concatenation-of-all-words/

class Solution 
{
public:
    //1. 哈希表+滑动窗口
    //假设words数组中单词数量为word_count，每个单词的长度为word_len
    //在遍历字符串s的过程中，尝试维持一个长度为单词数量x单词长度(total_len)的滑动窗口
    //初始化一个哈希表，保存words数组中每个单词出现次数的负数(表示欠几个)
    //在遍历滑动窗口的过程中，将滑动窗口中单词出现的次数增加到哈希表中，当次数为0时，从哈希表中删除该单词
    //在每次遍历完滑动窗口之后，检查哈希表是否为空，为空则表示有解，将滑动窗口开始位置的索引记录到结果中
    //继续向右移动滑动窗口，左边界去掉一个单词，右边界添加一个单词，直到剩下滑动窗口长度不足total_len为止
    //不断在字符串s中进行遍历，以每个索引作为滑动窗口的起点，直到结束，返回结果
    vector<int> findSubstring(string s, vector<string>& words) 
    {
        int word_len = words[0].size(); //单个单词的长度
        int word_count = words.size(); //单词数量
        int total_len = word_len * word_count; //所有单词的总长度
        vector<int> results;
        //遍历字符串s，直到剩下的字符串长度不满足total_len，无法获得结果时，结束遍历
        for (int i = 0; i < word_len && i + total_len <= s.size(); ++i)
        {
            //当前滑动窗口中记录所有单词的数量
            unordered_map<string, int> words_map;
            for (int cnt = 0; cnt < word_count; ++cnt)
            {
                string str = s.substr(i + cnt * word_len, word_len);
                ++words_map[str];
            }
            //减去words中单词出现的数量
            for (int i = 0; i < words.size(); ++i)
            {
                if (--words_map[words[i]] == 0)
                {
                    words_map.erase(words[i]);
                }
            } 
            //尝试右移滑动窗口，每次移动一个单词的长度word_len
            for (int index = i; index + total_len <= s.size(); index += word_len)
            {
                //如果是初始的滑动窗口则不处理
                if (index != i)
                {
                    //最右边单词加入滑动窗口
                    string right_str = s.substr(index + (word_count - 1) * word_len, word_len);
                    if (++words_map[right_str] == 0)
                    {
                        words_map.erase(right_str);
                    }

                    //最左边的的单词移出滑动窗口
                    string left_str = s.substr(index - word_len, word_len);
                    if (--words_map[left_str] == 0)
                    {
                        words_map.erase(left_str);
                    }
                }
                //哈希表为空，表示满足题解，记录结果
                if (words_map.empty())
                {
                    results.push_back(index);
                }
            }
        }

        return results;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     string str = "barfoothefoobarman";
//     vector<string> words = {"foo","bar"};
//     vector<int> result = s.findSubstring(str, words);

//     str = "barfoofoobarthefoobarman";
//     words = {"bar","foo","the"};
//     result = s.findSubstring(str, words);

//     str = "barfoothefoobarman";
//     words = {"foo","bar"};
//     result = s.findSubstring(str, words);

//     str = "wordgoodgoodgoodbestword";
//     words = {"word","good","best","good"};
//     result = s.findSubstring(str, words);

//     str = "lingmindraboofooowingdingbarrwingmonkeypoundcake";
//     words = {"fooo","barr","wing","ding","wing"};
//     result = s.findSubstring(str, words);

//     str = "aaaaaaaaaaaaaa";
//     words = {"aa", "aa"};
//     result = s.findSubstring(str, words);

//     str = "ababaab";
//     words = {"ab","ba","ba"};
//     result = s.findSubstring(str, words);

//     return 0;
// }