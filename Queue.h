#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <iostream>
#include <new>

//typedef int T; //Delete after debugging!

/*
 * Left to figure out:
 *      beginning empty node? maybe not necessary
 *      change destroyNode function to destructor - make sure no memory leaks
 */


/*
 *  Queue:
 *  This is a template class that can be used for managing decks of cards, the turns of players, and more.
*/


template <class T>
class Queue {
    class Node{
    public:
        T m_data;
        Node* m_next;
        //Constructor
        Node();
        //Destroy Node(s):
        void destroyNode(Node *node);
    };
public:
    /*
     * Queue::Iterator
     * This class is used in calculations and functions throughout the Queue class.
    */
    class Iterator;
    //Iterator methods included:
    Iterator begin();
    Iterator end();

    /*
    * Queue::ConstIterator
    * This class is used in calculations and functions throughout the Queue class.
    */
    class ConstIterator;
    //Const iterator methods included:
    ConstIterator begin() const;
    ConstIterator end() const;

    /*
     * Queue::EmptyQueue
     * This class is used for the errors thrown as a result of actions performed on an empty queue.
    */
    class EmptyQueue {};

    //Constructor
    Queue();
    //Destructor
    ~Queue();
    //Copy constructor
    Queue(const Queue& original);
    //Assignment operator
    Queue& operator=(const Queue& original);

    //Method Functions:
    void pushBack(const T& data);
    T& front();
    const T& front() const;
    void popFront();
    int size() const;
    int size();
private:
    Node *m_node;
};


//--------------------------------Queue: Method Functions & Constructors---------------------------------

//Constructor
template <class T>
Queue<T>::Queue()
{
    //Creating beginning empty node
    try {
        m_node = new Node;
    }
    catch (const std::bad_alloc& e) {
        delete m_node;
        throw std::bad_alloc();
    }
    //Creating end empty node
    Node *nodeNew = new Node;
    try {
        if (!nodeNew) {
            throw std::bad_alloc();
        }
    }
    catch (const std::bad_alloc& e) {
        delete nodeNew;
        throw std::bad_alloc();
    }
    m_node->m_next = nodeNew;
}

//Destructor
template <class T>
Queue<T>::~Queue() 
{
    Node* current;
    while (m_node != nullptr) {
        current = m_node->m_next;
        delete m_node;
        m_node = current;
    }
}

//Copy Constructor
template <class T>
Queue<T>::Queue(const Queue& original)
{
    try {
        m_node = new Node;
    }
    catch (const std::bad_alloc& e) {
        delete m_node;
        throw std::bad_alloc();
    }
    //Creating end empty node
    Node *nodeNew = new Node;
    try {
        if (!nodeNew) {
            throw std::bad_alloc();
        }
    }
    catch (const std::bad_alloc& e) {
        delete nodeNew;
        throw std::bad_alloc();
    }
    m_node->m_next = nodeNew;
    try {
        for (const T& elem : original) {
            this->Queue<T>::pushBack(elem);
        }
    }
    catch (...) {
        m_node->Node::destroyNode(m_node);
        throw;
    }
}


//Assignment Operator
template <class T>
typename Queue<T>::Queue& Queue<T>::operator=(const Queue& original)
{
    if (this == &original) {
        return *this;
    }
    Queue queueNew(original);
    Node* tmp = queueNew.m_node;
    queueNew.m_node = m_node;
    m_node = tmp;
    return *this;
}


template <class T>
void Queue<T>::pushBack(const T& data)
{
    Queue<T>::Iterator endIt = this->end();
    endIt.m_currentNode->m_data = data;
    //Creating end empty node
    Node *nodeNew = new Node;
    try {
        if (!nodeNew) {
            throw std::bad_alloc();
        }
    }
    catch (const std::bad_alloc& e) {
        delete nodeNew;
        throw std::bad_alloc();
    }
    endIt.m_currentNode->m_next = nodeNew;
}

template <class T>
T& Queue<T>::front()
{
    if (m_node->m_next->m_next == nullptr) {
        throw EmptyQueue();
    }
    return m_node->m_next->m_data;
}

template <class T>
const T& Queue<T>::front() const
{
    if (m_node->m_next->m_next == nullptr) {
        throw EmptyQueue();
    }
    return m_node->m_next->m_data;
}

template <class T>
void  Queue<T>::popFront()
{
    if (m_node->m_next->m_next == nullptr) {
        throw EmptyQueue();
    }
    //If the list isn't empty
    else {
        Node* toPop = m_node->m_next;
        m_node->m_next = m_node->m_next->m_next;
        toPop->m_next = nullptr;
        toPop->Node::destroyNode(toPop);
    }
}

//Returns the size of the linked list
template <class T>
int Queue<T>::size()
{
    Iterator current = this->begin();
    int counter = 0;
    while (current.m_currentNode->m_next != nullptr) {
        counter++;
        ++current;
    }
    return counter;
}

//Returns the size of the linked list - const version
template <class T>
int Queue<T>::size() const
{
    ConstIterator current = this->begin();
    int counter = 0;
    while (current.m_currentNode->m_next != nullptr) {
        counter++;
        ++current;
    }
    return counter;
}

//Returns the first node in the linked list
template <class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    Iterator current = Iterator(m_node);
    ++current;
    return current;
}

//Returns the after last node in the linked list
template <class T>
typename Queue<T>::Iterator Queue<T>::end()
{
    if (m_node->m_next->m_next == nullptr) {
        return Iterator(m_node->m_next);
    }
    Iterator current = this->begin();
    while (current.m_currentNode->m_next != nullptr) {
        ++current;
    }
    return current;
}

//Support for const objects: returns the first node in the linked list
template <class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    ConstIterator current = ConstIterator(m_node);
    ++current;
    return ConstIterator(current);
}

//Support for const objects: returns the after last node in the linked list
template <class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    if (m_node->m_next->m_next == nullptr) {
        return ConstIterator(m_node->m_next);
    }
    ConstIterator current = this->begin();
    while (current.m_currentNode->m_next != nullptr) {
        ++current;
    }
    return current;
}

//Copy given queue's elements to new queue if they fit the given condition
template <class T, typename Condition>
Queue<T> filter(const Queue<T>& current, const Condition c)
{
    if (!(current.begin() != current.end())) {
        throw typename Queue<T>::EmptyQueue();
    }
    Queue<T> newQueue;
    for (const T& elem : current) {
        if (c(elem)) {
            newQueue.pushBack(elem);
        }
    }
    return newQueue;
}

//Transform all the elements of the given queue according to the condition provided
template <class T, typename Condition>
void transform(Queue<T>& current, const Condition c) {
    if (!(current.begin() != current.end())) {
        throw typename Queue<T>::EmptyQueue();
    }
    for (T& elem : current) {
        c(elem);
    }
}

//--------------------------------Node Class---------------------------------

//Create a new node:
template <class T>
Queue<T>::Node::Node()
{
    m_next = nullptr;
}

//Destroy Nodes:
template <class T>
void Queue<T>::Node::destroyNode(Node* node) 
{
    Node* current = node;
    while (node != nullptr) {
        current = node->m_next;
        delete node;
        node = current;
    }
}

//--------------------------------Iterator Class---------------------------------

template <class T>
class Queue<T>::Iterator {
public:
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;
    ~Iterator() = default;

    //The minimal operators needed for defining an iterator:
    T& operator*() const;
    Iterator& operator++();
   // Iterator operator++(T);
    bool operator!=(const Iterator& i) const;
    class InvalidOperation {};

private:
    Queue<T>::Node* m_currentNode;
    Iterator(Queue<T>::Node* node);
    friend class Queue;
};

template <class T>
Queue<T>::Iterator::Iterator(Queue<T>::Node* node) :
        m_currentNode(node)
{}

template <class T>
T& Queue<T>::Iterator::operator*() const
{
    if (m_currentNode->m_next == nullptr) {
        throw Queue<T>::EmptyQueue();
    }
    return m_currentNode->m_data;
}

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if (m_currentNode->m_next == nullptr) {
        throw InvalidOperation();
    }
    m_currentNode = m_currentNode->m_next;
    return *this;
}
/*
template <class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(T)
{
    Iterator current = *this;
    if (m_currentNode->m_next == nullptr) {
        throw InvalidOperation();
    }
    m_currentNode = m_currentNode->m_next;
    return current;
}
*/
template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator& i) const
{
    return (m_currentNode != i.m_currentNode);
}

//--------------------------------ConstIterator Class---------------------------------

template <class T>
class Queue<T>::ConstIterator {
public:
    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;
    ~ConstIterator() = default;

    //The minimal operators needed for defining an iterator:
    const T& operator*() const;
    ConstIterator& operator++();
    //ConstIterator operator++(T);
    bool operator!=(const ConstIterator& i) const;
    class InvalidOperation {};

private:
    const Queue<T>::Node* m_currentNode;
    ConstIterator(const Node* node);
    friend class Queue;
};

template <class T>
Queue<T>::ConstIterator::ConstIterator(const Node* node) :
        m_currentNode(node)
{}

template <class T>
const T& Queue<T>::ConstIterator::operator*() const
{
    if (m_currentNode->m_next == nullptr) {
        throw Queue<T>::EmptyQueue();
    }
    return m_currentNode->m_data;
}

template <class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if (m_currentNode->m_next == nullptr) {
        throw InvalidOperation();
    }
    m_currentNode = m_currentNode->m_next;
    return *this;
}

/*
template <class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(T)
{
    ConstIterator current = *this;
    if (m_currentNode->m_next == nullptr) {
        throw InvalidOperation();
    }
    m_currentNode = m_currentNode->m_next;
    return current;
}
*/

template <class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& i) const
{
    return (m_currentNode != i.m_currentNode);
}

#endif //EX3_QUEUE_H