#include <vector>
#include <unordered_map>

// https://leetcode.cn/problems/contains-duplicate-ii/

using namespace std;

class Solution 
{
public:
    //1. 哈希表
    //在遍历数组的过程中，记录数字和其索引的映射关系，如果该数字已被记录过
    //就判断当前索引和上次数字出现时位置差值，小于等于k则返回true，否则遍历结束，返回false
    bool containsNearbyDuplicate(vector<int>& nums, int k) 
    {
        unordered_map<int, int> num2idx;
        for (int i = 0; i < nums.size(); ++i)
        {
            int num = nums[i];
            if (auto it = num2idx.find(num); it != num2idx.end())
            {
                if (i - it->second <= k)
                {
                    return true;
                }
            }
            num2idx[num] = i;
        }

        return false;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入：nums = [1,2,3,1], k = 3
//     //输出：true
//     vector<int> nums = {1, 2, 3, 1};
//     bool result = s.containsNearbyDuplicate(nums, 3);

//     //输入：nums = [1,0,1,1], k = 1
//     //输出：true
//     nums = {1, 0, 1, 1};
//     result = s.containsNearbyDuplicate(nums, 1);

//     //输入：nums = [1,2,3,1,2,3], k = 2
//     //输出：false
//     nums = {1, 2, 3, 1, 2, 3};
//     result = s.containsNearbyDuplicate(nums, 2);

//     return 0;
// }