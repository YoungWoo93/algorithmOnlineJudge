#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

namespace dataStructures
{
	template <typename V, typename L = LinkedList<V>>// c++ 17
	class Dequeue
	{
	public:
		Dequeue() {
			datas = new L();
			dataCount = 0;
		}
		~Dequeue() {
			delete datas;
		}


		void push_front(V value) {
			push_front(value, datas);
		}
		void push_back(V value) {
			push_back(value, datas);
		}

		bool pop_front() {
			return pop_front(datas);
		}
		bool pop_back() {
			return pop_back(datas);
		}

		V front() {
			return front(datas);
		}
		V back() {
			return back(datas);
		}

		int size() {
			return size(datas);
		}
		bool empty() {
			return size(datas) == 0;
		}

	protected:
		void push_front(V value, LinkedList<V>* datalist)
		{
			datalist->insert(value, 0);
		}
		void push_front(V value, vector<V>* datalist)
		{
			datalist->push_back(datalist->back());
			for (int i = size(datalist) - 1; i > 0; i--)
				(*datalist)[i] = (*datalist)[i - 1];

			(*datalist)[0] = value;
		}
		void push_front(V value, int* datalist)
		{
			if ((_msize(datalist) / sizeof(L)) == dataCount)
				datalist = resize((_msize(datalist) / sizeof(L)) * 2);

			for (int i = size(datalist); i > 0; i--)
				datalist[i] = datalist[i - 1];

			*datalist = value;
			dataCount++;
		}

		void push_back(V value, LinkedList<V>* datalist)
		{
			datalist->add(value);
		}
		void push_back(V value, vector<V>* datalist)
		{
			datalist->push_back(value);
		}
		void push_back(V value, int* datalist)
		{
			if ((_msize(datalist) / sizeof(L)) == dataCount)
				datalist = resize((_msize(datalist) / sizeof(L)) * 2);

			*(datalist + dataCount) = value;
			dataCount++;
		}

		bool pop_front(LinkedList<V>* datalist)
		{
			if (empty())
				return false;

			datalist->eraseIndex(0);
			return true;
		}
		bool pop_front(vector<V>* datalist)
		{
			if (empty())
				return false;

			for (int i = 1; i < (*datalist).size(); i++)
				(*datalist)[i - 1] = (*datalist)[i];

			datalist->pop_back();

			return true;
		}
		bool pop_front(int* datalist)
		{
			if (empty())
				return false;

			for (int i = 1; i < size(datalist); i++)
				datalist[i - 1] = datalist[i];

			dataCount--;
			return true;
		}

		bool pop_back(LinkedList<V>* datalist)
		{
			if (empty())
				return false;

			datalist->eraseIndex(datalist->size() - 1);
			return true;
		}
		bool pop_back(vector<V>* datalist)
		{
			if (empty())
				return false;

			datalist->pop_back();
			return true;
		}
		bool pop_back(int* datalist)
		{
			if (empty())
				return false;

			dataCount--;
			return true;
		}

		V front(LinkedList<V>* datalist)
		{
			if (empty())
				return NULL;

			return datalist->head->value;
		}
		V front(vector<V>* datalist)
		{
			if (empty())
				return NULL;

			return datalist->front();
		}
		V front(int* datalist)
		{
			if (empty())
				return NULL;

			return *(datalist);
		}

		V back(LinkedList<V>* datalist)
		{
			if (empty())
				return NULL;

			return datalist->tail->value;
		}
		V back(vector<V>* datalist)
		{
			if (empty())
				return NULL;

			return datalist->back();
		}
		V back(int* datalist)
		{
			if (empty())
				return NULL;

			return *(datalist + dataCount - 1);
		}

		int size(LinkedList<V>* datalist)
		{
			return datalist->size();
		}
		int size(vector<V>* datalist)
		{
			return datalist->size();
		}
		int size(int* datalist)
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