#include <problem.h>

#ifdef _2342_

/// 170
/// problem
/// https://www.acmicpc.net/problem/2342
/// 
/// solution
/// 
/// 

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;


vector<int> input()
{
	int inputs = 1;
	vector<int> ret;

	while (true)
	{
		cin >> inputs;

		if (inputs == 0)
			break;

		ret.push_back(inputs);
	}

	return ret;
}

int move(int before, int after)
{
	if (before == 0)
		return 2;

	if (before == after)
		return 1;

	if (abs(before - after) == 2)
		return 4;

	return 3;
}
void putValue(int* target, int value)
{
	if (*target == -1)
		*target = value;
	else
		*target = min(*target, value);
}

void printBoard(vector<vector<int>>* boardPtr, string comment)
{
	cout << endl << "=================" << endl;
	if (comment != "")
		cout << comment << endl;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << (*boardPtr)[i][j] << "\t";
		}
		cout << endl;
	}
}

int simulation(vector<int> cmd)
{
	vector<vector<int>> board1(5, vector<int>(5, -1));
	vector<vector<int>> board2(5, vector<int>(5, -1));

	vector<vector<int>>* boardPtr = &board1;
	vector<vector<int>>* tempBoardPtr = &board2;

	board1[0][0] = 0;

	for (int i = 0; i < cmd.size(); i++)
	{
		for (int left = 0; left < 5; left++)
		{
			for (int right = 0; right < 5; right++)
			{
				if ((*boardPtr)[left][right] != -1)
				{
					if (left == cmd[i] || right == cmd[i])
						putValue(&(*tempBoardPtr)[left][right],(*boardPtr)[left][right] + 1);
					else
					{
						putValue(&(*tempBoardPtr)[cmd[i]][right], (*boardPtr)[left][right] + move(left, cmd[i]));
						putValue(&(*tempBoardPtr)[left][cmd[i]], (*boardPtr)[left][right] + move(right, cmd[i]));
					}
					(*boardPtr)[left][right] = -1;

				}
			}
		}

		auto temp = boardPtr;
		boardPtr = tempBoardPtr;
		tempBoardPtr = temp;
	}

	int answer = INT_MAX;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if ((*boardPtr)[i][j] != -1)
				answer = min(answer, (*boardPtr)[i][j]);
		}
	}

	return answer;
}

int main()
{
	auto command = input();
	int answer = simulation(command);

	cout << answer << endl;
	return 0;
}
#endif
