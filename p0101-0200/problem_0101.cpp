#include <stdio.h>

// https://leetcode.cn/problems/symmetric-tree/

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
    //核心思路是通过递归函数来比较左右子树是否对称，在比较下一层子树的时候，需要左子树跟右子树比，右子树跟左子树比，才能判断出是否堆成
    //递归函数的判断条件列在下方，按照顺序进行判断
    // - 如果左右子树都为空，则表示对称，直接返回
    // - 如果左右子树中一个为空，一个非空，则表示不对称，直接返回
    // - 如果左右子树当前根节点的值不同，则表示不对称，直接返回
    // - 如果左子树的右节点和右子树的左节点不对称，则左右子树不对称，直接返回
    // - 最后判断左子树的左节点和右子树的右节点是否堆成，如果对称，则表示左右子树对称
    bool isSymmetric(TreeNode* root) 
    {
        if (root == nullptr)
        {
            return true;
        }
        return this->isSymmetricTwoNode(root->left, root->right);
    }
    
    bool isSymmetricTwoNode(TreeNode* left, TreeNode* right)
    {
        int count = 0;
        if (left != nullptr)
        {
            ++count;
        }
        if (right != nullptr)
        {
            ++count;
        }
        switch (count)
        {
            case 0:
            return true;
            case 1:
            return false;
        }
        if (left->val != right->val)
        {
            return false;
        }
        
        bool is_symmetric = this->isSymmetricTwoNode(left->right, right->left);
        if (!is_symmetric)
        {
            return false;
        }

        return this->isSymmetricTwoNode(left->left, right->right);
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;
//     TreeNode* n1_1 = new TreeNode(1);
//     TreeNode* n1_2 = new TreeNode(2);
//     TreeNode* n1_3 = new TreeNode(2);
//     TreeNode* n1_4 = new TreeNode(3);
//     TreeNode* n1_5 = new TreeNode(4);
//     TreeNode* n1_6 = new TreeNode(4);
//     TreeNode* n1_7 = new TreeNode(3);
//     n1_1->left = n1_2;
//     n1_1->right = n1_3;
//     n1_2->left = n1_4;
//     n1_2->right = n1_5;
//     n1_3->left = n1_6;
//     n1_3->right = n1_7;
//     bool result = s.isSymmetric(n1_1);

//     TreeNode* n2_1 = new TreeNode(1);
//     TreeNode* n2_2 = new TreeNode(2);
//     TreeNode* n2_3 = new TreeNode(2);
//     TreeNode* n2_4 = new TreeNode(3);
//     TreeNode* n2_5 = new TreeNode(3);
//     n2_1->left = n2_2;
//     n2_1->right = n2_3;
//     n2_2->right = n2_4;
//     n2_3->right = n2_5;
//     result = s.isSymmetric(n2_1);

//     return 0;
// }