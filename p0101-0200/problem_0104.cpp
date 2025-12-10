#include <stdio.h>
#include <algorithm>

// https://leetcode.cn/problems/maximum-depth-of-binary-tree/

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
    //1. 递归
    //将当前节点的左右子节点传入递归函数中并获得左右子树的深度
    //获得左右子树的较大值，再加上自身节点的1，然后返回树的最大深度
    int maxDepth(TreeNode* root) 
    {
        if (root == nullptr)
        {
            return 0;
        }
        int left_depth = root->left ? this->maxDepth(root->left) : 0;
        int right_depth = root->right ? this->maxDepth(root->right) : 0;
        return max(left_depth, right_depth) + 1;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;
//     TreeNode* n1_1 = new TreeNode(3);
//     TreeNode* n1_2 = new TreeNode(9);
//     TreeNode* n1_3 = new TreeNode(20);
//     TreeNode* n1_4 = new TreeNode(15);
//     TreeNode* n1_5 = new TreeNode(7); 
//     n1_1->left = n1_2;
//     n1_1->right = n1_3;
//     n1_3->left = n1_4;
//     n1_3->right = n1_5;
//     int result = s.maxDepth(n1_1);

//     TreeNode* n2_1 = new TreeNode(1);
//     TreeNode* n2_2 = new TreeNode(2);
//     n2_1->right = n2_2;
//     result = s.maxDepth(n2_1);

//     return 0;
// }