#include <stdio.h>
#include <vector>

// https://leetcode.cn/problems/kth-smallest-element-in-a-bst/

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
    //中序遍历的结果数组是升序的，遍历k个节点之后，结束递归，然后从数组中取出第k个节点，即为第k小的值
    int kthSmallest(TreeNode* root, int k) 
    {
        if (root == nullptr || k <= 0)
        {
            return 0;
        }

        vector<int> values;
        this->recursive(root, k, values);
        if (k <= values.size())
        {
            return values[k-1];
        }
        return 0;
    }

    void recursive(TreeNode* node, int k, vector<int>& values)
    {
        if (node->left != nullptr)
        {
            this->recursive(node->left, k, values);
            if (values.size() >= k)
            {
                return;
            }
        }
        
        values.push_back(node->val);
        if (values.size() >= k)
        {
            return;
        }

        if (node->right != nullptr)
        {
            this->recursive(node->right, k, values);
        }
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: root = [3,1,4,null,2], k = 1
//     //输出: 1
//     TreeNode* n1_1 = new TreeNode(3);
//     TreeNode* n1_2 = new TreeNode(1);
//     TreeNode* n1_3 = new TreeNode(4);
//     TreeNode* n1_4 = new TreeNode(2);
//     n1_1->left = n1_2;
//     n1_1->right = n1_3;
//     n1_2->right = n1_4;
//     int result = s.kthSmallest(n1_1, 1);
    
//     //输入: root = [5,3,6,2,4,null,null,1], k = 3
//     //输出: 3
//     TreeNode* n2_1 = new TreeNode(5);
//     TreeNode* n2_2 = new TreeNode(3);
//     TreeNode* n2_3 = new TreeNode(6);
//     TreeNode* n2_4 = new TreeNode(2);
//     TreeNode* n2_5 = new TreeNode(4);
//     TreeNode* n2_6 = new TreeNode(1);
//     n2_1->left = n2_2;
//     n2_1->right =  n2_3;
//     n2_2->left = n2_4;
//     n2_2->right = n2_5;
//     n2_4->left = n2_6;
//     result = s.kthSmallest(n2_1, 3);

//     return 0;
// }