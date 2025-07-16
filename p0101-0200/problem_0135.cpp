#include <vector>

using namespace std;

// https://leetcode.cn/problems/candy/

class Solution 
{
public:
    //1. 两次遍历
    //刚开始最直接想到的是只用一次遍历，然后判断每个rate与左右rate的大小就可以了，但是实际测试下来发现是无法获得正确结果的
    //假设当前rate比自身左右的rate都大，那当前rate获得的个数看起来应该是2，但是该rate右侧是一个长达5的递减区间
    //从右边算起的话，当前rate右边的rate能获得的个数是5，当前rate获得的个数是3的话，明显不满足题目中要求，如果当前rate比相邻的rate大，则获得个数得比相邻的多
    //所以需要从左右分别进行两次遍历，第一次从左遍历，使用数组保存从左遍历后每个rate获得的个数，如果比左边的值小，本身就获得一个糖果，否则获得比左侧rate+1的糖果数
    //然后再从右遍历一次，与右边的rate进行比较，计算出当前rate可获得的糖果数，然后与之前从左侧遍历获得的糖果数比较取较大值，才是实际获得的糖果数，并累加到结果中
    int candy(vector<int>& ratings) 
    {
        vector<int> nums(ratings.size(), 0);
        nums[0] = 1;
        for (int i = 1; i < ratings.size(); ++i)
        {
            if (ratings[i] > ratings[i-1])
            {
                nums[i] = nums[i-1] + 1;
            }
            else
            {
                nums[i] = 1;
            }
        }

        int n = 0;
        int temp = 1;
        for (int i = ratings.size() - 1; i >= 0; --i)
        {
            if (i < ratings.size() - 1 && ratings[i] > ratings[i+1])
            {
                ++temp;
            }
            else
            {
                temp = 1;
            }
            //左侧遍历获得的糖果数与右侧遍历获得的糖果数，取较大值
            n += max(temp, nums[i]);
        }

        return n;
    }

    //2. 不使用额外内存空间
    //解法1使用了左右两次遍历的方法，所以使用了额外的数组来保存第一次遍历的结果
    //如果能处理好当前rate右侧的递减序列影响当前rate获得糖果数的问题的话，其实可以不用两次遍历和额外数组，只需要一次遍历就能完成
    //划分出rating的递增和递减区间来处理，因为使用解法1的核心问题就是，单次遍历的时候，递增区间的最高点之后，遇到很长的一段递减区间
    //导致该递减区间最左侧rate获得的糖果数非常多，超过了递增区间最右rate获得糖果数，导致题目中的条件不成立(相邻rate大的获得更多的糖果)
    //才需要进行左右两次遍历来完成，那么如果在单次遍历的时候，在递增区间最右侧的rate，根据之后可能出现的递减区间的长度，增加自己能获得的糖果数，就能解决这个问题
    //假设一个递增区间[1,2,7]，从左侧开始遍历，那么这3个位置获得糖果分别为[1,2,3]
    //如果7之后开始出现递增区间了，比如[1,2,7,6]，那么这4个位置获得的糖为[1,2,3,1]，rate为6只能获得一个糖果，因为没有相邻的rate大
    //如果6之后继续递减，比如[1,2,7,6,5]，rate为5肯定只能获得一个糖果，rate6得多活的一个糖果，所以这5个位置获得的糖果为[1,2,3,2,1]
    //总体上来说比之前多了2个糖果，就好像增加了当前递减区间的长度一样[6,5]，长度为2，不包括之前递增区间最右侧的7
    //如果5之后继续递减，比如[1,2,7,6,5,4]，rate为4还是获得一个糖果，rate5获得2个，rate6获得3个，这5个位置获得的糖果为[1,2,3,3,2,1]
    //rate7获得的糖果是3，rate6获得的糖果是3，不符合题目条件，相邻大的rate获得的糖果更多
    //这种情况下，我们发现递增区间和递减区间一样长了，在这种情况下递增区间的最右侧rate获得的糖果数需要被递减区间影响，获得的糖果数需要变多(rate7获得的糖果数得比rate6多)
    //所以当递增区间长度和递减区间一样长的时候，我们就需要把每次增加的糖果数+1，保证递增区间最右侧的rate获得糖果数肯定大于递减区间最左侧rate的糖果数
    int candyNoExtraSpace(vector<int>& ratings)
    {
        int inc_len = 1; //递增区间长度
        int temp_inc_len = 1; 
        int dec_len = 0; //递减区间长度
        int temp = 1; //糖果数
        int result = 1; //总糖果数
        for (int i = 1; i < ratings.size(); ++i)
        {
            //递增区间
            if (ratings[i] >= ratings[i-1])
            {
                ++inc_len; //递增区间长度+1
                ++temp; //糖果数+1
                dec_len = 0;
                if (ratings[i] == ratings[i-1]) //相等
                {
                    temp = 1; //当前糖果数变为1
                    inc_len = 1; //递增区间长度回到1
                }
                temp_inc_len = inc_len; //保存递增区间长度
                result += temp; //累加糖果数
            }
            else
            {
                inc_len = 1; //递增区间长度重置为1(下次可能从这个位置开始递增)
                ++dec_len; //递减区间长度+1
                if (dec_len == temp_inc_len) 
                {
                    //递减区间和递增区间一样长了，影响递增区间最右侧rate的糖果数，dec_len需要+1
                    ++dec_len; 
                }
                result += dec_len; //递减区间长度即为需要多获得的糖果数
                temp = 1; 
            }
        }

        return result;
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;

//     vector<int> ratings = {1,0,2};
//     int result = s.candyNoExtraSpace(ratings);

//     ratings = {1, 2, 2};
//     result = s.candyNoExtraSpace(ratings);

//     ratings = {5,3,7,3};
//     result = s.candyNoExtraSpace(ratings);

//     return 0;
// }