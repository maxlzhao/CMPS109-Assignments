// Max Zhao 1466223 mlzhao@ucsc.edu

class
[[deprecated]] foo{
};

[[deprecated("updated with 'foobar', improved interface")]]
int bar(){ return 1 };

int main()
{
	foo a;
	return bar();
}

// at compile:
	// warning: 'foo' is deprecated [-Wdeprecated-declarations]
	// warning: 'bar' is deprecated: updated with 'foobar', improved interface