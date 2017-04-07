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
 *
 * This class models the behaviour of the state of a finite automata
 * and assigns each one a name. A state is composed of:
 *
 * - A name
 * - A set of transitions (edges connecting to other states)
 * - An attribute to indicate whether the state is final.
 *
 * We make the distinction that each state has a unique name. That is to
 * say we take for granted that the state will have a name like:
 * "s1"
 * "state3"
 * "whateveryouwant"
 *
 * Adding an indentical transition has no effect on the set and therefore
 * isn't added.
 *
 * TODO:
 *
 * 
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

#ifndef MYREGEX_STATE_H
#define MYREGEX_STATE_H

#include <string>
#include <vector>

#include "../Set/Set.h"

#include "Transition.h"

namespace Automata {

// DECLARATION
    class State {

    public:
        // TYPEDEFS
        typedef Set<Transition, Transition::Hasher> transition_set_type;

        // Classes
        struct Hasher {
            std::hash<std::string> h;
        public:
            size_t operator()(State state) const {
                size_t hash = 0;
                hash = h(state.name());
                return hash;
            }
        };

        // Methods
        State(std::string name, bool is_end = false, size_t bucket_count = 100);

        void addTransition(State *destination, char symbol);

        void setEnd(bool is_end);

        std::string name() const;

        bool isEnd() const;

        transition_set_type &transition_set() {
            return *transitions_;
        }

        transition_set_type const &ctransition_set() const {
            return *transitions_;
        }

    private:
        std::string name_; // this attribute must be unique to each state
        transition_set_type *transitions_;
        bool is_end_;
    };

    std::ostream &operator<<(std::ostream &os, const State &obj);

    inline bool operator==(State const &lhs, State const &rhs) {
        return lhs.name() == rhs.name();
    }
}
#endif //MYREGEX_STATE_H
