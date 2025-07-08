#include <vector>

using namespace std;

// https://leetcode.cn/problems/h-index/

class Solution 
{
public:
    //1. 排序遍历
    //对数组进行排序，然后遍历数组，每次遍历获得当前论文的引用数量，以及大于等于该引用数量的论文数量
    //两者取最小值，满足题目中"至少有h篇论文被引用次数大于等于h"的条件要求，h指数结果则尽可能选择更大的数值
    int hIndex(vector<int>& citations)
    {
        sort(citations.begin(), citations.end());
        int h_index = 0;
        for (int i = 0; i < citations.size(); ++i)
        {
            int ref_num = citations[i]; //引用数量
            int paper_num = citations.size() - i; //引用数量大于等于ref_num的论文数量
            int temp = min(ref_num, paper_num); //取较小者
            h_index = max(h_index, temp); //h指数的值要求尽可能的大
        }

        return h_index;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     vector<int> nums = {3, 0, 6, 1, 5};
//     int result = s.hIndex(nums);

//     nums = {1, 3, 1};
//     result = s.hIndex(nums);

//     return 0;
// }