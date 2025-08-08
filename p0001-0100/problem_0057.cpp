#include <vector>

using namespace std;

// https://leetcode.cn/problems/insert-interval/

class Solution 
{
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) 
    {
        if (intervals.size() == 0)
        {
            return vector<vector<int>>{newInterval};
        }

        vector<vector<int>> results;
        int index = 0;
        bool insert = false;
        for (int i = 0; i < intervals.size(); ++i)
        {
            if (insert)
            {
                results.push_back(intervals[i]);
                continue;
            }
            if (intervals[i][1] < newInterval[0])
            {
                results.push_back(intervals[i]);
                continue;
            }
            if (newInterval[1] < intervals[i][0])
            {
                results.push_back(newInterval);
                results.push_back(intervals[i]);
                insert = true;
                continue;
            }
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            if (i == intervals.size() - 1 || newInterval[1] < intervals[i+1][0])
            {
                results.push_back(newInterval);
                insert = true;
            }
        }
        if (!insert)
        {
            results.push_back(newInterval);
        }

        return results;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;
//     vector<vector<int>> intervals = {
//         vector<int>{1, 2},
//         vector<int>{3, 5},
//         vector<int>{6, 7},
//         vector<int>{8, 10},
//         vector<int>{12, 16},
//     };
//     vector<int> newInterval = vector<int>{4, 8};
//     vector<vector<int>> result = s.insert(intervals, newInterval);

//     intervals = {
//         vector<int>{1, 5},
//     };
//     newInterval = vector<int>{0, 0};
//     result = s.insert(intervals, newInterval);

//     return 0;
// }