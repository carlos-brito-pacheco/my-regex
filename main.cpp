#include <iostream>
#include "src/Automata/NFA.h"
#include "src/Regexp/Lexer.h"

using namespace std;

int main() {
    Regexp::Lexer lex("a*bc");

    cout << lex.nextToken() << endl;
    cout << lex.nextToken() << endl;
    cout << lex.nextToken() << endl;
    cout << lex.nextToken() << endl;
    cout << lex.nextToken() << endl;
    cout << lex.nextToken() << endl;

//    Automata::NFA nfa("0");
//
//    nfa.addState("1", false);
//    nfa.addState("2", true);
//
//
//    nfa.addTransition("0", "1", nfa.epsilon);
//    nfa.addTransition("1", "2", 'c');
//
//    nfa.setString("c");
//    nfa.advance();
//    cout << nfa.accepts() << endl;



    return 0;
}

