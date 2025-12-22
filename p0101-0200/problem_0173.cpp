#include <stack>

// https://leetcode.cn/problems/binary-search-tree-iterator/

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

class BSTIterator 
{
public:
    BSTIterator(TreeNode* root) 
    {
        while (root != nullptr)
        {
            this->nodes_.push(root);
            TreeNode* left = root->left;
            root->left = nullptr;
            root = left;
        }
    }
    
    int next() 
    {
        if (!this->nodes_.empty())
        {
            while (1)
            {
                TreeNode* node = this->nodes_.top();
                if (node->left != nullptr)
                {
                    this->nodes_.push(node->left);
                    node->left = nullptr;
                    continue;
                }
                this->nodes_.pop();
                if (node->right != nullptr)
                {
                    this->nodes_.push(node->right);
                }
                return node->val;
            }
        }
        return 0;
    }
    
    bool hasNext() 
    {
        return this->nodes_.size() != 0;
    }

private:
    stack<TreeNode*> nodes_;
};

// int main(int argc, char** argv)
// {
//     //输入: ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
//     //      [[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
//     //输出:
//     //      [null, 3, 7, true, 9, true, 15, true, 20, false]
//     TreeNode* n1_1 = new TreeNode(7);
//     TreeNode* n1_2 = new TreeNode(3);
//     TreeNode* n1_3 = new TreeNode(15);
//     TreeNode* n1_4 = new TreeNode(9);
//     TreeNode* n1_5 = new TreeNode(20);
//     n1_1->left = n1_2;
//     n1_1->right = n1_3;
//     n1_3->left = n1_4;
//     n1_3->right = n1_5;
    
//     BSTIterator iter(n1_1);
//     int val = iter.next();
//     val = iter.next();
//     bool has = iter.hasNext();
//     val = iter.next();
//     has = iter.hasNext();
//     val = iter.next();
//     has = iter.hasNext();
//     val = iter.next();
//     has = iter.hasNext();

//     return 0;
// }