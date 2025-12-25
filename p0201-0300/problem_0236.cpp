#include <stdio.h>
#include <vector>

// https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/

using namespace std;

struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution 
{
public:
    //1. 深度优先搜索
    //使用遍历进行深度优先搜索，分别保存从根节点到搜索到p/q两个节点这条链路上的所有节点
    //p/q都被找到之后结束搜索环节，比较两条链路上的节点，找到第一个不相同的节点，前一个相同的节点即未最近的祖先节点
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        this->p_nodes_.clear();
        this->q_nodes_.clear();
        this->find_p_ = false;
        this->find_q_ = false;
        this->recursive(root, p, q);
        TreeNode* result = nullptr;
        for (int i = 0, j = 0; i < this->p_nodes_.size() && j < this->q_nodes_.size(); ++i, ++j)
        {
            if (this->p_nodes_[i] == this->q_nodes_[j])
            {
                result = this->p_nodes_[i];
            }
            else
            {
                break;
            }
        }
        
        return result;
    }

    void recursive(TreeNode* node, TreeNode* p, TreeNode* q)
    {
        bool pop_p = false;
        bool pop_q = false;
        if (!this->find_p_)
        {
            this->p_nodes_.push_back(node);
            pop_p = true;
            if (node == p)
            {
                this->find_p_ = true;
            }
        }
        if (!this->find_q_)
        {
            this->q_nodes_.push_back(node);
            pop_q = true;
            if (node == q)
            {
                this->find_q_ = true;
            }
        }
        if (this->find_p_ && this->find_q_)
        {
            return;
        }
        if (node->left != nullptr)
        {
            this->recursive(node->left, p, q);
        }
        if (node->right != nullptr)
        {
            this->recursive(node->right, p, q);
        }
        if (this->find_p_ && this->find_q_)
        {
            return;
        }
        if (pop_p)
        {
            this->p_nodes_.pop_back();
        }
        if (pop_q)
        {
            this->q_nodes_.pop_back();
        }
    }

private:
    vector<TreeNode*> p_nodes_;
    vector<TreeNode*> q_nodes_;
    bool find_p_;
    bool find_q_;
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
//     //输出: 3
//     TreeNode* n1_1 = new TreeNode(3);
//     TreeNode* n1_2 = new TreeNode(5);
//     TreeNode* n1_3 = new TreeNode(1);
//     TreeNode* n1_4 = new TreeNode(6);
//     TreeNode* n1_5 = new TreeNode(2);
//     TreeNode* n1_6 = new TreeNode(0);
//     TreeNode* n1_7 = new TreeNode(8);
//     TreeNode* n1_8 = new TreeNode(7);
//     TreeNode* n1_9 = new TreeNode(4);
//     n1_1->left = n1_2;
//     n1_1->right = n1_3;
//     n1_2->left = n1_4;
//     n1_2->right = n1_5;
//     n1_3->left = n1_6;
//     n1_3->right = n1_7;
//     n1_5->left = n1_8;
//     n1_5->right = n1_9;
//     TreeNode* result = s.lowestCommonAncestor(n1_1, n1_2, n1_3);

//     //输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
//     //输出: 5
//     TreeNode* n2_1 = new TreeNode(3);
//     TreeNode* n2_2 = new TreeNode(5);
//     TreeNode* n2_3 = new TreeNode(1);
//     TreeNode* n2_4 = new TreeNode(6);
//     TreeNode* n2_5 = new TreeNode(2);
//     TreeNode* n2_6 = new TreeNode(0);
//     TreeNode* n2_7 = new TreeNode(8);
//     TreeNode* n2_8 = new TreeNode(7);
//     TreeNode* n2_9 = new TreeNode(4);
//     n2_1->left = n2_2;
//     n2_1->right = n2_3;
//     n2_2->left = n2_4;
//     n2_2->right = n2_5;
//     n2_3->left = n2_6;
//     n2_3->right = n2_7;
//     n2_5->left = n2_8;
//     n2_5->right = n2_9;
//     result = s.lowestCommonAncestor(n2_1, n2_2, n2_9);

//     //输入: root = [1,2], p = 1, q = 2
//     //输出: 1
//     TreeNode* n3_1 = new TreeNode(1);
//     TreeNode* n3_2 = new TreeNode(2);
//     n3_1->left = n3_2;
//     result = s.lowestCommonAncestor(n3_1, n3_1, n3_2);

//     return 0;
// }