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
 * TODO:
 * 
 * 
 * 
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

#ifndef MYREGEX_AUTOMATAERRORS_H
#define MYREGEX_AUTOMATAERRORS_H

#include <exception>
#include <string>
#include "Transition.h"

namespace Automata {
    class StateNotFoundError : public std::exception {
        std::string message_;

    public:
        StateNotFoundError(std::string name) {
            message_ = "State " + name + " not found!";
        }

        ~StateNotFoundError() throw() {

        }

        virtual const char *what() const throw() {

            return message_.c_str();
        }
    };

    class OutOfBoundsError : public std::exception {
        std::string message_;

    public:
        OutOfBoundsError(std::string str) {
            message_ = "Out of bounds error while advancing to next character in string: " + str;
        }

        ~OutOfBoundsError() throw() {

        }

        virtual const char *what() const throw() {

            return message_.c_str();
        }
    };

}


#endif //MYREGEX_AUTOMATAERRORS_H
