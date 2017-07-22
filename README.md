# What is it?
This is a Regex engine that matches a string like `abbccccaa` to a pattern like `a+b*(cc)*aa`.
It does this by building a Non-Deterministic Finite Automata  out of the given regular expression and recursively
emulating the automata.

One will find that the code has been abstracted in such a way that it will be easy to understand.
Albeit, there is still much to do. In particular, I have to profile the code.

# Basic usage
````cpp
#include <iostream>
#include "src/Regex/Regex.h"

using namespace std;

int main() {

    Regex::Regex regex("aaa(a|b)+c*");
    cout << "Match? " << regex.match("aaabbababacc") << endl;

    return 0;
}
````

Output:

`~ $ Match? 1`

# How-to use
Please see the Examples/ directory for examples on how to use the code. Each subfolder will have an explanation.

# Building

To build the project you just have to clone the repo using

`git clone https://github.com/carlosb/regexp-to-automata`

Navigate to the directory where you cloned:

`cd dir_where_you_cloned`

Type in:

````
cmake .
cd cmake-build-debug
make
````

And to execute:

`./MyRegex`

# Notes on Building
This project is coded using C++11 syntax. This should be set in CMakeLists.txt if using CMake with the flag

`set(CMAKE_CXX_STANDARD 11)`
