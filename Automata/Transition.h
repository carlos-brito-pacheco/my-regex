//<editor-fold desc="Preamble">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Copyright (C) 3/24/17 Carlos Brito
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
 * An object of the type Transition is meant to be inside
 * an object of the type State. A transition can be thought of
 * as an edge connecting a state to another. The transition indicates:
 *
 * - The source state
 * - The required symbol to be consumed
 * - The destination state
 *
 *
 * TODO:
 * 
 * 
 * 
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

#ifndef MYREGEX_TRANSITION_H
#define MYREGEX_TRANSITION_H

class State;

class Transition {
    char symbol_;
    State *source_;
    State *destination_;

public:
    Transition(State *source, State *destination, char symbol)
            : source_(source),
              destination_(destination),
              symbol_(symbol)
    {
    }

    char symbol() {
        return symbol_;
    }

    State* source() {
        return source_;
    }

    State* destination() {
        return destination_;
    }
};


#endif //MYREGEX_TRANSITION_H
