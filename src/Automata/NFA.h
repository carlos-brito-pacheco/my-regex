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
/**
 *
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/22/17.
 *
 * Header file for the class NFA. This class models the behaviour of a Non-Deterministic Finite Automaton
 *
 * # Description
 * This file defines the methods and attributes for a non deterministic finite automaton.
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
 * Compilers: Principles, Techniques and Tools (Aho et Al.)
 *
 *
 * The following methods are implemented according to the
 * algorithms in the book:
 * Compilers: Principles, Techniques and Tools (Aho et Al.)
 * Section 3.7.1 From Regular Expressions to Automata:
 *
 * state_set_type epsilon_closure(State s); // set of states reachable from state s
 * state_set_type epsilon_closure(state_set_type T); // union of e-closure for all state s in T
 * state_set_type move(state_set_type T, char c); // set of states to which there is a transition on symbol a from s in T
 *
 * # TODO
 *
 *
 *
 */
//</editor-fold>

#ifndef MYREGEX_NFA_H
#define MYREGEX_NFA_H

#include "State.h"
#include "../Hashtable/Hashtable.h"
namespace Automata {

    class NFA {
    public:
        typedef hashtable<std::string, State> state_table_type;
        typedef Set<State, State::Hasher> state_set_type;

        NFA(std::string start_state_name, size_t bucket_count=100);
        ~NFA();

        /// Adds a state to the NFA
        /**
         *
         * @param state_name Name of state to be added. Must be unique.
         * @param is_end true if state is end state, false otherwise
         *
         * # Implementation details
         * This method adds a state to the NFA by inserting it in the state table.
         * If the state is an end state, then it adds it to the end_states set defined
         * in the Variables section.
         * */
        void addState(std::string state_name, bool is_end = false);

        /// Adds a state to the NFA
        /**
         *
         * @param s state to add
         *
         * # Implementation details
         * This method adds an already constructed state to the NFA
         */
        void addState(State s);

        /// Add transition from one state to other
        /**
         *
         * @param from Pointer to state from where the transition begins
         * @param to  Pointer to state where the transition ends
         * @param symbol Character symbol required to make the transition
         */
        void addTransition(State *from, State *to, char symbol);

        /// Add transition from one state to other
        /**
         * States can be identified by their name, so you can actually add
         * transitions based on the names.
         *
         * @param from Name of the state from where the transition begins
         * @param to Name of the state to where the transition ends
         * @param symbol Character symbol required to make the transition
         */
        void addTransition(std::string from, std::string to, char symbol);

        /// Concatenates two automatas (NOT FINISHED)
        NFA concatenate(NFA const &to_nfa, std::string start="0", std::string end="1") const;

        /// Sets the string to parse
        /**
         * This method sets the string to parse. We can then use advance() to advance
         * to the next set of states the automaton is at.
         * @param str String to parse
         */
        void setString(std::string str);

        /// Advances to the next set of states after advancing to the next character
        /**
         * Advances to the next character of the string that we are currently parsing.
         * In other words, it sets the current states to the epsilon closure of the set
         * move of the current states on the current symbol.
         */
        void advance();

        /// Gets current set of states the automaton is at
        /**
         *
         * This method gets the current set of states the automaton is at after having
         * advanced a character using the advance() method.
         *
         * # Implementation Details
         * If the advanced method hasn't been used yet then, formally, it will return
         * the epsilon closure of the initial state.
         * @return the set of states that the automaton is at
         */
        state_set_type getCurrentStates();

        /// Returns whether the automata is at an accepting state
        /**
         * If any of the states in the current set of states is an end state,
         * then the automata must be at an accepting state and therefore it
         * accepts the string at that point.
         *
         * Note: This does not mean it accepts the whole string.
         */
        bool accepts();

        /// Returns a pointer to the state identified by its name
        /**
         *
         * @param name Name of state
         * @return a pointer to the state
         */
        State* getState(std::string name);

        /// Returns a pointer to the initial state of the NFA
        /**
         *
         * @return a pointer to the initial state of the NFA
         */
        State* initialState() const;

        /// Returns the table of states
        /**
         * This table type is of `NFA::state_table_type` so in case one would want to
         * access the table you simply have to do:
         *
         * `NFA::state_table_type table = nfa.table()`
         *
         * @return the table of states
         */
        state_table_type table();

        /// Returns a const reference of the table of states
        /**
         * This table type is of `NFA::state_table_type` so in case one would want to
         * access the table you simply have to do:
         *
         * `NFA::state_table_type table = nfa.ctable()`
         *
         * @return the table of states
         */
        const state_table_type & ctable() const;


        /// Returns the epsilon closure of state s
        /**
         * Formally, this method returns the epsilon closure of state s.
         * In other words, it returns the set of states reachable from state s
         * on an epsilon transition (i.e. transition with epsilon as its symbol)
         * @param s State s
         * @return set of states reachable from state s on epsilon transition
         */
        state_set_type epsilon_closure(State s);

        /// Returns the epsilon closure of a set of states T
        /**
         * In other words, this will return the union of epsilon closures for
         * each state s in T
         * @param T Set of states
         * @return union of epsilon closure for each state s in T
         */
        state_set_type epsilon_closure(state_set_type T);

        /// Returns a the set of states to which there is a move from T on symbol c
        /**
         * Formally, it returns a set of states to which there is a transition on symbol c from
         * some state s in T
         * @param T Set of states
         * @param c Symbol of transition
         * @return a set of states to which there is a transition on symbol c from
         * some state s in T
         */
        state_set_type move(state_set_type T, char c);

        /// Returns true if the string matches the nfa pattern
        /**
         * Note: It does not modify anything.
         * @param x String to match
         * @return true if string matches pattern, false otherwise
         */
        bool match(std::string x);


        // VARIABLES
        static const char epsilon = '\x08';

    private:
        // VARIABLES

        //! Containers
        state_table_type state_table_;
        state_set_type end_states_;

        //! Pointer to start state
        State *start_state_;


        //! String to match
        std::string str_to_match;

        //! Set that contains the current states
        state_set_type S_;

        //! Iterator pointing to the current char on str_to_match
        std::string::iterator current_ptr_;
    };

}
#endif //MYREGEX_NFA_H
