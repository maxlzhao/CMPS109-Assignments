// Max Zhao 1466223 mlzhao@ucsc.edu

template<typename T>
constexpr T pi = T(3.1415926535); // constexpr variables allowed to be templated

constexpr long long add(long long num)
{
	long long sum = 0; // local declaration of variables previously not allowed
	for (int i = 0; i <= num; i++) // for loops allowed now
	{
		sum += i;
	}

	return sum;
}

int main()
{
	constexpr auto sum = add(10);
	std::cout << res; // prints 55
}
