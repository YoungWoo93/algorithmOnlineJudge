#include <problem.h>

#ifdef _2042_

/// 
/// problem
/// https://www.acmicpc.net/problem/2042
/// 
/// solution
/// 
/// 


#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <algorithm>

using namespace std;

struct cmd {
	int type;
	int value1;
	long long int value2;
};

int getTreeSize(int n)
{
	return pow(2, ceil(log2(n)));
}

long long int makeSegmentTree(vector<long long int>& arr, int cur)
{
	if (cur * 2 < arr.size())
		arr[cur] = makeSegmentTree(arr, cur * 2) + makeSegmentTree(arr, cur * 2 + 1);

	return arr[cur];
}

vector<long long int> input(queue<cmd>& cmdList)
{
	int numberSize, changeCount, sumCount;
	cin >> numberSize >> changeCount >> sumCount;
	
	int treeSize = getTreeSize(numberSize);
	vector<long long int> ret(treeSize * 2, 0);

	for (int i = 0; i < numberSize; i++)
		cin >> ret[treeSize + i];
	
	makeSegmentTree(ret, 1);

	for (int i = 0; i < changeCount + sumCount; i++)
	{
		cmd temp;

		cin >> temp.type >> temp.value1 >> temp.value2;
		cmdList.push(temp);
	}

	return ret;
}

long long int sumFunction(vector<long long int>& tree, int start, int end, int cur, int sumRangeStart, int sumRangeEnd)
{
	if (sumRangeEnd < start || end < sumRangeStart)
		return 0;

	if (sumRangeStart <= start && end <= sumRangeEnd)
		return tree[cur];

	int mid = (start + end) / 2;

	return sumFunction(tree, start, mid, cur * 2, sumRangeStart, sumRangeEnd) + sumFunction(tree, mid + 1, end, cur * 2 + 1, sumRangeStart, sumRangeEnd);
}

void changeFunction(vector<long long int>&tree, int start, int end, int cur, int key, long long int offset)
{
	if (key < start || end < key)
		return;

	tree[cur] += offset;

	if (key == cur)
		return;

	int mid = (start + end) / 2;
	changeFunction(tree, start, mid, cur * 2, key, offset);
	changeFunction(tree, mid + 1, end, cur * 2 + 1, key, offset);
}

int main()
{
	queue<cmd> cmdList;
	auto tree = input(cmdList);

	int startIndex = tree.size() / 2;
	int endIndex = tree.size() - 1;

	while (!cmdList.empty())
	{
		auto cmd = cmdList.front();

		if (cmd.type == 1)
			changeFunction(tree, startIndex, endIndex, 1, startIndex + cmd.value1 - 1, cmd.value2 - tree[startIndex + cmd.value1 - 1]);
		else if (cmd.type == 2)
			cout << sumFunction(tree, startIndex, endIndex, 1, startIndex + cmd.value1 - 1, startIndex + cmd.value2 - 1) << endl;

		cmdList.pop();
	}

	return 0;
}
#endif
