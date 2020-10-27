#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

class Solution {
public:
	std::vector<std::vector<std::string>> SolveNQueens(const int n) {
		int count = 0;
		std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
		std::vector<int> row(2 * n - 1, 0);
		std::vector<int> column(2 * n - 1, 0);
		std::vector<int> diagonal(2 * n - 1, 0);
		std::vector<int> reverse_diagonal(2 * n - 1, 0);
		std::vector<std::vector<std::string>> results;

		this->Recursive(n, 0, 0, count, matrix, row, column, diagonal, reverse_diagonal, results);

		return results;
	}

	void Recursive(const int n, const int s, const int e, int& count, std::vector<std::vector<int>>& matrix, std::vector<int>& row, 
		std::vector<int>& column, std::vector<int>& diagonal, std::vector<int>& reverse_diagonal, std::vector<std::vector<std::string>>& results) {
		
		for (int i = s; i < n; ++i) {
			int j = i == s ? e : 0;
			for (; j < n; ++j) {
				int r = i;
				int c = j;
				int d = i - j + (n - 1);
				int rd = i + j;

				if (matrix[i][j] == 1 || row[r] == 1 || column[c] == 1 || diagonal[d] == 1 || reverse_diagonal[rd] == 1) {
					continue;
				}

				++count;
				matrix[i][j] = 1;
				row[r] = 1;
				column[c] = 1;
				diagonal[d] = 1;
				reverse_diagonal[rd] = 1;

				if (count == n) {
					this->Record(matrix, results);
				}
				else {
					//int ns = j == n - 1 ? i + 1 : i;
					//int ne = j == n - 1 ? 0 : j;

					this->Recursive(n, i + 1, 0, count, matrix, row, column, diagonal, reverse_diagonal, results);
				}

				--count;
				matrix[i][j] = 0;
				row[r] = 0;
				column[c] = 0;
				diagonal[d] = 0;
				reverse_diagonal[rd] = 0;
			}
		}
	}

	void Record(const std::vector<std::vector<int>>& matrix, std::vector<std::vector<std::string>>& results) {
		std::vector<std::string> vs;

		for (int i = 0; i < matrix.size(); ++i) {
			std::string str;
			for (int j = 0; j < matrix[i].size(); ++j) {
				if (matrix[i][j] == 0) {
					str += '.';
				}
				else {
					str += 'Q';
				}
			}

			vs.emplace_back(str);
		}

		results.emplace_back(vs);
	}
};

int main(int argc, char** argv) {
	Solution s;

	std::vector<std::vector<std::string>> results = s.SolveNQueens(4);

	return 0;
}