#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "LinkedList.h"

using namespace std;

namespace dataStructures
{
	template <typename V>
	class Graph
	{
	public:
		Graph() {

		}
		~Graph() {

		}

		void add(V value) {
			node<V>* newNode = new node<V>(value);
			
			add(newNode);
		}
		void add(node<V>* addNode) {
			nodeList.push_back(addNode);
			sort(nodeList.begin(), nodeList.end(), [](node<V>* first, node<V>* second) { return first->value < second->value; });
		}

		bool erase(V value) {
			int nodeIndex = findNodeIndex(value);
			return eraseIndex(nodeIndex);
		}
		bool erase(node<V>* eraseNode) {
			auto iter = find(nodeList.begin(), nodeList.end(), eraseNode);

			if (iter == nodeList.end())
				return false;

			for (auto link : (*iter)->next) {
				disconnectLink(eraseNode, link.first);
			}
			for (auto link : (*iter)->prev) {
				disconnectLink(link.first, eraseNode);
			}

			delete eraseNode;
			nodeList.erase(iter);

			return true;
		}
		bool eraseIndex(int nodeIndex) {
			if (nodeIndex < 0 || size() < nodeIndex)
				return false;

			delete nodeList[nodeIndex];
			nodeList.erase(nodeList.begin() + nodeIndex);

			return true;
		}

		node<V>* findNode(V value) {
			auto iter = find_if(nodeList.begin(), nodeList.end(), [=](const node<V>* ptr) {return ptr->value == value; });

			return *iter;
		}

		int findNodeIndex(V value) {
			auto iter = find_if(nodeList.begin(), nodeList.end(), [=](const node<V>* ptr) {return ptr->value == value; });
			if (iter == nodeList.end())
				return -1;

			return iter - nodeList.begin();
		}

		bool findLink(int startIndex, int endIndex) {
			if (startIndex < 0 || size() < startIndex)
				return false;
			if (endIndex < 0 || size() < endIndex)
				return false;

			return findLink(nodeList[startIndex], nodeList[endIndex]);
		}
		bool findLink(node<V>* startNode, node<V>* endNode) {
			auto iter = find_if(startNode->next.begin(), startNode->next.end(), [=](const pair<node<V>*, int> link) {return link.first == endNode; });
			if (iter == nodeList.end())
				return false;

			return true;
		}

		pair<node<V>*, int> getLink(int startIndex, int endIndex) {
			if (startIndex < 0 || size() < startIndex)
				return false;
			if (endIndex < 0 || size() < endIndex)
				return false;

			return getLink(nodeList[startIndex], nodeList[endIndex]);
		}

		pair<node<V>*, int> getLink(node<V>* startNode, node<V>* endNode) {
			auto iter = find_if(startNode->next.begin(), startNode->next.end(), [=](const pair<node<V>*, int> link) {return link.first == endNode; });
			if (iter == startNode->next.end())
				return {nullptr, 0};

			return *iter;
		}

		bool modify() {
			/// <summary>
			/// 
			/// 정의필요
			/// 구현필요 
			/// 
			/// </summary>
			/// <returns></returns>
			return true;
		}

		bool connectLink(int startIndex, int endIndex, int cost = 0) {
			if (startIndex < 0 || size() < startIndex)
				return false;
			if (endIndex < 0 || size() < endIndex)
				return false;

			return connectLink(nodeList[startIndex], nodeList[endIndex], cost);
		}
		bool connectLink(node<V>* startNode, node<V>* endNode, int cost = 0) {
			startNode->next.push_back({ endNode, cost });
			endNode->prev.push_back({ startNode, cost });

			sort(startNode->next.begin(), startNode->next.end(), [](pair<node<V>*, int> first, pair<node<V>*, int> second) { return first.first->value < second.first->value; });
			return true;
		}

		bool disconnectLink(int startIndex, int endIndex) {
			if (startIndex < 0 || size() < startIndex)
				return false;
			if (endIndex < 0 || size() < endIndex)
				return false;

			return disconnectLink(nodeList[startIndex], nodeList[endIndex]);
		}
		bool disconnectLink(node<V>* startNode, node<V>* endNode) {

			auto iter = find_if(startNode->next.begin(), startNode->next.end(), [=](const pair<node<V>*, int>& p) { return p.first == endNode; });
			if (iter == startNode->next.end())
				return false;;

			startNode->next.erase(iter);
			endNode->prev.erase(find_if(endNode->prev.begin(), endNode->prev.end(), [=](const pair<node<V>*, int> link) {return link.first == startNode; }));

			return true;
		}

		bool modifyLink(int startIndex, int endIndex, pair<node<V>*, int> link) {
			if (startIndex < 0 || size() < startIndex)
				return false;
			if (endIndex < 0 || size() < endIndex)
				return false;

			return modifyLink(nodeList[startIndex], nodeList[endIndex], link);
		}
		bool modifyLink(node<V>* startNode, node<V>* endNode, pair<node<V>*, int> link) {
			if(!disconnectLink(startNode, endNode))
				return false;

			connectLink(startNode, link.first, link.second);
			return true;
		}

		int size() {
			return nodeList.size();
		}

		bool empty() {
			return size() == 0;
		}

	protected:

	private:



	public:

	protected:
		vector<node<V>*> nodeList;
	private:



	};
}