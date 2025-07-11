#include <vector>
#include <unordered_map>

using namespace std;

// https://leetcode.cn/problems/insert-delete-getrandom-o1/

class RandomizedSet 
{
public:
    RandomizedSet() 
    {
        srand(time(NULL));
    }
    
    bool insert(int val) 
    {
        if (nmap_.find(val) != nmap_.end())
        {
            return false;
        }
        //将val放入数组中，并将val在数组数组中的索引作为映射关系存储在nmap中
        int len = nums_.size();
        nums_.push_back(val);
        nmap_[val] = len;
        return true;
    }
    
    bool remove(int val) 
    {
        auto it = nmap_.find(val);
        if (it == nmap_.end())
        {
            return false;
        }
        int index = it->second; //被删除元素val在数组中的索引
        int last_val = nums_[nums_.size() - 1]; //数组尾部元素
        nums_[index] = last_val; //将尾部元素赋值到被删除元素的索引位置
        nmap_[last_val] = index; //为尾部元素重新建立索引的映射关系
        nums_.pop_back(); //删除数组尾部元素
        nmap_.erase(val); //从nmap中删除val，这一步必须放在"nmap_[last_val] = index"后执行，防止数组中只剩val的情况，即last_val=val，val被删除后又给last_val重新建立了映射关系
        return true;
    }
    
    int getRandom() 
    {
        int index = rand() % nums_.size();
        return nums_[index];
    }

private:
    vector<int> nums_;
    unordered_map<int, int> nmap_; //key--num，value--num在数组中的索引
};
    
/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

//  int main(int argc, char** argv)
//  {
//     RandomizedSet rs;

//     bool result = rs.insert(1);
//     result = rs.remove(2);
//     result = rs.insert(2);
//     int val = rs.getRandom();
//     result = rs.remove(1);
//     result = rs.insert(2);
//     val = rs.getRandom();

//     return 0;
//  }
