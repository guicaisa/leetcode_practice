#include <vector>

using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if (nums.size() == 0)
        {
            return;
        }
        int shift = k % nums.size();
        if (shift == 0)
        {
            return;
        }
        int offset = nums.size() % shift;
        int n = nums.size() / shift * shift;
        int round = nums.size() / shift + 1;
        int temp = nums[0];
        int pos = shift % nums.size();
        for (; pos != 0;)
        {
            swap(nums[pos], temp);
            pos = (shift + pos) % nums.size();
        }
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;
//     vector<int> nums = {1,2,3,4,5,6};
//     int k = 4;
//     s.rotate(nums, k);

//     // {1,2,3,4,5,6}
//     // {5,2,3,4,1,6}
//     // {5,6,3,4,1,2}
//     // {3,6,5,4,1,2}
//     // {3,4,5,6,1,2}

//     // 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27
//     // 12,13,14,15,16,17,18,19,20,21,22,|1,2,3,4,5,6,7,8,9,10,11,|23,24,25,26,27
//     // 23,24,25,26,27,17,18,19,20,21,22,|1,2,3,4,5,6,7,8,9,10,11,|12,13,14,15,16
//     // 17,18,19,20,21,23,24,25,26,27,22
//     return 0;
// }