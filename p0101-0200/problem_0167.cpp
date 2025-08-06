#include <vector>

using namespace std;

// https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/

class Solution 
{
public:
    //1. 双指针
    //左右指针相向遍历，相加之后与target判断大小，如果相等就直接返回答案
    //由于数组是升序排列的，根据相加的值与target大小的判断，来定义下次的遍历方向
    //比target小，需要更大和，所以左边的指针右移，反之亦然
    vector<int> twoSum(vector<int>& numbers, int target) 
    {
        int left = 0;
        int right = numbers.size() - 1;
        while (left < right)
        {
            int sum = numbers[left] + numbers[right];
            if (sum == target)
            {
                return vector<int>{left+1, right+1};
            }
            if (sum < target)
            {
                ++left;
            }
            else
            {
                --right;
            }
        }

        return vector<int>{left, right};
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;
//     vector<int> numbers = {2,7,11,15};
//     int target = 9;
//     vector<int> result = s.twoSum(numbers, target);

//     numbers = {2,3,4}; 
//     target = 6;
//     result = s.twoSum(numbers, target);

//     numbers = {-1,0};
//     target = -1;
//     result = s.twoSum(numbers, target);

//     return 0;
// }