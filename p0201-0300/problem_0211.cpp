#include <string>
#include <vector>
#include <unordered_map>

// https://leetcode.cn/problems/design-add-and-search-words-data-structure/

using namespace std;

class WordDictionary 
{
public:
    WordDictionary() : end_(false)
    {
        
    }
    
    void addWord(string word) 
    {
        WordDictionary* node = this;
        for (int i = 0; i < word.size(); ++i)
        {
            char ch = word[i];
            auto it = node->nodes_.find(ch);
            if (it == node->nodes_.end())
            {
                WordDictionary* next_node = new WordDictionary();
                node->nodes_[ch] = next_node;
                node = next_node;
            } 
            else
            {
                node = it->second;
            }
        }
        node->end_ = true;
    }
    
    bool search(string word) 
    {
        return this->searchWord(word);
    }

private:
    bool searchWord(string word)
    {
        WordDictionary* node = this;
        for (int i = 0; i < word.size(); ++i)
        {
            char ch = word[i];
            if (ch != '.')
            {
                auto iter = node->nodes_.find(ch);
                if (iter == node->nodes_.end())
                {
                    return false;
                }
                node = iter->second;
                continue;
            }
            if (i == word.size() - 1)
            {
                for (auto it = node->nodes_.begin(); it != node->nodes_.end(); ++it)
                {
                    if (it->second->nodes_.size() == 0)
                    {
                        return true;
                    }
                }
            }
            string temp_word = word.substr(i+1, word.size() - i - 1);
            for (auto it = node->nodes_.begin(); it != node->nodes_.end(); ++it)
            {
                if (it->second->searchWord(temp_word))
                {
                    return true;
                }
            }
            return false;
        }

        return node->end_;
    }

private:
    unordered_map<char, WordDictionary*> nodes_;
    bool end_;
};

// int main(int argc, char** argv)
// {
//     //输入:
//     //["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
//     //[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
//     //输出:
//     //[null,null,null,null,false,true,true,true]

//     WordDictionary wordDictionary;
//     wordDictionary.addWord("ab");
//     bool result = wordDictionary.search("a."); // 返回 False

//     return 0;
// }
