#pragma once
#include "node.h"
#include <stdexcept>

template<typename T>
class Array {
private:
    DNode<T>* head;
    DNode<T>* tail;
    int size;
    int count;
    int growValue;

    DNode<T>* getNodeAt(int index) const {
        if (index < 0 || index >= size) return nullptr; 
        DNode<T>* curr = head;
        for (int i = 0; i < index; i++) curr = curr->next;
        return curr;
    }

public:
    Array() : head(nullptr), tail(nullptr), size(0), count(0), growValue(1) {}

    Array(const Array& other) : head(nullptr), tail(nullptr), size(0), count(0), growValue(other.growValue) {
        SetSize(other.size, other.growValue);
        for (int i = 0; i < other.count; i++) SetAt(i, other.GetAt(i));
        this->count = other.count;
    }

    ~Array() { RemoveAll(); }

    int GetSize() const { return size; }

    void SetSize(int newSize, int grow = 1) {
        growValue = grow;
        if (newSize < 0) newSize = 0;

        if (newSize < count) {
            for (int i = count - 1; i >= newSize; i--) RemoveAt(i);
        }
        else if (newSize > size) {
            for (int i = size; i < newSize; i++) {
                DNode<T>* newNode = new DNode<T>(T());
                if (!tail) head = tail = newNode;
                else { tail->next = newNode; newNode->prev = tail; tail = newNode; }
            }
        }
        size = newSize;
    }

    int GetUpperBound() const { return count > 0 ? count - 1 : -1; }
    bool IsEmpty() const { return count == 0; }

    void FreeExtra() {
        while (count < size && tail) {
            DNode<T>* temp = tail;
            tail = tail->prev;
            if (tail) tail->next = nullptr;
            else head = nullptr;
            delete temp;
            size--;
        }
    }

    void RemoveAll() {
        DNode<T>* curr = head;
        while (curr) {
            DNode<T>* next = curr->next;
            delete curr;
            curr = next;
        }
        head = tail = nullptr;
        size = 0;
        count = 0;
    }

    T GetAt(int index) const {
        if (index < 0 || index >= count) throw std::out_of_range("Index out of range");
        return getNodeAt(index)->data;
    }

    void SetAt(int index, const T& val) {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
        DNode<T>* node = getNodeAt(index);
        if (node) {
            node->data = val;
            if (index >= count) count = index + 1;
        }
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) SetSize(index + growValue);
        DNode<T>* node = getNodeAt(index);
        if (index >= count) count = index + 1;
        return node->data;
    }

    void Add(const T& val) {
        if (count >= size) SetSize(size == 0 ? growValue : size + growValue, growValue);
        DNode<T>* node = getNodeAt(count);
        if (node) {
            node->data = val;
            count++;
        }
    }

    void Append(const Array<T>& other) {
        for (int i = 0; i < other.count; i++) Add(other.GetAt(i));
    }

    Array& operator=(const Array& other) {
        if (this == &other) return *this;
        RemoveAll();
        growValue = other.growValue;
        SetSize(other.size, growValue);
        for (int i = 0; i < other.count; i++) SetAt(i, other.GetAt(i));
        count = other.count;
        return *this;
    }

    T* GetData() {
        if (count == 0) return nullptr;
        T* nativeArr = new T[count];
        DNode<T>* curr = head;
        for (int i = 0; i < count; i++) { nativeArr[i] = curr->data; curr = curr->next; }
        return nativeArr;
    }

    void InsertAt(int index, const T& val) {
        if (index < 0 || index > count) throw std::out_of_range("Invalid index");
        if (count >= size) SetSize(size == 0 ? growValue : size + growValue, growValue);
        for (int i = count; i > index; i--) {
            DNode<T>* curr = getNodeAt(i);
            DNode<T>* prev = getNodeAt(i - 1);
            if (curr && prev) curr->data = prev->data;
        }
        DNode<T>* target = getNodeAt(index);
        if (target) {
            target->data = val;
            count++;
        }
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= count) throw std::out_of_range("Invalid index");
        for (int i = index; i < count - 1; i++) {
            DNode<T>* curr = getNodeAt(i);
            DNode<T>* next = getNodeAt(i + 1);
            if (curr && next) curr->data = next->data;
        }
        DNode<T>* lastActive = getNodeAt(count - 1);
        if (lastActive) lastActive->data = T();
        count--;
    }
};