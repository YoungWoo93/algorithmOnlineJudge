#include <problem.h>
#include <test.h>
#include "../data structure/test.h"

#ifdef _test_

#include <iostream>


using namespace dataStructures;

template <typename T>
T getRandData(T start, T end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dis(start, end);


    return dis(gen);

}

void testMain()
{
    std::cout << "test main called" << std::endl;
}


int main()
{
    while (true) {
        vector<int> testList1 = { 1, 2, 3 };
        vector<int> testList2 = { 4, 5, 6 };


        LinkedList<int> testDefault;
        LinkedList<int> testSingle(singly);
        LinkedList<int> testDouble(doubly);

        testDefault.name = "testDefault";
        testSingle.name = "testSingle";
        testDouble.name = "testDouble";

        cout << testDefault.size() << endl;
        cout << testSingle.size() << endl;
        cout << testDouble.size() << endl;

        testDefault.add(testList1);
        testSingle.add(testList2);
        testDouble.add(testList1);

        cout << testDefault.size() << endl;
        cout << testSingle.size() << endl;
        cout << testDouble.size() << endl;

        testDefault.add(testSingle);
        testDouble.add(testList2);
        testSingle.add(testList1);

        cout << testDefault.size() << endl;
        cout << testSingle.size() << endl;
        cout << testDouble.size() << endl;

        testDefault.add(testDouble);

        cout << testDefault.at(0) << endl;
        cout << testDefault.at(1) << endl;
        cout << testDefault.at(100) << endl;

        LinkedList<int> test;
        testDefault.clone(test);//

        test.insert(testDefault, 1);
        test.erase(3);
        cout << test.size() << endl;
        test.erase(3, 5);

        for (auto item : test.getArray())
        {
            cout << item << " ";
        }
        cout << endl;
    }
    

    return 0;
}
#endif
