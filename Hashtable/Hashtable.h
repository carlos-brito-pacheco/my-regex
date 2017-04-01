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
 * This is a class implementing a hashtable à la STL.
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
 * - Implement operator=
 * - Implement const_iterator
 * - Implement hashtable(h)
 *
 * Iterator
 * - Implement constructor parameter validation to verify that
 * the index of the entry corresponds to the index passed
 *
 *
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

// - - - - - - - - CLASS DEFINITION  - - - - - - - - //
template <
        class Key,
        class T,
        class Hasher = std::hash<Key>,
        class KeyEqual = std::equal_to<Key>
>
class hashtable {

public:
    class iterator;
    friend class iterator;

    // TYPEDEFS
    typedef hashtable<Key,T,Hasher,KeyEqual> self_type;

    // TYPEDEFS STRUCTURES
    typedef typename std::pair<Key, T> hash_entry_type;
    typedef typename std::list<hash_entry_type> bucket_type;
    typedef typename std::vector<bucket_type> index_table;


    // TYPEDEFS ITERATORS
    typedef typename index_table::iterator index_iterator;
    typedef typename bucket_type::iterator bucket_iterator;

    // METHODS
public:
    hashtable(const size_t buckets)
            : bucket_count_(buckets),
              equal_to_(KeyEqual()),
              count_(0)
    {
        for (int i = 0; i < buckets; i++)
            table_.push_back( bucket_type() );
    }

     ~hashtable() {
    }

     size_t size() const {
        return bucket_count_;
    }

     iterator insert(Key key, T const& obj) {

        size_t index = h_(key);
        index %= bucket_count_;

        bucket_type *b = &table_[index];

        // Verify that we're not adding a duplicate hash_entry
        for (bucket_iterator it = b->begin(); it != b->end(); it++)
            if ( equal_to_( it->first, key ) )
                return iterator(*this, index, it); // return iterator to duplicate entry

         b->push_back( hash_entry_type(key, obj) ); // push to back of bucket
         count_++;

        return iterator( *this, index, --(b->end()) );
    }

     iterator find(Key key) {
        size_t index = h_(key);
        index %= bucket_count_;

        bucket_type *b = &table_[index];
        for (bucket_iterator it = b->begin(); it != b->end(); it++) // iterate over bucket
            if ( equal_to_( key, it->first ) ) // if we find key return iterator to it
                return iterator( *this, index, it );

        return this->end();
    }

     void erase(Key key) {
        size_t index = h_(key);
        index %= bucket_count_;

        bucket_type *b = &table_[index];
        for (bucket_iterator it = b->begin(); it != b->end(); it++)
            if (equal_to_(key, it->first))
            {
                b->erase(it); // erase entry
                count_--;
            }

    }

     bool contains_key(Key key) {
        size_t index = h_(key);
        index %= bucket_count_;

        bucket_type *b = &table_[index];
        for (bucket_iterator it = b->begin(); it != b->end(); it++)
            if (equal_to_(key, it->first))
                return true;

        return false;
    }

    size_t bucket_count() const {
        return bucket_count_;
    }

    iterator begin()  {
        size_t index = 0;

        while (at(index).empty() )// current at is empty
        {
            if ( index == bucket_count() - 1 )
                return iterator( *this, index, at(bucket_count() - 1).end() ); // return end of last bucket

            index++;
        }
        return iterator(*this, index, at(index).begin() ); // return beginning of first non-empty bucket
    }

    iterator end()  {
        size_t index = bucket_count() - 1;

        while (at(index).empty() ) // current at is empty
        {
            if ( index == 0 )
                return iterator( *this, index, at(bucket_count() - 1).end() ); // return end of last bucket

            index--;
        }
        return iterator( *this, index, at(index).end() ); // return end of first non-empty bucket
    }

     bucket_type& at(size_t index) {
         return table_[index];
    }

    T& at(Key key) {
        return find(key)->second;
    }

    T& operator[](Key key) {
        return at(key);
    }

    bucket_type& operator[](size_t index) {
        return at(index);
    }

    size_t count() {
        return count_;
    }

    double load_factor() {
        return count_/bucket_count_;
    }

    self_type& operator=(self_type const& rhs) {
        if (this != &rhs)
        {
            bucket_count_ = rhs.bucket_count_;
            count_ = rhs.count_;
            table_ = index_table( rhs.bucket_count_ ); // invalidate previous data, let the g.c. take care of it

            std::copy(rhs.table_.begin(), rhs.table_.end(), table_.begin()); // copy data from rhs into this
        }

        return *this;
    }

    // VARIABLES
private:
    KeyEqual equal_to_ = KeyEqual();
    index_table table_;
    Hasher h_;
    size_t bucket_count_;
    size_t count_;

};

template <
        class Key,
        class T,
        class Hasher,
        class KeyEqual
>
class hashtable<Key,T,Hasher,KeyEqual>::iterator {
public:
    typedef iterator self_type;
    typedef std::forward_iterator_tag iterator_category;
    typedef int difference_type;
    typedef hash_entry_type& reference;
    typedef hash_entry_type value_type;
    typedef hash_entry_type* pointer;


    // Be careful to instantiate an entry at its corresponding index
    // Else, undefined behaviour occurs
    iterator(hashtable& table, size_t index, bucket_iterator const& entry)
            : t_(table),
              index_(index),
              entry_(entry)
    {}

    self_type operator++() { // prefix

        if (t_.at(index_).empty() )
        {
            do // look for non empty bucket
            {
                index_++; // advance to next bucket

                if ( index_ == t_.bucket_count() ) // still no bucket found
                    return t_.end();

            } while (t_.at(index_).empty() ); // current at is empty
            entry_ = t_.at(index_).begin(); // return beginning of non-empty bucket

            return *this;
        } else {
            if ( ++entry_ != t_.at(index_).end() )
            {
                return *this;
            } else {
                do // look for non empty at
                {
                    index_++; // advance to next at

                    if ( index_ == t_.bucket_count() ) // still no bucket found
                        return t_.end();

                } while (t_.at(index_).empty() ); // current bucket is empty

                entry_ = t_.at(index_).begin(); // return beginning of non-empty bucket
                return *this;
            }
        }
    }

    self_type operator++(int dummy) { // postfix
        self_type it = *this; ++(*this); return it;
    }

    reference operator*() { return *entry_; }
    bucket_iterator operator->() { return entry_; }

    bool operator==(const self_type& rhs) { return entry_ == rhs.entry_; }
    bool operator!=(const self_type& rhs) { return !(*this == rhs); }

private:
    hashtable &t_;
    size_t index_;
    bucket_iterator entry_;
};
#endif //MYREGEX_HASHTABLE_H
