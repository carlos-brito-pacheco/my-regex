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
 * Implement operator=
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


    // TYPEDEFS STRUCTURES
    typedef typename std::pair<Key, T> hash_entry;
    typedef typename std::list<hash_entry> bucket;
    typedef typename std::vector<bucket> index_table;

    // TYPEDEFS ITERATORS
    typedef typename index_table::iterator index_iterator;
    typedef typename bucket::iterator bucket_iterator;

    // TYPEDEF GENERAL

    typedef hash_entry& reference;
    typedef hash_entry value_type;
    typedef hash_entry* pointer;

    // ITERATOR CLASS
public:
    class iterator {
    public:
        typedef iterator self_type;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

        /*
         * Note: Be super careful to NOT instantiate the iterator with  a copy of the bucket or the table
         * Do so with a REFERENCE or POINTER.
         */
        iterator(index_iterator const& index_it, bucket_iterator const& bucket_it)
                : index_it_(index_it),
                  bucket_it_(bucket_it)
        {}

        self_type operator++() { // prefix
            if ( bucket_it_ == index_it_->end() )
                // if we're at bucket end
            {
                bucket_it_ = (index_it_++)->begin(); // advance to next index and start of bucket
            } else {
                bucket_it_++;
            }
            return *this;
        }

        self_type operator++(int dummy) { // postfix
            self_type it = *this; ++(*this); return it;
        }

        reference operator*() { return *bucket_it_; }
        pointer operator->() { return &*bucket_it_; }

        bool operator==(const self_type& rhs) { return bucket_it_ == rhs.bucket_it_; }
        bool operator!=(const self_type& rhs) { return !(*this == rhs); }

    private:
        index_iterator index_it_;
        bucket_iterator bucket_it_;
    };


    // VARIABLES
private:
    KeyEqual equal_to = KeyEqual();
    index_table table_;
    Hasher h;
    const size_t size_;

    // METHODS
public:
    hashtable(const size_t size)
            : size_(size),
              h(Hasher()),
              equal_to(KeyEqual())
    {
        table_ = vector<bucket>(size);
    }

    virtual ~hashtable() {
    }

    virtual size_t size() const {
        return size_;
    }

    virtual iterator insert(Key const& key, T const& obj) {

        size_t index = h(key);
        index %= size_;

        bucket *b = &table_[index];

        // Verify that we're not adding a duplicate hash_entry
        for (bucket_iterator it = b->begin(); it != b->end(); it++)
            if ( equal_to( it->first, key ) )
                return this->end();

        b->push_back( hash_entry(key, obj) ); // push to back of bucket

        return iterator( table_.begin()+index, --(b->end()) );
    }

    virtual iterator find(Key const& key) {
        size_t index = h(key);
        index %= size_;

        bucket *b = &table_[index];
        for (bucket_iterator it = b->begin(); it != b->end(); it++)
            // iterate over bucket
            if ( equal_to( key, it->first ) )
                // if we find key return iterator to it
                return iterator( table_.begin()+index, it );

        return this->end();
    }

    virtual void remove(Key key) {
        size_t index = h(key);
        index %= size_;

        bucket *b = &table_[index];
        for (bucket_iterator it = b->begin(); it != b->end(); it++)
            if (equal_to(key, it->first))
                b->erase(it); // erase entry
    }

    virtual bool containsKey(Key key) {
        size_t index = h(key);
        index %= size_;

        bucket *b = &table_[index];
        for (bucket_iterator it = b->begin(); it != b->end(); it++)
            if (equal_to(key, it->first))
                return true;

        return false;
    }

    iterator begin() {
        bucket* first_bucket = &table_[0];
        return iterator(table_.begin(), first_bucket->begin());
    }

    iterator end() {
        bucket* last_bucket = &table_[size_ - 1];
        return iterator(table_.end(), last_bucket->end());
    }

};

#endif //MYREGEX_HASHTABLE_H
