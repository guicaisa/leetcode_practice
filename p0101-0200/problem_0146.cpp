#include <unordered_map>

// https://leetcode.cn/problems/lru-cache/

using namespace std;

struct ListNodeT {
    int key;
    int val;
    ListNodeT* pre;
    ListNodeT* next;
    ListNodeT(): key(0), val(0), pre(nullptr), next(nullptr) {}
    ListNodeT(int _key, int _value): key(_key), val(_value), pre(nullptr), next(nullptr) {}
};

// 1. 哈希表+双向链表
//哈希表用来存储每个键值对，每个键绑定一个节点，并连接在双向链表中
//每次get或者put操作了某个键，则将该将移到双向链表的尾部，视为最近操作的键
//当put新键超出容量上限时，将双向链表头部节点删除，并从哈希表中删除，头部节点即为最近最长时间未使用的键
class LRUCache 
{
public:
    LRUCache(int capacity) 
    {
        this->capacity_ = capacity;
        this->head_ = nullptr;
        this->tail_ = nullptr;
    }
    
    int get(int key) 
    {
        if (auto iter = this->key_to_nodes_.find(key); iter != this->key_to_nodes_.end())
        {
            ListNodeT* node = iter->second;
             if (node != this->tail_)
            {
                ListNodeT* pre = node->pre;
                ListNodeT* next = node->next;
                if (pre)
                {
                    pre->next = next;
                }
                if (next)
                {
                    next->pre = pre;
                }
                this->tail_->next = node;
                node->pre = this->tail_;
                node->next = nullptr;
                this->tail_ = node;
                if (this->head_ == node)
                {
                    this->head_ = next;
                }
            }
            return node->val;
        }
        return -1;
        
    }
    
    void put(int key, int value) 
    {
        auto iter = this->key_to_nodes_.find(key);
        if (iter == this->key_to_nodes_.end())
        {
            ListNodeT* node = new ListNodeT (key, value);
            this->key_to_nodes_[key] = node;
            if (this->tail_ == nullptr)
            {
                this->tail_ = node;
                this->head_ = node;
            }
            else
            {
                node->pre = this->tail_;
                this->tail_->next = node;
                this->tail_ = node;
            }
            if (this->key_to_nodes_.size() > this->capacity_)
            {
                this->key_to_nodes_.erase(this->head_->key);
                ListNodeT* next = this->head_->next;
                next->pre = nullptr;
                this->head_ = next;
            }
        }
        else
        {
            ListNodeT* node = iter->second;
            node->val = value;
            if (node != this->tail_)
            {
                ListNodeT* pre = node->pre;
                ListNodeT* next = node->next;
                if (pre)
                {
                    pre->next = next;
                }
                if (next)
                {
                    next->pre = pre;
                }
                this->tail_->next = node;
                node->pre = this->tail_;
                node->next = nullptr;
                this->tail_ = node;
                if (this->head_ == node)
                {
                    this->head_ = next;
                }
            }
        }
    }

private:
    int capacity_;
    ListNodeT* head_;
    ListNodeT* tail_;
    unordered_map<int, ListNodeT*> key_to_nodes_;
};

// int main(int argc, char** argv)
// {
//     LRUCache lRUCache = LRUCache(2);
//     lRUCache.put(1, 1); // 缓存是 {1=1}
//     lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
//     int ret = lRUCache.get(1);    // 返回 1
//     lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
//     ret = lRUCache.get(2);    // 返回 -1 (未找到)
//     lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
//     ret = lRUCache.get(1);    // 返回 -1 (未找到)
//     ret = lRUCache.get(3);    // 返回 3
//     ret =lRUCache.get(4);    // 返回 4

//     return 0;
// }