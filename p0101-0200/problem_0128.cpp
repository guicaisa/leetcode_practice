#include <vector>
#include <unordered_set>

// https://leetcode.cn/problems/longest-consecutive-sequence/

using namespace std;

class Solution 
{
public:
    //1. 哈希集合
    //首先将数组nums中的所有元素存入一个哈希集合中
    //遍历哈希集合中的每个元素num，为了高效定位连续序列，我们只从序列的起始点开始计数
    //通过检查num-1是否存在于集合中来判断起始点
    //如果num-1存在，说明num是某个序列的中间或末尾部分，直接跳过
    //如果num-1不存在，说明 num 是一个潜在连续序列的起始点
    //一旦确认num为起始点，便以此为基础向上匹配连续元素(num+1, num+2, ...)
    //循环不断检查后续元素是否存在于集合中，记录当前连续序列的长度，并同步更新全局最大长度max_len
    //在第二次遍历时，直接遍历哈希集合而非原数组，因为原数组可能包含大量重复元素，直接遍历会导致对同一个序列起始点进行多次无意义的重复触发，会增大常数项开销
    //虽然在第二次遍历中嵌套了一个循环，但每个元素最多只会被处理两次，一次是在外层循环中判断是否为起始点，另一次是在内层循环中作为连续序列的一部分被访问
    //因此，总的操作次数与n成线性关系，时间复杂度为O(n)
    int longestConsecutive(vector<int>& nums) 
    {
        unordered_set<int> set;
        set.reserve(nums.size());
        for (int i = 0; i < nums.size(); ++i)
        {
            set.insert(nums[i]);
        }
        int max_len = 0;
        for (auto it = set.begin(); it != set.end(); ++it)
        {
            int num = *it;
            if (set.find(num - 1) != set.end())
            {
                continue;
            }
            for (int n = 1; ; ++n)
            {
                if (set.find(num+n) == set.end())
                {
                    max_len = max(max_len, n);
                    break;
                }
            }
        }
        
        return max_len;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入：nums = [100,4,200,1,3,2]
//     //输出：4
//     vector<int> nums = {100,4,200,1,3,2};
//     int result = s.longestConsecutive(nums);

//     //输入：nums = [0,3,7,2,5,8,4,6,0,1]
//     //输出：9
//     nums = {0,3,7,2,5,8,4,6,0,1};
//     result = s.longestConsecutive(nums);

//     //输入：nums = [1,0,1,2]
//     //输出：3
//     nums = {1,0,1,2};
//     result = s.longestConsecutive(nums);

//     return 0;
// }