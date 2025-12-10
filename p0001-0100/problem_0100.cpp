#include <stdio.h>

// https://leetcode.cn/problems/same-tree/

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
    //核心思路是通过递归的方式，判断每个树的左右子树是否相同，往下递进，再将比较结果向上传递，得到最终结果
    //主要的几个判断条件罗列在如下，按顺序进行判断
    // - 如果两个树均为空树，则是相同的树，直接返回
    // - 如果两个树一个为空树，一个非空，则不是相同的树，直接返回
    // - 如果两个树都是非空，但是val不相同，则不是相同的树，直接返回
    // - 比较两个树的左子树是否相同，如果不同则不是相同的树，直接返回
    // - 比较两个树的右子树是否相同，如果相同则表示是相同的树，返回结果
    bool isSameTree(TreeNode* p, TreeNode* q) 
    {
        //都是空树，相同
        if (p == nullptr && q == nullptr)
        {
            return true;
        }
        //一个是空树，一个非空，不同
        if ((p != nullptr && q == nullptr) || (p == nullptr && q != nullptr))
        {
            return false;
        }    
        //都是非空树，但是val不同，不同
        if (p->val != q->val)
        {
            return false;
        }
        //比较左子树是否相同，如果不同直接返回，无需判断右子树
        bool same = this->isSameTree(p->left, q->left);
        if (!same) 
        {
            return false;
        }
        //比较右子树是否相同
        return this->isSameTree(p->right, q->right);
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;
//     TreeNode* n1_l1 = new TreeNode(1);
//     TreeNode* n1_l2 = new TreeNode(2);
//     TreeNode* n1_l3 = new TreeNode(3);
//     n1_l1->left = n1_l2;
//     n1_l1->right = n1_l3;
//     TreeNode* n1_r1 = new TreeNode(1);
//     TreeNode* n1_r2 = new TreeNode(2);
//     TreeNode* n1_r3 = new TreeNode(3);
//     n1_r1->left = n1_r2;
//     n1_r1->right = n1_r3;
//     bool result = s.isSameTree(n1_l1, n1_r1);

//     TreeNode* n2_l1 = new TreeNode(1);
//     TreeNode* n2_l2 = new TreeNode(2);
//     n2_l1->left = n2_l2;
//     TreeNode* n2_r1 = new TreeNode(1);
//     TreeNode* n2_r2 = new TreeNode(2);
//     n2_r1->right = n2_r2;
//     result = s.isSameTree(n2_l1, n2_r1);

//     TreeNode* n3_l1 = new TreeNode(1);
//     TreeNode* n3_l2 = new TreeNode(2);
//     TreeNode* n3_l3 = new TreeNode(3);
//     n3_l1->left = n3_l2;
//     n3_l1->right = n3_l3;
//     TreeNode* n3_r1 = new TreeNode(1);
//     TreeNode* n3_r2 = new TreeNode(1);
//     TreeNode* n3_r3 = new TreeNode(2);
//     n3_r1->left = n3_r2;
//     n3_r1->right = n3_r3;
//     result = s.isSameTree(n3_l1, n3_r1);

//     return 0;
// }