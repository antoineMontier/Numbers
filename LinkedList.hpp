#include "Cell.cpp"
#include <functional>

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

using namespace std;

/// @brief Dynamic linear stucture for storage, represented : head->cell->cell...cell->tail
/// @tparam T type of the data stored in the linked list
template <class T>

class LinkedList{
    
    private:
        /// @brief head pointer of the linked list
        Cell<T> * head;
        /// @brief tail pointer of the linked list
        Cell<T> * tail;

    public:

        LinkedList();

        /// @brief creates a new linked list containing only one element
        /// @param content only element in the list
        LinkedList(T content);

        ~LinkedList();

        /// @brief add an element at the beginning of the list
        /// @param content element to add
        void push(T content);

        /// @brief add an element at the end of the list
        /// @param content element to add
        void pushTail(T content);

        /// @brief removes an element at the beginning of the list
        /// @return element removed
        T pop();

        /// @brief removes an element at a precise position, may throw an exception if index < 0 or index >= size
        /// @param index index
        /// @return element removed
        T pop(int index);


        /// @brief removes an element at the end of the list
        /// @return element removed
        T popTail();

        /// @brief calculates the effective length of the list from 0
        /// @return size of the list
        int size() const;

        /// @brief get an index at a precise position, may throw an exception if index < 0 or index >= size
        /// @param index position
        /// @return data at position
        T get(int index) const;

        /// @brief set data at a precise position, may throw an exception if index < 0 or index >= size
        /// @param index position
        /// @param content data to add
        void set(int index, T content);

        /// @brief insert an element at a particular position, may throw an exception if index < 0 or index > size
        /// @param index index
        /// @param content data to insert
        void push(int index, T content);

        /// @brief look if two linked lists are equal
        /// @param other list to compare
        /// @return true if the two lists are equal, false otherwise
        bool equals(LinkedList<T> other) const;

        /// @brief apply bubble sort to the list
        /// @param comparator function, "[](a, b){return a < b;}" for a traditionnal sort
        /// @return new list sorted
        LinkedList<T> bubbleSort(std::function <bool(T, T)> comparator);

        /// @brief apply a function to every element of the list
        /// @param mapfunction function to apply to every element
        /// @return new list with all elements mapped
        LinkedList<T> map(std::function <T(T)> mapfunction) const;

        /// @brief filter the linkedlist with a predicate function
        /// @param filterfunction predicate, ex : [](a){return a % 2 == 0;}
        /// @return new list filtered
        LinkedList<T> filter(std::function <bool(T)> filterfunction) const;

        /// @brief find if a particular element is present in the list
        /// @param obj element to search
        /// @return true if founded at least one time
        bool contains(T obj) const;

        /// @brief removes first occurrence of a particular element
        /// @param obj object to remove
        /// @return true if removed, false if not founded
        bool remove(T obj);

        /// @brief removes all occurrences of a particular element
        /// @param obj object to remove
        /// @return false if no element founded, true otherwise
        bool removeAll(T obj);

        /// @brief reduce the list applying the given function
        /// @param first first iteration value
        /// @param reducefunction function to apply to every elements pair
        /// @return the reduced result
        T reduce(T first, std::function<T(T, T)> reducefunction) const;

        /// @brief find a max or a min according to a total order function
        /// @param comparator function used to search
        /// @return extremum
        T extremum(std::function <bool(T, T)> comparator) const;

        /// @brief reverse the order of the linkedlist elements
        /// @return linkedlist reversed
        LinkedList<T> reverse() const;

        /// @brief merge actual linked list with parameter linked list, actual elements merged before parameters elements
        /// @param other linkedlist to merge
        /// @return merged list
        LinkedList<T> merge(LinkedList<T> other) const;

        /// @brief string representation
        /// @return string of the linked list
        const string toString() const;

        /// @brief removes all elements from the linked list and set head and tail to nullptr
        void clear();
};


#endif