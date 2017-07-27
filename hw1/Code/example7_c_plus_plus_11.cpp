// Max Zhao 1466223 mlzhao@ucsc.edu

class foo
{
	int x;
	int y;
	int a[5];
	int b = 10; // in-class initialization of data members only available in C++11
	public:
		foo(int i, int j);
		foo() : a{1, 2, 3, 4, 5} {} // member array initializer
};

Foo bar {1,2}; // equivalent to Foo bar(1,2);

int* x = new int[3] {1, 2, 3}; // only available in C++11

