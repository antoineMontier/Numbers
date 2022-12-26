#include <iostream>
#include <sstream>
#include <iomanip>

#ifndef CELL_HPP
#define CELL_HPP

using namespace std;

template <class T>
class Cell{
    
    private:
        /// @brief the content of the cell
        T content;
        /// @brief the adress of the next cell, "nullptr" if no cells
        Cell<T> *next;

    public:
        /// @brief construct a new cell
        /// @param cont the content of the new cell
        /// @param nextcell the next cell
        Cell(T cont, Cell<T> nextcell);

        /// @brief construct a new cell
        /// @param other the other cell used for the copy
        Cell(const Cell<T>& other);

        /// @brief generate an empty cell
        Cell();

        /// @brief construct a new cell without neighbours
        /// @param cont the content of the new created cell
        Cell(T cont);

        /// @brief destruct the actual cell
        ~Cell();

        /// @brief get the content of the actual cell
        /// @return the content (can be null)
        T getContent() const;

        /// @brief set the new content of the actual cell, destructing the old one
        /// @param cont new content
        void setContent(T cont);

        /// @brief get the next cell
        /// @return next cell 
        Cell<T> getNext() const;

        /// @brief get the next cell adress 
        /// @return next cell adress or nullptr if not found
        Cell<T>* getNextPtr() const;

        /// @brief set the new next cell
        /// @param nextcell new next cell
        void setNext(Cell<T> *nextcell);

        /// @brief equality verification (content == content && next == next)
        /// @param other cell to compare
        /// @return true / false
        bool equal(Cell<T> other) const;

        /// @brief returns the string of the content of the cell
        /// @return a string representation of the cell
        const string toString() const;

        /// @brief check if the cel has a next cell
        /// @return true if the cel has a next cell false otherwise
        bool hasNext() const;

};

#endif