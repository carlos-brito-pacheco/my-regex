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
 * Implement collision handling
 * Implement perfect hashing
 * Check deletion of key in hashtable
 * Handle exceptions
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
//</editor-fold>

#ifndef MYREGEX_PEARSONHASHTABLE8_H
#define MYREGEX_PEARSONHASHTABLE8_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>

#include "Hashtable.h"
#include "HashtableErrors.h"

using namespace std;

// - - - - - - - - CLASS DEFINITION  - - - - - - - - //

template <class T>
class PearsonHashtable8 : public Hashtable<T> {
    static const size_t  HASH_TABLE_SIZE_ = 256;
    static const size_t LOOKUP_TABLE_SIZE_ = 256;

    vector<T*> *table_;
    vector<unsigned char> *lookup_table_;


public:
    PearsonHashtable8();

    int add(string key, T const& entry);
    T get(string key);
    bool containsKey(string key);
    void remove(string key);

private:
    int hashfunc(string key);
    void initLookupTable();
    void initHashTable();
};


// - - - - - - - - CLASS FUNCTION BODIES  - - - - - - - - //

// -----------------------
// constructs a hashtable of fixed size
template <class T>
PearsonHashtable8<T>::PearsonHashtable8()
        : Hashtable<T>(HASH_TABLE_SIZE_)
{

    initLookupTable();
    initHashTable();
}

// ------------------------
// adds an entry of type T into hashtable
// returns the hashkey of the new entry
template <class T>
int PearsonHashtable8<T>::add(string key, T const& entry) {

    int hash = hashfunc(key);

    if(table_->at(hash) == NULL)
        table_->at(hash) = new T(entry);
    else
        throw CollisionError(key);

    return hash;
}

// -----------------------
// gets item of type T from hashtable
template <class T>
T PearsonHashtable8<T>::get(string key) {
    int hash = hashfunc(key);

    T *entry = table_->at(hash);

    if (entry != NULL)
        return *entry;
    else
        throw KeyNotFoundError(key);
}

// -------------------------
// removes specified key from table
template <class T>
void PearsonHashtable8<T>::remove(string key) {
    int hash = hashfunc(key);
    T *entry = table_->at(hash);
    table_->at(hash) = NULL; // is this whole sequence correct? must check
    delete entry;
}

// -----------------------
// returns true if the specified key is in the hashtable
template <class T>
bool PearsonHashtable8<T>::containsKey(string key) {
    int hash = hashfunc(key);
    return table_->at(hash) != NULL;
}

// ----------------------
// returns the hash for the key
template  <class T>
int PearsonHashtable8<T>::hashfunc(string key) {

    /* Hashing is done using Pearson Hashing function.
     *
     * Please consult for a brief description:
     * https://en.wikipedia.org/wiki/Pearson_hashing
     *
     * THIS IS NOT a perfect hashing implementation.
     *
     */
    unsigned char hash = (unsigned char) (key.length() % (LOOKUP_TABLE_SIZE_ - 1));
    for (string::iterator it = key.begin(); it != key.end(); it++)
    {
        hash = lookup_table_->at( hash ^ (*it) ) % (unsigned char) (LOOKUP_TABLE_SIZE_ - 1);
    }

    return (int) hash;
}

// ------------------------
// initializes the lookup table to be used
template <class T>
void PearsonHashtable8<T>::initLookupTable() {

    // Seed
    srand( unsigned ( time(0) ));

    // Allocate space
    lookup_table_ = new vector<unsigned char>(LOOKUP_TABLE_SIZE_);

    // Fill table with values [0...255]
    int i = 0;
    for (vector<unsigned char>::iterator it = lookup_table_->begin(); it != lookup_table_->end(); it++)
    {
        *it = i++;
    }

    // Shuffle array
    random_shuffle(lookup_table_->begin(), lookup_table_->end());
}

// ----------------------
// initializes the hashtable
template <class T>
void PearsonHashtable8<T>::initHashTable() {
    // Allocate space for table
    table_ = new vector<T*>(HASH_TABLE_SIZE_);
}



#endif //MYREGEX_PEARSONHASHTABLE8_H
