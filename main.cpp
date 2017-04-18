#include <iostream>
#include "src/Regex/Regex.h"

using namespace std;

int main() {

    Regex::Regex regex("aaa(a|b)+c*");
    cout << "Match? " << regex.match("aaabbababacc") << endl;

    return 0;
}

