#include <vector>

using namespace std;

class Solution 
{
public:
    //1. 双指针
    //左右指针相向遍历，计算每次的面积，每次遍历时移动短边，在宽度变小的情况下，提高高度才能获得更大的结果
    int maxArea(vector<int>& height) 
    {
        int max_area = 0;
        int left = 0;
        int right = height.size() - 1;
        while (left <= right)
        {
            int h = min(height[left], height[right]);
            int w = right - left;
            max_area = max(max_area, h * w);
            if (height[left] < height[right])
            {
                ++left;
            }
            else
            {
                --right;
            }
        }

        return max_area;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     vector<int> height = {1,8,6,2,5,4,8,3,7};
//     int result = s.maxArea(height);

//     height = {1,1};
//     result = s.maxArea(height);

//     return 0;
// }