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
 * @brief This header file contains the class declarations and definitions for Set.
 *
 * # Description
 *
 * This file contains the definitions for a class Set. The file contains the definitions
 * for the `iterator` and `const_iterator` classes which are embedded into the class Set.
 *
 * # TODO
 * - Implement operator=
 * - Implement bool SubsetOf(self_type left)
 *
 */
//</editor-fold>

#ifndef MYREGEX_SET_H
#define MYREGEX_SET_H

#include <functional>
#include "../Hashtable/Hashtable.h"

/** @class Set
* # Description
* The class models the behaviour and notion of a set. The main methods are:
*
* ( Assuming an element access has average complexity of \f$ O(1) \f$ )
*
* - Union -  \f$ O(n + m) \f$
* - Intersection - \f$ O(n) \f$
* - Difference - \f$ O(n) \f$
*/
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

    class iterator {
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

    class const_iterator {
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

public:
    Set (size_t bucket_count)
            : table_( hashtable<Key,Key&,Hasher,KeyEqual>(bucket_count) )
    {}


    /**
     * @brief Inserts element into set
     * @param element Element to be inserted
     * @return
     */
    iterator insert( Key element ) {
        return iterator( table_.insert(element, element) );
    }

    /**
     * @brief Removes specified element from set
     * @param element Element to be removed
     */
    void remove( Key element ) {
        return table_.erase(element);
    }

    /**
     * @brief Finds element in set
     * @param element Element to find
     * @return Iterator to found element
     *
     * If no element is found then this will return `end()`.
     */
    iterator find( Key element ) {
        return iterator( table_.find(element) );
    }

    /**
     * @brief Finds element in set
     * @param element Element to find
     * @return Const iterator to found element
     */
    const_iterator find( Key element ) const {
        return const_iterator( table_.find(element) );
    }

    /**
     * @brief Returns true if element is contained in set, false otherwise
     * @param element Element in question
     * @return True if element is in set, else false
     */
    bool contains( Key element ) {
        return table_.contains_key(element);
    }

    /**
     * @brief Returns the union of the set with another set \f$ S \f$
     *
     * # Complexity
     * \f$ O(n + m) \f$ where \f$ n \f$ and \f$ m \f$ are both sets' respective sizes
     * @param S second set
     * @return union of both sets
     */
    self_type Union( self_type const& S ) {
        self_type result = *this;
        for (const_iterator it = S.cbegin(); it != S.cend(); it++)
            result.insert(*it);

        return result;
    }

    /**
     * @brief Returns the intersection of the set with another set \f$ S \f$
     *
     * # Complexity
     * \f$ O(n) \f$ where \f$ n \f$ is the number of elements in set \f$ S \f$
     * @param S second set
     * @return intersection of both sets
     */
    self_type Intersection( self_type const& S ) {
        self_type result(this->bucket_count());
        for (const_iterator it = S.cbegin(); it != S.cend(); it++)
            if (this->contains(*it))
                result.insert(*it);

        return result;
    }

    /**
     * @brief Returns the difference of the set with another set \f$ S \f$
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

    /**
     * @brief Returns iterator pointing to the first element of the set
     *
     * If no elemnent is in set, then this will return `end()`.
     *
     * @return Iterator pointing to first element in set
     */
    iterator begin() {
        return iterator(table_.begin());
    }

    /**
     * @brief Returns iterator pointing to the end of the set
     * @return Iterator pointing to the end of set
     */
    iterator end() {
        return iterator(table_.end());
    }

    /**
     * @brief Returns const iterator pointing to the first element of the set
     *
     * See `begin()` for a better understanding of what constitues the beginninng of a set.
     *
     * @return Const iterator to the beginning of set.
     */
    const_iterator cbegin() const {
        return const_iterator(table_.cbegin());
    }

    /**
     * @brief Returns const iterator pointing to the end of the set
     *
     * See `end()`.
     *
     * @return Const iterator pointing to the end of set.
     */
    const_iterator cend() const {
        return const_iterator(table_.cend());
    }

    /**
     * @brief Returns the number of elements in the set
     * @return Number of elements in set
     */
    size_t count() const {
        table_.count();
    }

    /**
     * @brief Returns the number of buckets that the set uses
     * @return Number of buckets used internally by the set
     */
    size_t bucket_count() const {
        return table_.bucket_count();
    }

    /**
     * @brief Returns true if the set is empty, false otherwise
     * @return True if the set is empty, else false
     */
    bool empty() {
        return count() > 0;
    }

    /**
     * @brief Overloaded copy operator
     * @param rhs Set to be copied
     * @return Reference to new set
     */
    self_type& operator=(const self_type& rhs) {
        bucket_count_ = rhs.bucket_count_;
        table_ = rhs.table_;
        return *this;
    }

    // VARIABLES
private:
    /// Number of buckets that the set uses to store the elements
    size_t bucket_count_;

    /// Internal hashtable of the set
    hashtable<Key, Key&, Hasher, KeyEqual> table_;
};

#endif //MYREGEX_SET_H
