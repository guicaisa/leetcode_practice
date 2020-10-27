#include <stdio.h>

/**
 * https://leetcode.com/problems/powx-n/
 */

class Solution {
public:
	// µÝ¹éÇó½â
	double MyPow(double x, int n) {
		if (n == 0) {
			return 1;
		}

		double t = MyPow(x, n / 2);

		if (n % 2) {
			return n > 0 ? x * t * t : 1 / x * t * t;
		} 
		else {
			return t * t;
		}
	}
};

//int main(int argc, char** argv) {
//	Solution s;
//
//	int ret = s.MyPow(3, 4);
//
//	return 0;
//}