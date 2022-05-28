#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <iostream>
#include <new>

typedef int T; //Delete after debugging!

/*
 *  Queue:
 *  This is a template class that can be used for managing decks of cards, the turns of players, and more.
*/


template <class T>
class Queue {
    class Node; //forward declaration
public:
    /*
     * Queue::Iterator
     * This class is used in calculations and functions throughout the Queue class.
    */
    class Iterator;

    //Iterator Methods Included:
    Iterator begin() const;
    Iterator end() const;

    /*
     * Queue::EmptyQueue
     * This class is used for the errors thrown as a result of actions performed on an empty queue.
    */
    class EmptyQueue {};

    /*
     * Constructor of the Queue:
     *
     * Receives no parameters.
     * @result
     *      An empty instance of the list (one node).
    */
    Queue();
    //Destructor
    ~Queue();
    //Copy constructor
    Queue(const Queue& original);
    //Assignment operator
    Queue& operator=(const Queue& original);

    //Method Functions:
    void pushBack(const T& data);
    T& front() const;
    void popFront();
    int size() const;
private:
    Node m_node;
};


//--------------------------------Queue: Method Functions & Constructors---------------------------------

//Constructor
template <class T>
Queue<T>::Queue()
{
   m_node = Node::newNode();
}

//Destructor
template <class T>
Queue<T>::~Queue() 
{
    Node::destroyNode(m_node);
}

//Copy Constructor
template <class T>
Queue<T>::Queue(const Queue& original)
{
    m_node = Node::newNode();  
    for (const T& elem : original) {
        m_node.Queue<T>::pushBack(elem);
    }
}

//Assignment Operator
template <class T>
typename Queue<T>::Queue& Queue<T>::operator=(const Queue& original)
{
    if (this == &original) {
        return *this;
    }
    Node::destroyNode(m_node);
    m_node = Node::newNode();
    for (const T& elem : original) {
        m_node.Queue<T>::pushBack(elem)
    }
    return *this;
}


template <class T>
void Queue<T>::pushBack(const T& data)
{
    if (m_node.m_data == NULL) {
        m_node.m_data = data;
    }
    else {
        Queue nodeNew = Node::newNode();
        nodeNew.m_data = data;
        m_node.m_next = nodeNew; //maybe need: *nodeNew;
    }
}

template <class T>
T& Queue<T>::front() const
{
    if (!m_node.m_data) {
        throw Queue<T>::EmptyQueue;
    }
    return m_node.m_data; //tried to return reference to the data
}

template <class T>
void  Queue<T>::popFront()
{
    if (!m_node.m_data) {
        throw Queue<T>::EmptyQueue;
    }
    if (!m_node.m_next) {
        m_node.m_data = NULL;
    }
    else {
        Node *current = this.begin();
        if (!m_node.m_next) {
            m_node = m_node.m_next;
        }
        current.m_next = NULL;
        Node::destroyNode(current);
    }
}

//Returns the size of the linked list
template <class T>
int Queue<T>::size() const
{
    Iterator current = this.begin();
    int counter = 0;
    if (!current.m_queue.m_data) {
        counter++;
        while (!current.m_queue.m_next) {
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
    if (!m_queue.m_data) {
        return Iterator(nullptr);
    }
    return Iterator(this);
}

//Returns the after last node in the linked list - fix!
template <class T>
typename Queue<T>::Iterator Queue<T>::end() const
{
    return Iterator(nullptr);
}

//Copy given queue's elements to new queue if they fit the given condition
template <class Condition>
Queue<T>& filter(const Queue<T> current, const Condition c) {
    if ((!current) || (!c)) {
        throw EmptyQueue();
    }
    Queue<T> newQueue = Queue();
    for (const T& elem : current) {
        if (c(elem)) {
            newQueue.pushBack(x);
        }
    }
    return newQueue;
}

//Transform all the elements of the given queue according to the condition provided
template <class Condition>
void transform(Queue<T> current, const Condition c) {
    if ((!current) || (!c)) {
        throw EmptyQueue();
    }
    for (T& elem : current) {
        c(elem);
    }
}

//--------------------------------Node Class---------------------------------

template <class T>
class Queue<T>::Node {
public:
    T m_data;
    Node* m_next;
    //Create a new node:
    Node newNode();
    //Destroy Node(s):
    void destroyNode(Node node);
    //Add const things
};

//Create a new node:
template <class T>
typename Queue<T>::Node Queue<T>::Node::newNode()
{
    Node *node = new Node;
    if (!node) {
        throw std::bad_alloc;
    }
    node.m_data = NULL;
    node.m_next = NULL;
    return node;
}

//Destroy Nodes:
template <class T>
void Queue<T>::Node::destroyNode(Node node) 
{
    Node current = node; //do we need an assignment operator?
    while(!node) {
        current = current.m_next;
        delete[] node;
        node = current;
    }
}

//--------------------------------Iterator Class---------------------------------
//Left to add: const version of the class?

template <class T>
class Queue<T>::Iterator {
public:
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;

    //The minimal operators needed for defining an iterator:
    const T& operator*() const;
    Iterator& operator++();
    Iterator operator++(T);
    bool operator!=(const Iterator& i) const;
    //Should this be public or private?
    class InvalidOperation {};

private:
    Queue* m_queue;
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
    if (!m_queue.m_data) {
        throw EmptyQueue();
    }
    return m_queue.m_data;
}

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if (!m_queue.m_data) {
        throw InvalidOperation()&;
    }
    if (m_queue.m_next) {
        return Iterator(nullptr);
    }
    m_queue = m_queue.m_next;
    return *this;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(T)
{
    Iterator current = *this;
    if (!m_queue.m_data) {
        throw InvalidOperation()&;
    }
    if (m_queue.m_next) {
        return Iterator(nullptr);
    }
    m_queue = m_queue.m_next;
    return current;
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator& i) const
{
    if (!(*this) && !i) {
        return false;
    }
    if (!(*this) || !i) {
        return true;
    }
    return (m_queue.m_data != i.m_queue.m_data);
}


#endif //EX3_QUEUE_H