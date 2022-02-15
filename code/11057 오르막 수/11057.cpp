#include <problem.h>

#ifdef _11057_

/// 
/// problem
/// https://www.acmicpc.net/problem/11057
/// 
/// solution
/// 
/// 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int process(int input)
{
	vector<vector<int>> list(input, vector<int>(11, 0));
	list[0].assign(11, 1);
	list[0][10] = 10;

	for (int i = 1; i < input; i++)
	{
		int sum = list[i - 1][10];
		list[i][0] = list[i - 1][10];

		for (int j = 1; j < 10; j++)
		{
			list[i][j] = (list[i][j - 1] - list[i - 1][j - 1]) % 10007;

			if (list[i][j] < 0)
				list[i][j] += 10007;
			sum += list[i][j];
		}
		list[i][10] = sum % 10007;
	}

	return list[input - 1][10];
}



int main()
{
	int digit;
	cin >> digit;

	cout << process(digit) % 10007 << endl;

	return 0;
}
#endif
