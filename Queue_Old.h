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
public:
    /*
     * Queue::Iterator
     * This class is used in calculations and functions throughout the Queue class.
    */
    class Iterator;
    class Node;

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
    T& front();
    void popFront();
    int size() const;
    //Filter & Transform Functions
private:
    Node* m_node;

};

//--------------------------------Queue: Method Functions & Constructors---------------------------------

//Constructor
template <class T>
Queue<T>::Queue()
{
    m_node = Queue<T>::Node::newNode();
}

//Destructor, etc.
template <class T>
void Queue<T>::pushBack(T data)
{
    if (this&.Node.m_data == NULL) {
        Node.m_data = data;
    }
    else {
        Node* newNode = new Node;
        m_node->next = newNode;
    }
}

template <class T>
T& Queue<T>::front()
{
    return *m_node;
}

template <class T>
void  Queue<T>::popFront()
{
    Queue* current = &m_node;
    if (m_node->m_next != NULL) {
        m_node = m_node->m_next;
    }

}

//Returns the size of the linked list
template <class T>
int size() const
{
    Iterator current = Iterator(this);
    int counter = 0;
    if (current->m_queue->m_data != NULL) {
        counter++;
        while (current->m_queue->m_next != NULL) {
            counter++;
            current++;
        }
    }
    return counter;
}

//Returns the first node in the linked list
template <class T>
typename Queue<T>::Iterator Queue<T>::begin() const
{
    return Iterator(this);
}

//Returns the last node in the linked list
template <class T>
typename Queue<T>::Iterator Queue<T>::end() const
{
    Iterator current = Iterator(this);
    while (m_queue->m_next != NULL) {
        current = m_queue->node->m_next;
    }
    return current;
}

//--------------------------------Node Class---------------------------------

template <class T> class Node {
    T m_data;
    Node* m_next;

};

//--------------------------------Iterator Class---------------------------------
//Left to add: begin and end functions, const version of the class?

template <class T>
class Queue<T>::Iterator {
public:
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Interator&) = default;

    //The minimal operators needed for defining an iterator:
    const T& operator*() const;
    Iterator& operator++();
    Iterator& operator++(T);
    bool operator!=(const Iterator& i) const;
    //Should this be public or private?
    class InvalidOperation {};

private:
    const Queue* m_queue;
    Iterator(const Queue* queue);
    friend class Queue;
};

template <class T>
Queue<T>::Iterator::Iterator(const Queue<T>* queue) :
    m_queue(queue)
{}

template <class T>
const T& Queue<T>::Iterator::operator*() const
{
    Queue* current = m_queue;
    if (!current->node->m_data) {
        throw EmptyQueue();
    }
    return current->node->m_data;
}

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if (!m_queue.Node.m_next) {
        throw InvalidOperation()&;
    }
    m_queue = m_queue->node->m_next;
    return *this;
}

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++(T)
{
    Iterator& current = *this;
    if (!m_queue.Node.m_next) {
        throw InvalidOperation()&;
    }
    m_queue = m_queue->node->m_next;
    return current;
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator& i) const
{
    if (!(*this) || !i) {
        throw InvalidOperation()&;
    }
    return (m_queue.Node.m_data == i.Node.m_data);
}


#endif //EX3_QUEUE_H
