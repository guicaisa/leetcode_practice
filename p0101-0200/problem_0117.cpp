#include <stdio.h>

class Node 
{
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution
{
public:
    //1. 广度优先搜索
    //处理当前节点时，根据next指针进行遍历，处理同层所有节点，为下一层的节点建立好next链接关系
    //然后进入到下一层，继续处理下下层的next关系，直到树的底部，完成所有next链接操作
    Node* connect(Node* root) 
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        
        this->connectHorizon(root);
        return root;
    }

    bool connectHorizon(Node* node)
    {
        Node* pre_node = nullptr;
        Node* temp = node;
        while (temp)
        {
            if (temp->left != nullptr)
            {
                if (pre_node != nullptr)
                {
                    pre_node->next = temp->left;
                }
                pre_node = temp->left;
            }
            if (temp->right != nullptr)
            {
                if (pre_node != nullptr)
                {
                    pre_node->next = temp->right;
                }
                pre_node = temp->right;
            }
            temp = temp->next;
        }
        if (node->left != nullptr && this->connectHorizon(node->left))
        {
            return true;
        }
        if (node->right != nullptr && this->connectHorizon(node->right))
        {
            return true;
        }
        return false;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: root = [1,2,3,4,5,null,7]
//     //输出: [1,#,2,3,#,4,5,7,#]
//     Node* n1_1 = new Node(1);
//     Node* n1_2 = new Node(2);
//     Node* n1_3 = new Node(3);
//     Node* n1_4 = new Node(4);
//     Node* n1_5 = new Node(5);
//     Node* n1_6 = new Node(7);
//     n1_1->left = n1_2;
//     n1_1->right = n1_3;
//     n1_2->left = n1_4;
//     n1_2->right = n1_5;
//     n1_3->right = n1_6;
//     Node* result = s.connect(n1_1);

//     //输入: root = [-1,-7,9,null,null,-1,-7,null,8,-9]
//     //输出: []
//     Node* n2_1 = new Node(-1);
//     Node* n2_2 = new Node(-7);
//     Node* n2_3 = new Node(9);
//     Node* n2_4 = new Node(-1);
//     Node* n2_5 = new Node(-7);
//     Node* n2_6 = new Node(8);
//     Node* n2_7 = new Node(-9);
//     n2_1->left = n2_2;
//     n2_1->right = n2_3;
//     n2_3->left = n2_4;
//     n2_3->right = n2_5;
//     n2_4->right = n2_6;
//     n2_5->left = n2_7;
//     result = s.connect(n2_1);

//     return 0;
// }