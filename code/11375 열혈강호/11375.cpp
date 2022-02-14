#include <problem.h>

#ifdef _11375_

/// 
/// problem
/// https://www.acmicpc.net/problem/11375
/// 
/// solution
/// 
/// 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void input(vector<pair<int, vector<int>>>& employeeTable, vector<pair<int, vector<int>>>& taskTable)
{
	int employees, tasks;
	cin >> employees >> tasks;

	employeeTable.assign(employees, { 0, vector<int>() });
	taskTable.assign(tasks + 1, { -1, vector<int>() });

	for (int i = 0; i < employees; i++)
	{
		cin >> employeeTable[i].first;
		for (int j = 0; j < employeeTable[i].first; j++)
		{
			int task;
			cin >> task;

			employeeTable[i].second.push_back(task);
			taskTable[task - 1].second.push_back(i);
		}
	}
}

bool change(vector<pair<int, vector<int>>>& employeeTable, vector<pair<int, vector<int>>>& taskTable, int taskNo, vector<bool> &memo)
{
	int employeeNo = taskTable[taskNo].first;
	if (taskTable[taskNo].first == -1)
	{
		taskTable[taskNo].first = employeeNo;
		return true;
	}

	if (!memo[employeeNo])
		return false;

	memo[employeeNo] = false;
	
	for (int i = 0; i < employeeTable[employeeNo].second.size(); i++)
	{
		int _taskNo = employeeTable[employeeNo].second[i];

		if (taskTable[_taskNo].first == -1 || change(employeeTable, taskTable, _taskNo, memo))
		{
			taskTable[_taskNo].first = employeeNo;
			return true;
		}
	}

	return false;
}

int process(vector<pair<int, vector<int>>>& employeeTable, vector<pair<int, vector<int>>>& taskTable)
{
	int ret = 0;
	vector<bool> memo(employeeTable.size(), true);

	for (int i = 0; i < employeeTable.size(); i++)
	{
		if (employeeTable[i].second.empty())
			continue;

		int taskNo = employeeTable[i].second[0];
		if (change(employeeTable, taskTable, taskNo, memo))
		{
			ret++;
			taskTable[taskNo].first = i;
		}
		memo.assign(employeeTable.size(), true);
	}

	return ret;
}

int main()
{
	vector<pair<int, vector<int>>> employeeTable;
	vector<pair<int, vector<int>>> taskTable;

	input(employeeTable, taskTable);
	sort(employeeTable.begin(), employeeTable.end(), greater<>());


	cout << process(employeeTable, taskTable) << endl;

	return 0;
}
#endif
