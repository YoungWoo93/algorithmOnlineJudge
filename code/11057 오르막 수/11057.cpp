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
vector<vector<int>> getDPs(int count)
{
	vector<vector<int>> ret(count + 1, vector<int>(10, 1));

	for (int i = 1; i < count + 1; i++)
	{
		for (int index = 8; index >= 0; index--)
		{
			ret[i][index] = (ret[i - 1][index] + ret[i][index + 1]) % 10007;
		}
	}


	return ret;

}



int main()
{
	int digit;
	cin >> digit;
	auto DPs = getDPs(digit);

	cout << DPs.back()[0] << endl;

	return 0;
}
#endif
