#include <vector>
#include <stack>

using namespace std;

// https://leetcode.cn/problems/trapping-rain-water/

class Solution 
{
public:
    //1. 每层累加
    //设立左右边界，高度从1开始，只要左右边界比当前高度高，就累加到总数中
    //不断缩减左右边界中低的一边，直到完全重合，此时的总数sum是总积水量+所有柱子的高度
    //总数减去所有柱子的高度，结果就是总积水量
    int trap(vector<int>& height) 
    {
        int sum = 0;
        int left = 0;
        int right = height.size() - 1;
        int h = 1;
        while (left <= right)
        {
            if (height[left] >= h && height[right] >= h)
            {
                int len = right - left + 1;
                sum += len;
                ++h;
                continue;
            }
            if (height[left] < height[right])
            {
                ++left;
            }
            else
            {
                --right;
            }
        }
        //减去所有柱子高度
        for (int i = 0; i < height.size(); ++i)
        {
            sum -= height[i];
        }

        return sum;
    }
    
    //2. 动态规划
    //使用两个数组left/right，保存在某个位置时，左右两侧柱子的最大高度
    //即当遍历到height[i]时，i左侧的柱子最大高度是left[i]，i右侧的柱子的最大高度是right[i]
    //使用left[i]和right[i]之间的较小者(短板)，减去height[i]即为height[i]处可以积水的值
    int trapDp(vector<int>& height)
    {
        vector<int> left(height.size(), 0); //left[i]为height[i]左侧最高的柱子
        vector<int> right(height.size(), 0); //right[i]为height[i]右侧最高的柱子
        int max_height = 0;
        for (int i = 0; i < height.size(); ++i)
        {
            max_height = max(max_height, height[i]);
            left[i] = max_height;
        }
        max_height = 0;
        for (int i = height.size() - 1; i >= 0; --i)
        {
            max_height = max(max_height, height[i]);
            right[i] = max_height;
        }
        int sum = 0;
        for (int i = 0; i < height.size(); ++i)
        {
            int temp = min(left[i], right[i]) - height[i];
            sum += temp;
        }

        return sum;
    }

    //3. 递减栈
    //使用栈维持一个柱子高度递减的序列，遇到右侧柱子比当前栈顶元素大的时候，即表示遇到了水洼
    //从栈里相继弹出元素作为水洼的左侧柱子，与右侧柱子一起计算中间水洼的积水
    int trapStack(vector<int>& height)
    {
        stack<int> si; //递减栈，栈里保存的是数组的索引
        int sum = 0;
        for (int i = 0; i < height.size(); ++i)
        {
            //保持柱子递减序列
            if (si.empty() || height[si.top()] >= height[i])
            {
                si.push(i);
                continue;
            }
            //右侧遇到了较高的柱子，此时的栈顶元素就是水洼，bottom为水洼处的高度
            int bottom = height[si.top()]; 
            si.pop();
            //不断从栈里弹出元素，作为左侧柱子，与右侧柱子一起包住水洼，形成积水
            while (!si.empty())
            {
                int index = si.top(); //栈顶元素索引
                int temp = height[index]; //左侧柱子高度
                int h = min(height[i], temp); //短板原理，取较小值
                int len = i - index - 1; //中间水洼的宽度
                sum += len * (h - bottom);  //累加积水
                if (temp <= height[i])
                {
                    //左侧这个柱子高度小于等于右侧柱子，该柱子可以作为水洼，继续往左侧查看更高的柱子，寻求更多的积水
                    si.pop();
                    bottom = temp;
                }
                else
                {
                    break;
                }
            }
            //右侧柱子自身加入递减栈
            si.push(i);
        }

        return sum;
    }

    // int trapTowPointers(vector<int>& height)
    // {
    //     int left = 0;
    //     int right = height.size() - 1;
    //     while (left <= right)
    //     {

    //     }

    //     return 0;
    // }
};

int main(int argc, char** argv)
{
    Solution s;

    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    int result = s.trapStack(height);

    height = {4,2,0,3,2,5};
    result = s.trapStack(height);

    return 0;
}