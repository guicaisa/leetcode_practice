#include <vector>
#include <algorithm>

// https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/

using namespace std;

class Solution 
{
public:
    //1. 排序+贪心
    //按区间的起始位置进行升序排列，这确保了在一次遍历中，只需关注当前区间与后续区间的重叠关系
    //引入变量left和right来界定当前重叠子集的边界，初始值为首个区间的范围
    //遍历后续区间，若当前区间的起点大于right，说明产生了断层，此时必须消耗一支箭，count自增，并开启一个新的重叠区间，将left和right设置为当前区间的起始和结束
    //若存在重叠，则更新当前公共重叠区的范围，左界取最大值max(left, start)，右界取最小值min(right, end)
    //遍历结束后，需将最后一组重叠区间计入总数(count + 1)，返回结果
    int findMinArrowShots(vector<vector<int>>& points) 
    {
        if (points.size() == 0)
        {
            return 0;
        }
        sort(points.begin(), points.end(), [](const vector<int>& l, const vector<int>& r) {
            return l[0] < r[0];
        });
        int left = points[0][0];
        int right = points[0][1];
        int count = 0;
        for (int i = 0; i < points.size(); ++i)
        {
            if (points[i][0] > right)
            {
                ++count;
                if (i < points.size() - 1)
                {
                    left = points[i][0];
                    right = points[i][1];
                }
                continue;
            }
            left = max(left, points[i][0]);
            right = min(right, points[i][1]);
        }

        return count+1;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入：points = [[10,16],[2,8],[1,6],[7,12]]
//     //输出：2
//     vector<vector<int>> points = {
//         {10,16},
//         {2,8},
//         {1,6},
//         {7,12},
//     };
//     int result = s.findMinArrowShots(points);

//     //输入：points = [[1,2],[3,4],[5,6],[7,8]]
//     //输出：4
//     points = {
//         {1,2},
//         {3,4},
//         {5,6},
//         {7,8},
//     };
//     result = s.findMinArrowShots(points);

//     //输入：points = [[1,2],[2,3],[3,4],[4,5]]
//     //输出：2
//     points = {
//         {1,2},
//         {2,3},
//         {3,4},
//         {4,5},
//     };
//     result = s.findMinArrowShots(points);

//     points = {
//         {77171087,133597895},
//         {45117276,135064454},
//         {80695788,90089372},
//         {91705403,110208054},
//         {52392754,127005153},
//         {53999932,118094992},
//         {11549676,55543044},
//         {43947739,128157751},
//         {55636226,105334812},
//         {69348094,125645633},
//     };
//     result = s.findMinArrowShots(points);

//     return 0;
// }