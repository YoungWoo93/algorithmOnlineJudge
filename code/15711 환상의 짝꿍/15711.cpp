#include <problem.h>

#ifdef _15711_

/// 
/// problem
/// https://www.acmicpc.net/problem/15711
/// 
/// solution
/// 
/// 

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<unsigned long long int> getPrimeNums()
{
	vector<unsigned long long int>  ret;
	long long int size = 2 * pow(10, 6);

	auto remove = [](vector<bool>& arr, int start, int scale) {
		for (int i = start * 2; i < arr.size(); i += scale)
			arr[i] = false;
	};
	vector<bool> eratos(size + 1, true);
	eratos[0] = eratos[1] = false;


	for (int i = 2; i < size + 1; i++)
	{
		if (eratos[i])
			remove(eratos, i, i);
	}

	for (int i = 0; i < eratos.size(); i++)
	{
		if (eratos[i])
			ret.push_back(i);
	}

	return ret;
}

bool isPrime(unsigned long long int value, vector<unsigned long long int>& table)
{

	for (int i = 0; i < table.size(); i++)
	{
		if (pow(table[i], 2) > value)
			break;

		if (value % table[i] == 0)
			return false;
	}

	return true;
}

bool check(unsigned long long int length, vector<unsigned long long int>& table)
{
	for (unsigned long long int i = 2; i <= length / 2; i++)
	{
		if (isPrime(i, table) && isPrime(length - i, table))
			return true;
	}

	return false;
}

int main()
{
	int cycles;
	cin >> cycles;

	vector<unsigned long long int> primeTable = getPrimeNums();

	for (int cycle = 0; cycle < cycles; cycle++)
	{
		unsigned long long int a, b;
		cin >> a >> b;

		unsigned long long int length = a + b;

		if (length >= 4)
		{
			if (length % 2 == 0)
				cout << "YES" << endl;
	
			else
			{
				if (isPrime(length - 2, primeTable))
					cout << "YES" << endl;
				else
					cout << "NO" << endl;
			}
		}
		else
			cout << "NO" << endl;
	}
}


#endif
