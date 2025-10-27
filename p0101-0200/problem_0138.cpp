#include "stdio.h"
#include <unordered_map>

using namespace std;

class Node 
{
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) 
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};


class Solution 
{
public:
    //1. 哈希表
    //将每个节点的索引与random节点的索引建立映射
    //从而在进行深拷贝之后，可以通过索引映射关系重新获得新链表中每个节点random值
    Node* copyRandomList(Node* head)
    {
        unordered_map<uintptr_t, int> ptr2idx;
        unordered_map<int, int> random_map;
        unordered_map<int, Node*> new_idx2ptr;
        Node* new_head = new Node(0);
        Node* dummy = new_head;

        int index = 0;
        Node* temp = head;
        while (head)
        {
            ptr2idx[uintptr_t(head)] = index;
            new_head->next = new Node(head->val);
            head = head->next;
            new_head = new_head->next;
            new_idx2ptr[index] = new_head;
            ++index;
        }

        index = 0;
        head = temp;
        while (head)
        {
            if (head->random != nullptr)
            {
                random_map[index] = ptr2idx[uintptr_t(head->random)];
            }
            head = head->next;
            ++index;
        }

        index = 0;
        new_head = dummy->next;
        while (new_head)
        {
            if (auto it = random_map.find(index); it != random_map.end())
            {
                new_head->random = new_idx2ptr[it->second];
            }
            new_head = new_head->next;
            ++index;
        }

        return dummy->next;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     // [[7,null],[13,0],[11,4],[10,2],[1,0]]
//     Node* node1_1 = new Node(7);
//     Node* node1_2 = new Node(13);
//     Node* node1_3 = new Node(11);
//     Node* node1_4 = new Node(10);
//     Node* node1_5 = new Node(1);
//     node1_1->next = node1_2;
//     node1_2->next = node1_3;
//     node1_3->next = node1_4;
//     node1_4->next = node1_5;
//     node1_2->random = node1_1;
//     node1_3->random = node1_5;
//     node1_4->random = node1_3;
//     node1_5->random = node1_1;
//     Node* result = s.copyRandomList(node1_1);
    
//     // [[1,1],[2,1]]
//     Node* node2_1 = new Node(1);
//     Node* node2_2 = new Node(2);
//     node2_1->next = node2_2;
//     node2_1->random = node2_2;
//     node2_2->random = node2_2;
//     result = s.copyRandomList(node2_1);

//     // [[3,null],[3,0],[3,null]]
//     Node* node3_1 = new Node(3);
//     Node* node3_2 = new Node(3);
//     Node* node3_3 = new Node(3);
//     node3_1->next = node3_2;
//     node3_2->next = node3_3;
//     node3_2->random = node3_1;
//     result = s.copyRandomList(node3_1);

//     return 0;
// }