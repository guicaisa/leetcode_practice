#include <vector>

// https://leetcode.cn/problems/permutations/

using namespace std;

class Solution 
{
public:
    vector<vector<int>> permute(vector<int>& nums) 
    {
        if (nums.size() == 0)
        {
            return vector<vector<int>>();
        }
        vector<int> temp;
        vector<vector<int>> results;
        this->recursive(nums, nums.size() - 1, temp, results);
        return results;
    }

    void recursive(vector<int>& nums, int max, vector<int>& temp, vector<vector<int>>& results)
    {
        for (int i = 0; i <= max; ++i)
        {
            int num = nums[i];
            temp.push_back(num);
            if (max == 0)
            {
                results.push_back(temp);
            }
            else
            {
                nums[i] = nums[max];
                nums[max] = num;
                this->recursive(nums, max-1, temp, results);
                nums[max] = nums[i];
                nums[i] = num; 
            }
            temp.pop_back();
        }
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: nums = [1,2,3]
//     //输出: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
//     vector<int> nums = {1, 2, 3};
//     vector<vector<int>> results = s.permute(nums);

//     //输入: nums = [0,1]
//     //输出: [[0,1],[1,0]]
//     nums = {0, 1};
//     results = s.permute(nums);

//     //输入: nums = [1]
//     //输出: [[1]]
//     nums = {1};
//     results = s.permute(nums);

//     return 0;
// }