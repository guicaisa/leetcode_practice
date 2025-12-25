#include <vector>

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
    vector<double> averageOfLevels(TreeNode* root) 
    {
        if (root == nullptr)
        {
            return vector<double>();
        }
        
        vector<double> results;
        vector<TreeNode*> layer_nodes = {root};
        vector<TreeNode*> next_layer_nodes;
        while (layer_nodes.size() > 0)
        {
            double sum = 0;
            for (int i = 0; i < layer_nodes.size(); ++i)
            {
                TreeNode* node = layer_nodes[i];
                if (node->left != nullptr)
                {
                    next_layer_nodes.push_back(node->left);
                }
                if (node->right != nullptr)
                {
                    next_layer_nodes.push_back(node->right);
                }
                sum += node->val;
            }
            double result = sum / layer_nodes.size();
            results.push_back(result);
            
            layer_nodes = next_layer_nodes;
            next_layer_nodes.clear();
        }

        return results;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: root = [3,9,20,null,null,15,7]
//     //输出: [3.00000,14.50000,11.00000]
//     TreeNode* n1_1 = new TreeNode(3);
//     TreeNode* n1_2 = new TreeNode(9);
//     TreeNode* n1_3 = new TreeNode(20);
//     TreeNode* n1_4 = new TreeNode(15);
//     TreeNode* n1_5 = new TreeNode(7);
//     n1_1->left = n1_2;
//     n1_1->right = n1_3;
//     n1_3->left = n1_4;
//     n1_3->right = n1_5;
//     vector<double> results = s.averageOfLevels(n1_1);

//     //输入: root = [3,9,20,15,7]
//     //输出: [3.00000,14.50000,11.00000]
//     TreeNode* n2_1 = new TreeNode(3);
//     TreeNode* n2_2 = new TreeNode(9);
//     TreeNode* n2_3 = new TreeNode(20);
//     TreeNode* n2_4 = new TreeNode(15);
//     TreeNode* n2_5 = new TreeNode(7);
//     n2_1->left = n2_2;
//     n2_1->right = n2_3;
//     n2_3->left = n2_4;
//     n2_3->right = n2_5;
//     results = s.averageOfLevels(n2_1);

//     return 0;
// }