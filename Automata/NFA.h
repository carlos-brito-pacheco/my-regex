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

class NFA {

public:

    // TYPEDEFS
    typedef hashtable<std::string, State, State::Hasher> state_table_type;

    // METHODS
    NFA(std::string start_state_name);
    ~NFA();
    void addState(std::string state_name);
    void addTransition(State *source_state, State *destination_state, char symbol);
    void addTransition(std::string source_name, std::string destination_name, char symbol);

    state_table_type table() {
        return *state_table_;
    }

private:
    // VARIABLES
    state_table_type *state_table_;
    State *start_state_;
};


#endif //MYREGEX_NFA_H
