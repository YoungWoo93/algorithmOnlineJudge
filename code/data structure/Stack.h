#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

namespace dataStructures
{
	template <typename V>
	class Stack : public LinkedList<V>
	{
	public:
		void push(V value)
		{
			this->insert(value, 0);
		}

		V top()
		{
			
			return this->head->value;
		}

		bool pop()
		{
			if (this->size() == 0)
				return false;

			this->eraseIndex(0);

			return true;
		}

	protected:


	private:

	};
}