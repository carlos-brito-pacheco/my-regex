# Description
Regular expression parser. This will be a part of a compiler for a small language.

# Notes on Building
This project is coded using C++11 syntax. This should be set in CMakeLists.txt if using CMake with the flag

`set(CMAKE_CXX_STANDARD 11)`

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
