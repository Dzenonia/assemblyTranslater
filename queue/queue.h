#pragma once

#include <initializer_list>
#include <exception>
#include <stdexcept>
#include <iostream>

template<class T>
class Queue {

public:

    Queue();

    Queue(const std::initializer_list<T> &list);

    Queue(const Queue &queue);

    Queue(Queue &&queue);

    Queue &operator=(Queue &&queue);

    Queue &operator=(const Queue &queue);

    ~Queue();

    void push(const T &value);

    int size() const;

    bool isEmpty() const;

    void clear();

    void pop();

    T &front();

    T &back();

    const T &front() const;

    const T &back() const;

    Queue copy() const;

    void move(Queue &&queue);

    bool operator==(const Queue &queue) const;

private:

    class Node {
    public:
        T value;
        Node *next_;
        Node *prev_;

        Node(const T &value, Node *next = nullptr, Node *prev = nullptr);

        Node();
    };

    Node *top_;
    Node *tail_;
    int size_;
};

template<class T>
Queue<T>::Node::Node(const T &value, Node *next, Node *prev) : value(value), next_(next), prev_(prev) {}

template<class T>
Queue<T>::Node::Node() : value(), next_(nullptr), prev_(nullptr) {}

template<class T>
Queue<T>::Queue() : top_(nullptr), tail_(nullptr), size_(0) {}

template<class T>
Queue<T>::Queue(const Queue<T> &queue) : top_(nullptr), tail_(nullptr), size_(0) {
    this->move(std::move(queue.copy()));
}

template<class T>
Queue<T>::Queue(Queue<T> &&queue) : top_(nullptr), tail_(nullptr), size_(0) {
    move(std::move(queue));
}

template<class T>
Queue<T> &Queue<T>::operator=(Queue<T> &&queue) {
    move(std::move(queue));
    return *this;
}

template<class T>
Queue<T>::Queue(const std::initializer_list<T> &list) : top_(nullptr), tail_(nullptr), size_(0) {
    for (const auto &value: list) {
        push(value);
    }
}

template<class T>
Queue<T> &Queue<T>::operator=(const Queue<T> &queue) {
    this->move(std::move(queue.copy()));
    return *this;
}

template<class T>
Queue<T>::~Queue() {
    clear();
}

template<class T>
void Queue<T>::push(const T &value) {
    if (isEmpty()) {
        top_ = new Node(value);
        tail_ = top_;
        size_ = 1;
        return;
    }
    tail_->prev_ = new Node(value, tail_);
    tail_ = tail_->prev_;
    ++size_;
}

template<class T>
int Queue<T>::size() const {
    return size_;
}

template<class T>
bool Queue<T>::isEmpty() const {
    return size_ == 0;
}

template<class T>
void Queue<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    if (size_ == 1) {
        delete top_;
        top_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
        return;
    }
    Node *oldTop = top_;
    top_ = top_->prev_;
    top_->next_ = nullptr;
    delete oldTop;
    --size_;
}

template<class T>
void Queue<T>::clear() {
    while (!isEmpty()) {
        pop();
    }
}

template<class T>
T &Queue<T>::front() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return top_->value;
}

template<class T>
T &Queue<T>::back() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return tail_->value;
}

template<class T>
const T &Queue<T>::front() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return top_->value;
}

template<class T>
const T &Queue<T>::back() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return tail_->value;
}

template<class T>
Queue<T> Queue<T>::copy() const {
    Queue<T> copyQueue;
    Node *tempNode = top_;
    while (tempNode != nullptr) {
        copyQueue.push(tempNode->value);
        tempNode = tempNode->prev_;
    }
    return copyQueue;
}

template<class T>
void Queue<T>::move(Queue<T> &&queue) {
    if (this == &queue) {
        return;
    }
    clear();
    top_ = std::move(queue.top_);
    tail_ = std::move(queue.tail_);
    size_ = std::move(queue.size_);
    queue.top_ = nullptr;
    queue.tail_ = nullptr;
    queue.size_ = 0;
}

template<class T>
bool Queue<T>::operator==(const Queue<T> &queue) const {
    if (size_ != queue.size_) {
        return false;
    }
    Node *lhsQueue = top_;
    Node *rhsQueue = queue.top_;
    for (int i = 0; i < size_; ++i) {
        if (lhsQueue->value != rhsQueue->value) {
            return false;
        }
        lhsQueue = lhsQueue->prev_;
        rhsQueue = rhsQueue->prev_;
    }
    return true;
}
