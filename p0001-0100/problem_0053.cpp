#include <vector>

using namespace std;

class Solution 
{
public:
    //1. 动态规划
    //设dp[i]表示以nums[i]为结尾的连续子数组的最大和，最终问题的解即为dp数组中的最大值(max(dp))
    //对于每个位置i，求解 dp[i]有两种选择，1是将nums[i]接在以nums[i-1]结尾的最大子数组之后，即dp[i-1] + nums[i]，2是以nums[i]作为新子数组的起点，即nums[i]本身
    //具体公式为dp[i]=max(dp[i-1] + nums[i], nums[i])，这本质上是在判断前面的累加和对当前元素是否具有“增益”效果
    //由于dp[i]的计算仅依赖于前一个状态dp[i-1]，我们无需开辟额外的数组空间，通过单次遍历，仅需使用一个变量pre_max_sum来实时维护当前结尾的最大和，并同步更新全局最大值max_sum
    int maxSubArray(vector<int>& nums) 
    {
        if (nums.size() == 0)
        {
            return 0;
        }
        int max_sum = nums[0];
        int pre_max_sum = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            int num = nums[i];
            pre_max_sum = max(pre_max_sum + num, num);
            max_sum = max(max_sum, pre_max_sum);
        }

        return max_sum;
    }
};

int main(int argc, char** argv)
{
    Solution s;

    //输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
    //输出：6
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    int result = s.maxSubArray(nums);

    //输入：nums = [1]
    //输出：1
    nums = {1};
    result = s.maxSubArray(nums);

    //输入：nums = [5,4,-1,7,8]
    //输出：23
    nums = {5,4,-1,7,8};
    result = s.maxSubArray(nums);

    return 0;
}