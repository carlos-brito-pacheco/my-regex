/*
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/21/17.
 */

#include "PearsonHashtable8.h"

template <class T>
PearsonHashtable8<T>::PearsonHashtable8(size_t size)
        : Hashtable<T>(LOOKUP_TABLE_SIZE_) {
}

template <class T>
int PearsonHashtable8<T>::add(string key, T entry) {
    return 0;
}

template <class T>
T PearsonHashtable8<T>::get(string key) {
    return NULL;
}

template <class T>
bool PearsonHashtable8<T>::containsKey(string key) {
    return false;
}

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
    static lookup_table;


    return 0;
}