#include <vector>

using namespace std;

// https://leetcode.cn/problems/minimum-size-subarray-sum/

class Solution 
{
public:
    //1. 暴力破解
    //使用双重循环，第一层循环以每个值作为起点，第二层循环从起点开始计算sum
    //当sum >= target时，记录当前位置与起点的距离，并将较小值保存在结果中
    //双循环的时间复杂度太高，有些测试用例会超时，无法通过
    int minSubArrayLenBruteForce(int target, vector<int>& nums)
    {
        if (nums.size() == 0) 
        {
            return 0;
        }

        int min_len = 0;
        //第一次层循环，以每个nums[i]为起点
        for (int i = 0; i < nums.size(); ++i)
        {
            //nums[i] >= target，min_len为1，直接退出循环
            if (nums[i] >= target)
            {
                min_len = 1;
                break;
            }
            int sum = nums[i];
            //第二层循环，从nums[i]之后开始累加sum
            for (int j = i + 1; j < nums.size(); ++j)
            {
                sum += nums[j];
                //sum >= target时满足条件，计算长度，并将较小值保存到min_len中
                if (sum >= target)
                {
                    int len = j - i + 1;
                    min_len = min_len == 0 ? len : min(min_len, len);
                    break;
                }
            }
        }

        return min_len;
    }

    //2. 前缀和+二分查找
    //暴力破解法时间复杂度的原因主要在于双层循环，由于nums所有元素都是正数，所以可以考虑构建生序的前缀和数组然后通过二分查找的方式降低时间复杂度
    //首先构建前缀和数组prefix_sum，prefix_sum[i]表示从nums[0]到nums[i]之间所有元素的和(包含nums[i])，这个数组是天然生序的
    //循环以每个nums[i]作为起点，在范围[1, nums.size()-1]中查找结果，假设某个索引x，满足nums[i]...nums[x]间所有元素的和大于等于target
    //这个和可以用前缀和来表示，即prefix_sum[x] - prefix_sum[i-1]，所以prefix_sum[x] - prefix_sum[i-1] >= target，可得prefix_sum[x] >= prefix_sum[i-1] + target
    //所以现在问题变成了在范围[1, nums.size()-1]中，查找第一个前缀和大于等于prefix_sum[i-1] + target的值索引，即可获以nums[i]为起点的最小数组长度
    //由于前缀和数组是生序的，这一步查找可以使用二分查找来处理，降低时间复杂度，c++中可以使用现成的函数lower_bound查找范围内大于等于某个值的迭代器
    //如果能找到对应的迭代器，就可以计算该位置和i的距离，将长度较小值保存在结果min_len中
    int minSubArrayLenPrefixSumBinary(int target, vector<int>& nums)
    {
        if (nums.size() == 0)
        {
            return 0;
        }

        int min_len = 0;
        //构建前缀和数组，prefix_num[i]表示从nums[0]到nums[i]之间所有元素的和，包括nums[i]本身
        vector<int> prefix_sum(nums.size(), 0);
        prefix_sum[0] = nums[0];
        for (int i = 1; i < nums.size(); ++i)
        {
            prefix_sum[i] = prefix_sum[i-1] + nums[i];
        }
        //循环，以每个nums[i]为起点
        for (int i = 0; i < nums.size(); ++i)
        {
            //nums[i] >= target，min_len为1，直接退出循环
            if (nums[i] >= target)
            {
                min_len = 1;
                break;
            }
            //在范围[i, num.size()-1]内查找结果，假设某个索引x，满足nums[i]...nums[x]间所有元素的和大于等于target
            //则这个和可以用前缀和来表示，即nums[i]...nums[x]间所有元素的和=prefix_sum[x] - prefix_sum[i-1]
            //即prefix_sum[x] - prefix_sum[i-1] >= target，可得prefix_sum[x] >= prefix_sum[i-1] + target
            //在范围中查找第一个大于等于sum的值，获得索引和子数组长度，将较小值保存到min_len中
            int sum = (i > 0 ? prefix_sum[i-1] : 0) + target;
            auto iter = lower_bound(prefix_sum.begin() + i, prefix_sum.end(), sum);
            if (iter != prefix_sum.end())
            {
                int len = iter - (prefix_sum.begin() + i) + 1;
                min_len = min_len == 0 ? len : min(min_len, len);
            }
        }

        return min_len;
    }

    //3. 滑动窗口
    //使用左右索引来维持一个滑动窗口，滑动窗口中的所有元素构成一个和sum
    //首先不断移动右边界，来容纳更多的值，直到sum >= target
    //在sum >= target时，更新并记录滑动窗口的长度，并不断移动左边界，尝试在满足sum >= target的情况下可以获得更小的长度
    int minSubArrayLenSlideWindow(int target, vector<int>& nums) 
    {
        int left = 0;
        int right = 0;
        int min_len = 0;
        int sum = 0;
        while (right < nums.size())
        {
            //小于target，不断移动右边界
            if (sum < target)
            {
                sum += nums[right++];
            }
            //sum >= target时，通过移动左边界，尝试获得更小的数组长度
            while (sum >= target)
            {
                int len = right - left;
                min_len = min_len == 0 ? len : min(min_len, len);
                sum -= nums[left++];
            }
        }
        
        return min_len;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: target = 7, nums = [2,3,1,2,4,3]
//     //输出: 2
//     vector<int> nums = {2, 3, 1, 2, 4, 3};
//     int result = s.minSubArrayLenSlideWindow(7, nums);

//     //输入: target = 4, nums = [1,4,4]
//     //输出: 1
//     nums = {1, 4, 4};
//     result = s.minSubArrayLenSlideWindow(4, nums);

//     //输入: target = 11, nums = [1,1,1,1,1,1,1,1]
//     //输出: 0
//     nums = {1, 1, 1, 1, 1, 1, 1, 1};
//     result = s.minSubArrayLenSlideWindow(11, nums);
    
//     return 0;
// }