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
/**
 * @file Set.h
 * # Details
 * Author: Carlos Brito (carlos.brito524@gmail.com)
 * Date: 3/22/17.
 *
 * @class Set
 * # Description
 * This header file contains the class declarations and definitions for Set.
 *
 * The class models the behaviour and notion of a set. The main methods are:
 *
 * ( Assuming an element access has average complexity of O(1) )
 *
 * - Union ===  O(n)
 * - Intersection === O(n)
 * - Difference === O(n)
 *
 * # TODO
 * - Implement operator=
 * - Implement bool SubsetOf(self_type left)
 * 
 * 
 *
 */
//</editor-fold>

#ifndef MYREGEX_SET_H
#define MYREGEX_SET_H

#include <functional>
#include "../Hashtable/Hashtable.h"

template <
        class Key,
        class Hasher = std::hash<Key>,
        class KeyEqual = std::equal_to<Key>
>
class Set {
    typedef Set<Key, Hasher, KeyEqual> self_type;
    typedef typename hashtable<Key, Key&, Hasher, KeyEqual>::iterator hashtable_iterator;
    typedef typename hashtable<Key, Key&, Hasher, KeyEqual>::const_iterator const_hashtable_iterator;

public:
    /// Iterator class
    class iterator;
    friend class iterator;

    /// Const iterator class
    class const_iterator;
    friend class iterator;

public:
    Set (size_t bucket_count)
            : table_( hashtable<Key,Key&,Hasher,KeyEqual>(bucket_count) )
    {}


    /// Inserts element into set
    iterator insert( Key element ) {
        return iterator( table_.insert(element, element) );
    }

    /// Removes specified element from set
    void remove( Key element ) {
        return table_.erase(element);
    }

    /// Finds element in set
    iterator find( Key element ) {
        return iterator( table_.find(element) );
    }

    /// Finds element in set
    const_iterator find( Key element ) const {
        return const_iterator( table_.find(element) );
    }

    /// Returns true if element is contained in set, false otherwise
    bool contains( Key element ) {
        return table_.contains_key(element);
    }

    /// Returns the union of the set with another set s
    /**
     *
     * @param s second set
     * @return union of both sets
     */
    self_type Union( self_type const& s ) {
        self_type result = *this;
        for (const_iterator it = s.cbegin(); it != s.cend(); it++)
            result.insert(*it);

        return result;
    }

    /// Returns the intersection of the set with another set s
    /**
     *
     * @param s second set
     * @return intersection of both sets
     */
    self_type Intersection( self_type const& s ) {
        self_type result(this->bucket_count());
        for (const_iterator it = s.cbegin(); it != s.cend(); it++)
            if (this->contains(*it))
                result.insert(*it);

        return result;
    }

    /// Returns the difference of the set with another set s
    /**
     *
     * @param right the right operand of the difference
     * @return the difference of this set minus the second set
     */
    self_type Difference( self_type const& right ) {
        self_type result = *this;
        for (const_iterator it = right.cbegin(); it != right.cend(); it++)
            if ( this->contains(*it) )
                result.remove(*it);

        return result;
    }

    /// Returns iterator pointing to the first element of the set
    iterator begin() {
        return iterator(table_.begin());
    }

    /// Returns iterator pointing to the end of the set
    iterator end() {
        return iterator(table_.end());
    }

    /// Returns const iterator pointing to the first element of the set
    const_iterator cbegin() const {
        return const_iterator(table_.cbegin());
    }

    /// Returns const iterator pointing to the end of the set
    const_iterator cend() const {
        return const_iterator(table_.cend());
    }

    /// Returns the number of elements in the set
    size_t count() {
        table_.count();
    }

    /// Returns the number of buckets that the set uses
    size_t bucket_count() {
        return table_.bucket_count();
    }

    /// Returns true if the set is empty, false otherwise
    bool empty() {
        return count() > 0;
    }

    // VARIABLES
private:
    size_t bucket_count_;
    hashtable<Key, Key&, Hasher, KeyEqual> table_;
};

template <class Key, class Hasher, class KeyEqual>
class Set<Key, Hasher, KeyEqual>::iterator {
public:
    typedef iterator self_type;
    typedef int difference_type;
    typedef Key& reference;
    typedef Key value_type;
    typedef Key* pointer;

    iterator(hashtable_iterator const& hashtable_it)
            : hash_it_(hashtable_it)
    {}

    self_type operator++() { // prefix
        hash_it_++;
    }

    self_type operator++(int dummy) { // postfix
        self_type it = *this; ++(*this); return it;
    }

    reference operator*() { return hash_it_->first; }
    pointer operator->() { return &(hash_it_->first); }

    bool operator==(const self_type& rhs) { return hash_it_ == rhs.hash_it_; }
    bool operator!=(const self_type& rhs) { return !(*this == rhs); }

private:
    hashtable_iterator hash_it_;
};

template <class Key, class Hasher, class KeyEqual>
class Set<Key, Hasher, KeyEqual>::const_iterator {
public:
    typedef const_iterator self_type;
    typedef int difference_type;
    typedef Key& reference;
    typedef Key value_type;
    typedef Key* pointer;

    const_iterator(const_hashtable_iterator const& hashtable_it)
            : hash_it_(hashtable_it)
    {}

    self_type operator++() { // prefix
        hash_it_++;
    }

    self_type operator++(int dummy) { // postfix
        self_type it = *this; ++(*this); return it;
    }

    const value_type& operator*() { return hash_it_->first; }
    const pointer operator->() { return &(hash_it_->first); }

    bool operator==(const self_type& rhs) { return hash_it_ == rhs.hash_it_; }
    bool operator!=(const self_type& rhs) { return !(*this == rhs); }

private:
    const_hashtable_iterator hash_it_;
};

#endif //MYREGEX_SET_H
