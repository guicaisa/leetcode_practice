#include <string>
#include <vector>

// https://leetcode.cn/problems/implement-trie-prefix-tree/

using namespace std;

class Trie 
{
public:
    Trie() : nodes_(26), end_(false)
    {
        
    }
    
    void insert(string word) 
    {
        Trie* node = this;
        for (int i = 0; i < word.size(); ++i)
        {
            char ch = word[i];
            int idx = ch - 'a';
            Trie* next_node = node->nodes_[idx];
            if (next_node == nullptr)
            {
                next_node = new Trie();
                node->nodes_[idx] = next_node;
            }
            node = next_node;
        }
        node->end_ = true;
    }
    
    bool search(string word) 
    {
        Trie* node = this->findPrefix(word);
        return node != nullptr && node->end_;
    }
    
    bool startsWith(string prefix) 
    {
        return this->findPrefix(prefix) != nullptr;
    }

private:
    Trie* findPrefix(string prefix)
    {
        Trie* node = this;
        for (int i = 0; i < prefix.size(); ++i)
        {
            char ch = prefix[i];
            int idx = ch - 'a';
            Trie* next_node = node->nodes_[idx];
            if (next_node == nullptr)
            {
                return nullptr;
            }
            node = next_node;
        }

        return node;
    }

    void addNode(Trie* node, int idx)
    {
        this->nodes_[idx] = node;
    }

private:
    vector<Trie*> nodes_;
    bool end_;
};

// int main(int argc, char** argv)
// {
//     //输入
//     //["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
//     //[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
//     //输出
//     //[null, null, true, false, true, null, true]

//     Trie trie;
//     trie.insert("apple");
//     bool result = trie.search("apple");   // 返回 True
//     result = trie.search("app");     // 返回 False
//     result = trie.startsWith("app"); // 返回 True
//     trie.insert("app");
//     result = trie.search("app");     // 返回 True

//     return 0;
// }