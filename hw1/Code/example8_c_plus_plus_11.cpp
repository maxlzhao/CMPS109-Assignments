// Max Zhao 1466223 mlzhao@ucsc.edu

int array[4] = {1, 2, 3, 4};

for(int &x : array)
	std::cout << x << ' '; // prints 1 2 3 4

std::vector<int> vector = {0, 1, 2, 3, 4, 5};
for(auto i : vector)
	std::cout << i << ' '; // prints 0 1 2 3 4 5

