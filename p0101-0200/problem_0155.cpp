#include <stack>

// https://leetcode.cn/problems/min-stack/

using namespace std;

//1. 双栈
//维护两个栈，一个为数据栈，用于常规元素的存储，另一个为辅助栈，用于同步存储当前栈内的最小值
//将元素压入数据栈的时候，比较当前入栈值与辅助栈栈顶值，将两者中的较小值再次压入辅助栈，如此确保辅助栈栈顶始终是数据栈中所有元素的最小值
//出栈时，两个栈执行同步弹出操作，以保证辅助栈始终能正确追踪数据栈每一时刻的状态
class MinStack 
{
public:
    MinStack() 
    {
    }
    
    void push(int val) 
    {
        val_st.push(val);
        if (min_st.empty())
        {
            min_st.push(val);
        }
        else
        {
            min_st.push(min(min_st.top(),val));
        }
    }
    
    void pop() 
    {
        if (val_st.empty())
        {
            return;
        }
        val_st.pop();
        min_st.pop();
    }
    
    int top() 
    {
        if (val_st.empty())
        {
            return 0;
        }
        return val_st.top();
    }
    
    int getMin() 
    {
        if (min_st.empty())
        {
            return 0;
        }
        return min_st.top();
    }

private:
    stack<int> val_st;
    stack<int> min_st;
};

//2. 单个栈+差值存储
//栈中不再直接存储原始数值val，而是存储当前值与当前最小值的差值diff=val-min_val，只需要一个栈和一个int变量即可
//通过这个差值的正负号，我们可以在一个栈里同时编码两种信息，正数(或零)表示当前值比最小值大，最小值未更新，负数表示当前值刷新了最小值记录，最小值已更新
//插入val时，计算差值diff，并且将diff入栈，如果diff<0，说明val成了新的"全场最小"，我们需要更新全局变量min_val
//出栈时，如果弹出的diff是负数，说明当前min_val正是由这个节点创造的，回溯公式为min_val=min_val-diff，由于diff是负数，减去一个负数等于加上一个正数，min_val成功回退到上一个较小的值
//查看栈顶时，由于栈里存的是差值，我们需要通过min_val进行还原，如果diff>0，原值val=min_val+diff，如果diff<=0，说明当前min_val就是我们要找的原值，直接返回即可
class MinStackAuxInt
{
public:
    MinStackAuxInt()
    {
    }

    void push(int val)
    {
        if (val_st.empty())
        {
            val_st.push(0);
            min_val = val;
        }
        else
        {
            long diff = long(val) - min_val;
            val_st.push(diff);
            if (diff < 0)
            {
                min_val = val;
            }
        }
    }

    void pop()
    {
        if (val_st.empty())
        {
            return;
        }
        long diff = val_st.top();
        val_st.pop();
        if (diff < 0)
        {
            min_val -= diff;
        }
    }

    int top() 
    {
        if (val_st.empty())
        {
            return 0;
        }
        int diff = val_st.top();
        if (diff > 0)
        {
            return min_val + diff;
        }
        return min_val;
    }

    int getMin() 
    {
        return min_val;
    }

private:
    stack<long> val_st;
    long min_val;
};

// int main(int argc, char** argv)
// {
//     //输入：
//     //["MinStack","push","push","push","getMin","pop","top","getMin"]
//     //[[],[-2],[0],[-3],[],[],[],[]]

//     //输出：
//     //[null,null,null,null,-3,null,0,-2]
//     MinStackAuxInt ms;
//     ms.push(-2);
//     ms.push(0);
//     ms.push(-3);
//     int num = ms.getMin();
//     ms.pop();
//     num = ms.top();
//     num = ms.getMin();

//     return 0;
// }




