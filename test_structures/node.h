#pragma once

template<typename T>
struct DNode {
    T data;
    DNode* prev;
    DNode* next;

    DNode(const T& val) : data(val), prev(nullptr), next(nullptr) {}
};
