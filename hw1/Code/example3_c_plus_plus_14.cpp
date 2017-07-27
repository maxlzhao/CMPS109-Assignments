// Max Zhao 1466223 mlzhao@ucsc.edu

auto foo(int i)
{
	return 1.1; // return type deduced as 'double'
}

auto bar(int i)
{
	if (i > 0)
		return 2; 
	else
		return 1.0;
} // returns error, return type deduced as int in first return statement, double in second

auto recurSuccess(int i){
	if (i == 0)
		return i; // return type deduced as int
	else
		return recur(i + 1); // works properly
}

auto recurFail(int i){
	if(i != 0)
		return recur(i + 1); // error because function doesnt know return type
	else
		return i; // return type deduced as int
}