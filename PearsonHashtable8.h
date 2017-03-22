/*
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/21/17.
 */

#ifndef MYREGEX_PEARSONHASHTABLE8_H
#define MYREGEX_PEARSONHASHTABLE8_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>

#include "Hashtable.h"

using namespace std;
int myrandom(int i) { return rand()%i; }

// - - - - - - - - CLASS DEFINITION  - - - - - - - - //

template <class T>
class PearsonHashtable8 : public Hashtable<T> {
    static const size_t LOOKUP_TABLE_SIZE_ = 256;

    vector<unsigned char> *lookup_table_;


public:
    PearsonHashtable8();

    int add(string key, T entry);
    T get(string key);
    bool containsKey(string key);

private:
    int hashfunc(string key);
    void initLookupTable();
};


// - - - - - - - - CLASS FUNCTION BODIES  - - - - - - - - //

// -----------------------
// constructs a hashtable with size 256
template <class T>
PearsonHashtable8<T>::PearsonHashtable8()
        : Hashtable<T>(LOOKUP_TABLE_SIZE_) {


    initLookupTable();
}

// ------------------------
// adds an entry of type T into hashtable
template <class T>
int PearsonHashtable8<T>::add(string key, T entry) {



    return 0;
}

// -----------------------
// gets item of type T from hashtable
template <class T>
T PearsonHashtable8<T>::get(string key) {
    return NULL;
}

// -----------------------
// returns true if the specified key is in the hashtable
template <class T>
bool PearsonHashtable8<T>::containsKey(string key) {
    return false;
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
     * TODO:
     * Implement perfect hashing.
     */
    unsigned char hash = (unsigned char) (key.length() % (LOOKUP_TABLE_SIZE_ - 1));
    for (string::iterator it = key.begin(); it != key.end(); it++)
    {
        hash = lookup_table_->at( hash ^ (*it) ) % (unsigned char) (LOOKUP_TABLE_SIZE_ - 1);
    }

    return hash;
}

// ------------------------
// initializes the lookup table to be used
template<class T>
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
    random_shuffle(lookup_table_->begin(), lookup_table_->end(), myrandom);
}



#endif //MYREGEX_PEARSONHASHTABLE8_H
