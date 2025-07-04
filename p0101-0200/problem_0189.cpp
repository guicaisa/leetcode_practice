#include <vector>

using namespace std;

// https://leetcode.cn/problems/rotate-array/

class Solution
{
public:
    //1. 数组
    //使用临时数组变量作为nums的副本，计算每个值的新位置，然后设置到结果数组中
    void rotate(vector<int>& nums, int k)
    {
        if (nums.size() == 0)
        {
            return;
        }
        int shift = k % nums.size();
        if (shift == 0)
        {
            return;
        }
        vector<int> temp = nums;
        for (int i = 0; i < temp.size(); ++i)
        {
            int index = (i + k) % nums.size();
            nums[index] = temp[i];
        }
    }

    //2. 翻转
    //根据题目中提示"部分翻转"而得到的启发，通过3次翻转即可得到轮转的结果
    void rotateReverse(vector<int>& nums, int k)
    {
        if (nums.size() == 0)
        {
            return;
        }
        int shift = k % nums.size();
        if (shift == 0)
        {
            return;
        }
        reverse(nums.begin(), nums.end()); //第一次，翻转整个数组
        reverse(nums.begin(), nums.begin() + shift); //第二次，翻转前shift个元素
        reverse(nums.begin() + shift, nums.end()); //第三次，翻转后剩下后半段的所有元素
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     vector<int> nums = {1,2,3,4,5,6,7};
//     int k = 3;
//     s.rotateReverse(nums, k);

//     nums = {-1,-100,3,99};
//     k = 2;
//     s.rotateReverse(nums, k);

//     return 0;
// }