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
 * @file NFA.h
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date 3/22/17.
 *
 * @brief Header file for the class NFA. This file contains declarations of methods and member variables.
 *
 * # Description
 * This file contains the declarations for all the methods and member variables of class NFA. For the majority of
 * the interface, we have based ourselves on the book:
 *
 * - Compilers: Principles, Techniques and Tools (Aho et Al.)
 *
 * # TODO
 * - Review if we need to split this class into two classes BasicNFA and CompositeNFA. First one permits access to methods
 * such as `addTransition()` and `addState()`. The second type is the result type of applying operations such as
 * concatenation and union to two automatas. Because we lose the ability to reference states solely on the name, this
 * should make sense.
 *
 * - Implement method for the union of two automatas
 * - Implement method for kleene star
 * - Implement method for positive kleen star
 *
 */
//</editor-fold>

#ifndef MYREGEX_NFA_H
#define MYREGEX_NFA_H

#include "State.h"
#include "../Hashtable/Hashtable.h"


namespace Automata {

    /** @class NFA
    * # Description
    * This file defines the methods and attributes for a non deterministic finite automaton.
    *
    * We keep a pointer to the start state as well as a
    * table for the states. We identify a state by a name key,
    * such as "s1" or "state3". It will be up to the user of the
    * class to keep track of the names he/she gives to the
    * states.
    * This means that we have to make references to the states with their names
    *
    * Please see the book:
    * Compilers: Principles, Techniques and Tools (Aho et Al.)
    */
    class NFA {
    public:
        typedef hashtable<std::string, State> state_table_type;
        typedef Set<State, State::Hasher> state_set_type;

        /// Instantiates the NFA with a starting state name
        /**
         * This constructor will instantiate the NFA given the name of the start state.
         * It also takes the number of buckets which regulates whether the internal
         * access to the elements will be \f$ O(1) \f$ or not.
         *
         * If the number of states is known beforehand, then you should set bucket count
         * to be equal to the number of states.
         *
         * @param start_state_name
         * @param bucket_count
         */
        NFA(std::string start_state_name, size_t bucket_count=100);

        /// Destructor method for NFA
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
//        void addState(State s);

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

        /// Concatenates two automatas
        /**
         * This method returns an automata that is the concatenation of both
         * automatas. It merges the sets of states and creates a new set of
         * states as well as it copies the transitions.
         *
         * Formally, if \f$ A \f$ and \f$ B \f$ are two NFAs which have respective languages
         * \f$ L(A) \f$ and \f$L(B)\f$ then this method returns a NFA \f$ C = AB \f$ which accepts
         * the language \f$ L(A)L(B) \f$.
         *
         * # Implementation Details
         *
         * The automata will merge both sets of states using their respective keys.
         * This means that if we have two states with equal names in both \f$ A \f$ and \f$ B \f$,
         * this will generate a collision and throw an exception.
         *
         * # Notes
         * If you didn't read the previous section then please note the following:
         * The concatenation of two NFAs with two states with identical names will generate an exception.
         *
         * # Complexity
         * Worst case \f$ O(n^2 + m^2) \f$
         * Where:
         * - \f$ n \f$ is the number of states in \f$ A \f$
         * - \f$ m \f$ is the number of states in \f$ B \f$
         *
         * ## Notes on the complexity
         * The complexity is actually really bad because we're reconstructing the whole "graph".
         * This means we first have to add the states which takes \f$ O(n) \f$.
         * Then we have to add all transitions. In the worst case scenario we have at most
         * \f$ kn^2 \f$ arrows coming out of each state. However, \f$ k \f$ is a constant which
         * represents the number of symbols in the alphabet. Therefore, we have to do \f$ O(n^2) \f$
         * operations for each graph.
         *
         * @param to_nfa Right side automata. (Aka. the automata B)
         * @return The concatenation of two NFAs
         */
        NFA concatenate(NFA const &to_nfa) const;

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
        state_table_type & table();

        /// Returns a const reference of the table of states
        /**
         * This table type is of `NFA::state_table_type` so in case one would want to
         * access the table you simply have to do:
         *
         * `NFA::state_table_type table = nfa.ctable()`
         *
         * @return the table of states
         */
        const state_table_type & table() const;

        /// Returns a reference to the set of end states of the automata
        /**
         *
         * @return End states
         */
        state_set_type & end_states();

        /// Returns a const reference to the set of end states of the automata
        /**
         *
         * @return End states
         */
        const state_set_type & end_states() const;


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

        /// We take the convention that the escape character '\x08' represents epsilon
        static const char epsilon = '\x08';

    private:
        const std::string id_string_;

        //! Table of states
        state_table_type state_table_;

        //! Set of end states
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
