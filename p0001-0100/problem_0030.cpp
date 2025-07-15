#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution 
{
public:
    vector<int> findSubstring(string s, vector<string>& words) 
    {
        int word_len = words[0].size();
        int word_count = words.size();
        int total_len = word_len * word_count;
        unordered_map<string, queue<int>> word_to_index;
        vector<int> results;
        for (int i = 0; i < word_len && i + total_len <= s.size(); ++i)
        {
            unordered_map<string, int> words_map;
            for (int cnt = 0; cnt < word_count; ++cnt)
            {
                string str = s.substr(i + cnt * word_len, word_len);
                ++words_map[str];
            }
            for (int i = 0; i < words.size(); ++i)
            {
                if (--words_map[words[i]] == 0)
                {
                    words_map.erase(words[i]);
                }
            } 
            
            for (int index = i; index + total_len <= s.size(); index += word_len)
            {
                if (index != i)
                {
                    string right_str = s.substr(index + (word_count - 1) * word_len, word_len);
                    if (++words_map[right_str] == 0)
                    {
                        words_map.erase(right_str);
                    }

                    string left_str = s.substr(index - word_len, word_len);
                    if (--words_map[left_str] == 0)
                    {
                        words_map.erase(left_str);
                    }
                }
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