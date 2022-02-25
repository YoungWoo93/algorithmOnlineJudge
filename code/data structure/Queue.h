#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

namespace dataStructures
{
	template <typename V, typename L = LinkedList<V>>// c++ 17
	class Queue
	{
	public:
		Queue() {
			datas = new L();
			dataCount = 0;
		}
		~Queue() {
			delete datas;
		}


		void push(V value) {
			push(value, datas);
		}

		bool pop() {
			return pop(datas);
		}
		V front() {
			return front(datas);
		}
		int size() {
			return size(datas);
		}
		bool empty() {
			return size(datas) == 0;
		}

	protected:
		// use linked list
		void push(V value, LinkedList<V>* datalist)
		{
			datalist->insert(value, 0);
		}
		bool pop(LinkedList<V>* datalist)
		{
			if (empty())
				return false;

			datalist->eraseIndex(datalist->size() - 1);
			return true;
		}
		V front(LinkedList<V>* datalist)
		{
			if (empty())
				return NULL;

			return datalist->tail->value;
		}
		int size(LinkedList<V>* datalist)
		{
			return datalist->size();
		}

		// use vector
		void push(V value, vector<V>* datalist)
		{
			datalist->push_back(value);
		}
		bool pop(vector<V>* datalist)
		{
			if (empty())
				return false;

			for (int i = 1; i < size(datalist); i++)
				(*datalist)[i - 1] = (*datalist)[i];

			datalist->pop_back();
			return true;
		}
		V front(vector<V>* datalist)
		{
			if (empty())
				return NULL;

			return datalist->front();
		}
		int size(vector<V>* datalist)
		{
			return datalist->size();
		}

		// use array
		void push(V value, V* datalist)
		{
			if ((_msize(datalist) / sizeof(L)) == dataCount)
				datalist = resize((_msize(datalist) / sizeof(L)) * 2);

			*(datalist + dataCount) = value;
			dataCount++;
		}
		bool pop(V* datalist)
		{
			if (empty())
				return false;

			for (int i = 1; i < size(datalist); i++)
				datalist[i - 1] = datalist[i];

			dataCount--;
			return true;
		}
		V front(V* datalist)
		{
			if (empty())
				return NULL;

			return *(datalist);
		}
		int size(V* datalist)
		{
			return dataCount;
		}
		V* resize(int size)
		{
			V* newArr = new V[size];

			memcpy(newArr, datas, _msize(datas));

			delete datas;
			datas = newArr;

			return newArr;
		}

	private:


	public:

	protected:
		L* datas;
		int dataCount;

	private:
	};
}