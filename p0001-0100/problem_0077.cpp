#include <vector>

using namespace std;

class Solution 
{
public:
    vector<vector<int>> combine(int n, int k) 
    {
        if (n == 0 || k == 0)
        {
            return vector<vector<int>>();
        }

        vector<int> temp(k, 0);
        vector<vector<int>> results;
        this->recursive(n, 1, 0, temp, results);
        return results;
    }

    void recursive(int n, int num, int index, vector<int>& temp, vector<vector<int>>& results)
    {
        for (int tn = num; tn <= n; ++tn)
        {
            temp[index] = tn;
            if (index == temp.size() - 1)
            {
                results.push_back(temp);
            }
            else
            {
                this->recursive(n, tn+1, index+1, temp, results);
            }
        }
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     //输入: n = 4, k = 2
//     //输出:
//     //[
//     //  [2,4],
//     //  [3,4],
//     //  [2,3],
//     //  [1,2],
//     //  [1,3],
//     //  [1,4],
//     //]
//     vector<vector<int>> results = s.combine(4, 2);

//     //输入: n = 1, k = 1
//     //输出: [[1]]
//     results = s.combine(1, 1);

//     return 0;
// }