#include <vector>
#include <unordered_map>

using namespace std;

// https://leetcode.cn/problems/insert-delete-getrandom-o1/

class RandomizedSet {
public:
    RandomizedSet() {
        srand(time(NULL));
    }
    
    bool insert(int val) {
        auto it = umap_.find(val);
        if (it != umap_.end())
        {
            return false;
        }
        nums_.push_back(val);
        umap_[val] = nums_.size() - 1;
        return true;
    }
    
    bool remove(int val) {
        auto it = umap_.find(val);
        if (it == umap_.end())
        {
            return false;
        }
        swap(nums_[nums_.size() - 1], nums_[it->second]);
        nums_.pop_back();
        umap_.erase(it);
        return true;
    }
    
    int getRandom() {
        int index = rand() % nums_.size();
        return nums_[index];
    }

private:
    vector<int> nums_;
    unordered_map<int, int> umap_;
};

// int main(int argc, char** argv)
// {
//     RandomizedSet rs;
//     rs.insert(0);
//     rs.insert(1);
//     rs.remove(0);
//     rs.insert(2);
//     rs.remove(1);
//     int result = rs.getRandom();
//     return 0;
// }
