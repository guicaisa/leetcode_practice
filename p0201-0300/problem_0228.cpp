#include <string>
#include <vector>

// https://leetcode.cn/problems/summary-ranges/

using namespace std;

class Solution 
{
public:
    //1. 遍历
    //遍历数组，并维护一个变量left_index作为当前连续区间的左边界起始索引
    //在遍历过程中，通过两个条件触发右边界确认，1是元素不连续，当前元素与后继元素差不为1(即nums[i+1] != nums[i] + 1)，2是当前元素已达到数组末尾
    //确认了区间之后，根据区间内元素个数进行分类处理，单元素区间则直接将数值转换为字符串，多元素区间按照'start->end'的格式拼接字符串
    //然后将left_index设置为下一个元素，开始寻找下一个连续区间，遍历完成之后返回结果即可
    vector<string> summaryRanges(vector<int>& nums) 
    {
        int left_index = 0;
        vector<string> results;
        for (int i = 0; i < nums.size(); ++i)
        {
            if (i == nums.size() - 1 || nums[i] + 1 != nums[i+1])
            {
                int right_index = i;
                if (left_index == right_index)
                {
                    results.push_back(to_string(nums[left_index]));
                } 
                else
                {
                    string str = to_string(nums[left_index]) + "->" + to_string(nums[right_index]);
                    results.push_back(str);
                }
                left_index = i+1;
            }
        }   
        
        return results;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入：nums = [0,1,2,4,5,7]
//     //  输出：["0->2","4->5","7"]
//     vector<int> nums = {0,1,2,4,5,7};
//     vector<string> results = s.summaryRanges(nums);

//     //输入：nums = [0,2,3,4,6,8,9]
//     //输出：["0","2->4","6","8->9"]
//     nums = {0,2,3,4,6,8,9};
//     results = s.summaryRanges(nums);

//     return 0;
// }