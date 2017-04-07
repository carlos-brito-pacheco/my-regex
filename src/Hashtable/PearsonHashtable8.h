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
 * A PearsonHashtable8 is a Hashtable which uses
 * the Pearson Hashing function to obtain the key.
 * This particular case is an 8-bit implementation,
 * which means we only have 256 (0-255) available keys.
 *
 * Uses of this class could be for a table of reserved words
 * and symbols of a compiler.
 *
 * TODO:
 * Implement collision handling
 * Check deletion of key in hashtable
 * Handle exceptions
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
//</editor-fold>

#ifndef MYREGEX_PEARSONHASHTABLE8_H
#define MYREGEX_PEARSONHASHTABLE8_H

#include <iostream>
#include <string>

#include "Hashtable.h"

using namespace std;

// - - - - - - - - CLASS DEFINITION  - - - - - - - - //

class PearsonHasher8 {

    unsigned char *lookup_;

public:
    static const size_t table_size_ = 256;

public:
    PearsonHasher8() {

        // init table
        lookup_ = new unsigned char [ table_size_ ];
        for (int i = 0; i < table_size_; i++)
            lookup_[i] = i;
    }

    virtual size_t operator()(string const& key) const {
        size_t hash = 0;
        for (string::const_iterator it = key.begin(); it != key.end(); it++)
            hash = lookup_[ hash ^ *it ];
        return hash;
    }
};

template <class T>
class PearsonHashtable8 : public hashtable<string, T, PearsonHasher8> {
public:
    PearsonHashtable8()
            : hashtable<string,T,PearsonHasher8>(PearsonHasher8::table_size_) {}

};

#endif //MYREGEX_PEARSONHASHTABLE8_H
