#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    Solution() {
        unordered_map<int, char> temp = {
            {1, 'I'},
            {5, 'V'},
            {10, 'X'}
        };
        nmap_[1] = temp;

        temp = {
            {1, 'X'},
            {5, 'L'},
            {10, 'C'}
        };
        nmap_[10] = temp;

        temp = {
            {1, 'C'},
            {5, 'D'},
            {10, 'M'}
        };
        nmap_[100] = temp;

        temp = {
            {1, 'M'}
        };
        nmap_[1000] = temp;
    }

    string intToRoman(int num) {
        string result;
        int step = 1;
        while (num)
        {
            int n = num % 10;
            string str;
            switch (n)
            {
                case 0:
                    break;
                case 9:
                    str += nmap_[step][1];
                    str += nmap_[step][10];
                    break;
                case 4:
                    str += nmap_[step][1];
                    str += nmap_[step][5];
                    break;
                default:
                    if (n >=5 )
                    {
                        str += nmap_[step][5];
                    }
                    for (int i = 0; i < n % 5; ++i)
                    {
                        str += nmap_[step][1];
                    }
                    break;
            }
            result = str + result;
            num /= 10;
            step *= 10;
        }

        return result;
    }

    unordered_map<int, unordered_map<int, char>> nmap_;
};

// int main(int argc, char** argv)
// {
//     Solution s;
//     string result = s.intToRoman(3749);

//     return 0;
// }