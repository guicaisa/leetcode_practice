#include <vector>

using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        for (int i = 0; i < n;)
        {
            int gas_sum = 0;
            int cost_sum = 0;
            int pos = i;
            int count = 0;
            for (; count < n; ++count)
            {
                gas_sum += gas[pos];
                cost_sum += cost[pos];
                if (gas_sum < cost_sum)
                {
                    break;
                }
                pos = (pos + 1) % n;
            }
            if (count >= n)
            {
                return i;
            }
            i += count + 1;
        }
        return -1;
    }

    int canCompleteCircuitOneLoop(vector<int>& gas, vector<int>& cost) {
        int avail = 0;
        int min_sum = 0;
        int min_index = -1;
        for (int i = 0; i < gas.size(); ++i)
        {
            avail += gas[i] - cost[i];
            if (avail < min_sum)
            {
                min_sum = avail;
                min_index = i;
            }
        }

        return avail < 0 ? -1 : (min_index + 1) % gas.size();
    }
};

// int main(int argc, char** argv)
// {
//     Solution s;
//     vector<int> gas = {3, 1, 1};
//     vector<int> cost = {1, 2, 2};
//     int result = s.canCompleteCircuitOneLoop(gas, cost);

//     return 0;
// }

