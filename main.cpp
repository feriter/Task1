#include <iostream>
#include "linked_list.h"

using namespace LLST;

void print_list(linked_list<int> & list) {
    for (auto it : list) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

void print_list(linked_list<char> & list) {
    for (auto it : list) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

void test1() {
    std::cout << "test1 begins" << std::endl;
    auto list1 = new linked_list<int>();
    std::cout << "is empty:" << list1->empty() << std::endl;
    std::cout << "full list: ";
    list1->push_back(1);
    list1->push_back(2);
    list1->push_back(3);
    list1->push_front(4);
    list1->push_front(5);
    list1->push_front(6);
    print_list(*list1);
    std::cout << "is empty:" << list1->empty() << std::endl;
    std::cout << "size of list: " << list1->size() << std::endl;
    std::cout << "front element: " << list1->front() << std::endl;
    std::cout << "back element: " << list1->back() << std::endl;
    std::cout << "delete last element: ";
    list1->pop_back();
    print_list(*list1);
    std::cout << "delete first element: ";
    list1->pop_front();
    print_list(*list1);
    std::cout << "test1 ends" << std::endl << std::endl;
}

void test2() {
    std::cout << "test2 begins" << std::endl;
    auto list1 = new linked_list<int>();
    std::cout << "full list: ";
    list1->push_back(1);
    list1->push_back(2);
    list1->push_back(3);
    list1->push_back(4);
    list1->push_back(2);
    list1->push_front(5);
    list1->push_front(6);
    list1->push_front(7);
    list1->push_front(8);
    print_list(*list1);
    std::cout << "delete element number 3: ";
    auto a = list1->begin();
    a++; a++;
    list1->erase(a);
    print_list(*list1);
    std::cout << "delete elements from 2 to 4 : ";
    auto b1 = list1->begin();
    b1++;
    auto b2 = list1->begin();
    b2++; b2++; b2++;
    list1->erase(b1, b2);
    print_list(*list1);
    std::cout << "delete all occurrences of 2: ";
    list1->remove(2);
    print_list(*list1);
    std::cout << "insert 0 before element number 2: ";
    auto c = list1->begin();
    c++;
    list1->insert(c, 0);
    print_list(*list1);
    std::cout << "test2 ends" << std::endl << std::endl;
}

void test3() {
    std::cout << "test3 begins" << std::endl;
    auto list1 = new linked_list<int>;
    std::cout << "full list1: ";
    list1->push_back(1);
    list1->push_back(2);
    list1->push_back(3);
    list1->push_front(4);
    list1->push_front(5);
    list1->push_front(6);
    print_list(*list1);
    auto list2 = new linked_list<int>;
    std::cout << "full list2: ";
    list2->push_back(7);
    list2->push_back(8);
    list2->push_back(9);
    print_list(*list2);
    std::cout << "concat of list1 and list2: ";
    *list1 += *list2;
    print_list(*list1);
    std::cout << "is list1 equal to list2: " << ((*list1)==(*list2)) << std::endl;
    auto list3 = new linked_list<int>;
    std::cout << "full list3: ";
    list3->push_back(7);
    list3->push_back(8);
    list3->push_back(9);
    print_list(*list3);
    std::cout << "is list2 equal to list3: " << ((*list2)==(*list3)) << std::endl;
    std::cout << "is list1 not equal to list3: " << ((*list1)!=(*list3)) << std::endl;
    std::cout << "test3 ends" << std::endl << std::endl;
}

int main() {
    test1();
    test2();
    test3();
    return 0;
}
