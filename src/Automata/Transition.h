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

#include <string>

namespace Automata {

    class State; // forward declare: state and transition are codependent

    class Transition {
    public:
        // Classes
        struct Hasher {
            std::hash<std::string> h;
        public:
            size_t operator()(Transition transition) const {
                size_t hash = 0;
                std::string unique_name = transition.source_name_
                                          + std::string(1, transition.symbol())
                                          + transition.destination_name_;

                hash = h(unique_name);
                return hash;
            }
        };

        // Methods
        Transition(State *source, State *destination, char symbol);

        char symbol() const;

        State *source() const;

        State *destination() const;

    private:
        const char symbol_;
        State *source_;
        State *destination_;


        /*
         * NOTE:
         * A note on the following two variables.
         * We should be able to access the names using the pointers defined above.
         * However, we need the definition of State in Hasher. Because they are
         * codependent, this means we won't be able to access the names.
         * Instead, AS A WORKAROUND, we store them directly.
         */
        std::string source_name_;
        std::string destination_name_;
    };

    inline bool operator==(Transition const &lhs, Transition const &rhs) {

        return lhs.source() == rhs.source() &&
               lhs.destination() == rhs.destination() &&
               lhs.symbol() == rhs.symbol();
    }

}
#endif //MYREGEX_TRANSITION_H
