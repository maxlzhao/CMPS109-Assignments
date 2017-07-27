// Max Zhao 1466223 mlzhao@ucsc.edu

#include <memory> //to access c++11 smart pointers

shared_ptr<Item> find();

shared_ptr<Item> do_something(shared_ptr<Item> ptr);

void foo()
{
	shared_ptr<Item> ptr1(new Item);
	shared_ptr<Item> ptr2 = ptr1; // p1 and p2 share ownership of Item
	shared_ptr<Item> ptr3(new Item); // another Item
	ptr1 = find(); // p1 may no longer point to first Item
	do_something(p2);
	ptr3 -> defrangulate(); // calls a member function like a built-in pointer
	cout << *ptr2 << endl; // dereference like a built on pointer
	ptr1.reset; // reset with member function
	ptr2 = nullptr; // convert nullptr to empty shared_ptr
}