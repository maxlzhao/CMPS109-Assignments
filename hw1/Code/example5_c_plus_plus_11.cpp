// Max Zhao 1466223 mlzhao@ucsc.edu

#include <memory> // to access smart pointers

int main(int argc, char** argv){
	unique_ptr<Item> ptr1(new Item()); // creates new item

	unique_ptr<Item> ptr2(ptr1); // error, no copy constructor	
	unique_ptr<Item> ptr3;
	ptr3 = ptr1; // error, no assignment constructor
} // ptr1 out of scope, destroy and destruct pointed object