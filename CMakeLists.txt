cmake_minimum_required(VERSION 3.7)
project(MyRegex)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Regexp/Regexp.cpp Regexp/Regexp.h
        Automata/DFA.cpp Automata/DFA.h
        Automata/NFA.cpp Automata/NFA.h
        Regexp/Errors.h
        Regexp/RegexpOperator.cpp Regexp/RegexpOperator.h
        Hashtable/Hashtable.h
        Hashtable/PearsonHashtable8.h
        Hashtable/HashtableErrors.h
        Regexp/Token.h
        Regexp/Parser.cpp Regexp/Parser.h
        Regexp/TokenTag.h Regexp/Lexer.cpp Regexp/Lexer.h Regexp/RegexpTokens.h Automata/State.cpp Automata/State.h Automata/Transition.h)
add_executable(MyRegex ${SOURCE_FILES})