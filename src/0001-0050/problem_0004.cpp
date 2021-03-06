#include <stdio.h>
#include <vector>
#include <algorithm>

// https://leetcode-cn.com/problems/median-of-two-sorted-arrays/


class Solution
{
public:

	// 根据2个数组的长度算出中间值的索引，以升序分别从2个数组中取值，递增索引，直到找到中间值
	double FindMedianSortedArrays(const std::vector<int>& nums1, const std::vector<int>& nums2) 
	{
		int even_flag = (nums1.size() + nums2.size()) % 2 == 0 ? 1 : 0;
		int previous_num = 0;
		int current_num = 0;
		int middle_index = (nums1.size() + nums2.size()) / 2;
		int index = -1;

		for (size_t i = 0, j = 0; ; )
		{
			if (i < nums1.size() && j < nums2.size())
			{
				if (nums1[i] < nums2[j])
				{
					current_num = nums1[i++];
				}
				else
				{
					current_num = nums2[j++];
				}
			}
			else if (i < nums1.size())
			{
				current_num = nums1[i++];
			}
			else if (j < nums2.size())
			{
				current_num = nums2[j++];
			}
			else
			{
				break;
			}

			if (++index == middle_index)
			{
				return even_flag == 1 ? (previous_num + current_num) / 2.0f : current_num;
			}

			previous_num = current_num;
		}

		return 0;
	}

	// 假设有2个已排序好的数组A，B长度分别为m，n，如果将这两个数组合并在一起，升序排列后得到新的数组，一定可以平均分成两部分(如果总长度为奇数中间就会多一个数)
	// 这时候就一定会有两个分割点索引i，j，将数组A和B分别从i，j位置分成左右两个部分
	// A左 + B左构成新数组的左半部分，A右 + B右构成新数组的右半部分，如果A和B的总长度为偶数的话，这两部分长度相同，如果为奇数的话，就让左边的长度比右边多1
	// 在进行了这样的拆分之后，可以保证A左和B左中任意一个数永远 <= A右和B右中的任意一个数，即A[i - 1] <= B[j] && B[j - 1] <= A[i]，举例
	// A: 1 4 5 9 11 i为3(以0开始)，A左为 1 4 5，A右为9 11 
	// B: 2 3 6 8 10 j为2(以0开始)，B左为 2 3，B右为6 8 10
	// 最终组成的数组为 1 2 3 4 5 6 8 9 10 11，中位数位为 (5 + 6) / 2 = 5.5
	// 
	// 由此结论我们可以推导出一个公式 i + j = m - i + n - j(如果m+n为奇数，这里等号右边需要+1)，即j = (m + n + 1) / 2 - i，其中+1是为了处理m+n为奇数时的情况
	// 这个公式有一个要求，m <= n，即数组A应该为长度较小的那一个，因为 0 <= i < m，如果m > n，可能会导致j为负数
	// 之后就可以对数组A(长度较小的)进行二分查找了，找到合适的i，并通过公式得到相应的j，根据结果推断下一次二分查找的方向或是得出结果
	// 二分查找中只会遇到三种情况:
	// 
	// 1: (i == 0 || j == n || A[i - 1] <= B[j]) && (j == 0 || i == m || B[j - 1] <= A[i])，A左的最大值小于等于B右的最小值，B左的最大值小于等于A右的最小值，
	// 表示找到正确结果，考虑到边界情况可能遇到i - 1，i，j - 1，j的索引值无效，加上额外判断条件
	//
	// 2: i > 0 && j < len2 && A[i - 1] > B[j]，当前的i值过大，i需要向左移动，找到更小的值(数组是按升序排列)，根据求j公式相应的j会更大，找到更大的值
	// 将下一次二分查找的区间定位到左半区，同样需要考虑边界
	//
	// 3: j > 0 && i < len1 && B[j - 1] > A[i]，当前的i值过小，i需要向右移动，找到更大的值，根据求j公式相应的j会更小，找到更小的值
	// 将下一次二分查找的区间定位到右半区，同样需要考虑边界
	// 
	// 不断进行二分查找，直到找到结果或者循环结束，得到相应的i，j，如果m + n为奇数，则中位数位max(A[i - 1], B[j - 1])，此时也需要注意边界，如果i == 0或j == 0则要取另外一个值
	// 如果m + n为偶数，则取(max(A[i - 1], B[j - 1]) + min(A[i], B[j])) / 2，同样如果有边界问题的话，取另一个值
	double FindMedianSortedArraysBinarySerach(const std::vector<int>& nums1, const std::vector<int>& nums2)
	{
		if (nums1.size() > nums2.size())
		{
			return FindMedianSortedArraysBinarySerach(nums2, nums1);
		}

		int len1 = nums1.size();
		int len2 = nums2.size();

		int low = 0;
		int high = len1;
		int i = 0;
		int j = 0;

		while (low <= high)
		{
			i = (low + high) / 2;
			j = (len1 + len2 + 1) / 2 - i;
			
			if ((i == 0 || j == len2 || nums1[i - 1] <= nums2[j]) &&
				(i == len1 || j == 0 || nums2[j - 1] <= nums1[i]))
			{
				break;
			}
			else if (i > 0 && j < len2 && nums1[i - 1] > nums2[j])
			{
				high = i - 1;
			}
			else if (j > 0 && i < len1 && nums2[j - 1] > nums1[i])
			{
				low = i + 1;
			}
		}

		int left_max = 0;
		if (i == 0)
		{
			left_max = nums2[j - 1];
		}
		else if (j == 0)
		{
			left_max = nums1[i - 1];
		}
		else
		{
			left_max = std::max(nums1[i - 1], nums2[j - 1]);
		}

		if ((len1 + len2) % 2 == 1)
		{
			return left_max;
		}

		int right_min = 0;
		if (i == len1)
		{
			right_min = nums2[j];
		}
		else if (j == len2)
		{
			right_min = nums1[i];
		}
		else
		{
			right_min = std::min(nums1[i], nums2[j]);
		}

		return (left_max + right_min) / 2.0f;
	}
};

//int main(int argc, char** argv)
//{
//	Solution s;
//	std::vector<int> nums1;
//	std::vector<int> nums2 = {1};
//
//	double ret = s.FindMedianSortedArraysBetter(nums1, nums2);
//
//	return 0;
//
//}