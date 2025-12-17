#include <vector>
#include <unordered_map>
#include <algorithm>

// https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) 
    {
        vector<int> preorder = postorder;
        reverse(preorder.begin(), preorder.end());
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
        int next_val = preorder[pre_idx+1]; //前序遍历中的下一个值，要么是右子树的第一个值，要么是左子树的第一个值
        int next_val_in_idx = this->inorder_map_[next_val]; //该值在中序遍历中的索引
        if (next_val_in_idx > in_idx) //索引小于当前值，则表示该值为右子树的第一个值
        {
            //处理右子树
            if (in_left <= next_val_in_idx && next_val_in_idx <= in_right)
            {
                int cur_most_right_pre_idx = 0;
                TreeNode* right_node = this->processRootNode(pre_idx+1, in_idx+1, in_right, preorder, inorder, cur_most_right_pre_idx);
                most_right_pre_idx = max(most_right_pre_idx, cur_most_right_pre_idx);
                root->right = right_node;
                //处理完右子树后，获得右子树上在前序遍历中最右的一个值的索引，在这个值基础上获得下一个值，即可能存在的左节点
                if (cur_most_right_pre_idx + 1 < preorder.size())
                {
                    next_val = preorder[cur_most_right_pre_idx+1];
                    next_val_in_idx = this->inorder_map_[next_val];
                    if (next_val_in_idx < in_idx && in_left <= next_val_in_idx && next_val_in_idx <= in_right)
                    {
                        int temp = 0;
                        TreeNode* left_node = this->processRootNode(cur_most_right_pre_idx+1, in_left, in_idx-1, preorder, inorder, temp);
                        root->left = left_node;
                        most_right_pre_idx = max(most_right_pre_idx, temp);
                    }
                }
            }
            return root;
        }
        //索引小于当前值，则表示该值为左子树的第一个值，处理左子树
        if (next_val_in_idx < in_idx && in_left <= next_val_in_idx && next_val_in_idx <= in_right)
        {
            int temp = 0;
            TreeNode* left_node = this->processRootNode(pre_idx+1, in_left, in_idx-1, preorder, inorder, temp);
            root->left = left_node;
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

//     //输入: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
//     //输出: [3,9,20,null,null,15,7]
//     vector<int> inorder = {9, 3, 15, 20, 7};
//     vector<int> postorder = {9, 15, 7, 20, 3};
//     TreeNode* result = s.buildTree(inorder, postorder);

//     //输入: inorder = [-1], postorder = [-1]
//     //输出: [-1]
//     inorder = {-1};
//     postorder = {-1};
//     result = s.buildTree(inorder, postorder);

//     return 0;
// }