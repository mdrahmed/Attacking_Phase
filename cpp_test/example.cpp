#include <iostream>
using namespace std;

int foo() {
    cout << "Original foo() function\n";
    return 0;
}

int main() {
    if(foo()){
	cout<<"foo is false.\n";
    }
    return 0;
}

