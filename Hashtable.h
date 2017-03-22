/*
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

template <class T>
class Hashtable {

    vector<list<T> > *table_;
    const size_t size_;

public:
    Hashtable(size_t size);

    size_t size() const {
        return size_;
    }

    virtual int add(string key, T entry)= 0;
    virtual T get(string key)= 0;
    virtual bool containsKey(string key)= 0;
};

template <class T>
Hashtable<T>::Hashtable(size_t size)
        : size_(size) {
    table_ = new vector<list < T> > (size_);
}


#endif //MYREGEX_HASHTABLE_H
