#include <vector>

using namespace std;

// https://leetcode.cn/problems/merge-sorted-array/

class Solution 
{
public:
    //1. 归并排序
    //使用双指针分别遍历nums1和nums2，比较两个值，将较小的放入结果数组中，需要使用额外的内存空间
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) 
    {
        vector<int> temp_nums = nums1;
        int t = 0;
        int j = 0;
        for (int i = 0; i < nums1.size(); ++i)
        {
            //temp_nums已遍历结束，直接将nums2中的元素放入结果数组中
            //temp_nums由nums1复制得来，只有前m个元素才是有效元素
            if (t >= m)
            {
                nums1[i] = nums2[j++];
                continue;
            }
            //nums2已遍历结束，直接将temp_nums中的元素放入结果数组中
            if (j >= nums2.size())
            {
                nums1[i] = temp_nums[t++];
                continue;
            }
            //否则比较大小，将较小的元素放入结果数组中
            nums1[i] = nums2[j] < temp_nums[t] ? nums2[j++] : temp_nums[t++];
        }
    }

    //2. 反向双指针
    //倒序遍历，使用双指针指向nums1中的前m个元素和nums2中的前n个元素，比较两个值，将较大的从尾部开始放入结果数组中
    //不需要使用额外的空间，由于nums1的后n个元素都为无效元素，nums2长度为n，所以从尾部开始赋值不会出现有效元素被覆盖的情况
    void mergeReverseTowPointers(vector<int>& nums1, int m, vector<int>& nums2, int n)
    {
        int i = m - 1; //nums1从前m个元素开始
        int j = n - 1;
        for (int index = nums1.size() - 1; index >= 0; --index)
        {
            //nums1已遍历结束，直接将nums2的元素放入结果数组中
            if (i < 0)
            {
                nums1[index] = nums2[j--];
                continue;
            }
            //nums2已遍历结束，直接将nums1的元素放入结果数组中
            if (j < 0)
            {
                nums1[index] = nums1[i--];
                continue;
            }
            //否则比较大小，将较大的元素放入结果数组中
            nums1[index] = nums1[i] > nums2[j] ? nums1[i--] : nums2[j--];
        }
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     vector<int> nums1 = {1, 2, 3, 0, 0, 0};
//     vector<int> nums2 = {2, 5, 6};
//     int m = 3;
//     int n = 3;
//     s.mergeReverseTowPointers(nums1, m, nums2, n);

//     nums1 = {1};
//     nums2 = {};
//     m = 1;
//     n = 0;
//     s.mergeReverseTowPointers(nums1, m, nums2, n);
  
//     nums1 = {0};
//     nums2 = {1};
//     m = 0;
//     n = 1;
//     s.mergeReverseTowPointers(nums1, m, nums2, n);

//     return 0;
// }