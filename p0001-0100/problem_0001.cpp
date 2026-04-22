#include <vector>
#include <unordered_map>

// https://leetcode.cn/problems/two-sum/

using namespace std;

class Solution 
{
public:
    //1. 哈希表
    //遍历数组的过程中，使用一个哈希表，建立每个数字和其在数组中的索引的映射关系
    //在遍历到某个数字num的时候，计算其与target的差值diff，如果diff存在在哈希表中，视为有解，将diff的索引和当前num的索引作为结果返回即可
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        unordered_map<int, int> ch2idx;
        for (int i = 0; i < nums.size(); ++i)
        {
            int num = nums[i];
            int diff = target - num;
            if (auto it = ch2idx.find(diff); it != ch2idx.end())
            {
                return vector<int>{it->second, i};
            }
            ch2idx[num] = i;
        }

        return vector<int>{0, 0};
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;
    
//     //输入：nums = [2,7,11,15], target = 9
//     //输出：[0,1]
//     vector<int> nums = {2, 7, 11, 15};
//     vector<int> result = s.twoSum(nums, 9);

//     //输入：nums = [3,2,4], target = 6
//     //输出：[1,2]
//     nums = {3, 2, 4};
//     result = s.twoSum(nums, 6);

//     //输入：nums = [3,3], target = 6
//     //输出：[0,1]
//     nums = {3, 3};
//     result = s.twoSum(nums, 6);

//     return 0;
// }