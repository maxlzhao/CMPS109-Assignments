// Max Zhao mlzhao 1466223

#include "Problem3.h"

int main()
{
	Heap base(10);                          // creates a new heap w/ MaxSize 10
	for(int i = 0; i < 10; i++){
		base.insert(i);                     // inserts values 0-9 into 'base'
	}
	cout << "Control heap" << endl;
	cout << base << endl;

	// copy constructor
	Heap copiedHeap(base);
	cout << "Copied heap w/ copy constructor" << endl;
	cout << copiedHeap << endl;             // overloaded << operator

	// overloaded + operator
	Heap plusHeap(base);
	cout << "Adding single integer to heap with overloaded + operator" << endl;
	cout << plusHeap + 5 << endl;           // addition of a heap and single integer

	cout << "Adding two heaps together with overloaded + operator" << endl;
	cout << plusHeap + copiedHeap << endl;  // addition of two heaps

	// overloaded [] operator
	cout << "Accessing individual elements of the heap" << endl;
	cout << "3rd largest element in heap is " << base[3] << endl;
	cout << "5th largest element in heap is " << base[5] << endl;
	cout << endl;

	// overloaded = operator
	Heap equalHeap = base;
	cout << "Heap created with overloaded = assignment operator" << endl;
	cout << equalHeap << endl;

	// overloaded += operator
	equalHeap+=5;
	cout << "Adding 5 to heap with += assignment operator" << endl;
	cout << equalHeap<< endl;

	equalHeap+=base;
	cout << "Adding two heaps with += assignment operator" << endl;
	cout << equalHeap << endl;

	// given delMax function
	cout << "Given delMax function, deletes max element from heap" << endl;
	int x;
	base.delMax(x);
	cout << base << endl;

	return 0;
}