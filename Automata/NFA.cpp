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
 * CPP file for the class NFA declared in NFA.h
 *
 * TODO:
 *
 *
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

#include <string>
#include <queue>

#include "NFA.h"
#include "AutomataErrors.h"

NFA::NFA(std::string start_state_name) {
    state_table_ = new state_table_type(100);
    end_states_ = new state_set_type(100);
    addState( start_state_name ); // add initial state
    start_state_ = &state_table_->find(start_state_name)->second;
}

NFA::~NFA() {
    delete state_table_;
}

void NFA::addState(std::string state_name, bool is_end) {
    State s(state_name, is_end);

    if (is_end)
        end_states_->insert(s);

    state_table_->insert(state_name, s);
}

void NFA::addTransition(State* source, State* destination, char symbol) {
    source->addTransition(destination, symbol); // add the transition to the source state
}

void NFA::addTransition(std::string source_name, std::string destination_name, char symbol) {

    // Get elements
    state_table_type::iterator src = state_table_->find(source_name);
    state_table_type::iterator dst = state_table_->find(destination_name);

    // Handle exceptions
    if (src == state_table_->end())
        throw StateNotFoundError(source_name);
    if (dst == state_table_->end())
        throw StateNotFoundError(destination_name);

    // add transition
    State *source, *destination;
    source = &src->second;
    destination = &dst->second;

    addTransition(source, destination, symbol);
}

NFA::state_table_type NFA::table() {
    return *state_table_;
}

NFA::state_table_type const& NFA::ctable() const {
    return *state_table_;
}

NFA::state_set_type NFA::epsilon_closure(State s) {
    state_set_type result(state_table_->count());
    result.insert(s);

    State::transition_set_type transitions = s.ctransition_set();
    for ( State::transition_set_type::iterator it = transitions.begin(); it != transitions.end(); it++ ) // iterate over transitions
    {
        Transition t = *it;
        if (t.symbol() == epsilon)
        {
            if ( !result.contains(*t.destination()) ) // we do not need to recalculate e closure for a state that is already in the set
                result = result.Union( epsilon_closure( *t.destination() ) );
        }
    }

    return result;
}

NFA::state_set_type NFA::epsilon_closure(state_set_type T) {
    state_set_type result(state_table_->count());
    for ( state_set_type::iterator it = T.begin(); it != T.end(); it++ ) // iterate over states s in T
    {
        State s = *it;
        if (!result.contains(s)) // dont even make the call if s is in result
            result = result.Union( epsilon_closure( s ) );
    }
    return result;
}

State NFA::getState(std::string name) {
    State s = state_table_->find(name)->second;
    return s;
}

NFA::state_set_type NFA::move(NFA::state_set_type T, char c) {
    state_set_type result(state_table_->count());

    for ( state_set_type::iterator s_it = T.begin(); s_it != T.end(); s_it++ ) // iterate over states s in T
    {
        State::transition_set_type s_transitions = s_it->transition_set();

        for ( State::transition_set_type::iterator t_it = s_transitions.begin(); t_it != s_transitions.end(); t_it++ )
        {
            Transition t = *t_it;
            if (t.symbol() == c)
            {
                result.insert( *t.destination() );
            }

        }
    }

    return result;
}

bool NFA::match(std::string x) {

    state_set_type S = epsilon_closure( *start_state_ );

    for (std::string::iterator c = x.begin(); c != x.end(); c++)
    {

        S = epsilon_closure( move( S, *c ) );
    }

    return ( S.Intersection(*end_states_) ).empty();
}




