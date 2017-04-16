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
/**
 * @file State.h
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date 3/22/17
 *
 * @brief Header file for the class State.
 *
 * # Description
 * It contains only the declarations for the methods and member variables of the class State
 *
 * # TODO
 * - THIS CLASS LEAKS MEMORY
 * - THERE IS A POINTER NOT BEING ALLOCATED
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
    /**
     * @class State
     *
     * @brief A class to represent a state of a finite automata
     *
     * # Description
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
    */
    class State {

    public:
        /// Set of transitions
        typedef Set<Transition, Transition::Hasher> transition_set_type;

        /**
         * @class Hasher
         * @brief Functor which returns a `size_t` hash for the state
         *
         * This class serves as a way of hashing the state. It generates a hash of type `size_t`
         * which a set or hashtable can then use.
         */
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
        /**
         * @brief Constructs a state given a unique name and whether the state is final or not
         * @param name Name of state
         * @param is_end `true` if the state is final, `false` otherwise
         * @param bucket_count Number of buckets to be used for a transition set
         */
        State(std::string name, bool is_end = false, size_t bucket_count = 100);

        /**
         * @brief Destructor for state
         */
        ~State();

        /**
         * @brief Adds a transition from this state to the destination on a given symbol
         * @param destination Destination state
         * @param symbol Symbol required to move from this state to destination
         */
        void addTransition(State *destination, char symbol);

        /**
         * @brief Sets whether the state is final or not
         * @param is_end `true` if state is final, `false` otherwise
         */
        void setEnd(bool is_end);

        /**
         * @brief Sets the name of the state
         * @param name Name of state
         */
        void setName(std::string name);

        /**
         * @brief Returns the name of the state
         * @return Name of state
         */
        std::string name() const;

        /**
         * @brief Returns whether the state is final or not
         * @return `true` if final, `false` otherwise
         */
        bool isEnd() const;

        /**
         * @brief Returns a reference to the transition set
         * @return Reference to the transition set
         */
        transition_set_type &transition_set();

        /**
         * @brief Returns a const reference to the transition set
         * @return Const reference to the transition set
         */
        transition_set_type const &transition_set() const;

    private:
        /// Name of state. Must be unique.
        std::string name_; // this attribute must be unique to each state

        /// Set of transitons
        transition_set_type *transitions_;

        /// Whether state is final
        bool is_end_;
    };

    std::ostream &operator<<(std::ostream &os, const State &obj);

    inline bool operator==(State const &lhs, State const &rhs) {
        return lhs.name() == rhs.name();
    }
}
#endif //MYREGEX_STATE_H
