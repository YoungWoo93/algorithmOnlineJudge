#include <problem.h>

#ifdef _5638_

/// 
/// problem
/// https://www.acmicpc.net/problem/5638
/// 
/// solution
/// 
/// 


#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

struct gate {
	int flux;
	int cost;
};

deque<gate> inputGates();
deque<gate> inputCase();
deque<gate> getDPtable(deque<gate>& gates);
deque<gate> merge(deque<gate>& first, deque<gate>& second);


deque<gate> inputGates()
{
	int gateCount;
	cin >> gateCount;

	deque<gate> gates(gateCount);

	for (auto &g : gates)
	{
		cin >> g.flux;
		cin >> g.cost;
	}

	return gates;
}

deque<gate> inputCase()
{
	int caseCount;
	cin >> caseCount;

	deque<gate> cases(caseCount);

	for (auto& c : cases)
	{
		cin >> c.flux;
		cin >> c.cost;
	}

	return cases;
}

deque<gate> getDPtable(deque<gate>& gates)
{
	deque<gate> ret;
	gate init;
	init.flux = 0;
	init.cost = 0;

	ret.push_back(init);

	for (auto _gate : gates)
	{
		deque<gate> temp;
		for (auto dpitem : ret)
		{
			gate tempitem;
			tempitem.cost = dpitem.cost + _gate.cost;
			tempitem.flux = dpitem.flux + _gate.flux;

			temp.push_back(tempitem);
		}

		ret = merge(ret, temp);
	}

	return ret;
}

deque<gate> merge(deque<gate>& first, deque<gate>& second)
{
	int size = first.size() + second.size();
	deque<gate> ret;

	for (int i = 0; i < size; i++)
	{
		if (first.empty())
		{
			ret.push_back(second[0]);
			second.pop_front();
		}
		else if (second.empty())
		{
			ret.push_back(first[0]);
			first.pop_front();
		}
		else if (first[0].flux < second[0].flux)
		{
			if(first[0].cost < second[0].cost)
				ret.push_back(first[0]);
			first.pop_front();
		}
		else
		{
			if (second[0].cost < first[0].cost)
				ret.push_back(second[0]);
			second.pop_front();
		}
	}

	return ret;
}

int main()
{
	auto g = inputGates();
	auto table = getDPtable(g);
	auto c = inputCase();

	for (int i=0; i<c.size(); i++)
	{
		for (int j = 0; j < table.size() + 1; j++)
		{
			if (j == table.size())
			{
				cout << "Case " << i + 1 << ": IMPOSSIBLE" << endl;
				break;
			}

			if (c[i].flux <= table[j].flux * c[i].cost)
			{
				cout << "Case " << i + 1 << ": " << table[j].cost << endl;
				break;
			}
		}
	}

	return 0;
}

#endif