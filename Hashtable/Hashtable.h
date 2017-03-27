//<editor-fold desc="Preamble">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Copyright (C) 3/24/17 Carlos Brito
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
 * This is a class implementing a Hashtable à la STL.
 *
 * This header file has been compiled for C++11.
 *
 * We have to note that the default value for the Hasher is to utilize
 * std::hash which overloads  operator() and has a result of type size_t
 *
 * For insertion of an hash_entry of type T, we expect that the object class
 * for T has an appropiate and well behaved copy constructor.
 *
 * TODO:
 *
 * Re-implement methods
 * Implement operator=
 * Implement operator==
 * Implement iterator operators
 * Finish custom iterator class
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

#ifndef MYREGEX_HASHTABLE_H
#define MYREGEX_HASHTABLE_H

#include <iostream>
#include <string>
#include <list>
#include <array>
#include <functional>
#include <memory>
#include <vector>
#include <list>

#include "HashtableErrors.h"

// - - - - - - - - CLASS DEFINITION  - - - - - - - - //
template <
        class Key,
        class T,
        class Hasher = std::hash<Key>,
        class KeyEqual = std::equal_to<Key>
        >
class Hashtable {


    // TYPEDEFS
    typedef typename std::pair<Key, T*> hash_entry;
    typedef typename std::list<hash_entry> bucket;
    typedef typename std::vector<bucket> index_table;
    typedef typename index_table::iterator index_iterator;
    typedef typename bucket::iterator bucket_iterator;

    // ITERATOR CLASS
public:
    class iterator {
    public:
        typedef iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

        iterator(index_iterator index_it, bucket_iterator bucket_it)
                : index_it_(index_it),
                  bucket_it_(bucket_it)
        {
            entry_ptr_ = bucket_it->second;
        }

        self_type operator++() { // prefix
            if (bucket_it_ == index_it_->end())
            {
                bucket_it_ = (index_it_++)->begin();
                entry_ptr_ = bucket_it_->second;
            }
            else
            {
                entry_ptr_ = (bucket_it_++)->second;
            }
            return *this;
        }

        self_type operator++(int dummy) { // postfix
            self_type it = *this; ++(*this); return it;
        }

        reference operator*() { return *entry_ptr_; }
        pointer operator->() { return entry_ptr_;}

        bool operator==(const self_type& rhs) { return false; }
        bool operator!=(const self_type& rhs) { return false; }

    private:

        pointer entry_ptr_;

        bucket_iterator bucket_it_;
        index_iterator index_it_;
    };


    // VARIABLES
private:
    index_table table_;

    Hasher h;
    KeyEqual equal_to;
    const size_t size_;

    // METHODS
public:
    Hashtable(const size_t size)
            : size_(size),
              h(Hasher()),
              equal_to(KeyEqual())
    {
        table_ = vector<bucket>(size);
    }

    virtual ~Hashtable() {
    }

    virtual size_t size() const {
        return size_;
    }

    virtual size_t insert(Key key, T const &entry) {

        size_t index = h(key);
        index %= size_;

        // Verify that we're not adding a duplicate hash_entry
        for (bucket_iterator it = table_[index].begin(); it != table_[index].end(); it++)
            if ( equal_to(it->first, key) )
                throw DuplicateEntryError(index);

        table_[index].push_back( std::make_pair( key, new T(entry) ) ); // create copy of object using copy constructor

        return 0;
    }

    virtual iterator find(Key const& key) {
        size_t index = h(key);
        index %= size_;
    }

    virtual void remove(Key key) {
    }

    virtual bool containsKey(Key key) {
    }

    iterator begin() {
        bucket bucket0 = table_[0];
        return iterator(table_.begin(), bucket0.begin());
    }


};

#endif //MYREGEX_HASHTABLE_H
