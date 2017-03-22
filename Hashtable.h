/*
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/21/17.
 */

#ifndef MYREGEX_HASHTABLE_H
#define MYREGEX_HASHTABLE_H

#include <string>
#include <list>
#include <vector>

using  namespace std;

template <class T>
class Hashtable {

    vector<list<T> > table_;
    const size_t size_;

public:
    Hashtable(size_t size)
            : size_(size)
    {
        table_.reserve(size);
    }

    size_t size() const {
        return size_;
    }

    virtual int add(string key, T entry)= 0;
    virtual T get(string key)= 0;
    virtual bool containsKey(string key);
};

#endif //MYREGEX_HASHTABLE_H
