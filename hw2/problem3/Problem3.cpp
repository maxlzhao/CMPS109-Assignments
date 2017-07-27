// Max Zhao mlzhao 1466223

#include "Problem3.h"

using namespace std;

// constructor
Heap::Heap(int MSize):MaxSize(MSize)
{
	array = (int *) calloc(MSize,sizeof(int)); // allocates array with size accordingly to user-provided max size
	Nel = 0;
}

// destructor
Heap::~Heap()
{
	delete[] array; // frees memory allocated to array
}

// copy constructor
Heap::Heap(const Heap& copy):MaxSize(copy.MaxSize)
{
	array = (int *) calloc(MaxSize,sizeof(int)); // allocates copied array with same memory as original array
	for(int i = 0; i < MaxSize; i++){
		array[i] = copy.array[i]; // copies each respective element into its respective place in copied array
		//cout << array[i] << endl;
	}
	//cout << endl;
}

// + operator overloaded to allow adding of two heaps
Heap operator+(const Heap& heap1, const Heap& heap2){
	Heap newHeap(heap1.MaxSize + heap2.MaxSize); // creates a new heap to store data from both heaps
	//cout << newHeap.MaxSize << endl;
	for(int i = 0; i < heap1.MaxSize; i++){
		newHeap.insert(heap1.array[i]);          // inserts data from first heap added
	}
	for(int i = 0; i < heap2.MaxSize; i++){
		newHeap.insert(heap2.array[i]);          // inserts data from second heap added
	}
	return newHeap;
}

// + operator overloaded to allow adding of a single integer to a heap
Heap operator+(const Heap& heap1, int item)
{
	Heap newHeap(heap1.MaxSize + 1);             // creates a new heap with size 1 larger to account for integer added
	// cout << newHeap.MaxSize << endl;
	for(int i = 0; i < heap1.MaxSize; i++){
		newHeap.insert(heap1.array[i]);          // inserts data from first heap added
	}
	newHeap.insert(item);                        // inserts the single element
	cout << "Created new heap and inserted " << item << endl;
	return newHeap;
}

// [] operator overloaded to allow for accessing indiv elements of the heap as if they were in a sorted array
int Heap::operator[](int i ){
	if(i > this->MaxSize){                       // accoutns for overflow/invalid index
		cout << "invalid range" << endl;
		return -1;
	}
	Heap sortedHeap = *this;                     // creates a new heap w/ assignment operator to original heap
	//cout << sortedHeap << endl;
	sort(sortedHeap.array, sortedHeap.array + sortedHeap.MaxSize); // sorts the new heap from smallest to largest

	return sortedHeap.array[MaxSize-i];          // returns i'th largest element in heap
}

// = operator overloaded to allow for heap assignments
Heap& Heap::operator=(Heap heap)
{
	swap(*this, heap);                           // access swap helper function for assignment
	return *this;
}

// additional swap helper function to use with = operator overloading
void swap(Heap& first, Heap& second)
{
	using std::swap;
	swap(first.MaxSize, second.MaxSize);     	 //swap members of the two heaps
	swap(first.array, second.array);
}

// += opeartor overloaded to allow for heap assignments
Heap& Heap::operator+=(int item)
{
	Heap newHeap(this->MaxSize+1);               // creates new heap to encompass added integer
	for (int i = 0; i < this->MaxSize; i++) {
		newHeap.insert(this->array[i]);          // adds old elements
	}
	//this->~Heap();
	newHeap.insert(item);                        // inserts new elements into array
	*this = newHeap; 
	return *this;                                // returns pointer to this
}

Heap& Heap::operator+=(const Heap& heap)
{
	Heap newHeap(heap.MaxSize+this->MaxSize);   // creates new heap large enough to store data from both heaps
	for (int i = 0; i < heap.MaxSize; i++) {    // inserts data form first heap
		newHeap.array[i] = heap.array[i];
	}
	for (int i = 0; i < this->MaxSize; i++) {   // inserts data from second heap
		newHeap.insert(this->array[i]);
	}
	*this = newHeap;
	return *this;                               // returns pointer to this
}

// << operator overloaded to allow for printing heaps on cout
ostream& operator<<(ostream& os, const Heap& heap)
{
    for(int i = 0; i < heap.MaxSize; i++){       // iterates through heap to print individual elements
		os << heap.array[i] << endl;
	}
	os << endl;
	return os;
}

// adjust heap after insertion
void Heap::adjust (int a[], int i, int n)
{
	int j = 2*i, item = a[i];
	while ( j <= n )
	{
		if (j<n && (a[j] < a[j+1])) j++;
			// Compare left and right child
			// and let j be the larger child
		if ( item >= a[j] ) break;
		a[j/2] = a[j]; j*=2;
	}
	a[j/2] = item;
}

// inserts single integer into heap
bool Heap::insert (int item)
{
	int i = Nel++;
	if ( i == MaxSize)
	{
		cout << "heap size exceeded" << endl;
		return false;
	}
	while ( (i > 0 ) && ( array[i/2] < item )) {
		array[i] = array[i/2];
		i/=2;
	}
	array[i] = item;
	return true;
}

// deletes the maximum value from the heap
bool Heap::delMax(int & item)
{
	if ( !Nel) { cout << "heap is empty" << endl ; return false; }
	item = array[0];
	array [0] = array[Nel--];
	adjust (array,0,Nel);
	return true;
}
