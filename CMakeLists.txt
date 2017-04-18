cmake_minimum_required(VERSION 3.7)
project(MyRegex)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        src/Automata/NFA.cpp src/Automata/NFA.h
        src/Regex/RegexErrors.h
        src/Hashtable/Hashtable.h
        src/Hashtable/PearsonHashtable8.h
        src/Regex/Token.h
        src/Regex/Lexer.cpp src/Regex/Lexer.h
        src/Regex/TokenDecls.h
        src/Automata/State.cpp src/Automata/State.h
        src/Automata/Transition.h
        src/Set/Set.h
        src/Automata/AutomataErrors.h
        src/Automata/Transition.cpp src/Regex/AutomataDecls.h src/Regex/Parser.cpp src/Regex/Parser.h src/Regex/Regex.cpp src/Regex/Regex.h)
add_executable(MyRegex ${SOURCE_FILES})