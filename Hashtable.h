/*
 * Copyright (C) 3/22/17 Carlos Brito
 *
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/21/17.
 *
 * Description:
 * This is an abstract class to define the behaviour
 * of a basic Hashtable.
 *
 */

#ifndef MYREGEX_HASHTABLE_H
#define MYREGEX_HASHTABLE_H

#include <string>
#include <list>
#include <vector>

using  namespace std;

// - - - - - - - - CLASS DEFINITION  - - - - - - - - //

template <class T>
class Hashtable {

private:
    const size_t size_;

public:
    Hashtable(size_t size);
    virtual ~Hashtable();

    virtual size_t size() const;

    virtual int add(string key, T const& entry)= 0;
    virtual T get(string key)= 0;
    virtual void remove(string key)= 0;
    virtual bool containsKey(string key)= 0;
};

// - - - - - - - - CLASS FUNCTION BODIES  - - - - - - - - //

template <class T>
Hashtable<T>::Hashtable(size_t size)
        : size_(size) {
}

template <class T>
size_t Hashtable<T>::size() const {
    return size_;
}

template <class T>
Hashtable<T>::~Hashtable() {
}

#endif //MYREGEX_HASHTABLE_H
