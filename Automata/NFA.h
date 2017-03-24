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
 * - Instead of a Hashtable, we should probably implement
 * a type Set<T>.
 *
 *
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

#ifndef MYREGEX_NFA_H
#define MYREGEX_NFA_H

#include "State.h"

class NFA {
    State *start_state_;
    Hashtable<State> *states_;

public:
    void addState(string state_name);
    void addTransition(string s1, string s2, char symbol);

};


#endif //MYREGEX_NFA_H
