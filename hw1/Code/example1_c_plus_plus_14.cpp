// Max Zhao 1466223 mlzhao@ucsc.edu

std::vector<int> ints = { 1, 2, 3, 4 };
std::vector<std::string> strings = { "abc", "def", "ghi" };

auto lambda = [](auto x, auto y){ return x + y; };
// using generic parameters makes it so user doesn't have to write the same lambda twice,
// once for adding integers and once for adding strings

std::cout << "int result: " 
		  << std::accumulate(ints.begin(), ints.end(), 0, lambda) << "\n";
std::cout << "string result: "
          << std.accumulate(strings.begin(). strings.end(), std::string(""), lambda) << "\n";

// prints 
	// int result: 10
	// string result: abcdefghi