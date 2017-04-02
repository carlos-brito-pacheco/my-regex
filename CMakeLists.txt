cmake_minimum_required(VERSION 3.7)
project(MyRegex)

set(CMAKE_CXX_STANDARD 11)


set(SOURCE_FILES
        main.cpp
#        Regexp/Regexp.cpp Regexp/Regexp.h
#        Automata/DFA.cpp Automata/DFA.h
        Automata/NFA.cpp Automata/NFA.h
#        Regexp/Errors.h
#        Regexp/RegexpOperator.cpp Regexp/RegexpOperator.h
        Hashtable/hashtable.h
        Hashtable/PearsonHashtable8.h
#        Regexp/Token.h
#        Regexp/Parser.cpp Regexp/Parser.h
#        Regexp/TokenTag.h
#        Regexp/Lexer.cpp Regexp/Lexer.h
#        Regexp/RegexpTokens.h
        Automata/State.cpp Automata/State.h
        Automata/Transition.h
        Set/Set.h
        Automata/AutomataErrors.h
        Automata/Transition.cpp)
add_executable(MyRegex ${SOURCE_FILES})