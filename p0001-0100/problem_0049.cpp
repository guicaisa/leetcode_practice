#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

// https://leetcode.cn/problems/group-anagrams/

using namespace std;

class Solution 
{
public:
    //1. 哈希表+排序
    //针对每个字符串，优先进行排序，然后根据排序后的字符串作为键进行归类，存储到哈希表中
    //然后遍历哈希表，构建返回结果
    vector<vector<string>> groupAnagrams(vector<string>& strs) 
    {
        unordered_map<string, vector<string>> str_map;
        for (int i = 0; i < strs.size(); ++i)
        {
            string str = strs[i];
            sort(str.begin(), str.end());
            str_map[str].push_back(strs[i]);
        }

        vector<vector<string>> results;
        for (auto it = str_map.begin(); it != str_map.end(); ++it)
        {
            results.push_back(it->second);
        }

        return results;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
//     //输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
//     vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
//     vector<vector<string>> results = s.groupAnagrams(strs);

//     //输入: strs = [""]
//     //输出: [[""]]
//     strs = {""};
//     results = s.groupAnagrams(strs);

//     //输入: strs = ["a"]
//     //输出: [["a"]]
//     strs = {"a"};
//     results = s.groupAnagrams(strs);

//     return 0;
// }