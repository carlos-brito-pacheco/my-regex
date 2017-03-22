/*
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/21/17.
 */

#include "PearsonHashtable.h"

template <class T>
PearsonHashtable<T>::PearsonHashtable(size_t size)
        : Hashtable<T>(size) {
}

template <class T>
int PearsonHashtable<T>::add(string key, T entry) {
    return 0;
}

template <class T>
T PearsonHashtable<T>::get(string key) {
    return NULL;
}

template <class T>
bool PearsonHashtable<T>::containsKey(string key) {
    return false;
}

template  <class T>
int PearsonHashtable<T>::hashfunc(string key) {

    /* Hashing is done using Pearson Hashing function.
     * 
     *
     *
     */

    return 0;
}


