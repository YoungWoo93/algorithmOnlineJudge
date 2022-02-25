#pragma once

#include <vector>
#include <iostream>
#include <string>

using namespace std;

namespace dataStructures
{

#define	singly	1
#define	doubly	2

	template <typename V>
	struct node
	{
		V value;
		vector<pair<node*, int>> prev;
		vector<pair<node*, int>> next;

		node(){};
		node(V initValue) : value(initValue) {};
		~node() {
			if (std::is_pointer<V>::value)
				delete (V*&)value;
		};

		bool operator==(node<V> &cmp) {
			return value == cmp.value;
		}

		bool operator==(V cmp) {
			return value == cmp;
		}

		node<V> operator=(node<V> &other) {
			node<V> ret(other.value);
			ret.prev.assign(other.prev.begin(), other.prev.end());
			ret.next.assign(other.next.begin(), other.next.end());

			return  ret;
		}
	};

	template <typename V>
	class LinkedList
	{
	public:
		LinkedList() {
			this->linkType = singly;
			linearType = true;
		}
		LinkedList(int linkType) {
			this->linkType = linkType;
			linearType = true;
		}
		~LinkedList() {
			for (node<V>* item : itemList)
				delete item;

			itemList.clear();
		}

		unsigned int size() {
			return itemList.size();
		}

		V at(unsigned int index) {
			try {
				eraseIndexCheck(index);
			}
			catch (const std::exception& e) {
				cout << "at " << e.what() << endl;

				return itemList[size() - 1]->value;
			}
			return itemList[index]->value;
		}

		vector<V> getArray() {
			vector<V> ret(itemList.size());

			unsigned int index = 0;
			for (auto item : itemList)
				ret[index++] = item->value;

			return ret;
		}

		void clone(LinkedList<V>& list) {
			list.erase(0, list.size() - 1);
			list.linearType = linearType;
			list.linkType = linkType;

			list.add(*this);
		}


		void connectPrevLink(node<V>* prevNode, node<V>* nextNode)
		{
			nextNode->prev.push_back({ prevNode, 0});
		}
		void connectNextLink(node<V>* prevNode, node<V>* nextNode)
		{
			prevNode->next.push_back({ nextNode, 0});
		}
		void connectLink(node<V>* prevNode, node<V>* nextNode)
		{
			connectNextLink(prevNode, nextNode);

			if (linkType == doubly)
				connectPrevLink(prevNode, nextNode);

		}
		void connectLink(int startIndex, int endIndex)
		{
			try {
				eraseIndexCheck(startIndex);
				eraseIndexCheck(endIndex);
			}
			catch (const std::exception& e) {
				cout << "connectLink " << e.what() << endl;
				return;
			}

			connectNextLink(itemList[startIndex], itemList[endIndex]);

			if (linkType == doubly)
				connectPrevLink(itemList[startIndex], itemList[endIndex]);

		}

		void disconnectNextLink(node<V>* prevNode, node<V>* nextNode)
		{
			if (prevNode->next.empty())
				return;

			auto iter = find_if(prevNode->next.begin(), prevNode->next.end(), [=](const pair<node<V>*, int>& p) { return p.first == nextNode; });
			if (iter != prevNode->next.end())
				prevNode->next.erase(iter);
		}
		void disconnectPrevLink(node<V>* prevNode, node<V>* nextNode)
		{
			if (nextNode->prev.empty())
				return;

			auto iter = find_if(nextNode->prev.begin(), nextNode->prev.end(), [=](const pair<node<V>*, int>& p) { return p.first == prevNode; });
			if (iter != nextNode->prev.end())
				nextNode->next.erase(iter);
		}
		void disconnectLink(int startIndex, int endIndex)
		{
			try {
				eraseIndexCheck(startIndex);
				eraseIndexCheck(endIndex);
			}
			catch (const std::exception& e) {
				cout << "disconnectLink " << e.what() << endl;
				return;
			}

			disconnectNextLink(itemList[startIndex], itemList[endIndex]);

			if (linkType == doubly)
				disconnectPrevLink(itemList[startIndex], itemList[endIndex]);
		}

		void disconnectNextLinkAll(node<V>* node)
		{
			node->next.clear();
		}
		void disconnectNextLinkAll(int index)
		{
			try {
				eraseIndexCheck(index);
			}
			catch (const std::exception& e) {
				cout << "disconnectLink " << e.what() << endl;
				return;
			}

			disconnectNextLinkAll(itemList[index]);
		}
		void disconnectPrevLinkAll(node<V>* node)
		{
			node->prev.clear();
		}
		void disconnectPrevLinkAll(int index)
		{
			try {
				eraseIndexCheck(index);
			}
			catch (const std::exception& e) {
				cout << "disconnectLink " << e.what() << endl;
				return;
			}

			disconnectPrevLinkAll(itemList[index]);
		}
		void disconnectLinkAll(node<V>* node)
		{
			disconnectNextLinkAll(node);
			disconnectPrevLinkAll(node);
		}
		void disconnectLinkAll(int index)
		{
			try {
				eraseIndexCheck(index);
			}
			catch (const std::exception& e) {
				cout << "disconnectLink " << e.what() << endl;
				return;
			}

			disconnectLinkAll(itemList[index]);
		}

		bool add(LinkedList<V> &list) {

			try {
				typeCheck(list);
			}
			catch (const std::exception& e) {
				cout << "add " << e.what() << endl;
				return false;
			}

			disconnectNextLinkAll(list.tail);
			connectLink(this->tail, list.head);
			connectLink(this->tail, list.head);

			this->tail = list.tail;
			this->itemList.insert(this->itemList.end(), list.itemList.begin(), list.itemList.end());
			list.itemList.clear();

			return true;
		}
		bool add(vector<V> &list) {

			for (V item : list)
				add(item);

			return true;
		}
		bool add(node<V>* node) {
			if (itemList.empty())
			{
				head = node;
				tail = node;
				itemList.push_back(node);

				return true;
			}

			if (linkType == doubly)
				connectPrevLink(tail, node);

			connectNextLink(tail, node);
			tail = node;

			itemList.push_back(node);

			return true;
		}
		bool add(V value) {
			node<V>* newNode = new node<V>(value);

			add(newNode);

			return true;
		}

		bool insert(LinkedList<V> &list, int index)
		{
			try {
				insertIndexCheck(index);
				typeCheck(list);
			}
			catch (const std::exception& e) {
				cout << "insert " << e.what() << endl;
				return false;
			}

			if (index == size())
			{
				add(list);
				return true;
			}

			disconnectPrevLinkAll(list.head);
			disconnectNextLinkAll(list.tail);

			if (index == 0)
			{
				disconnectPrevLinkAll(head);
				connectLink(list.tail, head);

				head = list.head;
			}
			else
			{
				disconnectLink(index - 1, index);
				connectLink(itemList[index - 1], list.head);
				connectLink(list.tail, itemList[index]);
			}

			this->itemList.insert(this->itemList.begin() + index, list.itemList.begin(), list.itemList.end());
			list.itemList.clear();

			return true;
		}
		bool insert(V value, int index)
		{
			try {
				insertIndexCheck(index);
			}
			catch (const std::exception& e) {
				cout << "insert " << e.what() << endl;
				return false;
			}

			node<V>* newNode = new node<V>(value);

			if (index == size())
			{
				add(newNode);
				return true;
			}


			if (index == 0)
			{
				disconnectPrevLinkAll(head);
				connectLink(newNode, head);

				head = newNode;
			}
			else
			{
				disconnectLink(index - 1, index);
				connectLink(itemList[index - 1], newNode);
				connectLink(newNode, itemList[index]);
			}

			itemList.insert(itemList.begin() + index, newNode);

			return true;
		}

		bool erase(V value)
		{
			int index = this->find(value);
			if (index == -1)
				return false;

			eraseIndex(index);

			return true;
		}
		bool erase(bool (*option)(V ...))
		{
			int index = this->find(option);
			if (index == -1)
				return false;

			eraseIndex(index);

			return true;
		}
		bool erase(int startIndex, int endIndex)
		{
			try {
				eraseIndexCheck(startIndex);
				eraseIndexCheck(endIndex);
			}
			catch (const std::exception& e) {
				cout << "erase " << e.what() << endl;
				return false;
			}

			vector<node<V>*> temp(itemList.begin() + startIndex, itemList.begin() + endIndex);

			if (startIndex == 0)
			{
				disconnectLink(endIndex, endIndex + 1);
				head = itemList[endIndex + 1];
			}
			else if (endIndex == size() - 1)
			{
				disconnectLink(startIndex - 1, startIndex);
				tail = itemList[startIndex - 1];
			}
			else
			{
				disconnectLink(startIndex - 1, startIndex);
				disconnectLink(endIndex, endIndex + 1);
				connectLink(startIndex - 1, endIndex + 1);
			}

			itemList.erase(itemList.begin() + startIndex, itemList.begin() + endIndex);
			for (auto item : temp)
				delete item;

			return true;
		}

		bool eraseIndex(unsigned int index)
		{
			try {
				eraseIndexCheck(index);
			}
			catch (const std::exception& e) {
				cout << "erase " << e.what() << endl;
				return false;
			}

			auto temp = itemList[index];

			if (size() != 1)
			{
				if (index == 0)
				{
					disconnectLink(index, index + 1);
					head = itemList[index + 1];
				}
				else if (index == size() - 1)
				{
					disconnectLink(index - 1, index);
					tail = itemList[index - 1];
				}
				else
				{
					disconnectLink(index, index + 1);
					disconnectLink(index - 1, index);
					connectLink(index - 1, index + 1);
				}
			}

			itemList.erase(itemList.begin() + index);


			delete temp;

			return true;
		}

		bool eraseAll(V value)
		{
			int cmp = size();

			for (int i = 0; i < size(); i++)
			{
				if (*itemList[i] == value)
					eraseIndex(i--);
			}

			return cmp == size();
		}
		bool eraseAll(V value, bool (*compare)(V cmpValue, V itemListValue))
		{
			int cmp = size();

			for (int i = 0; i < size(); i++)
			{
				if (compare(*itemList[i].value, value))
					eraseIndex(i--);
			}

			return cmp == size();
		}
		bool eraseAll(node<V> node)
		{
			int cmp = size();

				for (int i = 0; i < size(); i++)
				{
					if (*itemList[i] == node)
						eraseIndex(i--);
				}

			return cmp == size();
		}

		int find(V value)
		{
			for (int i = 0; i < size(); i++)
			{
				if (*itemList[i] == value)
					return i;
			}

			return -1;
		}

		vector<int> findAll(V value)
		{
			vector<int> ret;

			for (int i = 0; i < size(); i++)
			{
				if (*itemList[i] == value)
					ret.push_back(i);
			}

			return ret;
		}
		node<V> max()
		{
			if (itemList.empty())
				return *head;

			int index = 0;

			for (int i = 1; i < size(); i++)
			{
				if (itemList[i]->value > itemList[index]->value)
					index = i;
			}

			return *itemList[index];
		}
		node<V> min()
		{
			if (itemList.empty())
				return *head;

			int index = 0;

			for (int i = 1; i < size(); i++)
			{
				if (itemList[i]->value < itemList[index]->value)
					index = i;
			}

			return *itemList[index];
		}
				

		LinkedList& operator+=(LinkedList& list)
		{
			add(list);

			return *this;
		}
		LinkedList& operator+=(vector<V>& list)
		{
			add(list);

			return *this;
		}
		LinkedList& operator+=(V value)
		{
			add(value);

			return *this;
		}
		LinkedList& operator-=(V value)
		{
			erase(find(value));

			return *this;
		}
		node<V> operator[](int index)
		{
			try {
				eraseIndexCheck(index);
			}
			catch (const std::exception& e) {
				cout << "[] " << e.what() << endl;

				return *itemList.back();
			}
			
			return *itemList[index];
		}

	protected:
		bool typeCheck(LinkedList<V>& list) 
		{
			if (this->linearType != list.linearType)
			{
				throw out_of_range("LinkedList typCheck linearType mismatch\n");
				return false;
			}
			if (this->linkType != list.linkType)
			{
				throw out_of_range("LinkedList typCheck linkType mismatch\n");
				return false;
			}

			return true;
		}
		bool insertIndexCheck(int index) 
		{
			if (index < 0 || size() < index)
			{
				throw out_of_range("index out of range\n");
				return false;
			}

			return true;
		}
		bool eraseIndexCheck(int index)
		{
			if (index < 0 || size() <= index)
			{
				throw out_of_range("index out of range\n");
				return false;
			}

			return true;
		}
	
	private:



	public:
		bool				linearType;
		int					linkType;

		node<V>* head;
		node<V>* tail;
		vector<node<V>*>	itemList;
	protected:

	private:

	};
}