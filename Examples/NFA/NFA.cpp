#include <iostream>
#include "Hashtable/hashtable.h"
#include "Automata/NFA.h"

using namespace std;
using namespace Automata;

int main() {
    NFA nfa("0");

    // add the states

    // nfa.addState(state_name, is_end=false)
    nfa.addState("1");
    nfa.addState("2");
    nfa.addState("3");
    nfa.addState("4");
    nfa.addState("5");
    nfa.addState("6");
    nfa.addState("7");
    nfa.addState("8");
    nfa.addState("9");
    nfa.addState("10", true);

    // add the transitions

    //nfa.addTransition(source_name, destination_name, symbol)
    nfa.addTransition("0", "1", nfa.epsilon);
    nfa.addTransition("0", "7", nfa.epsilon);

    nfa.addTransition("1", "2", nfa.epsilon);
    nfa.addTransition("1", "4", nfa.epsilon);

    nfa.addTransition("2", "3", 'a');

    nfa.addTransition("3", "6", nfa.epsilon);

    nfa.addTransition("4", "5", 'b');

    nfa.addTransition("5", "6", nfa.epsilon);

    nfa.addTransition("6", "7", nfa.epsilon);
    nfa.addTransition("6", "1", nfa.epsilon);

    nfa.addTransition("7", "8", 'a');

    nfa.addTransition("8", "9", 'b');

    nfa.addTransition("9", "10", 'b');


    // Match the string
    cout << "Match? " << nfa.match("abababbbabababaabb") << endl;

    return 0;
}

