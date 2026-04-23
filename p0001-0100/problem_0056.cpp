#include <vector>
#include <algorithm>

// https://leetcode.cn/problems/merge-intervals/

using namespace std;

class Solution 
{
public:
    //1. 滑动窗口+排序
    //首先对intervals进行升序排序，排序准则为区间的起始值，确保处理过程中，所有可能发生重叠的区间是连续出现的，从而将复杂的二维搜索转化为一维的线性处理
    //维护一个代表当前合并区间的边界，使用left_index记录当前正在合并的区间起始索引，使用right_num并将其初始化为第一个区间的结束值，它代表了当前窗口向右延伸的最远距离
    //遍历排序后的区间数组，通过比较当前窗口的right_num与下一个区间的起始值来决定后续操作
    //若下一区间起始值大于right_num或已到达数组末尾，说明当前连续区间已无法进一步向右延伸
    //将[intervals[left_index][0], right_num]存入结果集，将left_index更新为下一个区间的索引，继续进行遍历
    //每次遍历时直接使用每个区间的结束值更新right_num即可，取最大值
    vector<vector<int>> merge(vector<vector<int>>& intervals) 
    {
        if (intervals.size() == 0)
        {
            return vector<vector<int>>{};
        }
        sort(intervals.begin(), intervals.end(), [](const vector<int>& l, const vector<int>& r) {
            return l[0] < r[0];
        });
        vector<vector<int>> results;
        int left_index = 0;
        int right_num = intervals[0][1];
        for (int i = 0; i < intervals.size(); ++i)
        {
            right_num = max(right_num, intervals[i][1]);
            if (i == intervals.size() - 1 || right_num < intervals[i+1][0])
            {
                results.push_back(vector<int>{intervals[left_index][0], right_num});
                left_index = i + 1;
            }
        }

        return results;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
//     //输出：[[1,6],[8,10],[15,18]]
//     vector<vector<int>> intervals = {
//         {1,3},
//         {2,6},
//         {8,10},
//         {15,18},
//     };
//     vector<vector<int>> results = s.merge(intervals);

//     //输入：intervals = [[1,4],[4,5]]
//     //输出：[[1,5]]
//     intervals = {
//         {1,4},
//         {4,5},
//     };
//     results = s.merge(intervals);

//     //输入：intervals = [[4,7],[1,4]]
//     //输出：[[1,7]]
//     intervals = {
//         {4,7},
//         {1,4},
//     };
//     results = s.merge(intervals);

//     //[[2,3],[4,5],[6,7],[8,9],[1,10]]
//     intervals = {
//         {2,3},
//         {4,5},
//         {6,7},
//         {8,9},
//         {1,10},
//     };
//     results = s.merge(intervals);

//     return 0;
// }