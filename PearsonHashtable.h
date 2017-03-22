/*
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/21/17.
 */

#ifndef MYREGEX_PEARSONHASHTABLE_H
#define MYREGEX_PEARSONHASHTABLE_H

#include "Hashtable.h"

template <class T>
class PearsonHashtable : Hashtable<T> {
public:
    PearsonHashtable(size_t size);

    int add(string key, T entry);
    T get(string key);
    bool containsKey(string key);

private:
    int hashfunc(string key);
};




#endif //MYREGEX_PEARSONHASHTABLE_H
