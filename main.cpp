#include <iostream>
#include <string>
#include "Regexp/Regexp.h"
#include "Hashtable/PearsonHashtable8.h"

using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;

    Regexp regularexpression("a&b**|c");
    cout << regularexpression.toPostfix() << endl;

    return 0;
}