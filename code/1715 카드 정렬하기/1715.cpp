#include <problem.h>

#ifdef _1715_

/// 
/// problem
/// https://www.acmicpc.net/problem/1715
/// 
/// solution
/// 
/// 

#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

multiset<int> input()
{
	int cases;
	cin >> cases;

	multiset<int> ret;
	for (int i = 0; i < cases; i++)
	{
		int temp;

		cin >> temp;
		ret.insert(temp);
	}

	return ret;
}

int main()
{
	auto s = input();
	int ret = 0;
	while (s.size() > 1)
	{
		int temp = *s.begin();
		s.erase(s.find(*s.begin()));
		temp += *s.begin();
		s.erase(s.find(*s.begin()));

		ret += temp;
		s.insert(temp);
	}


	cout << ret;

	return 0;
}

#endif
