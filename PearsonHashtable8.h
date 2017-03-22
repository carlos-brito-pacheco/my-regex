/*
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/21/17.
 */

#ifndef MYREGEX_PEARSONHASHTABLE8_H
#define MYREGEX_PEARSONHASHTABLE8_H

#include <vector>
#include "Hashtable.h"

template <class T>
class PearsonHashtable8 : Hashtable<T> {
    static const size_t LOOKUP_TABLE_SIZE_;

    vector<unsigned char> lookup_table_;

public: // Public methods
    PearsonHashtable8(size_t size);

    int add(string key, T entry);
    T get(string key);
    bool containsKey(string key);

private: // Private methods
    int hashfunc(string key);
};




#endif //MYREGEX_PEARSONHASHTABLE8_H
