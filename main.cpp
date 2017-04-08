#include <iostream>
#include "src/Automata/NFA.h"

using namespace std;

int main() {

    Automata::NFA digits1("A"); // declare nfa digits with initial state "A"
    digits1.addState("B",true); // add state "B" as end state

    for (int i = 0; i < 10; i++)
        digits1.addTransition("A", "B", i + '0'); // add 10 transitions with digits 0-9 as symbols

    Automata::NFA digits2("AA"); // declare nfa digits with initial state "A"
    digits2.addState("BB",true); // add state "B" as end state

    for (int i = 0; i < 10; i++)
        digits2.addTransition("AA", "BB", i + '0'); // add 10 transitions with digits 0-9 as symbols

    Automata::NFA float_n = digits1.concatenate(digits2);

    cout << float_n.match("82") << endl;


    return 0;
}

