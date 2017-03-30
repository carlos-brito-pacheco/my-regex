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
 * TODO:
 * 
 * 
 * 
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

#ifndef MYREGEX_SET_H
#define MYREGEX_SET_H

#include <functional>
#include "../Hashtable/hashtable.h"

template <
        class Key,
        class Hasher = std::hash<Key>,
        class KeyEqual = std::equal_to<Key>
>
class Set {
    typedef Set<Key, Hasher, KeyEqual> self_type;
    typedef typename hashtable<Key, Key&, Hasher, KeyEqual>::iterator hashtable_iterator;

public:
    class iterator;
    friend class iterator;


public:
    Set (size_t bucket_count)
            : table_( hashtable<Key,Key&,Hasher,KeyEqual>(bucket_count) )
    {}

    iterator insert( Key element ) {
        return iterator( table_.insert(element, element) );
    }

    iterator find( Key element ) {
        return iterator( table_.find(element) );
    }

    void remove( Key element ) {
        return table_.erase(element);
    }

    bool contains( Key element ) {
        return table_.contains_key(element);
    }

    self_type Union( self_type &s ) {
        self_type result = *this;
        for (iterator it = s.begin(); it != s.end(); it++)
            result.insert(*it);
        return result;
    }

    self_type Intersection( self_type &s ) {
        self_type result(table_.bucket_count());
        for (iterator it = s.begin(); it != s.end(); it++)
            if (this->contains(*it))
                result.insert(*it);
        return result;
    }

    iterator begin() {
        return iterator(table_.begin());
    }

    iterator end() {
        return iterator(table_.end());
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
    typedef std::forward_iterator_tag iterator_category;
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


#endif //MYREGEX_SET_H
