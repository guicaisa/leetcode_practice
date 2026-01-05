#include <vector>

// https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/

using namespace std;

class Solution 
{
public:
    //1. 二分查找
    //由于numbers数组是升序排列的，所以可以使用二份查找的方式来处理
    //在遍历数组的过程中，选定一个数字，然后在其之后的范围中进行二分查找，找到与其相加等于target的值即可获得结果
    //如果相加结果大于target，表示需要更小的值，则下次二分查找定位到左边区间，反之定位到右边区间
    vector<int> twoSumBinarySearch(vector<int>& numbers, int target)
    {
        for (int i = 0; i < numbers.size() - 1; ++i)
        {
            int num = numbers[i];
            int left = i + 1;
            int right = numbers.size() - 1;
            while (left <= right)
            {
                int mid = (left + right) / 2;
                int sum = num + numbers[mid];
                if (sum == target)
                {
                    return vector<int>{i+1, mid+1};
                }
                if (sum > target)
                {
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
            }
        }

        return vector<int>{0, 0};
    }

    //2. 双指针
    //左右指针相向遍历，相加之后与target判断大小，如果相等就直接返回答案
    //由于数组是升序排列的，根据相加的值与target大小的判断，来定义下次的遍历方向
    //比target小，需要更大的和，所以左边的指针右移，反之亦然
    vector<int> twoSumTwoPointers(vector<int>& numbers, int target) 
    {
        int left = 0;
        int right = numbers.size() - 1;
        while (left < right)
        {
            int sum = numbers[left] + numbers[right];
            if (sum == target)
            {
                return vector<int>{left+1, right+1};
            }
            if (sum < target)
            {
                ++left;
            }
            else
            {
                --right;
            }
        }

        return vector<int>{left, right};
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;
//     vector<int> numbers = {2,7,11,15};
//     int target = 9;
//     vector<int> result = s.twoSumBinarySearch(numbers, target);

//     numbers = {2,3,4}; 
//     target = 6;
//     result = s.twoSumBinarySearch(numbers, target);

//     numbers = {-1,0};
//     target = -1;
//     result = s.twoSumBinarySearch(numbers, target);

//     return 0;
// }