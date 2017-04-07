//<editor-fold desc="Preamble">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Copyright (C) 3/23/17 Carlos Brito
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.*
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

//<editor-fold desc="Description">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/22/17.
 *
 * Description:
 * Header file for the class NFA.
 *
 * This file defines the methods and attributes for a
 * non deterministic finite automaton.
 *
 * We keep a pointer to the start state as well as a
 * table for the states. We identify a state by a name key,
 * such as "s1" or "state3". It will be up to the user of the
 * class to keep track of the names he/she gives to the
 * states.
 * <<< This means that we have to make references to the states
 * with their names >>>
 *
 * Please see the book:
 *
 * Compilers: Principles, Techniques and Tools (Aho et Al.)
 *
 *
 *
 *
 *
 *
 * TODO:
 *
 *
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

#ifndef MYREGEX_NFA_H
#define MYREGEX_NFA_H

#include "State.h"
#include "../Hashtable/Hashtable.h"
namespace Automata {

    class NFA {
    public:
        // TYPEDEFS
        typedef hashtable<std::string, State> state_table_type;
        typedef Set<State, State::Hasher> state_set_type;


        // MEMBER FUNCTIONS

        NFA(std::string start_state_name);

        ~NFA();

        // modifiers
        void addState(std::string state_name, bool is_end = false);
        void addState(State s);

        void connect(NFA const &nfa, std::string from, std::string to, char symbol);

        void addTransition(State *source_state, State *destination_state, char symbol); // do not use
        void addTransition(std::string source_name, std::string destination_name, char symbol);

        // lookup
        State* getState(std::string name) const;
        State* initialState() const;
        state_table_type table();

        state_table_type const &ctable() const;

        // operations
        /*
         * The following methods are implemented according to the
         * algorithms in the book:
         * Compilers: Principles, Techniques and Tools (Aho et Al.)
         * Section 3.7.1 From Regular Expressions to Automata
         */
        state_set_type epsilon_closure(State s); // set of states reachable from state s
        state_set_type epsilon_closure(state_set_type T); // union of e-closure for all state s in T
        state_set_type
        move(state_set_type T, char c); // set of states to which there is a transition on symbol a from s in T
        bool match(std::string x);

        // VARIABLES
        static const char epsilon = '\x08';

    private:
        // VARIABLES
        state_table_type *state_table_;
        State *start_state_;

        state_set_type *end_states_;

        std::string str_to_match;
    };

}
#endif //MYREGEX_NFA_H
