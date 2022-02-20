#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

namespace dataStructures
{
	template <typename V, typename L = LinkedList<V>> // c++ 17
	class Stack
	{
	public:
		Stack() {
			datas = new L();
			dataCount = 0;
		}
		~Stack() {
			delete datas;
		}


		void push(V value){
			push(value, datas);
		}

		bool pop(){
			return pop(datas);
		}
		V top(){
			return top(datas);
		}
		int size(){
			return size(datas);
		}
		bool empty(){
			return size(datas) == 0;
		}
		
	protected:
		void push(V value, LinkedList<V>* datalist)
		{
			datalist->insert(value, 0);
		}
		void push(V value, vector<V>* datalist)
		{
			datalist->push_back(value);
		}
		void push(V value, int* datalist)
		{
			if ((_msize(datalist) / sizeof(L)) == dataCount)
				datalist = resize((_msize(datalist) / sizeof(L)) * 2);

			*(datalist + dataCount) = value;
			dataCount++;
		}

		bool pop(LinkedList<V>* datalist)
		{
			if (empty())
				return false;

			datalist->eraseIndex(0);
			return true;
		}
		bool pop(vector<V>* datalist)
		{
			if (empty())
				return false;

			datalist->pop_back();
			return true;
		}
		bool pop(int* datalist)
		{
			if (empty())
				return false;

			dataCount--;
			return true;
		}

		V top(LinkedList<V>* datalist)
		{
			if (empty())
				return NULL;

			return datalist->head->value;
		}
		V top(vector<V>* datalist)
		{
			if (empty())
				return NULL;

			return datalist->back();
		}
		V top(int* datalist)
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