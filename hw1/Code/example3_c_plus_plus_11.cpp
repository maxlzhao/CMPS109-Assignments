// Max Zhao 1466223 mlzhao@ucsc.edu

auto line = [](double m, double x, double b) -> double
	{
	return m*x+b;
	};
cout << sum(1,2.3) << endl; // prints 5
cout << sum(3,2,1) << endl; // prints 7

vector<int> numarray{1,2,3,4,5,10,15};

int mult = 5;
size_t c;
c = count_if(numarray.begin(), numarray.end(), [mult](int x){ return !(x % mult); });
// lambda expression to return multiples of 'mult'
cout << "number of integers that are a multiple of " << mult << " : " << c << endl;
// prints 3