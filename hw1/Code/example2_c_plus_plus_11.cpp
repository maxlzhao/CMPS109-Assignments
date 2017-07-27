// Max Zhao 1466223 mlzhao@ucsc.edu

void func(int n);      // #1
void func(char *s);    // #2

func(NULL);            // calls #1 before C++11, #2 after C++11;

char *ptr = nullptr;   // ok
int *pi = nullptr;     // ok
bool a = nullptr;      // a is false
int i = nullptr;       // error