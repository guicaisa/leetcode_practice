#include <vector>

// https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/

using namespace std;

struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution 
{
public:
    //1. 递归+二分
    //通过二分查找确定当前根节点的值，将数组从中点一分为二，再递归调用函数分别处理左右子树的情况
    //并将结果保存在当前根节点的左右节点中即可
    TreeNode* sortedArrayToBST(vector<int>& nums) 
    {
        if (nums.size() == 0)
        {
            return nullptr;
        }    
        
        int mid = nums.size() / 2;
        TreeNode* node = new TreeNode(nums[mid]);

        vector<int> left_nums = vector<int>(nums.begin(), nums.begin() + mid);
        TreeNode* left = sortedArrayToBST(left_nums);
        node->left = left;

        vector<int> right_nums = vector<int>(nums.begin() + mid + 1, nums.end());
        TreeNode* right = sortedArrayToBST(right_nums);
        node->right = right;

        return node;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入：nums = [-10,-3,0,5,9]
//     //输出：[0,-3,9,-10,null,5]
//     vector<int> nums = {-10, -3, 0, 5, 9};
//     TreeNode* result = s.sortedArrayToBST(nums);

//     //输入：nums = [1,3]
//     //输出：[3,1]
//     nums = {1, 3};
//     result = s.sortedArrayToBST(nums);

//     return 0;
// }