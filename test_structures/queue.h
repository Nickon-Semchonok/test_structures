#pragma once
#include "doubly_linked_list.h"
#include <stdexcept>

template<typename T>
class Queue : private DoublyLinkedList<T> {
public:
    Queue() : DoublyLinkedList<T>() {}

    void enqueue(const T& val) {
        this->push_back(val);
    }

    T dequeue() {
        if (this->isEmpty()) throw std::out_of_range("Queue is empty");
        DNode<T>* temp = this->head;
        T val = temp->data;

        this->head = this->head->next;
        if (this->head) this->head->prev = nullptr;
        else this->tail = nullptr;

        delete temp;
        this->count--;
        return val;
    }

    T& front() {
        if (this->isEmpty()) throw std::out_of_range("Queue is empty");
        return this->head->data;
    }

    bool isEmpty() const { return DoublyLinkedList<T>::isEmpty(); }
    size_t size() const { return DoublyLinkedList<T>::getCount(); }
};
