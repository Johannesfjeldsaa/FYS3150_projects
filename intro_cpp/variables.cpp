// learning how to declare variables in c++
// the basic syntax is:
// type variable_name = value;

#include <iostream>
#include <fmt/core.h>
using namespace std;

int predefinedinteger;

int main() {
    int integernumber = 5;
    string message = fmt::format("The integer number is {}", integernumber);
    cout << message << endl;
    predefinedinteger = 10;
    cout << int (integernumber + predefinedinteger) << endl;

    // using multiple variables
    int a, b, c;
    a = 5;
    b = 10;
    c = 15;
    cout << a + b + c << endl;

    // constants
    const double pi = 3.141592653589793;
    string pimessage = fmt::format("The value of pi is {}", pi);
    cout << pimessage << endl;
    return 0;
}