#include <stdio.h>
#include <algorithm>
#include <vector>

// https://leetcode.cn/problems/minimum-absolute-difference-in-bst/

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
    //1. 二叉树中序遍历
    //二叉树中序遍历的结果是一个递增的数组，只要比较相邻两个值的差值然后获取最小值即可
    int getMinimumDifference(TreeNode* root) 
    {
        if (root == nullptr)
        {
            return 0;
        }

        vector<int> values;
        this->recursive(root, values);
        int min_diff = INT_MAX;
        for (int i = 1; i < values.size(); ++i)
        {
            int diff = abs(values[i] - values[i-1]);
            min_diff = min(min_diff, diff);
        }
        return min_diff;
    }

    void recursive(TreeNode* node, vector<int>& values)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            values.push_back(node->val);
            return;
        }
        if (node->left != nullptr)
        {
            this->recursive(node->left, values);
        }
        values.push_back(node->val);
        if (node->right != nullptr)
        {
            this->recursive(node->right, values);
        }
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: root = [4,2,6,1,3]
//     //输出: 1
//     TreeNode* n1_1 = new TreeNode(4);
//     TreeNode* n1_2 = new TreeNode(2);
//     TreeNode* n1_3 = new TreeNode(6);
//     TreeNode* n1_4 = new TreeNode(1);
//     TreeNode* n1_5 = new TreeNode(3);
//     n1_1->left = n1_2;
//     n1_1->right = n1_3;
//     n1_2->left = n1_4;
//     n1_2->right = n1_5;
//     int result = s.getMinimumDifference(n1_1);

//     //输入: root = [1,0,48,null,null,12,49]
//     //输出: 1
//     TreeNode* n2_1 = new TreeNode(1);
//     TreeNode* n2_2 = new TreeNode(0);
//     TreeNode* n2_3 = new TreeNode(48);
//     TreeNode* n2_4 = new TreeNode(12);
//     TreeNode* n2_5 = new TreeNode(49);
//     n2_1->left = n2_2;
//     n2_1->right = n2_3;
//     n2_3->left = n2_4;
//     n2_3->right = n2_5;
//     result = s.getMinimumDifference(n2_1);

//     return 0;
// }