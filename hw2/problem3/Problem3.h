// Max Zhao mlzhao 1466223

#include <iostream> // cpp standard library header
#include <algorithm> // used for sorting and swapping

using namespace std;

class Heap // begin declaration of Heap class
{
	private:
		int * array; // array data structure used to store data of heap
		int MaxSize, Nel; // private member variables to dictate max size of heap
		void adjust (int a[], int i, int n); // function to adjust heap after insertions

	public:
		Heap(int MSize); // constructor
		bool insert (int item); // inserts single integers into MAX heap
		bool delMax(int & item); // deletes maximum value from heap
		Heap(const Heap& copy); // copy constructor

		friend Heap operator+(const Heap& heap1, int item); // overloading of + operator for addition of heap and single integer
		friend Heap operator+(const Heap& heap1, const Heap& heap2); // overloading of + operator for addition of two heaps
		int operator[](int i); // overloading of [] operator to allow for accessing heap as if it were sorted array
		Heap& operator=(const Heap heap); // overloading of = operator to allow for assigment
		friend void swap(Heap& first, Heap& second); // helper function used for = overloading
		Heap& operator+=(const Heap& heap);
		Heap& operator+=(int item);
		friend ostream& operator<<(ostream& os, const Heap& heap); // overloading of << operator

		~Heap(); // destructor
};