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
 * @file NFA.cpp
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date 3/22/17
 *
 * # Description
 * This is the .cpp file which contains the implementation for all the methods declared in the header file NFA.h
 *
 * # TODO
 * Nothing for the moment.
 */
//</editor-fold>


#include <iostream>
#include "AutomataErrors.h"
#include "NFA.h"

namespace Automata {

    NFA::NFA(std::string start_state_name, size_t bucket_count)
            : stateTable_(state_table_type(bucket_count)),
              endStates_(state_set_type(bucket_count)),
              S_(state_set_type(1))
    {
        addState(start_state_name); // add initial state
        startState_ = getState(start_state_name); // find the address of the initial state
    }

    NFA::NFA()
    {}

    NFA::~NFA() {
    }

    void NFA::addState(std::string state_name, bool is_end) {
        State s(state_name, is_end);

        if (stateTable_.contains_key(s.name()))
            throw DuplicateStateError(s.name());

        if (s.isEnd())
            endStates_.insert(s);

        stateTable_.insert(s.name(), s);
    }

    void NFA::addTransition(State *from, State *to, char symbol) {
        from->addTransition(to, symbol); // add the transition to the source state
    }

    void NFA::addTransition(std::string from, std::string to, char symbol) {
        // get elements
        State *source = getState(from);
        State *destination = getState(to);

        // add transition
        addTransition(source, destination, symbol);
    }

    NFA::state_table_type & NFA::table() {
        return stateTable_;
    }

    const NFA::state_table_type &NFA::table() const {
        return stateTable_;
    }

    State *NFA::getState(std::string name) {
        state_table_type::iterator it = stateTable_.find(name);

        if (stateTable_.count() == 0)
            throw EmptyStateSetError();

        if (it == stateTable_.end())
            throw StateNotFoundError(name);

        State *s = &(it->second);
        return s;
    }

    NFA::state_set_type NFA::epsilon_closure(State s) {
        state_set_type result(stateTable_.count());
        result.insert(s);

        State::transition_set_type transitions = s.transition_set();
        for (State::transition_set_type::iterator it = transitions.begin();
             it != transitions.end(); it++) // iterate over transitions
        {
            Transition t = *it;
            if (t.symbol() == epsilon)
            {
                if (!result.contains(
                        *t.destination())) // we do not need to recalculate e closure for a state that is already in the set
                    result = result.Union(epsilon_closure(*t.destination()));
            }
        }

        return result;
    }

    NFA::state_set_type NFA::epsilon_closure(state_set_type T) {
        state_set_type result(stateTable_.count());
        for (state_set_type::iterator it = T.begin(); it != T.end(); it++) // iterate over states s in T
        {
            State s = *it;
            if (!result.contains(s)) // dont even make the call if s is in result
                result = result.Union(epsilon_closure(s));
        }
        return result;
    }

    NFA::state_set_type NFA::move(NFA::state_set_type T, char c) {
        state_set_type result(stateTable_.count());

        for (state_set_type::iterator s_it = T.begin(); s_it != T.end(); s_it++) // iterate over states s in T
        {
            State::transition_set_type s_transitions = s_it->transition_set();

            for (State::transition_set_type::iterator t_it = s_transitions.begin();
                 t_it != s_transitions.end(); t_it++)
            {
                Transition t = *t_it;
                if (t.symbol() == c)
                {
                    result.insert(*t.destination());
                }
            }
        }

        return result;
    }

    bool NFA::match(std::string x) {


        state_set_type S = epsilon_closure(*startState_);

        for (std::string::iterator c = x.begin(); c != x.end(); c++)
        {

            S = epsilon_closure(move(S, *c));
        }

        return !(S.Intersection(endStates_)).empty();
    }

    State *NFA::initialState() const {
        return startState_;
    }


    void NFA::setString(std::string str) {
        str_to_match = str;
        current_ptr_ = str_to_match.begin();
        S_ = epsilon_closure(*startState_);
    }

    void NFA::advance() {
        if (current_ptr_ == str_to_match.end())
            throw OutOfBoundsError(str_to_match);

        S_ = epsilon_closure(move(S_, *current_ptr_));

        current_ptr_++;
    }

    bool NFA::accepts() {
        return !(S_.Intersection(endStates_)).empty();
    }

    NFA::state_set_type NFA::getCurrentStates() {
        return S_;
    }

    NFA::state_set_type &NFA::end_states() {
        return endStates_;
    }

    const NFA::state_set_type &NFA::end_states() const {
        return endStates_;
    }

    NFA &NFA::operator=(const NFA &rhs) {

        // Overwriting of automata
        S_ = rhs.S_;
        stateTable_ = state_table_type( rhs.table().bucket_count() );
        endStates_ = state_set_type( rhs.end_states().bucket_count() );

        // Copy states of other automata
        for (state_table_type::const_iterator entry_it = rhs.stateTable_.cbegin();
             entry_it != rhs.stateTable_.cend(); entry_it++)
        {
            State s = entry_it->second;
            this->addState(s.name(), s.isEnd());
        }

        startState_ = getState(rhs.initialState()->name());


        // Add the transitions
        for (state_table_type::const_iterator entry_it = rhs.stateTable_.cbegin();
             entry_it != rhs.stateTable_.cend(); entry_it++)
        {
            State s = entry_it->second;
            State::transition_set_type transitions = s.transition_set();
            for (State::transition_set_type::iterator t_it = transitions.begin(); t_it != transitions.end(); t_it++)
            {
                Transition t = *t_it;
                this->addTransition(t.source()->name(), t.destination()->name(), t.symbol());
            }
        }
        return *this;
    }

    NFA::NFA(const NFA &nfa)
            : stateTable_( state_table_type( nfa.table().bucket_count() ) ),
              endStates_( state_set_type( nfa.end_states().bucket_count() ) ),
              S_( nfa.S_ )
    {
        // Copy states of other automata
        for (state_table_type::const_iterator entry_it = nfa.stateTable_.cbegin();
             entry_it != nfa.stateTable_.cend(); entry_it++)
        {
            State s = entry_it->second;
            this->addState(s.name(), s.isEnd());
        }

        startState_ = getState(nfa.initialState()->name());


        // Add the transitions
        for (state_table_type::const_iterator entry_it = nfa.stateTable_.cbegin();
             entry_it != nfa.stateTable_.cend(); entry_it++)
        {
            State s = entry_it->second;
            State::transition_set_type transitions = s.transition_set();
            for (State::transition_set_type::iterator t_it = transitions.begin(); t_it != transitions.end(); t_it++)
            {
                Transition t = *t_it;
                this->addTransition(t.source()->name(), t.destination()->name(), t.symbol());
            }
        }
    }

    void NFA::setInitialState(std::string name) {
        startState_ = getState(name);
    }

    NFA NFA::alternate(NFA const &to_nfa) const {
        std::string start = "3_0";
        std::string end = "3_1";

        // Declaration of automata
        NFA result(start, // initial state with name start
                   this->stateTable_.bucket_count() +
                   to_nfa.stateTable_.bucket_count()); // maximum size to reduce load factor of hashtable
        result.addState(end, true); // add end state

        // Copy states of other automata
        for (state_table_type::const_iterator entry_it = to_nfa.stateTable_.cbegin();
             entry_it != to_nfa.stateTable_.cend(); entry_it++)
        {
            State s = entry_it->second;
            result.addState("2_" + s.name(), s.isEnd());
        }

        // Add the transitions of other automata
        for (state_table_type::const_iterator entry_it = to_nfa.stateTable_.cbegin();
             entry_it != to_nfa.stateTable_.cend(); entry_it++)
        {
            State s = entry_it->second;
            State::transition_set_type transitions = s.transition_set();
            for (State::transition_set_type::iterator t_it = transitions.begin(); t_it != transitions.end(); t_it++)
            {
                Transition t = *t_it;
                result.addTransition("2_" + t.source()->name(), "2_" + t.destination()->name(), t.symbol());
            }
        }

        // Copy states of this automata
        for (state_table_type::const_iterator entry_it = this->stateTable_.cbegin();
             entry_it != this->stateTable_.cend(); entry_it++)
        {
            State s = entry_it->second;
            result.addState("1_" + s.name(), s.isEnd());
        }

        // Add the transitions
        for (state_table_type::const_iterator entry_it = this->stateTable_.cbegin();
             entry_it != this->stateTable_.cend(); entry_it++)
        {
            State s = entry_it->second;
            State::transition_set_type transitions = s.transition_set();
            for (State::transition_set_type::iterator t_it = transitions.begin(); t_it != transitions.end(); t_it++)
            {
                Transition t = *t_it;
                result.addTransition("1_" + t.source()->name(), "1_" + t.destination()->name(), t.symbol());
            }
        }

        // Add two epsilon transitions from result to both automatas
        State *this_init_state = this->initialState();
        result.addTransition(result.initialState()->name(), "1_" + this_init_state->name(), epsilon);

        State *other_init_state = to_nfa.initialState();
        result.addTransition(result.initialState()->name(), "2_" + other_init_state->name(), epsilon);


        return result;
    }

    NFA NFA::concatenate(NFA const &to_nfa) const {

        std::string start = "3_0";
        std::string end = "3_1";

        // Declaration of automata
        NFA result(start, // initial state with name start
                   this->stateTable_.bucket_count() +
                   to_nfa.stateTable_.bucket_count()); // maximum size to reduce load factor of hashtable
        result.addState(end, true); // add end state


        // Copy states of other automata
        for (state_table_type::const_iterator entry_it = to_nfa.stateTable_.cbegin();
             entry_it != to_nfa.stateTable_.cend(); entry_it++)
        {
            State s = entry_it->second;
            result.addState("2_" + s.name(), false);

            if(s.isEnd()) // if is end then connect to the result's end state
                result.addTransition("2_" + s.name(), end, epsilon);
        }

        // Add the transitions of other automata
        for (state_table_type::const_iterator entry_it = to_nfa.stateTable_.cbegin();
             entry_it != to_nfa.stateTable_.cend(); entry_it++)
        {
            State s = entry_it->second;
            State::transition_set_type transitions = s.transition_set();
            for (State::transition_set_type::iterator t_it = transitions.begin(); t_it != transitions.end(); t_it++)
            {
                Transition t = *t_it;
                result.addTransition("2_" + t.source()->name(), "2_" + t.destination()->name(), t.symbol());
            }
        }

        // Copy states of this automata
        State *init_state_other = to_nfa.initialState();
        for (state_table_type::const_iterator entry_it = this->stateTable_.cbegin();
             entry_it != this->stateTable_.cend(); entry_it++)
        {
            State s = entry_it->second;
            result.addState("1_" + s.name(), false);

            if (s.isEnd()) // if is end then connect to other initial state
                result.addTransition("1_" + s.name(), "2_" + init_state_other->name(), epsilon);
        }

        // Add the transitions
        for (state_table_type::const_iterator entry_it = this->stateTable_.cbegin();
             entry_it != this->stateTable_.cend(); entry_it++)
        {
            State s = entry_it->second;
            State::transition_set_type transitions = s.transition_set();
            for (State::transition_set_type::iterator t_it = transitions.begin(); t_it != transitions.end(); t_it++)
            {
                Transition t = *t_it;
                result.addTransition("1_" + t.source()->name(), "1_" + t.destination()->name(), t.symbol());
            }
        }

        // Connect start to initial state of this
        State *this_init_state = this->initialState();
        result.addTransition(result.initialState()->name(), "1_" + this_init_state->name(), epsilon);

        return result;
    }

    NFA NFA::kleene() const {
        std::string start = "3_0";
        std::string end = "3_1";

        // Declaration of automata
        NFA result(start, // initial state with name start
                   this->stateTable_.bucket_count()); // maximum size to reduce load factor of hashtable
        result.addState(end, true); // add end state

        // Copy states of this automata
        for (state_table_type::const_iterator entry_it = this->stateTable_.cbegin();
             entry_it != this->stateTable_.cend(); entry_it++)
        {
            State s = entry_it->second;
            result.addState("1_" + s.name(), false);
        }

        // Add the transitions
        for (state_table_type::const_iterator entry_it = this->stateTable_.cbegin();
             entry_it != this->stateTable_.cend(); entry_it++)
        {
            State s = entry_it->second;
            State::transition_set_type transitions = s.transition_set();
            for (State::transition_set_type::iterator t_it = transitions.begin(); t_it != transitions.end(); t_it++)
            {
                Transition t = *t_it;
                result.addTransition("1_" + t.source()->name(), "1_" + t.destination()->name(), t.symbol());
            }

            if (s.isEnd())
            {
                // connect end states with the initial state of this automata
                result.addTransition("1_" + s.name(), "1_" + this->initialState()->name(), epsilon);

                // connect end state to the result's end state
                result.addTransition("1_" + s.name(), end, epsilon);
            }

        }

        // Connect start to initial state of this
        State *this_init_state = this->initialState();
        result.addTransition(result.initialState()->name(), "1_" + this_init_state->name(), epsilon);

        // Connect start to end state
        result.addTransition(start, end, epsilon);

        return result;
    }

    NFA NFA::kleene_plus() const {
        return this->concatenate(this->kleene());
    }

    NFA NFA::optional() const {

        NFA empty("0");
        empty.addState("1");
        empty.addTransition("0", "1", epsilon);

        return this->alternate(empty);
    }
}


