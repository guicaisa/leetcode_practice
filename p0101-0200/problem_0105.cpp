#include <vector>
#include <unordered_map>

// https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

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
    //1. 哈希表+递归
    //由于所有节点的val值都是不重复的，所以先用哈希表为每个值与其在先序遍历数组和中序遍历数组中的位置建立映射关系
    //将问题分解为构造每个节点，构造每个节点的过程中，又分为构造该节点的左子树和右子树，从而形成递归调用
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
    {

        this->preorder_map_.clear();
        for (int i = 0; i < preorder.size(); ++i)
        {
            this->preorder_map_[preorder[i]] = i;
        }
        this->inorder_map_.clear();
        for (int i = 0; i < inorder.size(); ++i)
        {
            this->inorder_map_[inorder[i]] = i;
        }

        int most_right_pre_idx = 0;
        return this->processRootNode(0, 0, preorder.size()-1, preorder, inorder, most_right_pre_idx);
    }

    TreeNode* processRootNode(int pre_idx, int in_left, int in_right, vector<int>& preorder, vector<int>& inorder, int& most_right_pre_idx)
    {
        int val = preorder[pre_idx];
        TreeNode* root = new TreeNode(val);
        most_right_pre_idx = max(most_right_pre_idx, pre_idx);
        //在前序遍历中为最后一个值，则表示该节点无任何左右子树
        if (pre_idx >= preorder.size() - 1)
        {
            return root;
        }
        int in_idx = this->inorder_map_[val]; //在中序遍历中的索引
        int next_val = preorder[pre_idx+1]; //前序遍历中的下一个值，要么是左子树的第一个值，要么是右子树的第一个值
        int next_val_in_idx = this->inorder_map_[next_val]; //该值在中序遍历中的索引
        if (next_val_in_idx < in_idx) //索引小于当前值，则表示该值为左子树的第一个值
        {
            //处理左子树
            if (in_left <= next_val_in_idx && next_val_in_idx <= in_right)
            {
                int cur_most_right_pre_idx = 0;
                TreeNode* left_node = this->processRootNode(pre_idx+1, in_left, in_idx-1, preorder, inorder, cur_most_right_pre_idx);
                most_right_pre_idx = max(most_right_pre_idx, cur_most_right_pre_idx);
                root->left = left_node;
                //处理完左子树后，获得左子树上在前序遍历中最右的一个值的索引，在这个值基础上获得下一个值，即可能存在的右节点
                if (cur_most_right_pre_idx + 1 < preorder.size())
                {
                    next_val = preorder[cur_most_right_pre_idx+1];
                    next_val_in_idx = this->inorder_map_[next_val];
                    if (next_val_in_idx > in_idx && in_left <= next_val_in_idx && next_val_in_idx <= in_right)
                    {
                        int temp = 0;
                        TreeNode* right_node = this->processRootNode(cur_most_right_pre_idx+1, in_idx+1, in_right, preorder, inorder, temp);
                        root->right = right_node;
                        most_right_pre_idx = max(most_right_pre_idx, temp);
                    }
                }
            }
            return root;
        }
        //索引大于当前值，则表示该值为右子树的第一个值，处理右子树
        if (next_val_in_idx > in_idx && in_left <= next_val_in_idx && next_val_in_idx <= in_right)
        {
            int temp = 0;
            TreeNode* right_node = this->processRootNode(pre_idx+1, in_idx+1, in_right, preorder, inorder, temp);
            root->right = right_node;
            most_right_pre_idx = max(most_right_pre_idx, temp);
        }
        return root;
    }

private:
    unordered_map<int, int> preorder_map_;
    unordered_map<int, int> inorder_map_;
};

// int main(int argc, char** argv)
// {
//     Solution s;
//     vector<int> preorder = {3, 9, 20 ,15, 7};
//     vector<int> inorder = {9, 3, 15, 20, 7};
//     TreeNode* result = s.buildTree(preorder, inorder);

//     preorder = {-1};
//     inorder = {-1};
//     result = s.buildTree(preorder, inorder);

//     preorder = {3, 1, 2, 4};
//     inorder = {1, 2, 3, 4};
//     result = s.buildTree(preorder, inorder);

//     preorder = {3, 2, 1, 4};
//     inorder = {1, 2, 3, 4};
//     result = s.buildTree(preorder, inorder);
    
//     return 0;
// }