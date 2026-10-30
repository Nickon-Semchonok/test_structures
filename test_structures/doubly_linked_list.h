#pragma once
#include <iostream>
#include "node.h"

template<typename T>
class DoublyLinkedList {
protected:
    DNode<T>* head;
    DNode<T>* tail;
    size_t count;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), count(0) {
        DNode<T>* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    virtual ~DoublyLinkedList() {
        clear();
    }

    bool isEmpty() const { return count == 0; }
    size_t getCount() const { return count; }

    void push_back(const T& val) {
        DNode<T>* newNode = new DNode<T>(val);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }

    void clear() {
        DNode<T>* current = head;
        while (current != nullptr) {
            DNode<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
        count = 0;
    }

    DNode<T>* clone() const {
        if (head == nullptr) return nullptr;
        DNode<T>* newHead = new DNode<T>(head->data);
        DNode<T>* newTail = newHead;
        DNode<T>* current = head->next;

        while (current != nullptr) {
            DNode<T>* newNode = new DNode<T>(current->data);
            newTail->next = newNode;
            newNode->prev = newTail;
            newTail = newNode;
            current = current->next;
        }
        return newHead;
    }

    DNode<T>* operator+(const DoublyLinkedList<T>& other) const {
        DoublyLinkedList<T> res;
        DNode<T>* curr = this->head;
        while (curr) { res.push_back(curr->data); curr = curr->next; }
        curr = other.head;
        while (curr) { res.push_back(curr->data); curr = curr->next; }

        DNode<T>* h = res.head;
        res.head = res.tail = nullptr;
        res.count = 0;
        return h;
    }

    DNode<T>* operator*(const DoublyLinkedList<T>& other) const {
        DoublyLinkedList<T> res;
        DNode<T>* c1 = this->head;
        while (c1) {
            DNode<T>* c2 = other.head;
            bool found = false;
            while (c2) {
                if (c1->data == c2->data) { found = true; break; }
                c2 = c2->next;
            }
            if (found) {
                bool exists = false;
                DNode<T>* rc = res.head;
                while (rc) {
                    if (rc->data == c1->data) { exists = true; break; }
                    rc = rc->next;
                }
                if (!exists) res.push_back(c1->data);
            }
            c1 = c1->next;
        }
        DNode<T>* h = res.head;
        res.head = res.tail = nullptr;
        res.count = 0;
        return h;
    }

    void printList(DNode<T>* h) const {
        DNode<T>* curr = h;
        std::cout << "[ ";
        while (curr) { std::cout << curr->data << " "; curr = curr->next; }
        std::cout << "]" << std::endl;
    }
};
