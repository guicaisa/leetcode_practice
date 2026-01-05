#include <vector>
#include <algorithm>

// https://leetcode.cn/problems/combination-sum/

using namespace std;

class Solution 
{
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) 
    {
        if (candidates.size() == 0)
        {
            return vector<vector<int>>();
        }

        sort(candidates.begin(), candidates.end());
        vector<int> temp;
        vector<vector<int>> results;
        this->recursive(candidates, 0, target, 0, temp, results);
        return results;
    }

    void recursive(vector<int>& candidates, int index, int target, int num, vector<int>& temp, vector<vector<int>>& results)
    {
        for (int i = index; i < candidates.size(); ++i)
        {
            int n = candidates[i];
            temp.push_back(n);
            int sum = num + n;
            if (sum == target)
            {
                results.push_back(temp);
                temp.pop_back();
                break;
            }
            if (sum > target)
            {
                temp.pop_back();
                break;
            }
            this->recursive(candidates, i, target, sum, temp, results);
            temp.pop_back();
        }
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: candidates = [2,3,6,7], target = 7
//     //输出: [[2,2,3],[7]]
//     vector<int> candidates = {2, 3, 6, 7};
//     vector<vector<int>> results = s.combinationSum(candidates, 7);

//     //输入: candidates = [2,3,5], target = 8
//     //输出: [[2,2,2,2],[2,3,3],[3,5]]
//     candidates = {2, 3, 5};
//     results = s.combinationSum(candidates, 8);

//     //输入: candidates = [2], target = 1
//     //输出: []
//     candidates = {2};
//     results = s.combinationSum(candidates, 1);

//     return 0;
// }