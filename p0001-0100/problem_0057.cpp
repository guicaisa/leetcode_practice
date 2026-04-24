#include <vector>

using namespace std;

// https://leetcode.cn/problems/insert-interval/

class Solution 
{
public:
    //1. 遍历
    //由于输入数组intervals已经按起始位置升序排列，我们可以通过一次遍历，将处理逻辑分为三个连续的阶段
    //阶段一: 处理左侧非重叠区间，从左向右遍历，只要当前区间的结束位置小于新区间newInterval的起始位置，说明两者完全不重合，直接将当前区间推入结果数组
    //阶段二: 合并重叠区间，一旦发现当前区间与新区间存在交集(即阶段一的条件不再满足)，且当前区间的起始位置小于或等于新区间的结束位置
    //不断更新新区间的边界，取两者起始位置的最小值和结束位置的最大值，newStart=min(newStart, currentStart)，newEnd=max(newEnd, currentEnd)
    //这是一个动态合并的过程，直至遇到一个完全在新区间右侧的区间
    //阶段三: 处理右侧非重叠区间，在完成合并并插入新区间后，剩下的所有区间必然都在新区间的右侧且互不重叠
    //首先将合并后的newInterval存入结果数组，随后将其余区间顺序存入即可
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) 
    {
        if (intervals.size() == 0)
        {
            return vector<vector<int>>{newInterval};
        }

        vector<vector<int>> results;
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