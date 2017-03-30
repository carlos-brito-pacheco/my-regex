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

#include "NFA.h"
#include "AutomataErrors.h"

NFA::NFA(std::string start_state_name) {
    state_table_ = new state_table_type(10);
    addState( start_state_name ); // add initial state
}

NFA::~NFA() {
    delete state_table_;
}

void NFA::addState(std::string state_name) {
    State s(state_name);

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




