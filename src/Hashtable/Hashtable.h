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
 * @file Hashtable.h
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date 3/22/17.
 *
 * This header file has been compiled for C++11.
 *
 *
 * # TODO
 *
 * - Implement operator=
 * - Implement const_iterator
 * - Implement hashtable(h)
 *
 * Iterator
 * - Implement constructor parameter validation to verify that
 * the index of the entry corresponds to the index passed
 */
//</editor-fold>

#ifndef MYREGEX_HASHTABLE_H
#define MYREGEX_HASHTABLE_H

#include <string>
#include <vector>
#include <list>

// - - - - - - - - CLASS DEFINITION  - - - - - - - - //
/** @class hashtable
* # Description
*
* This is a class implementing a hashtable à la STL.
*
* We have to note that the default value for the Hasher is to utilize
* `std::hash` which overloads `operator()` and has a result of type `size_t`
*
* For insertion of an hash_entry of type `T`, we expect that the object class
* for `T` has an appropiate and well behaved copy constructor.
*/
template <
        class Key,
        class T,
        class Hasher = std::hash<Key>,
        class KeyEqual = std::equal_to<Key>
>
class hashtable {

public:
    // TYPEDEFS
    typedef hashtable<Key,T,Hasher,KeyEqual> self_type;

    // TYPEDEFS STRUCTURES
    typedef typename std::pair<Key, T> hash_entry_type;
    typedef typename std::list<hash_entry_type> bucket_type;
    typedef typename std::vector<bucket_type> index_table;


    // TYPEDEFS ITERATORS
    typedef typename index_table::iterator index_iterator;
    typedef typename bucket_type::iterator bucket_iterator;
    typedef typename bucket_type::const_iterator const_bucket_iterator;

    // CLASSES

    /// Class iterator
    class iterator;
    friend class iterator;

    /// Class const_iterator
    class const_iterator;
    friend class const_iterator;

    class iterator {
    public:
        typedef iterator self_type;
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

    class const_iterator {
    public:
        typedef const_iterator self_type;
        typedef int difference_type;
        typedef hash_entry_type& reference;
        typedef hash_entry_type value_type;
        typedef hash_entry_type* pointer;


        // Be careful to instantiate an entry at its corresponding index
        // Else, undefined behaviour occurs
        const_iterator(hashtable const& table, size_t index, const_bucket_iterator const& entry)
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
                        return t_.cend();

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
                            return t_.cend();

                    } while (t_.at(index_).empty() ); // current bucket is empty

                    entry_ = t_.at(index_).begin(); // return beginning of non-empty bucket
                    return *this;
                }
            }
        }

        self_type operator++(int dummy) { // postfix
            self_type it = *this; ++(*this); return it;
        }

        const reference operator*() const { return *entry_; }
        const_bucket_iterator operator->() const { return entry_; }

        bool operator==(const self_type& rhs) { return entry_ == rhs.entry_; }
        bool operator!=(const self_type& rhs) { return !(*this == rhs); }

    private:
        hashtable const& t_;
        size_t index_;
        const_bucket_iterator entry_;
    };

    // METHODS
public:

    hashtable()
    {}

    /// Constructs a hashtable with specified number of buckets
    hashtable(const size_t buckets)
            : bucket_count_(buckets),
              equal_to_(KeyEqual()),
              count_(0)
    {
        for (int i = 0; i < buckets; i++)
            table_.push_back( bucket_type() );
    }

    /**
     * @brief Inserts an element using its key into hashtable
     * @param key key of object
     * @param obj object
     * @return iterator pointing to the inserted object
     *
     * # Complexity
     * - Average \f$ O(1) \f$
     * - Worst \f$ O(n) \f$
     */
    iterator insert(Key const& key, T const& obj) {

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


    /**
     * @brief Finds an element in the hashtable
     *
     * This method returns an iterator pointing to the requested object.
     * If the specified key does not belong to an object the it will
     * return end()
     *
     * @param key key of object to find
     * @return an iterator pointing to the object, if object isn't found then return `end()`
     *
     * # Complexity
     * - Average \f$ O(1) \f$
     * - Worst \f$ O(n) \f$
     */
    iterator find(Key const& key) {
        size_t index = h_(key);
        index %= bucket_count_;

        bucket_type *b = &table_[index];
        for (bucket_iterator it = b->begin(); it != b->end(); it++) // iterate over bucket
            if ( equal_to_( key, it->first ) ) // if we find key return iterator to it
                return iterator( *this, index, it );

        return this->end();
    }

    /**
     * @brief Finds an element in the hashtable
     *
     * This is a const overload of the function `find(Key key)`.
     * It returns a const iterator pointing to the requested object.
     * In the given case the specified key does not belong to an object, then
     * it will return `cend()`.
     *
     * @param key key of object
     * @return a const iterator pointing to the object, if object isn't found then return cend()
     *
     * - Average \f$ O(1) \f$
     * - Worst \f$ O(n) \f$
     */
    const_iterator find(Key const& key) const {
        size_t index = h_(key);
        index %= bucket_count_;

        bucket_type *b = &table_[index];
        for (const_bucket_iterator it = b->begin(); it != b->end(); it++) // iterate over bucket
            if ( equal_to_( key, it->first ) ) // if we find key return iterator to it
                return const_iterator( *this, index, it );

        return this->cend();
    }

    /**
     * @brief Erases an object by its key
     *
     * It the specified key isn't found then it has no effect
     * @param key key of object
     */
    void erase(Key const& key) {
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

    /**
     * @brief Returns true if the key is found in the hashtable
     *
     * This method looks to see if a specified key is in the
     * hashtable.
     * If the key is found, then return true.
     * If the key isn't found, then return false.
     * @param key Key of object
     * @return `true` if key is found, `false` otherwise
     */
    bool contains_key(Key const& key) {
        size_t index = h_(key);
        index %= bucket_count_;

        bucket_type *b = &table_[index];
        for (bucket_iterator it = b->begin(); it != b->end(); it++)
            if (equal_to_(key, it->first))
                return true;

        return false;
    }

    /**
     * @brief  Returns the number of buckets in the hashtable
     * @return Number of buckets
     */
    size_t bucket_count() const {
        return bucket_count_;
    }

    /**
     * @brief Returns an iterator pointing to the first element of the table
     *
     * If no elements are in the hashtable, then it will return `end()`
     *
     * @return `iterator` pointing to the first element
     */
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

    /**
     * @brief Returns an iterator pointing to the end of the hashtable
     *
     * The end of the hashtable is defined as being one position after
     * the last element.
     * @return End of hashtable
     */
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

    /**
     * @brief Returns a const iterator the beginning of hashtable. See `begin()`.
     *
     * @return Const iterator pointing to the beginning of hashtable
     */
    const_iterator cbegin()  const{
        size_t index = 0;

        while (at(index).empty() )// current at is empty
        {
            if ( index == bucket_count() - 1 )
                return const_iterator( *this, index, at(bucket_count() - 1).end() ); // return end of last bucket

            index++;
        }
        return const_iterator(*this, index, at(index).begin() ); // return beginning of first non-empty bucket
    }

    /**
     * @brief Returns a const iterator to the end of hashtable. See `end()`.
     *
     * @return Const iterator pointing to the end of hashtable.
     */
    const_iterator cend() const {
        size_t index = bucket_count() - 1;

        while (at(index).empty() ) // current at is empty
        {
            if ( index == 0 )
                return const_iterator( *this, index, at(bucket_count() - 1).end() ); // return end of last bucket

            index--;
        }
        return const_iterator( *this, index, at(index).end() ); // return end of first non-empty bucket
    }

    /**
     * @brief Returns the bucket at the specified index
     * @param index Index of bucket
     * @return Bucket at specified index
     */
    bucket_type& at(size_t index) {
        return table_.at(index);
    }

    /**
     * @brief Returns a const reference to the specified bucket at index
     * @param index Index of bucket
     * @return Const reference to bucket
     */
    const bucket_type& at(size_t index) const {
        return table_.at(index);
    }

    /**
     * @brief Returns a reference to the object with the specified key
     * @param key Key of object
     * @return Reference to hashtable object
     */
    T& at(Key const& key) {
        return find(key)->second;
    }

    /**
     * @brief Returns a const reference to the object with the specified key
     * @param key Key of object
     * @return Const reference to object
     */
    const T& at(Key const& key) const {
        return find(key)->second;
    }

    /**
     * @brief Returns a reference to the object with the specified key
     * @param key Key of object
     * @return Reference to object
     */
    T& operator[](Key const& key) {
        return at(key);
    }

    /**
     * @brief Returns the bucket at the specified index
     * @param index Index of bucket
     * @return Bucket at specified index
     */
    bucket_type operator[](size_t index) {
        return at(index);
    }

    /**
     * @brief Returns a const reference to the object with the specified key
     * @param key Key of object
     * @return Const reference to object
     */
    const T& operator[](Key const& key) const {
        return at(key);
    }

    /**
     * @brief Returns a const reference to the specified bucket at index
     * @param index Index of bucket
     * @return Bucket at specified index
     */
    const bucket_type& operator[](size_t index) const {
        return at(index);
    }

    /**
     * @brief Returns the object count in the hashtable
     * @return Count of objects in hashtable
     */
    size_t count() {
        return count_;
    }

    /**
     * @brief Returns the object count in the hashtable
     * @return Count of objects in hashtable
     */
    size_t count() const {
        return count_;
    }

    /**
     * @brief Returns the load factor of the hashtable
     *
     * This value is calculated as follows:
     * \f$ n/k \f$
     *
     * Where:
     * $n$ is the number of objects in the hashtable
     * $k$ is the number of buckets in the hashtable
     *
     * @return Load factor of hashtable
     */
    double load_factor() {
        return count_/bucket_count_;
    }

    /**
     * @brief Overload of the operator `=`
     *
     * This operator overwrites the left hand side value completely.
     *
     * @param rhs Hashtable to be copied
     * @return Reference to new object
     */
    self_type& operator=(self_type const& rhs) {
        if (this != &rhs)
        {
            bucket_count_ = rhs.bucket_count_;
            count_ = rhs.count_;

            while (!table_.empty())
                table_.pop_back();

            for (int i = 0; i < bucket_count_; i++)
                table_.push_back( rhs.at(i) );
        }
        return *this;
    }

    hashtable(const hashtable& table) {
        bucket_count_ = table.bucket_count_;
        count_ = table.count_;
        table_ = index_table(bucket_count_); // invalidate previous data, let the g.c. take care of it

        for (int i = 0; i < bucket_count_; i++)
            table_.push_back( table.at(i) );
    }

    // VARIABLES
private:
    /// Key comparator
    KeyEqual equal_to_ = KeyEqual();

    /// Table of indexes to buckets
    index_table table_;

    /// Hasher
    Hasher h_;

    /// Number of buckets in table
    size_t bucket_count_;

    /// Number of inserted elements
    size_t count_;

};

#endif //MYREGEX_HASHTABLE_H

