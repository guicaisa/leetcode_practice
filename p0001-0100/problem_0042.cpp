#include <vector>

using namespace std;

// https://leetcode.cn/problems/trapping-rain-water/

class Solution 
{
public:
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

        for (int i = 0; i < height.size(); ++i)
        {
            sum -= height[i];
        }

        return sum;
    }
};

int main(int argc, char** argv)
{
    Solution s;

    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    int result = s.trap(height);

    height = {4,2,0,3,2,5};
    result = s.trap(height);

    return 0;
}