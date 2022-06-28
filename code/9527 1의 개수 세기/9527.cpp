#include <problem.h>

#ifdef _9527_

/// 7
/// problem
/// https://www.acmicpc.net/problem/9527
/// 
/// solution
/// 
/// 

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;



void getDPTable(vector<unsigned long long int>& table)
{
	table.push_back(0);

	for (int i = 0; i < 63; i++)
	{
		unsigned long long int value = pow(2, i);
		unsigned long long int temp = value;
		unsigned long long int offset = 1;
		
		table.push_back(value);

		while (temp)
		{
			temp = temp >> 1;
			table.back() += temp * offset;
			offset = offset << 1;
		}
	}
}

unsigned long long int getOnce(unsigned long long int value, vector<unsigned long long int>& dpTable)
{
	if (value == 1)
		return 1;
	if (value == 0)
		return 0;

	int x = 0;
	unsigned long long int temp = 1;
	unsigned long long int ret = 0;

	while (temp * 2 <= value)
	{
		x++;
		ret += dpTable[x];
		temp *= 2;
	}
	
	// ret = value �̸��� 2^n �� ���� ������
	// t1 = value �̻��� 2^n - 1 (�׻� value �̸���)
	// t2 = value�� t1 �� ���� (�� ���� 1 �� ����)
	// t3 = �� ���� 1�� �����ϰ�, (�� n�� 0�̶� ������) ���� ��, = t2 - 1
	// t4 = 0~t3 ������ ��Ʈ1 ������

	auto t1 = temp - 1;
	auto t2 = value - t1;
	auto t3 = t2 - 1;
	auto t4 = getOnce(t3, dpTable);
	
	return ret + value - (temp - 1) + getOnce(value - temp, dpTable);
}


int main()
{
	vector<unsigned long long int> dpTable;
	getDPTable(dpTable);

	unsigned long long int a;
	unsigned long long int b;
	
	cin >> a >> b;

	cout <<  getOnce(b, dpTable) - getOnce(a - 1, dpTable) << endl;
}
#endif
