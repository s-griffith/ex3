#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <iostream>

typedef int T; //Delete after debugging!

/*
 *  Queue:
 *  This is a template class that can be used for managing decks of cards, the turns of players, and more.
*/
template <class T>
class Queue {
    struct Node {
        T m_data;
        Node *m_next;
    };
public:
    /*
     * Queue::Iterator
     * This class is used in calculations and functions throughout the Queue class.
    */
    class Iterator;
   // class Iterator;
    //Iterator Methods Included:
    Iterator& begin() const;
    Iterator& end() const;

    /*
     * Queue::EmptyQueue
     * This class is used for the errors thrown as a result of actions performed on an empty queue.
    */
    class EmptyQueue {};

//--------------------------------Queue Class---------------------------------
    
    /*
     * Constructor of the Queue:
     *
     * Receives no parameters.
     * @result
     *      An empty instance of the list (one node).
    */
    Queue();
    //Copy constructor
    //Destructor
    //Constructor for const queue

    //Method Functions:
    void pushBack(T data);
    T front();
    void popFront();
    int size();
    //Filter & Transform Functions

};

//--------------------------------Queue: Method Functions & Constructors---------------------------------

//Constructor
template <class T> Queue<T>::Queue() 
{
    Node.m_data = NULL;
    Node.m_next = NULL;
}

//Destructor, etc.
template <class T> void Queue<T>::pushBack(T data) {
    if (this&.Node.m_data == NULL) {
        Node.m_data = data;
    }
    else {
        Queue node();
        node.Node.m_data = data;
        //Move pointer over so that the last one points to the new one added now.
    }
}


//--------------------------------Iterator Class---------------------------------
//Left to add: begin and end functions, const version of the class?

template <class T> class Queue<T>::Iterator {
    //constructor(s)
public:
    //The minimal operators needed for defining an iterator:
    const T& operator*() const;
    Iterator& operator++();
    Iterator& operator++(T);
    bool operator!=(const Iterator& i) const;
    //Should this be public or private?
    class InvalidOperation {};

};

template <class T> const T& Queue<T>::Iterator::operator*() const {
    //Exception stuff
    try {
        //make sure not out of bounds or undefined somehow?
        const T& data = Node.m_data;
        if (!data) {
            throw EmptyQueue();
        }
    }
    catch (Queue<T>::EmptyQueue& e) { //not recognized - why?
        //what to do?
    }
    return data;
}

template <class T> Queue<T>::Iterator& Queue<T>::Iterator::operator++() {
    try {
        Iterator& next = Node.m_next;
        if (!next) {
            throw InvalidOperation()&;
        }
    }
    catch (Queue<T>::Iterator::InvalidOperation& e) {
        //what to do?
    }
    return next;
}

template <class T> Queue<T>::Iterator& Queue<T>::Iterator::operator++(T) { //What should the difference be between ++NUM and NUM++?
//This is just copied from the other function for now.
    try {
        Iterator& next = Node.m_next;
        if (!next) {
            throw InvalidOperation()&;
        }
    }
    catch (Queue<T>::Iterator::InvalidOperation& e) {
        //what to do?
    }
    return next;
}

template <class T> bool Queue<T>::Iterator::operator!=(const Iterator& i) const {
    try {
        bool result = !(*this == i);
        if (!(*this) && !i) {
            throw InvalidOperation()&;
        }
    }
    catch (Queue<T>::Iterator::InvalidOperation& e) {
        //what to do?
    }
    return result;
}


#endif //EX3_QUEUE_H