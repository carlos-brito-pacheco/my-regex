//<editor-fold desc="License">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Copyright (C) 3/22/17 Carlos Brito
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
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
//</editor-fold>

#ifndef MYREGEX_HASHTABLEERRORS_H
#define MYREGEX_HASHTABLEERRORS_H

#include <exception>
#include <string>
using namespace std;

class KeyNotFoundError : public exception {

    const string key_;
    string message_;

public:
    KeyNotFoundError(string key)
            : key_(key)
    {
        message_ = "Requested entry with key: \"" + key_ + "\" could not be found";
    }

    ~KeyNotFoundError() throw() {

    }

    virtual const char *what() const throw() {

        return message_.c_str();
    }
};


class CollisionError : public exception {
    const string key_;
    string message_;

public:
    CollisionError(string key)
            : key_(key)
    {
        message_ = "Insertion of entry with key: \"" + key_ + "\" causes collision.";
    }

    ~CollisionError() throw() {

    }
};
#endif //MYREGEX_HASHTABLEERRORS_H
