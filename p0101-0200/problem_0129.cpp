#include <stdio.h>

// https://leetcode.cn/problems/sum-root-to-leaf-numbers/

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
    int sumNumbers(TreeNode* root) 
    {
        if (root == nullptr)
        {
            return 0;
        }   
        return this->recursive(root, 0);
    }

    int recursive(TreeNode* node, int cur)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            return node->val + cur;
        }
        int left_num = 0;
        int right_num = 0;
        cur = (cur + node->val) * 10;
        if (node->left != nullptr)
        {
            left_num = this->recursive(node->left, cur); 
        }
        if (node->right != nullptr)
        {
            right_num = this->recursive(node->right, cur);
        }
        return left_num + right_num;
    }
};

int main(int argc, char** argv)
{
    Solution s;

    //输入: root = [1,2,3]
    //输出: 25
    TreeNode* n1_1 = new TreeNode(1);
    TreeNode* n1_2 = new TreeNode(2);
    TreeNode* n1_3 = new TreeNode(3);
    n1_1->left = n1_2;
    n1_1->right = n1_3;
    int result = s.sumNumbers(n1_1);

    //输入: root = [4,9,0,5,1]
    //输出: 1026
    TreeNode* n2_1 = new TreeNode(4);
    TreeNode* n2_2 = new TreeNode(9);
    TreeNode* n2_3 = new TreeNode(0);
    TreeNode* n2_4 = new TreeNode(5);
    TreeNode* n2_5 = new TreeNode(1);
    n2_1->left = n2_2;
    n2_1->right = n2_3;
    n2_2->left = n2_4;
    n2_2->right = n2_5;
    result = s.sumNumbers(n2_1);

    return 0;
}