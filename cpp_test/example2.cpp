#include <iostream>
using namespace std;

bool isConditionFalse() {
    return false;
}

int main() {
    if (isConditionFalse()) {
        cout << "Condition is true." << endl;
    } else {
        cout << "Condition is false." << endl;
    }

    return 0;
}

