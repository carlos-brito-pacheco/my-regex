cmake_minimum_required(VERSION 3.7)
project(MyRegex)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
#        Regexp/Regexp.cpp Regexp/Regexp.h
        src/Automata/NFA.cpp src/Automata/NFA.h
        src/Regexp/Errors.h
#        Regexp/RegexpOperator.cpp Regexp/RegexpOperator.h
        src/Hashtable/Hashtable.h
        src/Hashtable/PearsonHashtable8.h
        src/Regexp/Token.h
#        Regexp/Parser.cpp Regexp/Parser.h
        src/Regexp/Lexer.cpp src/Regexp/Lexer.h
        src/Regexp/TokenDecls.h
        src/Automata/State.cpp src/Automata/State.h
        src/Automata/Transition.h
        src/Set/Set.h
        src/Automata/AutomataErrors.h
        src/Automata/Transition.cpp src/Regexp/AutomataDecls.h)
add_executable(MyRegex ${SOURCE_FILES})