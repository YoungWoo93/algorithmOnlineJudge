#include <problem.h>
#include <test.h>
#include "../data structure/LinkedList.h"
#include "../data structure/Stack.h"
#include "../data structure/Queue.h"
#include "../data structure/Dequeue.h"

#ifdef _test_

#include <iostream>

template <typename T>
T getRandData(T start, T end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dis(start, end);


    return dis(gen);

}


using namespace dataStructures;


template <typename T>
void print(vector<T> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        cout << list[i] << " ";
    }
    cout << endl;
}

template <typename T>
void print(LinkedList<T> &list)
{
    for (int i = 0; i < list.size(); i++)
    {
        cout << list[i].value << " ";
    }
    cout << endl;
}

#include <list>
#include "../data structure/Graph.h"
#include "../data structure/Tree.h"
int main()
{
    while (true)
    {
        Tree<int> test; 

        test.add(5);
        test.add(2);
        test.add(3);
        test.add(7);
        test.add(1);
        test.add(6);
        test.add(9);

        treeNode<int>* temp = (treeNode<int>*)test.root->next[1];

        test.erase(temp);
      
       
    }
    return 0;
}
#endif
