#include <vector>

using namespace std;

// https://leetcode.cn/problems/remove-element/

class Solution 
{
public:
    //1. 双指针
    //使用一个单独的指针指向数组头部，然后用另外一个指针遍历数组，遇到与val不同的值则根据第一个指针赋值到数组中
    //并指向下一个位置，否则就略过，数组遍历结束后，前n个元素即所有不等于val的元素
    int removeElement(vector<int>& nums, int val) 
    {
        int n = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            if (nums[i] != val)
            {
                nums[n++] = nums[i];
            }
        }
        return n;
    }

    //2. 反向指针
    //双指针的另一种处理方式，跟方法一差不多，不过第二个指针指向了尾部，在遍历数组的过程中将与val相同的元素与尾部元素互换
    //并且将尾部指针往前挪，数组遍历只能遍历到尾指针之前，因为尾指针之后存储的都是需要排除的元素
    int removeElementTailPointer(vector<int>& nums, int val)
    {
        int tail = nums.size();
        for (int i = 0; i < tail; )
        {
            if (nums[i] == val)
            {
                nums[i] = nums[--tail];
            }
            else
            {
                ++i;
            }
        }
        return tail;
    }
};

// int main(int argc, char** argv) 
// {
//     Solution s;
    
//     vector<int> nums = {3, 2, 2, 3};
//     int val = 3;
//     int result = s.removeElementTailPointer(nums, val);

//     nums = {0, 1, 2, 2, 3, 0, 4, 2};
//     val = 2;
//     result = s.removeElementTailPointer(nums, val);

//     return 0;
// }