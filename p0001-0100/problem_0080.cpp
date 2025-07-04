#include <vector>

using namespace std;

// https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii/

class Solution 
{
public:
    //1. 双指针
    //具体思路跟problem26差不多，使用双指针的方式来处理，只是遍历中的那段if条件需要改动下
    //改为判断当前元素是否等于index指向的元素和index之前的元素，来满足题目中一个数字最多出现2次的要求
    //对于nums的遍历需要从1开始，不然第一次遍历的时候，就会出现由于不满足if条件语句导致nums[0]被赋值到nums[1]的情况出现，导致结果错误
    int removeDuplicates(vector<int>& nums) 
    {
        int index = 0;
        for (int i = 1; i < nums.size(); ++i)
        {
            int num = nums[i];
            //index > 0 用于处理边界情况
            if (num == nums[index] && index > 0 && num == nums[index - 1]) 
            {
                continue;
            }
            nums[++index] = num;
        }
        return index + 1;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     vector<int> nums = {1, 1, 1, 2, 2, 3};
//     int result = s.removeDuplicates(nums);

//     nums = {0, 0, 1, 1, 1, 1, 2, 3, 3};
//     result = s.removeDuplicates(nums);

//     return 0;
// }